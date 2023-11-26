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
    return rt_fn_call_handler(
        rt_Data_null(),
        "", "max",
        (rt_DataList_t*) args
    );
}

rt_Data_t rt_fn_f64_min()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(0);
    /* if no args are passed, return min double */
    if (rt_DataList_length(args) == 0)
        return rt_Data_f64(DBL_MIN);
    /* else return min of args */
    return rt_fn_call_handler(
        rt_Data_null(),
        "", "max",
        (rt_DataList_t*) args
    );
}

#else
    #warning re-inclusion of module 'functions/module_f64.c.h'
#endif
