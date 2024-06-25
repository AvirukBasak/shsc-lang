#ifndef FN_NOMODULE_C_H
#define FN_NOMODULE_C_H

#include <stdint.h>
#include <stdlib.h>

#include "runtime/data/Data.h"
#include "runtime/data/DataStr.h"
#include "runtime/data/DataList.h"
#include "runtime/functions.h"
#include "runtime/functions/nomodule.h"
#include "runtime/io.h"
#include "runtime/VarTable.h"

rt_Data_t rt_fn_isnull()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(0);
    const rt_Data_t data = *rt_DataList_getref(args, 0);
    return rt_Data_bul(rt_Data_isnull(data));
}

rt_Data_t rt_fn_tostr()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(1);
    const rt_Data_t data = *rt_DataList_getref(args, 0);
    char *strdata = rt_Data_tostr(data);
    const rt_Data_t retdata = rt_Data_str(rt_DataStr_init(strdata));
    free(strdata);
    strdata = NULL;
    return retdata;
}

rt_Data_t rt_fn_type()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(1);
    const rt_Data_t data = *rt_DataList_getref(args, 0);
    switch (data.type) {
        case rt_DATA_TYPE_BUL:
            return rt_Data_i64(rt_DATA_TYPE_BUL);
        case rt_DATA_TYPE_CHR:
            return rt_Data_i64(rt_DATA_TYPE_CHR);
        case rt_DATA_TYPE_I64:
            return rt_Data_i64(rt_DATA_TYPE_I64);
        case rt_DATA_TYPE_F64:
            return rt_Data_i64(rt_DATA_TYPE_F64);
        case rt_DATA_TYPE_STR:
            return rt_Data_i64(rt_DATA_TYPE_STR);
        case rt_DATA_TYPE_INTERP_STR:
            return rt_Data_i64(rt_DATA_TYPE_INTERP_STR);
        case rt_DATA_TYPE_LST:
            return rt_Data_i64(rt_DATA_TYPE_LST);
        case rt_DATA_TYPE_MAP:
            return rt_Data_i64(rt_DATA_TYPE_MAP);
        case rt_DATA_TYPE_PROC:
            return rt_Data_i64(rt_DATA_TYPE_PROC);
        case rt_DATA_TYPE_LAMBDA:
            return rt_Data_i64(rt_DATA_TYPE_LAMBDA);
        case rt_DATA_TYPE_LIBHANDLE:
            return rt_Data_i64(rt_DATA_TYPE_LIBHANDLE);
        case rt_DATA_TYPE_ANY:
            return rt_Data_isnull(data) ?
                rt_VarTable_rsv_null : rt_Data_i64(rt_DATA_TYPE_ANY);
    }
    return rt_Data_i64(rt_DATA_TYPE_ANY);
}

rt_Data_t rt_fn_cast()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(2);

    const rt_Data_t data = *rt_DataList_getref(args, 0);
    const rt_Data_t typeid = *rt_DataList_getref(args, 1);
    rt_Data_assert_type(typeid, rt_DATA_TYPE_I64, "arg 1");

    return rt_Data_cast(data, typeid.data.i64);
}

#define rt_fn_MIN_MAX_HANDLER(args, vname, compare_op)       \
    for (int i = 0; i < rt_DataList_length(args); ++i) {     \
        const rt_Data_t data = *rt_DataList_getref(args, i); \
        if (i == 0) {                                        \
            switch (data.type) {                             \
                case rt_DATA_TYPE_BUL:                       \
                    vname = rt_Data_bul(data.data.bul);      \
                    break;                                   \
                case rt_DATA_TYPE_CHR:                       \
                    vname = rt_Data_chr(data.data.chr);      \
                    break;                                   \
                case rt_DATA_TYPE_I64:                       \
                    vname = rt_Data_i64(data.data.i64);      \
                    break;                                   \
                case rt_DATA_TYPE_F64:                       \
                    vname = rt_Data_f64(data.data.f64);      \
                    break;                                   \
                default:                                     \
                    continue;                                \
            }                                                \
        }                                                    \
        vname = rt_Data_compare(data, vname) compare_op 0 ?  \
            data : vname;                                    \
    }

rt_Data_t rt_fn_max()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(0);
    /* if argument is a single list */
    if (rt_DataList_length(args) == 1
        && rt_DataList_getref(args, 0)->type == rt_DATA_TYPE_LST)
            args = rt_DataList_getref(args, 0)->data.lst;
    /* if no args are passed, return null */
    if (rt_DataList_length(args) == 0)
        return rt_Data_null();
    /* else return max of args */
    rt_Data_t max = rt_Data_null();
    rt_fn_MIN_MAX_HANDLER(args, max, >);
    return max;
}

rt_Data_t rt_fn_min()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(0);
    /* if argument is a single list */
    if (rt_DataList_length(args) == 1
        && rt_DataList_getref(args, 0)->type == rt_DATA_TYPE_LST)
            args = rt_DataList_getref(args, 0)->data.lst;
    /* if no args are passed, return null */
    if (rt_DataList_length(args) == 0)
        return rt_Data_null();
    rt_Data_t min = rt_Data_null();
    rt_fn_MIN_MAX_HANDLER(args, min, <);
    return min;
}

rt_Data_t rt_fn_errndie()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(1);

    const rt_Data_t data = *rt_DataList_getref(args, 0);
    rt_Data_assert_type(data, rt_DATA_TYPE_STR, "arg 1");

    rt_Data_t exitcode = *rt_DataList_getref(args, 1);
    if (rt_Data_isnull(exitcode)) exitcode = rt_Data_i64(1);
    rt_Data_assert_type(exitcode, rt_DATA_TYPE_I64, "arg 2");

    char *errmsg = rt_DataStr_tostr(data.data.str);
    rt_throw_exitcode((int) exitcode.data.i64, "errndie: %s", errmsg);
    free(errmsg);

    return rt_Data_null();
}

#else
    #warning re-inclusion of module 'functions/nomodule.c.h'
#endif
