#ifndef RT_OP_TOKOP_TERNARY_COND_C_H
#define RT_OP_TOKOP_TERNARY_COND_C_H

#include <stdbool.h>

#include "errcodes.h"
#include "io.h"
#include "runtime/data/Data.h"
#include "runtime/operators.h"
#include "runtime/VarTable.h"

void rt_op_ternary_cond(const rt_Data_t *lhs, const rt_Data_t *rhs, const rt_Data_t *condition)
{
    if (!lhs) io_errndie("rt_op_ternary_cond:" ERR_MSG_NULLPTR " for `lhs`");
    if (!rhs) io_errndie("rt_op_ternary_cond:" ERR_MSG_NULLPTR " for `rhs`");
    if (!condition) io_errndie("rt_op_ternary_cond:" ERR_MSG_NULLPTR " for `condition`");

    bool cond = rt_Data_tobool(*condition);
    if (cond) rt_VarTable_acc_setval(*lhs);
    else rt_VarTable_acc_setval(*rhs);
}

void rt_op_ternary_cond_shortckted(const ast_Expression_t *expr)
{
    /* 1st deal with the condition operand */
    RT_OP_SHORTCKTING_EVAL_OPERAND(expr->condition_type, expr->condition);
    bool cond = rt_Data_tobool(*RT_VTABLE_ACC);

    /* if condition is true evaluate and return lhs */
    if (cond) {
        RT_OP_SHORTCKTING_EVAL_OPERAND(expr->lhs_type, expr->lhs);
        rt_VarTable_acc_setval(*RT_VTABLE_ACC);
        return;
    }

    /* if condition is false evaluate and return rhs */
    RT_OP_SHORTCKTING_EVAL_OPERAND(expr->rhs_type, expr->rhs);
    rt_VarTable_acc_setval(*RT_VTABLE_ACC);
}

#else
    #warning re-inclusion of module 'runtime/operators/tokop_ternary_cond.c.h'
#endif
