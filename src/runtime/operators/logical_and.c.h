#ifndef RT_OP_LOGICAL_AND_C_H
#define RT_OP_LOGICAL_AND_C_H

#include "errcodes.h"
#include "io.h"
#include "runtime/data/Data.h"
#include "runtime/operators.h"
#include "runtime/VarTable.h"

void rt_op_logical_and(const rt_Data_t *lhs, const rt_Data_t *rhs)
{
    if (!lhs) io_errndie("rt_op_logical_and:" ERR_MSG_NULLPTR " for `lhs`");
    if (!rhs) io_errndie("rt_op_logical_and:" ERR_MSG_NULLPTR " for `rhs`");

    bool cond1 = rt_Data_tobool(*lhs);

    /* short-circuiting */
    rt_VarTable_acc_setval(
        cond1 ? *rhs : *lhs
    );
}

void rt_op_logical_and_shortckted(const ast_Expression_t *expr)
{
    /* 1st deal with the left operand */
    RT_OP_SHORTCKTING_EVAL_OPERAND(expr->lhs_type, expr->lhs);
    bool cond1 = rt_Data_tobool(*RT_VTABLE_ACC);
    if (!cond1) {
        rt_VarTable_acc_setval(*RT_VTABLE_ACC);
        return;
    }

    /* if 1st operand is false return 1st operand
       else evaluate second operand and return it */
    RT_OP_SHORTCKTING_EVAL_OPERAND(expr->rhs_type, expr->rhs);
    rt_VarTable_acc_setval(*RT_VTABLE_ACC);
}

#else
    #warning re-inclusion of module 'runtime/operators/logical_and.c.h'
#endif
