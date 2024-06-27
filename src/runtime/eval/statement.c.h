#ifndef RT_EVAL_STATEMENT_C_H
#define RT_EVAL_STATEMENT_C_H

#include "ast.h"
#include "ast/api.h"
#include "runtime/eval.h"
#include "runtime/VarTable.h"

rt_ControlStatus_t rt_eval_Statement(const ast_Statement_t *statement)
{
    if (!statement) return rt_CTRL_PASS;
    rt_VarTable_top_proc()->current_line = statement->line_no;
    switch (statement->type) {
        case STATEMENT_TYPE_EMPTY:
            rt_VarTable_acc_setval(rt_Data_null());
            return rt_CTRL_PASS;
        case STATEMENT_TYPE_BREAK:
            return rt_CTRL_BREAK;
        case STATEMENT_TYPE_CONTINUE:
            return rt_CTRL_CONTINUE;
        case STATEMENT_TYPE_RETURN:
            rt_eval_Expression(statement->statement.expression);
            return rt_CTRL_RETURN;
        case STATEMENT_TYPE_ASSIGNMENT:
            rt_eval_Assignment(statement->statement.assignment);
            break;
        case STATEMENT_TYPE_COMPOUND:
            return rt_eval_CompoundSt(statement->statement.compound_statement);
    }
    return rt_CTRL_PASS;
}

rt_ControlStatus_t rt_eval_CompoundSt(const ast_CompoundSt_t *compound_st)
{
    if (!compound_st) return rt_CTRL_PASS;
    switch (compound_st->type) {
        case COMPOUNDST_TYPE_IF:
            return rt_eval_IfBlock(compound_st->compound_statement.if_block);
        case COMPOUNDST_TYPE_WHILE:
            return rt_eval_WhileBlock(compound_st->compound_statement.while_block);
        case COMPOUNDST_TYPE_FOR:
            return rt_eval_ForBlock(compound_st->compound_statement.for_block);
        case COMPOUNDST_TYPE_BLOCK:
            return rt_eval_Statements_newscope(compound_st->compound_statement.block->statements);
    }
    return rt_CTRL_PASS;
}

#else
    #warning re-inclusion of module 'runtime/eval/statement.c.h'
#endif
