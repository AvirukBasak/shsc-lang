#ifndef FN_MODULE_IT_C_H
#define FN_MODULE_IT_C_H

#include "runtime/data.h"
#include "runtime/data/string.h"
#include "runtime/vartable.h"

RT_Data_t FN_it_len()
{
    const RT_Data_t data = *RT_VarTable_getref_tmpvar(0);
    switch (data.type) {
        case RT_DATA_TYPE_STR:
        case RT_DATA_TYPE_INTERP_STR:
            return RT_Data_i64(RT_DataStr_length(data.data.str));
        case RT_DATA_TYPE_LST:
            return RT_Data_i64(RT_DataList_length(data.data.lst));
        case RT_DATA_TYPE_MAP:
            return RT_Data_i64(RT_DataMap_length(data.data.mp));
        default:
            return RT_Data_i64(1);
    }
    return RT_Data_i64(0);
}

#else
    #warning re-inclusion of module 'functions/module_it.c.h'
#endif
