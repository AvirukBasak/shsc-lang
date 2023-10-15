#ifndef FN_MODULE_IT_C_H
#define FN_MODULE_IT_C_H

#include "io.h"
#include "functions/module_it.h"
#include "runtime/data.h"
#include "runtime/data/string.h"
#include "runtime/data/list.h"
#include "runtime/data/map.h"
#include "runtime/VarTable.h"

RT_Data_t FN_it_len()
{
    RT_Data_t args = *RT_VarTable_getref("$");
    if (args.type != RT_DATA_TYPE_LST)
        io_errndie("FN_it_len: "
                   "received arguments list as type '%s'", RT_Data_typename(args));
    const RT_Data_t data = *RT_DataList_getref(args.data.lst, 0);
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
