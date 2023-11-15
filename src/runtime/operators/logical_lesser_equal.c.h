#ifndef RT_OP_LOGICAL_LESSER_EQUAL_C_H
#define RT_OP_LOGICAL_LESSER_EQUAL_C_H

#include "errcodes.h"
#include "io.h"
#include "runtime/data/Data.h"
#include "runtime/operators.h"
#include "runtime/VarTable.h"

void rt_op_logical_lesser_equal(const rt_Data_t *lhs, const rt_Data_t *rhs)
{
    if (!lhs) io_errndie("rt_op_logical_lesser_equal:" ERR_MSG_NULLPTR " for `lhs`");
    if (!rhs) io_errndie("rt_op_logical_lesser_equal:" ERR_MSG_NULLPTR " for `rhs`");

    rt_VarTable_acc_setval(
        rt_Data_bul(rt_Data_compare(*lhs, *rhs) <= 0)
    );
}

#else
    #warning re-inclusion of module 'runtime/operators/logical_lesser_equal.c.h'
#endif
