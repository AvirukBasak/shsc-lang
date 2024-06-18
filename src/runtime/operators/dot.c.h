#ifndef RT_OP_DOT_C_H
#define RT_OP_DOT_C_H

#include "runtime/data/Data.h"
#include "runtime/data/DataMap.h"
#include "runtime/io.h"
#include "runtime/operators.h"
#include "runtime/VarTable.h"

void rt_op_dot(const rt_Data_t *lhs, const rt_Data_t *rhs)
{
    if (lhs->type != rt_DATA_TYPE_MAP)
        rt_throw("cannot apply membership on type '%s'", rt_Data_typename(*lhs));
    switch (lhs->type) {
        case rt_DATA_TYPE_MAP: {
            if (!rhs)
                rt_throw("invalid member name");
            char *key = rt_Data_tostr(*rhs);
            rt_Data_t *ref = rt_DataMap_getref(lhs->data.mp, key);
            if (ref && ref->type == rt_DATA_TYPE_PROC) {
                /* setting context object via reference only coz lhs
                   is a ref to a map
                   rc is not increased here as it increases when
                   the fn is actually called when the context variable
                   is created in scope */
                ref->data.proc.context = lhs;
            } else if (ref && ref->type == rt_DATA_TYPE_LAMBDA) {
                /* setting context object via reference only coz lhs
                   is a ref to a map
                   rc is not increased here as it increases when
                   the fn is actually called when the context variable
                   is created in scope */
                ref->data.lambda.context = lhs;
            }
            rt_VarTable_acc_setadr(ref);
            free(key);
            break;
        }
        case rt_DATA_TYPE_BUL:
        case rt_DATA_TYPE_CHR:
        case rt_DATA_TYPE_I64:
        case rt_DATA_TYPE_F64:
        case rt_DATA_TYPE_INTERP_STR:
        case rt_DATA_TYPE_ANY:
        case rt_DATA_TYPE_STR:
        case rt_DATA_TYPE_LST:
        case rt_DATA_TYPE_PROC:
        case rt_DATA_TYPE_LAMBDA:
            rt_throw("cannot apply membership on type '%s'", rt_Data_typename(*lhs));
    }
}

#else
    #warning re-inclusion of module 'runtime/operators/dot.c.h'
#endif
