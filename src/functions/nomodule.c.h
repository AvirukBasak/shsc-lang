#ifndef FN_NOMODULE_C_H
#define FN_NOMODULE_C_H

#include "runtime/data.h"
#include "runtime/data/string.h"
#include "runtime/vartable.h"

RT_Data_t FN_isnull()
{
    const RT_Data_t data = *RT_VarTable_getref_tmpvar(0);
    return RT_Data_bul(RT_Data_isnull(data));
}

RT_Data_t FN_tostr()
{
    const RT_Data_t data = *RT_VarTable_getref_tmpvar(0);
    return RT_Data_str(RT_DataStr_init(RT_Data_tostr(data)));
}

RT_Data_t FN_type()
{
    const RT_Data_t data = *RT_VarTable_getref_tmpvar(0);
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
    }
    return RT_VarTable_typeid_any;
}

#else
    #warning re-inclusion of module 'functions/nomodule.c.h'
#endif
