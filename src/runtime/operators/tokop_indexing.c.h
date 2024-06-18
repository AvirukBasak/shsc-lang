#ifndef RT_OP_TOKOP_INDEXING_C_H
#define RT_OP_TOKOP_INDEXING_C_H

#include "runtime/data/Data.h"
#include "runtime/data/DataList.h"
#include "runtime/data/DataStr.h"
#include "runtime/data/DataMap.h"
#include "runtime/io.h"
#include "runtime/operators.h"
#include "runtime/VarTable.h"


void rt_op_indexing(const rt_Data_t *lhs, const rt_Data_t *rhs)
{
    if (lhs->type != rt_DATA_TYPE_LST && lhs->type != rt_DATA_TYPE_STR && lhs->type != rt_DATA_TYPE_MAP)
        rt_throw("cannot index type '%s'", rt_Data_typename(*lhs));
    switch (lhs->type) {
        case rt_DATA_TYPE_STR:
            if (!rhs || rhs->type != rt_DATA_TYPE_I64)
                rt_throw("index should evaluate to `i64` for type `str`");
            rt_VarTable_acc_setadr(
                rt_DataStr_getref(lhs->data.str, rhs->data.i64));
            break;
        case rt_DATA_TYPE_LST:
            if (!rhs || rhs->type != rt_DATA_TYPE_I64)
                rt_throw("index should evaluate to `i64` for type `lst`");
            rt_VarTable_acc_setadr(
                rt_DataList_getref(lhs->data.lst, rhs->data.i64));
            break;
        case rt_DATA_TYPE_MAP: {
            if (!rhs)
                rt_throw("index should evaluate to `str` for type `map`");
            char *key = rt_Data_tostr(*rhs);
            rt_VarTable_acc_setadr(
                rt_DataMap_getref(lhs->data.mp, key));
            free(key);
            break;
        }
        case rt_DATA_TYPE_BUL:
        case rt_DATA_TYPE_CHR:
        case rt_DATA_TYPE_I64:
        case rt_DATA_TYPE_F64:
        case rt_DATA_TYPE_INTERP_STR:
        case rt_DATA_TYPE_ANY:
        case rt_DATA_TYPE_PROC:
        case rt_DATA_TYPE_LAMBDA:
            rt_throw("cannot index type '%s'", rt_Data_typename(*lhs));
    }
}

#else
    #warning re-inclusion of module 'runtime/operators/tokop_indexing.c.h'
#endif
