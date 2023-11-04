#ifndef RT_OP_ASSIGN_C_H
#define RT_OP_ASSIGN_C_H

#include <stdbool.h>

#include "runtime/VarTable.h"
#include "runtime/data/Data.h"
#include "runtime/operators.h"

void rt_op_assign(rt_Data_t *lhs, const rt_Data_t *rhs, bool is_const, bool is_weak)
{
    /* never use setadr here coz it is not needed
       setadr is a rather unsafe fn as it causes the acc to
       strongly point to a variable that is weakly pointing to
       something else and as a result the acc ends up hiding the weak
       ref property of that variable */
    rt_VarTable_acc_setval(
        *rt_VarTable_modf(lhs, *rhs, is_const, is_weak));
}

#else
    #warning re-inclusion of module 'runtime/operators/assign.c.h'
#endif
