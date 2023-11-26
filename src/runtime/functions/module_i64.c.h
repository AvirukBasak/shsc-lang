#ifndef RT_FN_MODULE_I64_C_H
#define RT_FN_MODULE_I64_C_H

#include <stdint.h>

#include "runtime/data/Data.h"
#include "runtime/data/DataList.h"
#include "runtime/functions.h"
#include "runtime/functions/module_i64.h"

rt_Data_t rt_fn_i64_max()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(0);
    /* if no args are passed, return max int64_t */
    if (rt_DataList_length(args) == 0)
        return rt_Data_i64(INT64_MAX);
    /* else return max of args */
    return rt_fn_call_handler(
        rt_Data_null(),
        "", "max",
        (rt_DataList_t*) args
    );
}

rt_Data_t rt_fn_i64_min()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(0);
    /* if no args are passed, return min int64_t */
    if (rt_DataList_length(args) == 0)
        return rt_Data_i64(INT64_MIN);
    /* else return min of args */
    return rt_fn_call_handler(
        rt_Data_null(),
        "", "max",
        (rt_DataList_t*) args
    );
}

#else
    #warning re-inclusion of module 'functions/module_i64.c.h'
#endif
