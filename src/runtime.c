#include "ast/api.h"
#include "runtime.h"
#include "runtime/data.c.h"
#include "runtime/io.c.h"
#include "runtime/vartable.c.h"

const char *rt_currfile = NULL;
const int rt_currline = 0;

void RT_Eval_Statement(const AST_Statement_t *statement);

#define RT_Eval_Statements(code) do {     \
    const AST_Statements_t *st = code;    \
    while (st) {                          \
        RT_Eval_Statement(st->statement); \
        st = st->statements;              \
    }                                     \
} while(0);

void runtime_exec(void)
{
    /* const AST_Identifier_t module = { .identifier_name = "main" };
    const AST_Identifier_t proc = { .identifier_name = "main" };
    const AST_Statements_t *code = AST_ProcedureMap_get_code(&module, &proc);
    RT_Eval_Statements(code); */
}

/* void RT_Eval_Statement(const AST_Statement_t *statement)
{
    if (!statement) return;
    switch (statement->type) {
        case STATEMENT_TYPE_EMPTY:
            break;
        case STATEMENT_TYPE_RETURN: {
            RT_Data_t ret_data = RT_Eval_Expression(statement->expression);
            RT_VarTable_set("-", ret_data);
            break;
        }
        case STATEMENT_TYPE_ASSIGNMENT: {
            RT_Eval_Assignment(statement->assignment);
            break;
        }
        case STATEMENT_TYPE_COMPOUND: {
            const AST_CompoundSt_t *cmp_st = statement->compound_statement;
            case COMPOUNDST_TYPE_IF:    RT_Eval_IfBlock(cmp_st->if_block);
            case COMPOUNDST_TYPE_WHILE: RT_Eval_WhileBlock(cmp_st->while_block);
            case COMPOUNDST_TYPE_FOR:   RT_Eval_ForBlock(cmp_st->for_block);
            case COMPOUNDST_TYPE_BLOCK: RT_Eval_Block(cmp_st->block);
        }
    }
} */
