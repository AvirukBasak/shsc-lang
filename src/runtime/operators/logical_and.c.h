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
    bool cond2 = rt_Data_tobool(*rhs);
    rt_VarTable_acc_setval(rt_Data_bul(cond1 && cond2));
}

#else
    #warning re-inclusion of module 'runtime/operators/logical_and.c.h'
#endif
