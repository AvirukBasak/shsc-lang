#ifndef RT_FN_MODULE_DBG_C_H
#define RT_FN_MODULE_DBG_C_H

#include <stdint.h>

#include "io.h"
#include "runtime/data/Data.h"
#include "runtime/data/DataStr.h"
#include "runtime/data/DataList.h"
#include "runtime/data/DataMap.h"
#include "runtime/functions/module_dbg.h"
#include "runtime/VarTable.h"

rt_Data_t rt_fn_dbg_typename()
{
    rt_Data_t args = *rt_VarTable_getref(RT_VTABLE_ARGSVAR);
    if (args.type != rt_DATA_TYPE_LST)
        io_errndie("rt_fn_dbg_typename: "
                   "received arguments list as type '%s'", rt_Data_typename(args));
    const rt_Data_t data = *rt_DataList_getref(args.data.lst, 0);
    const char *tname= rt_Data_typename(data);
    return rt_Data_str(rt_DataStr_init(tname));
}

rt_Data_t rt_fn_dbg_refcnt()
{
    rt_Data_t args = *rt_VarTable_getref(RT_VTABLE_ARGSVAR);
    if (args.type != rt_DATA_TYPE_LST)
        io_errndie("rt_fn_dbg_refcnt: "
                   "received arguments list as type '%s'", rt_Data_typename(args));
    const rt_Data_t data = *rt_DataList_getref(args.data.lst, 0);
    switch (data.type) {
        case rt_DATA_TYPE_STR:
        case rt_DATA_TYPE_INTERP_STR:
            return rt_Data_i64(data.data.str->var->rc);
        case rt_DATA_TYPE_LST:
            return rt_Data_i64(data.data.lst->rc);
        case rt_DATA_TYPE_MAP:
            return rt_Data_i64(data.data.mp->rc);
        case rt_DATA_TYPE_BUL:
        case rt_DATA_TYPE_CHR:
        case rt_DATA_TYPE_I64:
        case rt_DATA_TYPE_F64:
        case rt_DATA_TYPE_ANY:
        case rt_DATA_TYPE_PROC:
            return rt_Data_i64(1);
    }
    return rt_Data_i64(1);
}

rt_Data_t rt_fn_dbg_id()
{
    rt_Data_t args = *rt_VarTable_getref(RT_VTABLE_ARGSVAR);
    if (args.type != rt_DATA_TYPE_LST)
        io_errndie("rt_fn_dbg_refcnt: "
                   "received arguments list as type '%s'", rt_Data_typename(args));
    const rt_Data_t data = *rt_DataList_getref(args.data.lst, 0);
    void *id_ptr = NULL;
    switch (data.type) {
        case rt_DATA_TYPE_STR:
        case rt_DATA_TYPE_INTERP_STR:
            id_ptr = (void*) data.data.str->var;
            break;
        case rt_DATA_TYPE_LST:
            id_ptr = (void*) data.data.lst;
            break;
        case rt_DATA_TYPE_MAP:
            id_ptr = (void*) data.data.mp;
            break;
        case rt_DATA_TYPE_BUL:
        case rt_DATA_TYPE_CHR:
        case rt_DATA_TYPE_I64:
        case rt_DATA_TYPE_F64:
        case rt_DATA_TYPE_ANY:
        case rt_DATA_TYPE_PROC:
            id_ptr = (void*) &data;
            break;
    }
    /* convert void* to hex pointer string */
    char id_str[64];
    sprintf(id_str, "%p", id_ptr);
    return rt_Data_str(rt_DataStr_init(id_str));
}

#else
    #warning re-inclusion of module 'functions/module_dbg.c.h'
#endif
