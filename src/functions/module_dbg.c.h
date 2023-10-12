#ifndef FN_MODULE_DBG_C_H
#define FN_MODULE_DBG_C_H

#include "runtime/data.h"
#include "runtime/data/string.h"
#include "runtime/data/list.h"
#include "runtime/data/map.h"
#include "runtime/vartable.h"

RT_Data_t FN_dbg_typename()
{
    const RT_Data_t data = *RT_VarTable_getref_tmpvar(0);
    const char *tname= RT_Data_typename(data);
    return RT_Data_str(RT_DataStr_init(tname));
}

RT_Data_t FN_dbg_refcnt()
{
    const RT_Data_t data = *RT_VarTable_getref_tmpvar(0);
    switch (data.type) {
        case RT_DATA_TYPE_STR:
        case RT_DATA_TYPE_INTERP_STR:
            return RT_Data_i64(data.data.str->rc);
        case RT_DATA_TYPE_LST:
            return RT_Data_i64(data.data.lst->rc);
        case RT_DATA_TYPE_MAP:
            return RT_Data_i64(data.data.mp->rc);
        default:
            return RT_Data_i64(1);
    }
    return RT_Data_i64(1);
}

#else
    #warning re-inclusion of module 'functions/module_dbg.c.h'
#endif
