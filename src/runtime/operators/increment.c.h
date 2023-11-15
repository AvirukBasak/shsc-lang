#ifndef RT_OP_INCREMENT_C_H
#define RT_OP_INCREMENT_C_H

#include "errcodes.h"
#include "io.h"
#include "runtime/VarTable.h"
#include "runtime/data/Data.h"
#include "runtime/operators.h"

void rt_op_increment(rt_Data_t *lhs, rt_Data_t *rhs)
{
    if (!lhs && !rhs)
        io_errndie("rt_op_increment:" ERR_MSG_NULLPTR " for `lhs` and `rhs`");
    const rt_Data_t one = rt_Data_i64(1);
    if (!lhs) {
        /* pre-increment mode */
        rt_op_plus(rhs, &one);
        rt_op_assign(rhs, RT_VTABLE_ACC, rhs->is_const, rhs->is_weak);
        return;
    } else if (!rhs) {
        /* post-increment mode */
        rt_Data_t ret;
        rt_op_assign(&ret, lhs, lhs->is_const, lhs->is_weak);
        rt_op_plus(lhs, &one);
        rt_op_assign(lhs, RT_VTABLE_ACC, lhs->is_const, lhs->is_weak);
        rt_VarTable_acc_setval(ret);
        rt_Data_destroy(&ret);
        return;
    }
}

#else
    #warning re-inclusion of module 'runtime/operators/increment.c.h'
#endif
