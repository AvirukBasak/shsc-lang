#ifndef RT_FN_MODULE_DBG_C_H
#define RT_FN_MODULE_DBG_C_H

#include <stdint.h>

#include "io.h"
#include "runtime/data/Data.h"
#include "runtime/data/DataStr.h"
#include "runtime/data/DataList.h"
#include "runtime/data/DataMap.h"
#include "runtime/functions.h"
#include "runtime/io.h"
#include "runtime/functions/module_dbg.h"
#include "runtime/VarTable.h"

rt_Data_t rt_fn_dbg_typename()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(1);
    const rt_Data_t data = *rt_DataList_getref(args, 0);
    const char *tname= rt_Data_typename(data);
    return rt_Data_str(rt_DataStr_init(tname));
}

rt_Data_t rt_fn_dbg_refcnt()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(1);
    const rt_Data_t data = *rt_DataList_getref(args, 0);
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
    const rt_DataList_t *args = rt_fn_get_valid_args(1);
    const rt_Data_t data = *rt_DataList_getref(args, 0);
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

rt_Data_t rt_fn_dbg_callproc()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(4);

    const rt_Data_t context = *rt_DataList_getref(args, 0);

    const rt_Data_t module = *rt_DataList_getref(args, 1);
    /* module should be string */
    if (module.type != rt_DATA_TYPE_STR) {
        rt_throw("invalid type for module name: '%s', expected 'str'", rt_Data_typename(module));
    }

    const rt_Data_t proc = *rt_DataList_getref(args, 2);
    /* proc should be string */
    if (proc.type != rt_DATA_TYPE_STR) {
        rt_throw("invalid type for procedure name: '%s', expected 'str'", rt_Data_typename(proc));
    }

    const rt_Data_t fnargs = *rt_DataList_getref(args, 3);
    /* fnargs should be list */
    if (fnargs.type != rt_DATA_TYPE_LST) {
        rt_throw("invalid type for procedure arguments: '%s', expected 'lst'", rt_Data_typename(fnargs));
    }

    /* call procedure */
    char *module_str = rt_Data_tostr(module);
    char *proc_str = rt_Data_tostr(proc);
    rt_Data_t ret = rt_fn_call_handler(
        context,
        module_str,
        proc_str,
        fnargs.data.lst
    );

    free(module_str);
    free(proc_str);
    return ret;
}

#else
    #warning re-inclusion of module 'functions/module_dbg.c.h'
#endif
