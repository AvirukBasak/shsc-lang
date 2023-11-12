#ifndef RT_FN_MODULE_F64_C_H
#define RT_FN_MODULE_F64_C_H

#include <float.h>

#include "runtime/data/Data.h"
#include "runtime/data/DataList.h"
#include "runtime/functions.h"
#include "runtime/functions/module_f64.h"

rt_Data_t rt_fn_f64_max()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(0);
    /* if no args are passed, return max double */
    if (rt_DataList_length(args) == 0)
        return rt_Data_f64(DBL_MAX);
    /* else return max of args */
    double max = DBL_MIN;
    for (int i = 0; i < rt_DataList_length(args); ++i) {
        const rt_Data_t data = *rt_DataList_getref(args, i);
        double val = 0;
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
    return rt_Data_f64(max);
}

rt_Data_t rt_fn_f64_min()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(0);
    /* if no args are passed, return min double */
    if (rt_DataList_length(args) == 0)
        return rt_Data_f64(DBL_MIN);
    /* else return min of args */
    double min = DBL_MAX;
    for (int i = 0; i < rt_DataList_length(args); ++i) {
        const rt_Data_t data = *rt_DataList_getref(args, i);
        double val = 0;
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
    return rt_Data_f64(min);
}

#else
    #warning re-inclusion of module 'functions/module_f64.c.h'
#endif
