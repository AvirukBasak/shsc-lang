#ifndef RT_OP_TOKOP_TERNARY_COND_C_H
#define RT_OP_TOKOP_TERNARY_COND_C_H

#include <stdbool.h>

#include "errcodes.h"
#include "io.h"
#include "runtime/data/Data.h"
#include "runtime/operators.h"
#include "runtime/VarTable.h"

void rt_op_ternary_cond(rt_Data_t *lhs, rt_Data_t *rhs, rt_Data_t *condition)
{
    if (!lhs) io_errndie("rt_op_ternary_cond:" ERR_MSG_NULLPTR " for `lhs`");
    if (!rhs) io_errndie("rt_op_ternary_cond:" ERR_MSG_NULLPTR " for `rhs`");
    if (!condition) io_errndie("rt_op_ternary_cond:" ERR_MSG_NULLPTR " for `condition`");

    bool cond = rt_Data_tobool(*condition);
    if (cond) rt_VarTable_acc_setval(*lhs);
    else rt_VarTable_acc_setval(*rhs);
}

#else
    #warning re-inclusion of module 'runtime/operators/tokop_ternary_cond.c.h'
#endif
