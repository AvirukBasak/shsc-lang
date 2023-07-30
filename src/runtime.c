#include "ast/api.h"
#include "runtime.h"
#include "runtime/util/evalstack.h"

#include "runtime/data.c.h"
#include "runtime/io.c.h"
#include "runtime/util/evalstack.c.h"
#include "runtime/vartable.c.h"

const char *rt_currfile = NULL;
int rt_currline = 0;

void RT_AST_eval(const AST_Statements_t *code);
RT_Data_t RT_Expression_eval(void);

void rt_exec(void)
{
    const AST_Identifier_t module = { .identifier_name = "main" };
    const AST_Identifier_t proc = { .identifier_name = "main" };
    const AST_Statements_t *code = AST_ProcedureMap_get_code(&module, &proc);
    rt_currfile = AST_ProcedureMap_get_filename(&module, &proc);
    RT_AST_eval(code);
}

void RT_AST_eval(const AST_Statements_t *code)
{
    RT_EvalStack_push((const RT_StackEntry_t) {
        .node.code = code,
        .type = STACKENTRY_TYPE_STATEMENTS
    });
    while (!RT_EvalStack_isempty()) {
        const RT_StackEntry_t pop = RT_EvalStack_pop();
        switch (RT_EvalStack_top().type) {
            case STACKENTRY_TYPE_STATEMENTS: {
                const AST_Statements_t *st = pop.node.code;
                if (!st) break;
                /* push next node to eval */
                RT_EvalStack_push((const RT_StackEntry_t) {
                    .node.statement = st->statement,
                    .type = STACKENTRY_TYPE_STATEMENT
                });
                /* push next node */
                RT_EvalStack_push((const RT_StackEntry_t) {
                    .node.code = st->statements,
                    .type = STACKENTRY_TYPE_STATEMENTS
                });
                break;
            }
            case STACKENTRY_TYPE_STATEMENT: {
                const AST_Statement_t *st = pop.node.statement;
                if (!st) break;
                rt_currline = st->line_no;
                switch (st->type) {
                    case STATEMENT_TYPE_EMPTY: break;
                    case STATEMENT_TYPE_RETURN: {
                        RT_EvalStack_push((const RT_StackEntry_t) {
                            .node.expression = st->statement.expression,
                            .type = STACKENTRY_TYPE_EXPRESSION
                        });
                        RT_VarTable_set("-", RT_Expression_eval());
                        break;
                    }
                    case STATEMENT_TYPE_ASSIGNMENT: {
                        RT_EvalStack_push((const RT_StackEntry_t) {
                            .node.assignment = st->statement.assignment,
                            .type = STACKENTRY_TYPE_ASSIGNMENT
                        });
                        break;
                    }
                    case STATEMENT_TYPE_COMPOUND: {
                        const AST_CompoundSt_t *cmpd = st->statement.compound_statement;
                        RT_VarTable_push_scope();
                        RT_EvalStack_push((const RT_StackEntry_t) { { NULL }, STACKENTRY_TYPE_SCOPE_POP });
                        switch (cmpd->type) {
                            case COMPOUNDST_TYPE_IF: {
                                RT_EvalStack_push((const RT_StackEntry_t) {
                                    .node.if_block = cmpd->compound_statement.if_block,
                                    .type = STACKENTRY_TYPE_IF_BLOCK
                                });
                                break;
                            }
                            case COMPOUNDST_TYPE_WHILE: {
                                RT_EvalStack_push((const RT_StackEntry_t) {
                                    .node.while_block = cmpd->compound_statement.while_block,
                                    .type = STACKENTRY_TYPE_WHILE_BLOCK
                                });
                                break;
                            }
                            case COMPOUNDST_TYPE_FOR: {
                                RT_EvalStack_push((const RT_StackEntry_t) {
                                    .node.for_block = cmpd->compound_statement.for_block,
                                    .type = STACKENTRY_TYPE_FOR_BLOCK
                                });
                                break;
                            }
                            case COMPOUNDST_TYPE_BLOCK: {
                                const AST_Statements_t *st = cmpd->compound_statement.block->statements;
                                RT_EvalStack_push((const RT_StackEntry_t) {
                                    .node.code = st,
                                    .type = STACKENTRY_TYPE_STATEMENTS
                                });
                                break;
                            }
                        }
                        break;
                    }
                }
                break;
            }
            case STACKENTRY_TYPE_ASSIGNMENT: {
                switch (pop.node.assignment->type) {
                    case ASSIGNMENT_TYPE_TOVOID: {
                        RT_EvalStack_push((const RT_StackEntry_t) {
                            .node.expression = pop.node.assignment->rhs,
                            .type = STACKENTRY_TYPE_EXPRESSION
                        });
                        RT_VarTable_set("-", RT_Expression_eval());
                        break;
                    }
                    case ASSIGNMENT_TYPE_CREATE: {
                        const char *idf = pop.node.assignment->lhs->identifier_name;
                        RT_EvalStack_push((const RT_StackEntry_t) {
                            .node.expression = pop.node.assignment->rhs,
                            .type = STACKENTRY_TYPE_EXPRESSION
                        });
                        RT_VarTable_new(idf, RT_Expression_eval());
                        break;
                    }
                }
                break;
            }
            case STACKENTRY_TYPE_IF_BLOCK: {
                break;
            }
            case STACKENTRY_TYPE_ELSE_IF_BLOCK: {
                break;
            }
            case STACKENTRY_TYPE_ELSE_IF_STATEMENT: {
                break;
            }
            case STACKENTRY_TYPE_WHILE_BLOCK: {
                RT_EvalStack_push((const RT_StackEntry_t) {
                    .node.expression = pop.node.while_block->condition,
                    .type = STACKENTRY_TYPE_EXPRESSION
                });
                bool cond =  RT_Data_tobool(RT_Expression_eval());
                /* if condition is true, don't let the while be removed from stack
                   i.e. push it back into the stack coz it was popped earlier */
                if (cond) RT_EvalStack_push((const RT_StackEntry_t) {
                    .node.while_block = pop.node.while_block,
                    .type = STACKENTRY_TYPE_WHILE_BLOCK
                });
                RT_EvalStack_push((const RT_StackEntry_t) {
                    .node.code = pop.node.while_block->statements,
                    .type = STACKENTRY_TYPE_STATEMENTS
                });
                break;
            }
            case STACKENTRY_TYPE_FOR_BLOCK: {
                break;
            }
            case STACKENTRY_TYPE_EXPRESSION: {
                RT_Expression_eval();
                break;
            }
            case STACKENTRY_TYPE_PROC_POP: {
                const AST_Statement_t *st = RT_VarTable_pop_proc();
                RT_EvalStack_push((const RT_StackEntry_t) {
                    .node.statement = st,
                    .type = STACKENTRY_TYPE_STATEMENT
                });
                break;
            }
            case STACKENTRY_TYPE_SCOPE_POP: {
                RT_VarTable_set("-", RT_VarTable_pop_scope());
                break;
            }
        }
    }
}

RT_Data_t RT_Expression_eval(void)
{
    if (RT_EvalStack_isempty()) {
        rt_throw("RT_Expression_eval: stack underflow");
        return RT_Data_null();
    } else if (RT_EvalStack_top().type != STACKENTRY_TYPE_EXPRESSION) {
        rt_throw("RT_Expression_eval: no expression at stack top");
        return RT_Data_null();
    }
    const AST_Expression_t *expr = RT_EvalStack_pop().node.expression;
    return RT_Data_null();
}
