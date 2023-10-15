#ifndef FN_NOMODULE_C_H
#define FN_NOMODULE_C_H

#include "io.h"
#include "functions/nomodule.h"
#include "runtime/data.h"
#include "runtime/data/string.h"
#include "runtime/data/list.h"
#include "runtime/VarTable.h"

RT_Data_t FN_isnull()
{
    RT_Data_t args = *RT_VarTable_getref("$");
    if (args.type != RT_DATA_TYPE_LST)
        io_errndie("FN_isnull: "
                   "received arguments list as type '%s'", RT_Data_typename(args));
    const RT_Data_t data = *RT_DataList_getref(args.data.lst, 0);
    return RT_Data_bul(RT_Data_isnull(data));
}

RT_Data_t FN_tostr()
{
    RT_Data_t args = *RT_VarTable_getref("$");
    if (args.type != RT_DATA_TYPE_LST)
        io_errndie("FN_tostr: "
                   "received arguments list as type '%s'", RT_Data_typename(args));
    const RT_Data_t data = *RT_DataList_getref(args.data.lst, 0);
    return RT_Data_str(RT_DataStr_init(RT_Data_tostr(data)));
}

RT_Data_t FN_type()
{
    RT_Data_t args = *RT_VarTable_getref("$");
    if (args.type != RT_DATA_TYPE_LST)
        io_errndie("FN_type: "
                   "received arguments list as type '%s'", RT_Data_typename(args));
    const RT_Data_t data = *RT_DataList_getref(args.data.lst, 0);
    switch (data.type) {
        case RT_DATA_TYPE_BUL:
            return RT_VarTable_typeid_bul;
        case RT_DATA_TYPE_CHR:
            return RT_VarTable_typeid_chr;
        case RT_DATA_TYPE_I64:
            return RT_VarTable_typeid_i64;
        case RT_DATA_TYPE_F64:
            return RT_VarTable_typeid_f64;
        case RT_DATA_TYPE_STR:
            return RT_VarTable_typeid_str;
        case RT_DATA_TYPE_INTERP_STR:
            return RT_VarTable_typeid_interp_str;
        case RT_DATA_TYPE_LST:
            return RT_VarTable_typeid_lst;
        case RT_DATA_TYPE_MAP:
            return RT_VarTable_typeid_map;
        case RT_DATA_TYPE_ANY:
            return RT_Data_isnull(data) ?
                RT_VarTable_rsv_null : RT_VarTable_typeid_any;
        case RT_DATA_TYPE_PROC:
            return RT_VarTable_typeid_proc;
    }
    return RT_VarTable_typeid_any;
}

#else
    #warning re-inclusion of module 'functions/nomodule.c.h'
#endif
