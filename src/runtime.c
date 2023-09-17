#include <inttypes.h>
#include <stdbool.h>

#include "ast.h"
#include "ast/api.h"
#include "runtime.h"
#include "ast/nodes/enums.h"
#include "ast/util/procedure_map.h"
#include "functions.h"
#include "lexer.h"
#include "parser.yy.h"
#include "runtime/data.h"
#include "runtime/data/list.h"
#include "runtime/data/string.h"
#include "runtime/io.h"
#include "runtime/util/evalstack.h"

#include "runtime/data.c.h"
#include "runtime/io.c.h"
#include "runtime/util/evalstack.c.h"
#include "runtime/vartable.c.h"
#include "runtime/vartable.h"

#define RT_ACC_DATA (RT_VarTable_acc_get()->adr ? RT_VarTable_acc_get()->adr : &RT_VarTable_acc_get()->val)

const char *rt_currfile = NULL;
int rt_currline = 0;

const AST_Identifier_t *rt_current_module = NULL;
const AST_Identifier_t *rt_current_proc = NULL;

const AST_Identifier_t *rt_modulename_get(void);
const AST_Identifier_t *rt_procname_get(void);

void rt_AST_eval(const AST_Statements_t *code);
RT_Data_t *rt_Expression_eval(const AST_Expression_t *expr);
RT_Data_t *rt_Expression_eval_literal(const AST_Literal_t *lit);
RT_Data_t rt_Expression_eval_lst(const AST_CommaSepList_t *lst);

void rt_fncall_handler(const AST_Identifier_t *module, const AST_Identifier_t *proc);

void RT_exec(void)
{
    const AST_Identifier_t *module = AST_ProcedureMap_main();
    const AST_Identifier_t *proc = AST_ProcedureMap_main();
    const AST_Statements_t *code = AST_ProcedureMap_get_code(module, proc);
    rt_currfile = AST_ProcedureMap_get_filename(module, proc);
    RT_VarTable_push_proc(proc->identifier_name, NULL);
    rt_AST_eval(code);
}

const AST_Identifier_t *rt_modulename_get(void)
{
    if (!rt_current_module) rt_current_module = AST_ProcedureMap_main();
    return rt_current_module;
}

const AST_Identifier_t *rt_procname_get(void)
{
    if (!rt_current_module) rt_current_module = AST_ProcedureMap_main();
    return rt_current_module;
}

void rt_AST_eval(const AST_Statements_t *code)
{
    /* push first statements */
    RT_EvalStack_push((const RT_StackEntry_t) {
        .entry.node.code = code,
        .type = STACKENTRY_ASTNODE_TYPE_STATEMENTS
    });
    while (!RT_EvalStack_isempty()) {
        RT_StackEntry_t pop = RT_EvalStack_pop();
        switch (pop.type) {
            case STACKENTRY_ASTNODE_TYPE_STATEMENTS: {
                const AST_Statements_t *st = pop.entry.node.code;
                if (!st) break;
                /* push next entry to eval */
                RT_EvalStack_push((const RT_StackEntry_t) {
                    .entry.node.statement = st->statement,
                    .type = STACKENTRY_ASTNODE_TYPE_STATEMENT
                });
                /* push next entry */
                RT_EvalStack_push((const RT_StackEntry_t) {
                    .entry.node.code = st->statements,
                    .type = STACKENTRY_ASTNODE_TYPE_STATEMENTS
                });
                break;
            }
            case STACKENTRY_ASTNODE_TYPE_STATEMENT: {
                const AST_Statement_t *st = pop.entry.node.statement;
                if (!st) break;
                rt_currline = st->line_no;
                switch (st->type) {
                    case STATEMENT_TYPE_EMPTY: break;
                    case STATEMENT_TYPE_RETURN: {
                        RT_VarTable_acc_setval(*rt_Expression_eval(st->statement.expression));
                        break;
                    }
                    case STATEMENT_TYPE_ASSIGNMENT: {
                        RT_EvalStack_push((const RT_StackEntry_t) {
                            .entry.node.assignment = st->statement.assignment,
                            .type = STACKENTRY_ASTNODE_TYPE_ASSIGNMENT
                        });
                        break;
                    }
                    case STATEMENT_TYPE_COMPOUND: {
                        const AST_CompoundSt_t *cmpd = st->statement.compound_statement;
                        RT_VarTable_push_scope();
                        RT_EvalStack_push((const RT_StackEntry_t) {
                            .entry.node.code = NULL,
                            .type = STACKENTRY_TYPE_PROC_POP
                        });
                        switch (cmpd->type) {
                            case COMPOUNDST_TYPE_IF: {
                                RT_EvalStack_push((const RT_StackEntry_t) {
                                    .entry.node.if_block = cmpd->compound_statement.if_block,
                                    .type = STACKENTRY_ASTNODE_TYPE_IF_BLOCK
                                });
                                break;
                            }
                            case COMPOUNDST_TYPE_WHILE: {
                                RT_EvalStack_push((const RT_StackEntry_t) {
                                    .entry.node.while_block = cmpd->compound_statement.while_block,
                                    .type = STACKENTRY_ASTNODE_TYPE_WHILE_BLOCK
                                });
                                break;
                            }
                            case COMPOUNDST_TYPE_FOR: {
                                RT_EvalStack_push((const RT_StackEntry_t) {
                                    .entry.state.lp.for_block = cmpd->compound_statement.for_block,
                                    .entry.state.lp.i = 0,
                                    .entry.state.lp.is_running = false,
                                    .type = STACKENTRY_STATES_TYPE_LOOP
                                });
                                break;
                            }
                            case COMPOUNDST_TYPE_BLOCK: {
                                const AST_Statements_t *st = cmpd->compound_statement.block->statements;
                                RT_EvalStack_push((const RT_StackEntry_t) {
                                    .entry.node.code = st,
                                    .type = STACKENTRY_ASTNODE_TYPE_STATEMENTS
                                });
                                break;
                            }
                        }
                        break;
                    }
                }
                break;
            }
            case STACKENTRY_ASTNODE_TYPE_ASSIGNMENT: {
                switch (pop.entry.node.assignment->type) {
                    case ASSIGNMENT_TYPE_TOVOID: {
                        RT_VarTable_acc_setval(*rt_Expression_eval(
                            pop.entry.node.assignment->rhs));
                        break;
                    }
                    case ASSIGNMENT_TYPE_CREATE: {
                        const char *idf = pop.entry.node.assignment->lhs->identifier_name;
                        RT_VarTable_create(idf, *rt_Expression_eval(pop.entry.node.assignment->rhs));
                        break;
                    }
                }
                break;
            }
            case STACKENTRY_ASTNODE_TYPE_IF_BLOCK: {
                bool cond =  RT_Data_tobool(*rt_Expression_eval(pop.entry.node.if_block->condition));
                if (cond) {
                    RT_EvalStack_push((const RT_StackEntry_t) {
                        .entry.node.code = pop.entry.node.if_block->if_st,
                        .type = STACKENTRY_ASTNODE_TYPE_STATEMENTS
                    });
                    break;
                } else {
                    RT_EvalStack_push((const RT_StackEntry_t) {
                        .entry.node.else_block = pop.entry.node.if_block->else_block,
                        .type = STACKENTRY_ASTNODE_TYPE_ELSE_BLOCK
                    });
                    break;
                }
                break;
            }
            case STACKENTRY_ASTNODE_TYPE_ELSE_BLOCK: {
                /* takes care of [ else nwp statements end ] */
                if (!pop.entry.node.else_block->condition && !pop.entry.node.else_block->else_block) {
                    RT_EvalStack_push((const RT_StackEntry_t) {
                        .entry.node.code = pop.entry.node.else_block->else_if_st,
                        .type = STACKENTRY_ASTNODE_TYPE_STATEMENTS
                    });
                    break;
                }
                /* takes care of [ else if condition then nwp statements ] */
                bool cond = RT_Data_tobool(*rt_Expression_eval(pop.entry.node.else_block->condition));
                if (cond) {
                    /* if condition true, execute statements and don't go
                       any further down the else if ladder */
                    RT_EvalStack_push((const RT_StackEntry_t) {
                        .entry.node.code = pop.entry.node.else_block->else_if_st,
                        .type = STACKENTRY_ASTNODE_TYPE_STATEMENTS
                    });
                    break;
                } else {
                    /* if condition failed and no more else if blocks,
                       just break out and do nothing */
                    if (!pop.entry.node.else_block->else_block) break;
                    RT_EvalStack_push((const RT_StackEntry_t) {
                        .entry.node.else_block = pop.entry.node.else_block->else_block,
                        .type = STACKENTRY_ASTNODE_TYPE_ELSE_BLOCK
                    });
                    break;
                }
                break;
            }
            case STACKENTRY_ASTNODE_TYPE_WHILE_BLOCK: {
                bool cond = RT_Data_tobool(*rt_Expression_eval(pop.entry.node.while_block->condition));
                /* if condition is true, don't let the while be removed from stack
                   i.e. push it back into the stack coz it was popped earlier */
                if (cond) RT_EvalStack_push(pop);
                RT_EvalStack_push((const RT_StackEntry_t) {
                    .entry.node.code = pop.entry.node.while_block->statements,
                    .type = STACKENTRY_ASTNODE_TYPE_STATEMENTS
                });
                break;
            }
            case STACKENTRY_STATES_TYPE_LOOP: {
                switch (pop.entry.state.lp.for_block->type) {
                    case FORBLOCK_TYPE_RANGE: {
                        /* if loop not running, start it and eval range */
                        if (!pop.entry.state.lp.is_running) {
                            /* calculate start, end and by */
                            RT_Data_t start = *rt_Expression_eval(pop.entry.node.for_block->iterable.range.start);
                            if (start.type != RT_DATA_TYPE_I64)
                                rt_throw("for loop range start should be an i64");
                            RT_Data_t end = *rt_Expression_eval(pop.entry.node.for_block->iterable.range.end);
                            if (end.type != RT_DATA_TYPE_I64)
                                rt_throw("for loop range end should be an i64");
                            RT_Data_t by = RT_Data_null();
                            if (pop.entry.node.for_block->iterable.range.by) {
                                by = *rt_Expression_eval(pop.entry.node.for_block->iterable.range.by);
                                if (by.type != RT_DATA_TYPE_I64)
                                    rt_throw("for loop by value should be an i64");
                            }
                            const int64_t start_i = start.data.i64;
                            const int64_t end_i = end.data.i64;
                            const int64_t by_i = RT_Data_isnull(by) ?
                                (start_i <= end_i ? +1 : -1) : by.data.i64;
                            if (!by_i) rt_throw("for loop by value cannot be 0");
                            if ( (start_i < end_i && by_i < 0) || (start_i > end_i && by_i > 0) )
                                rt_throw("possible infinite for loop for by value '%" PRId64 "'", by_i);
                            /* add loop info to for loop stack entry */
                            pop.entry.state.lp.it.range.start = start_i;
                            pop.entry.state.lp.it.range.end = end_i;
                            pop.entry.state.lp.it.range.by = by_i;
                            /* set i to start of range */
                            pop.entry.state.lp.i = start_i;
                            /* start loop */
                            pop.entry.state.lp.is_running = true;
                        }
                        else pop.entry.state.lp.i += pop.entry.state.lp.it.range.by;
                        if ( (pop.entry.state.lp.it.range.by > 0 && pop.entry.state.lp.i >= pop.entry.state.lp.it.range.end)
                          || (pop.entry.state.lp.it.range.by < 0 && pop.entry.state.lp.i <= pop.entry.state.lp.it.range.end) ) {
                            pop.entry.state.lp.is_running = false;
                            break;
                        }
                        /* break, i.e. don't push new loop state */
                        if (!pop.entry.state.lp.is_running) break;
                        RT_VarTable_create(pop.entry.node.for_block->iter->identifier_name,
                            RT_Data_i64(pop.entry.state.lp.i));
                        /* push newly modified loop state */
                        RT_EvalStack_push(pop);
                        RT_EvalStack_push((const RT_StackEntry_t) {
                            .entry.node.code = pop.entry.node.for_block->statements,
                            .type = STACKENTRY_ASTNODE_TYPE_STATEMENTS
                        });
                        break;
                    }
                    case FORBLOCK_TYPE_LIST: {
                        /* if loop not running, start it and eval list */
                        if (!pop.entry.state.lp.is_running) {
                            /* convert expression to a data list */
                            RT_Data_t data = *rt_Expression_eval(pop.entry.node.for_block->iterable.lst);
                            switch (data.type) {
                                case RT_DATA_TYPE_LST:
                                    pop.entry.state.lp.it.iter.type = RT_DATA_TYPE_LST;
                                    pop.entry.state.lp.it.iter.lst = data.data.lst;
                                    break;
                                case RT_DATA_TYPE_STR:
                                    pop.entry.state.lp.it.iter.type = RT_DATA_TYPE_STR;
                                    pop.entry.state.lp.it.iter.str = data.data.str;
                                    break;
                                default:
                                    rt_throw("unsupported data type in iterator type for loop");
                            }
                            pop.entry.state.lp.i = 0;
                            pop.entry.state.lp.is_running = true;
                        }
                        else pop.entry.state.lp.i += 1;
                        /* calc lis length */
                        int64_t length = 0;
                        switch (pop.entry.state.lp.it.iter.type) {
                            case RT_DATA_TYPE_LST:
                                length = RT_DataList_length(pop.entry.state.lp.it.iter.lst);
                                break;
                            case RT_DATA_TYPE_STR:
                                length = RT_DataStr_length(pop.entry.state.lp.it.iter.str);
                                break;
                            default:
                                rt_throw("unsupported data type in iterator type for loop");
                        }
                        /* stop loop */
                        if (pop.entry.state.lp.i >= length) {
                            /* destroy list if rc is 0 */
                            switch (pop.entry.state.lp.it.iter.type) {
                                case RT_DATA_TYPE_LST:
                                    if (pop.entry.state.lp.it.iter.lst->rc == 0)
                                        RT_DataList_destroy(&pop.entry.state.lp.it.iter.lst);
                                    break;
                                case RT_DATA_TYPE_STR:
                                    if (pop.entry.state.lp.it.iter.str->rc == 0)
                                        RT_DataStr_destroy(&pop.entry.state.lp.it.iter.str);
                                    break;
                                default:
                                    rt_throw("unsupported data type in iterator type for loop");
                            }
                            pop.entry.state.lp.is_running = false;
                            break;
                        }
                        /* break, i.e. don't push new loop state */
                        if (!pop.entry.state.lp.is_running) break;
                        /* store current iteration element in loop variable */
                        switch (pop.entry.state.lp.it.iter.type) {
                            case RT_DATA_TYPE_LST: RT_VarTable_create(pop.entry.node.for_block->iter->identifier_name,
                                    *RT_DataList_getref(pop.entry.state.lp.it.iter.lst, pop.entry.state.lp.i)
                                );
                                break;
                            case RT_DATA_TYPE_STR: RT_VarTable_create(pop.entry.node.for_block->iter->identifier_name,
                                    RT_Data_chr(*RT_DataStr_getref(pop.entry.state.lp.it.iter.str, pop.entry.state.lp.i))
                                );
                                break;
                            default:
                                rt_throw("unsupported data type in iterator type for loop");
                        }
                        /* push newly modified loop state */
                        RT_EvalStack_push(pop);
                        RT_EvalStack_push((const RT_StackEntry_t) {
                            .entry.node.code = pop.entry.node.for_block->statements,
                            .type = STACKENTRY_ASTNODE_TYPE_STATEMENTS
                        });
                        break;
                    }
                }
                break;
            }
            case STACKENTRY_STATES_TYPE_EXPR: {
                rt_Expression_eval(pop.entry.node.expression);
                break;
            }
            case STACKENTRY_TYPE_SCOPE_POP: {
                RT_VarTable_pop_scope();
                break;
            }
            case STACKENTRY_ASTNODE_TYPE_COMMA_SEP_LIST:
            case STACKENTRY_ASTNODE_TYPE_LITERAL:
            case STACKENTRY_ASTNODE_TYPE_IDENTIFIER:
            case STACKENTRY_ASTNODE_TYPE_FOR_BLOCK:
            case STACKENTRY_ASTNODE_TYPE_EXPRESSION:
            case STACKENTRY_TYPE_ASTNODE:
            case STACKENTRY_TYPE_STATE:
            case STACKENTRY_TYPE_PROC_POP: break;
        }
    }
}

RT_Data_t *rt_Expression_eval(const AST_Expression_t *expr)
{
    /* take care pf fn calls and membership operations */
    switch (expr->op) {
        case LEXTOK_DOT:
            return RT_ACC_DATA;
        case LEXTOK_DCOLON:
            return RT_ACC_DATA;
        case TOKOP_FNCALL: {
            const AST_CommaSepList_t *ptr = expr->rhs.literal->data.lst;
            /* copy fn args into temporary location */
            for (int i = 0; i < RT_TMPVAR_CNT; ++i) {
                const char var[4] = { ((i % 100) / 10) + '0', (i % 10) + '0', '\0' };
                RT_Data_t data = ptr ? *rt_Expression_eval(ptr->expression) : RT_Data_null();
                RT_VarTable_modf(RT_VarTable_getref(var), data);
                ptr = ptr ? ptr->comma_list : ptr;
            }
            /* get fn code and push code to stack */
            rt_fncall_handler(rt_modulename_get(), expr->lhs.variable);
            return RT_ACC_DATA;
        }
        default: break;
    }

    /* handle lhs and evaluate it */
    RT_Data_t *lhs = NULL;
    switch (expr->lhs_type) {
        case EXPR_TYPE_EXPRESSION:
            lhs = rt_Expression_eval(expr->lhs.expr);
            break;
        case EXPR_TYPE_LITERAL:
            lhs = rt_Expression_eval_literal(expr->lhs.literal);
            break;
        case EXPR_TYPE_IDENTIFIER:
            lhs = RT_VarTable_getref(expr->lhs.variable->identifier_name);
            break;
        case EXPR_TYPE_NULL: break;
    }

    /* handle rhs and evaluate it */
    RT_Data_t *rhs = NULL;
    switch (expr->rhs_type) {
        case EXPR_TYPE_EXPRESSION:
            rhs = rt_Expression_eval(expr->rhs.expr);
            break;
        case EXPR_TYPE_LITERAL:
            rhs = rt_Expression_eval_literal(expr->rhs.literal);
            break;
        case EXPR_TYPE_IDENTIFIER:
            rhs = RT_VarTable_getref(expr->rhs.variable->identifier_name);
            break;
        case EXPR_TYPE_NULL: break;
    }

    /* handle condition and evaluate it */
    RT_Data_t *condition = NULL;
    switch (expr->condition_type) {
        case EXPR_TYPE_EXPRESSION:
            condition = rt_Expression_eval(expr->condition.expr);
            break;
        case EXPR_TYPE_LITERAL:
            condition = rt_Expression_eval_literal(expr->condition.literal);
            break;
        case EXPR_TYPE_IDENTIFIER:
            condition = RT_VarTable_getref(expr->condition.variable->identifier_name);
            break;
        case EXPR_TYPE_NULL: break;
    }

    switch (expr->op) {
        case LEXTOK_BANG:
        case LEXTOK_LOGICAL_UNEQUAL:
        case LEXTOK_PERCENT:
        case LEXTOK_MODULO_ASSIGN:
        case LEXTOK_AMPERSAND:
        case LEXTOK_LOGICAL_AND:
        case LEXTOK_LOGICAL_AND_ASSIGN:
        case LEXTOK_BITWISE_AND_ASSIGN:
        case LEXTOK_ASTERIX:
        case LEXTOK_EXPONENT:
        case LEXTOK_EXPONENT_ASSIGN:
        case LEXTOK_MULTIPLY_ASSIGN:
        case LEXTOK_PLUS:
        case LEXTOK_INCREMENT:
            rt_throw("unary increment operator is not yet supported");
            break;
        case LEXTOK_ADD_ASSIGN:
        case LEXTOK_MINUS:
        case LEXTOK_DECREMENT:
            rt_throw("unary decrement operator is not yet supported");
            break;
        case LEXTOK_SUBSTRACT_ASSIGN:
        case LEXTOK_DOT:
            rt_throw("memebership operator '.' is not yet supported");
            break;
        case LEXTOK_FSLASH:
        case LEXTOK_FLOOR_DIVIDE:
        case LEXTOK_FLOOR_DIVIDE_ASSIGN:
        case LEXTOK_DIVIDE_ASSIGN:
        case LEXTOK_DCOLON:
            rt_throw("memebership operator '::' is not yet supported");
            break;
        case LEXTOK_LBRACE_ANGULAR:
        case LEXTOK_BITWISE_LSHIFT:
        case LEXTOK_BITWISE_LSHIFT_ASSIGN:
        case LEXTOK_LOGICAL_LESSER_EQUAL:
        case LEXTOK_ASSIGN:
            RT_VarTable_acc_setval(*RT_VarTable_modf(lhs, *rhs));
            break;
        case LEXTOK_LOGICAL_EQUAL:
        case LEXTOK_RBRACE_ANGULAR:
        case LEXTOK_LOGICAL_GREATER_EQUAL:
        case LEXTOK_BITWISE_RSHIFT:
        case LEXTOK_BITWISE_RSHIFT_ASSIGN:
        case LEXTOK_ARITH_RSHIFT:
        case LEXTOK_ARITH_RSHIFT_ASSIGN:
        case LEXTOK_CARET:
        case LEXTOK_BITWISE_XOR_ASSIGN:
        case LEXTOK_PIPE:
        case LEXTOK_BITWISE_OR_ASSIGN:
        case LEXTOK_LOGICAL_OR:
        case LEXTOK_LOGICAL_OR_ASSIGN:
        case LEXTOK_TILDE:
        case TOKOP_FNCALL: break;
        case TOKOP_INDEXING:
        case TOKOP_TERNARY_COND:
        case TOKOP_FNARGS_INDEXING: break;
        case TOKOP_NOP: break;
        /* stuff that doesn't form an operation */
        default: io_errndie("rt_Expression_eval: invalid operation '%s'", lex_get_tokcode(expr->op));
    }
    return RT_ACC_DATA;
}

RT_Data_t *rt_Expression_eval_literal(const AST_Literal_t *lit)
{
    switch (lit->type) {
        case DATA_TYPE_BUL:
            RT_VarTable_acc_setval(RT_Data_bul(lit->data.bul));
            break;
        case DATA_TYPE_CHR:
            RT_VarTable_acc_setval(RT_Data_chr(lit->data.chr));
            break;
        case DATA_TYPE_I64:
            RT_VarTable_acc_setval(RT_Data_i64(lit->data.i64));
            break;
        case DATA_TYPE_F64:
            RT_VarTable_acc_setval(RT_Data_f64(lit->data.f64));
            break;
        case DATA_TYPE_STR:
            RT_VarTable_acc_setval(RT_Data_str(RT_DataStr_init(lit->data.str)));
            break;
        case DATA_TYPE_INTERP_STR:
            RT_VarTable_acc_setval(RT_Data_interp_str(RT_DataStr_init(lit->data.str)));
            break;
        case DATA_TYPE_LST:
            RT_VarTable_acc_setval(rt_Expression_eval_lst(lit->data.lst));
            break;
        case DATA_TYPE_ANY:
            /* void* must be explicitly casted */
            RT_VarTable_acc_setval(RT_Data_any((void*) lit->data.any));
            break;
    }
    return RT_ACC_DATA;
}

RT_Data_t rt_Expression_eval_lst(const AST_CommaSepList_t *lst)
{
    const AST_CommaSepList_t *ptr = lst;
    RT_DataList_t *new_list = RT_DataList_init();
    while (ptr) {
        RT_DataList_append(new_list, *rt_Expression_eval(ptr->expression));
        ptr = ptr->comma_list;
    }
    return RT_Data_list(new_list);
}

void rt_fncall_handler(const AST_Identifier_t *module, const AST_Identifier_t *proc)
{
    const AST_Statements_t *code = AST_ProcedureMap_get_code(module, proc);
    if (code) {
        RT_EvalStack_push((const RT_StackEntry_t) {
            .entry.node.code = code,
            .type = STACKENTRY_ASTNODE_TYPE_STATEMENTS
        });
        return;
    }
    FN_FunctionDescriptor_t fn = FN_FunctionsList_getfn(proc->identifier_name);
    if (fn == FN_UNDEFINED)
        rt_throw("undefined procedure '%s::%s'", module->identifier_name, proc->identifier_name);
    RT_VarTable_acc_setval(FN_FunctionsList_call(fn));
}
