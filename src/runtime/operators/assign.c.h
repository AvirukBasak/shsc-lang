#ifndef RT_OP_ASSIGN_C_H
#define RT_OP_ASSIGN_C_H

#include "runtime/VarTable.h"
#include "runtime/data/Data.h"
#include "runtime/operators.h"

void rt_op_assign(rt_Data_t *lhs, const rt_Data_t *rhs)
{
    rt_VarTable_acc_setadr(
        rt_VarTable_modf(lhs, *rhs));
}

void rt_op_weak_assign(rt_Data_t *lhs, const rt_Data_t *rhs)
{
    rt_VarTable_acc_setadr(
        rt_VarTable_weak_modf(lhs, *rhs));
}

#else
    #warning re-inclusion of module 'runtime/operators/assign.c.h'
#endif
