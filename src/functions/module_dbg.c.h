#ifndef FN_MODULE_DBG_C_H
#define FN_MODULE_DBG_C_H

#include "io.h"
#include "functions/module_dbg.h"
#include "runtime/data/Data.h"
#include "runtime/data/DataStr.h"
#include "runtime/data/DataList.h"
#include "runtime/data/DataMap.h"
#include "runtime/VarTable.h"

RT_Data_t FN_dbg_typename()
{
    RT_Data_t args = *RT_VarTable_getref("$");
    if (args.type != RT_DATA_TYPE_LST)
        io_errndie("FN_dbg_typename: "
                   "received arguments list as type '%s'", RT_Data_typename(args));
    const RT_Data_t data = *RT_DataList_getref(args.data.lst, 0);
    const char *tname= RT_Data_typename(data);
    return RT_Data_str(RT_DataStr_init(tname));
}

RT_Data_t FN_dbg_refcnt()
{
    RT_Data_t args = *RT_VarTable_getref("$");
    if (args.type != RT_DATA_TYPE_LST)
        io_errndie("FN_dbg_refcnt: "
                   "received arguments list as type '%s'", RT_Data_typename(args));
    const RT_Data_t data = *RT_DataList_getref(args.data.lst, 0);
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
