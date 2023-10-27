#ifndef FN_NOMODULE_C_H
#define FN_NOMODULE_C_H

#include <stdlib.h>

#include "io.h"
#include "runtime/data/Data.h"
#include "runtime/data/DataStr.h"
#include "runtime/data/DataList.h"
#include "runtime/functions/nomodule.h"
#include "runtime/VarTable.h"

rt_Data_t rt_fn_isnull()
{
    rt_Data_t args = *rt_VarTable_getref(RT_VTABLE_ARGSVAR);
    if (args.type != rt_DATA_TYPE_LST)
        io_errndie("rt_fn_isnull: "
                   "received arguments list as type '%s'", rt_Data_typename(args));
    const rt_Data_t data = *rt_DataList_getref(args.data.lst, 0);
    return rt_Data_bul(rt_Data_isnull(data));
}

rt_Data_t rt_fn_tostr()
{
    rt_Data_t args = *rt_VarTable_getref(RT_VTABLE_ARGSVAR);
    if (args.type != rt_DATA_TYPE_LST)
        io_errndie("rt_fn_tostr: "
                   "received arguments list as type '%s'", rt_Data_typename(args));
    const rt_Data_t data = *rt_DataList_getref(args.data.lst, 0);
    char *strdata = rt_Data_tostr(data);
    const rt_Data_t retdata = rt_Data_str(rt_DataStr_init(strdata));
    free(strdata);
    strdata = NULL;
    return retdata;
}

rt_Data_t rt_fn_type()
{
    rt_Data_t args = *rt_VarTable_getref(RT_VTABLE_ARGSVAR);
    if (args.type != rt_DATA_TYPE_LST)
        io_errndie("rt_fn_type: "
                   "received arguments list as type '%s'", rt_Data_typename(args));
    const rt_Data_t data = *rt_DataList_getref(args.data.lst, 0);
    switch (data.type) {
        case rt_DATA_TYPE_BUL:
            return rt_VarTable_typeid_bul;
        case rt_DATA_TYPE_CHR:
            return rt_VarTable_typeid_chr;
        case rt_DATA_TYPE_I64:
            return rt_VarTable_typeid_i64;
        case rt_DATA_TYPE_F64:
            return rt_VarTable_typeid_f64;
        case rt_DATA_TYPE_STR:
            return rt_VarTable_typeid_str;
        case rt_DATA_TYPE_LST:
            return rt_VarTable_typeid_lst;
        case rt_DATA_TYPE_MAP:
            return rt_VarTable_typeid_map;
        case rt_DATA_TYPE_INTERP_STR:
        case rt_DATA_TYPE_PROC:
        case rt_DATA_TYPE_ANY:
            return rt_Data_isnull(data) ?
                rt_VarTable_rsv_null : rt_VarTable_typeid_any;
    }
    return rt_VarTable_typeid_any;
}

#else
    #warning re-inclusion of module 'functions/nomodule.c.h'
#endif