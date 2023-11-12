#ifndef RT_FN_MODULE_I64_C_H
#define RT_FN_MODULE_I64_C_H

#include <stdint.h>

#include "runtime/data/Data.h"
#include "runtime/data/DataList.h"
#include "runtime/functions.h"

rt_Data_t rt_fn_i64_max()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(0);
    /* if no args are passed, return max int64_t */
    if (rt_DataList_length(args) == 0)
        return rt_Data_i64(INT64_MAX);
    /* else return max of args */
    int64_t max = INT64_MIN;
    for (int i = 0; i < rt_DataList_length(args); ++i) {
        const rt_Data_t data = *rt_DataList_getref(args, i);
        int64_t val = 0;
        switch (data.type) {
            case rt_DATA_TYPE_BUL:
                val = data.data.bul ? 1 : 0;
                break;
            case rt_DATA_TYPE_CHR:
                val = data.data.chr;
                break;
            case rt_DATA_TYPE_I64:
                val = data.data.i64;
                break;
            case rt_DATA_TYPE_F64:
                val = data.data.f64;
                break;
            default:
                continue;
        }
        max = val > max ? val : max;
    }
    return rt_Data_i64(max);
}

rt_Data_t rt_fn_i64_min()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(0);
    /* if no args are passed, return min int64_t */
    if (rt_DataList_length(args) == 0)
        return rt_Data_i64(INT64_MIN);
    /* else return min of args */
    int64_t min = INT64_MAX;
    for (int i = 0; i < rt_DataList_length(args); ++i) {
        const rt_Data_t data = *rt_DataList_getref(args, i);
        int64_t val = 0;
        switch (data.type) {
            case rt_DATA_TYPE_BUL:
                val = data.data.bul ? 1 : 0;
                break;
            case rt_DATA_TYPE_CHR:
                val = data.data.chr;
                break;
            case rt_DATA_TYPE_I64:
                val = data.data.i64;
                break;
            case rt_DATA_TYPE_F64:
                val = data.data.f64;
                break;
            default:
                continue;
        }
        min = val < min ? val : min;
    }
    return rt_Data_i64(min);
}

#else
    #warning re-inclusion of module 'functions/module_i64.c.h'
#endif
