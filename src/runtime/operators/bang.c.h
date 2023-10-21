#ifndef RT_OP_BANG_C_H
#define RT_OP_BANG_C_H

#include <stdbool.h>

#include "errcodes.h"
#include "io.h"
#include "runtime/data/Data.h"
#include "runtime/operators.h"
#include "runtime/VarTable.h"

void rt_op_bang(rt_Data_t *lhs, rt_Data_t *rhs)
{
    if (!lhs) io_errndie("rt_op_bang:" ERR_MSG_NULLPTR " for `lhs`");
    if (rhs) io_errndie("rt_op_bang: expected `rhs` to be null");

    bool cond = rt_Data_tobool(*lhs);
    rt_VarTable_acc_setval(rt_Data_bul(!cond));
}

#else
    #warning re-inclusion of module 'runtime/operators/bang.c.h'
#endif
