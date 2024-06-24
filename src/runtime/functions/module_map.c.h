#ifndef RT_FN_MODULE_MAP_C_H
#define RT_FN_MODULE_MAP_C_H

#include <inttypes.h>

#include "runtime/data/Data.h"
#include "runtime/data/DataStr.h"
#include "runtime/data/DataList.h"
#include "runtime/data/DataMap.h"
#include "runtime/functions.h"
#include "runtime/functions/module_map.h"
#include "runtime/io.h"

rt_Data_t rt_fn_map_get()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(2);

    const rt_Data_t data = *rt_DataList_getref(args, 0);
    const rt_Data_t key = *rt_DataList_getref(args, 1);
    rt_Data_assert_type(data, rt_DATA_TYPE_MAP, "arg 0");
    rt_Data_assert_type(key, rt_DATA_TYPE_STR, "arg 1");

    char *key_str = rt_Data_tostr(key);
    const rt_Data_t *val = rt_DataMap_getref_errnull(data.data.mp, key_str);
    free(key_str);
    
    return val ? *val : rt_Data_null();
}

rt_Data_t rt_fn_map_set()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(3);

    const rt_Data_t data = *rt_DataList_getref(args, 0);
    const rt_Data_t key = *rt_DataList_getref(args, 1);
    const rt_Data_t val = *rt_DataList_getref(args, 2);
    rt_Data_assert_type(data, rt_DATA_TYPE_MAP, "arg 0");
    rt_Data_assert_type(key, rt_DATA_TYPE_STR, "arg 1");

    char *key_str = rt_Data_tostr(key);
    rt_DataMap_insert(data.data.mp, key_str, val);
    free(key_str);

    return data;
}

rt_Data_t rt_fn_map_erase()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(2);

    const rt_Data_t data = *rt_DataList_getref(args, 0);
    const rt_Data_t key = *rt_DataList_getref(args, 1);
    rt_Data_assert_type(data, rt_DATA_TYPE_MAP, "arg 0");
    rt_Data_assert_type(key, rt_DATA_TYPE_STR, "arg 1");

    char *key_str = rt_Data_tostr(key);
    rt_DataMap_del(data.data.mp, key_str);
    free(key_str);

    return data;
}

rt_Data_t rt_fn_map_concat()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(2);

    const rt_Data_t data1 = *rt_DataList_getref(args, 0);
    const rt_Data_t data2 = *rt_DataList_getref(args, 1);
    rt_Data_assert_type(data1, rt_DATA_TYPE_MAP, "arg 0");
    rt_Data_assert_type(data2, rt_DATA_TYPE_MAP, "arg 1");

    rt_DataMap_concat(data1.data.mp, data2.data.mp);

    return data1;
}

rt_Data_t rt_fn_map_find()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(2);

    const rt_Data_t data = *rt_DataList_getref(args, 0);
    const rt_Data_t key = *rt_DataList_getref(args, 1);
    rt_Data_assert_type(data, rt_DATA_TYPE_MAP, "arg 0");
    rt_Data_assert_type(key, rt_DATA_TYPE_STR, "arg 1");

    if (data.type != rt_DATA_TYPE_MAP)
        return rt_Data_null();

    char *key_str = rt_Data_tostr(key);
    rt_Data_t *val = rt_DataMap_getref(data.data.mp, key_str);
    free(key_str);

    return val ? rt_Data_bul(true) : rt_Data_bul(false);
}

rt_Data_t rt_fn_map_keys()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(1);

    const rt_Data_t data = *rt_DataList_getref(args, 0);
    rt_Data_assert_type(data, rt_DATA_TYPE_MAP, "arg 0");

    rt_DataList_t *keys = rt_DataList_init();
    for (
        rt_DataMap_iter_t it = rt_DataMap_begin(data.data.mp);
        it != rt_DataMap_end(data.data.mp);
        ++it
    ) {
        if (!rt_DataMap_exists(data.data.mp, it)) continue;
        const rt_DataMap_Entry_t *entry = rt_DataMap_get(data.data.mp, it);
        rt_DataStr_t *key = rt_DataStr_init(entry->key);
        rt_DataList_append(keys, rt_Data_str(key));
    }

    return rt_Data_list(keys);
}

rt_Data_t rt_fn_map_lockonce()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(2);

    const rt_Data_t data = *rt_DataList_getref(args, 0);
    rt_Data_assert_type(data, rt_DATA_TYPE_MAP, "arg 0");

    const rt_Data_t lockid = *rt_DataList_getref(args, 1);
    rt_Data_assert_type(lockid, rt_DATA_TYPE_I64, "arg 1");

    if (lockid.data.i64 == rt_DATA_MAP_LOCKID_RESERVED) {
        rt_throw("cannot use reserved lock id 0x%" PRIXPTR, (uintptr_t) rt_DATA_MAP_LOCKID_RESERVED);
    }

    rt_DataMap_lockonce(data.data.mp, lockid.data.i64);

    return data;
}

#else
    #warning re-inclusion of module 'functions/module_map.c.h'
#endif
