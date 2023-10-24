#ifndef RT_EVAL_IFBLOCK_C_H
#define RT_EVAL_IFBLOCK_C_H

#include <stdbool.h>

#include "ast.h"
#include "ast/api.h"
#include "runtime/data/Data.h"
#include "runtime/eval.h"
#include "runtime/VarTable.h"

rt_ControlStatus_t rt_eval_IfBlock(const ast_IfBlock_t *if_block)
{
    if (!if_block) return rt_CTRL_PASS;
    rt_eval_Expression(if_block->condition);
    bool cond = rt_Data_tobool(*RT_VTABLE_ACC);
    if (cond) return rt_eval_Statements_newscope(if_block->if_st);
    else return rt_eval_ElseBlock(if_block->else_block);
}

rt_ControlStatus_t rt_eval_ElseBlock(const ast_ElseBlock_t *else_block)
{
    if (!else_block) return rt_CTRL_PASS;
    /* takes care of [ else nwp statements end ] */
    if (!else_block->condition && !else_block->else_block) {
        return rt_eval_Statements_newscope(else_block->else_if_st);
    }
    /* takes care of [ else if condition then nwp statements ] */
    rt_eval_Expression(else_block->condition);
    bool cond = rt_Data_tobool(*RT_VTABLE_ACC);
    if (cond) return rt_eval_Statements_newscope(else_block->else_if_st);
    else return rt_eval_ElseBlock(else_block->else_block);
}

#else
    #warning re-inclusion of module 'runtime/eval/ifblock.c.h'
#endif
