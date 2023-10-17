#ifndef OP_TOKOP_FNARGS_INDEXING_C_H
#define OP_TOKOP_FNARGS_INDEXING_C_H

#include "io.h"
#include "runtime/data/Data.h"
#include "runtime/data/DataList.h"
#include "runtime/io.h"
#include "runtime/operators.h"
#include "runtime/VarTable.h"

void rt_op_fnargs_indexing(rt_Data_t *lhs, rt_Data_t *rhs)
{
    if (!rhs || rhs->type != rt_DATA_TYPE_I64)
        rt_throw("argument index should evaluate to an `i64`");
    rt_Data_t args = *rt_VarTable_getref("$");
    if (args.type != rt_DATA_TYPE_LST)
        io_errndie("rt_eval_Expression: TOKOP_FNARGS_INDEXING: "
                   "received arguments list as type '%s'", rt_Data_typename(args));
    rt_VarTable_acc_setadr(
        rt_DataList_getref(args.data.lst, rhs->data.i64));
}

#else
    #warning re-inclusion of module 'operators/tokop_fnargs_indexing.c.h'
#endif
