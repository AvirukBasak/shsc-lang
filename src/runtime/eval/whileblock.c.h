#ifndef RT_EVAL_WHILEBLOCK_C_H
#define RT_EVAL_WHILEBLOCK_C_H

#include <stdbool.h>

#include "ast.h"
#include "ast/api.h"
#include "runtime/data/Data.h"
#include "runtime/eval.h"
#include "runtime/VarTable.h"

rt_ControlStatus_t rt_eval_WhileBlock(const ast_WhileBlock_t *while_block)
{
    if (!while_block) return rt_CTRL_PASS;
    rt_eval_Expression(while_block->condition);
    bool cond = rt_Data_tobool(*RT_VTABLE_ACC);
    while (cond) {
        rt_ControlStatus_t ctrl = rt_eval_Statements_newscope(while_block->statements);
        if (ctrl == rt_CTRL_PASS)
            /* do nothing in pass */;
        if (ctrl == rt_CTRL_RETURN)   return ctrl;
        if (ctrl == rt_CTRL_BREAK)    break;
        if (ctrl == rt_CTRL_CONTINUE) continue;
    }
    return rt_CTRL_PASS;
}

#else
    #warning re-inclusion of module 'runtime/eval/whileblock.c.h'
#endif
