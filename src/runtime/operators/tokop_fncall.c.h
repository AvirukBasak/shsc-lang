#ifndef OP_TOKOP_FNCALL_C_H
#define OP_TOKOP_FNCALL_C_H

#include "io.h"
#include "runtime/data/Data.h"
#include "runtime/data/DataList.h"
#include "runtime/eval.h"
#include "runtime/io.h"
#include "runtime/operators.h"
#include "runtime/VarTable.h"

void rt_op_fncall(rt_Data_t *lhs, rt_Data_t *rhs) {
    if (lhs->type != rt_DATA_TYPE_PROC)
        rt_throw("cannot make procedure call to type '%s'", rt_Data_typename(*lhs));
    /** temporary data variable for rhs */
    rt_Data_t rhs_;
    if (!rhs) {
        rhs_ = rt_Data_list(rt_DataList_init());
        rhs = &rhs_;
    }
    if (rhs->type != rt_DATA_TYPE_LST)
        rt_throw("cannot pass type '%s' as procedure argument", rt_Data_typename(*rhs));
    /* copy fn args into temporary location */
    rt_VarTable_modf(rt_VarTable_getref("$"), *rhs);
    /* get fn code and push code to stack */
    rt_call_function(lhs->data.proc.modulename, lhs->data.proc.procname);
    /* set no data to accumulator as data is already set by procedure called above
       return early to prevent accumulator being modified by some other code */
    return;
}

#else
    #warning re-inclusion of module 'operators/tokop_fncall.c.h'
#endif
