#ifndef RT_FN_MODULE_ASSERT_C_H
#define RT_FN_MODULE_ASSERT_C_H

#include <stdbool.h>

#include "runtime/data/Data.h"
#include "runtime/data/DataList.h"
#include "runtime/functions.h"
#include "runtime/functions/module_assert.h"
#include "runtime/io.h"

rt_Data_t rt_fn_assert_type()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(2);
    const rt_Data_t data = *rt_DataList_getref(args, 0);
    const rt_Data_t type = *rt_DataList_getref(args, 1);
    rt_Data_assert_type(type, rt_DATA_TYPE_I64, "arg 1");
    if (data.type != type.data.i64) {
        rt_throw(
            "assertion failed: argument type '%s', expected '%s'",
            rt_Data_typename(data),
            rt_Data_typename((rt_Data_t) { .type = type.data.i64 })
        );
    }
    return rt_Data_bul(true);
}

rt_Data_t rt_fn_assert_equals()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(2);
    const rt_Data_t data1 = *rt_DataList_getref(args, 0);
    const rt_Data_t data2 = *rt_DataList_getref(args, 1);
    if (!rt_Data_isequal(data1, data2))
        rt_throw("assertion failed: arguments are not equal");
    return rt_Data_bul(true);
}

rt_Data_t rt_fn_assert_notnull()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(1);
    const rt_Data_t data = *rt_DataList_getref(args, 0);
    if (rt_Data_isnull(data))
        rt_throw("assertion failed: argument is null");
    return rt_Data_bul(true);
}

#else
    #warning re-inclusion of module 'functions/module_assert.c.h'
#endif
