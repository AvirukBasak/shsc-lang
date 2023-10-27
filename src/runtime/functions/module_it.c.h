#ifndef RT_FN_MODULE_IT_C_H
#define RT_FN_MODULE_IT_C_H

#include "io.h"
#include "runtime/data/Data.h"
#include "runtime/data/DataStr.h"
#include "runtime/data/DataList.h"
#include "runtime/data/DataMap.h"
#include "runtime/functions/module_it.h"
#include "runtime/VarTable.h"

rt_Data_t rt_fn_it_len()
{
    rt_Data_t args = *rt_VarTable_getref(RT_VTABLE_ARGSVAR);
    if (args.type != rt_DATA_TYPE_LST)
        io_errndie("rt_fn_it_len: "
                   "received arguments list as type '%s'", rt_Data_typename(args));
    const rt_Data_t data = *rt_DataList_getref(args.data.lst, 0);
    switch (data.type) {
        case rt_DATA_TYPE_STR:
        case rt_DATA_TYPE_INTERP_STR:
            return rt_Data_i64(rt_DataStr_length(data.data.str));
        case rt_DATA_TYPE_LST:
            return rt_Data_i64(rt_DataList_length(data.data.lst));
        case rt_DATA_TYPE_MAP:
            return rt_Data_i64(rt_DataMap_length(data.data.mp));
        case rt_DATA_TYPE_BUL:
        case rt_DATA_TYPE_CHR:
        case rt_DATA_TYPE_I64:
        case rt_DATA_TYPE_F64:
        case rt_DATA_TYPE_ANY:
        case rt_DATA_TYPE_PROC:
            return rt_Data_i64(1);
    }
    return rt_Data_i64(0);
}

#else
    #warning re-inclusion of module 'functions/module_it.c.h'
#endif