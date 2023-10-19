#ifndef RT_OP_TOKOP_NOP_C_H
#define RT_OP_TOKOP_NOP_C_H

#include "runtime/VarTable.h"
#include "runtime/data/Data.h"
#include "runtime/operators.h"

void rt_op_nop(rt_Data_t *lhs)
{
    rt_VarTable_acc_setval(*lhs);
}

#else
    #warning re-inclusion of module 'runtime/operators/tokop_nop.c.h'
#endif
