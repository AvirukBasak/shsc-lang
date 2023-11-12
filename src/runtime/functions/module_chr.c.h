#ifndef RT_FN_MODULE_CHR_C_H
#define RT_FN_MODULE_CHR_C_H

#include <ctype.h>
#include <limits.h>

#include "runtime/data/Data.h"
#include "runtime/data/DataList.h"
#include "runtime/functions.h"
#include "runtime/functions/module_chr.h"

rt_Data_t rt_fn_chr_isdigit()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(1);
    const rt_Data_t data = *rt_DataList_getref(args, 0);
    rt_Data_assert_type(data, rt_DATA_TYPE_CHR, "arg 0");
    return rt_Data_bul(isdigit(data.data.chr));
}

rt_Data_t rt_fn_chr_isalpha()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(1);
    const rt_Data_t data = *rt_DataList_getref(args, 0);
    rt_Data_assert_type(data, rt_DATA_TYPE_CHR, "arg 0");
    return rt_Data_bul(isalpha(data.data.chr));
}

rt_Data_t rt_fn_chr_isalnum()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(1);
    const rt_Data_t data = *rt_DataList_getref(args, 0);
    rt_Data_assert_type(data, rt_DATA_TYPE_CHR, "arg 0");
    return rt_Data_bul(isalnum(data.data.chr));
}

rt_Data_t rt_fn_chr_islower()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(1);
    const rt_Data_t data = *rt_DataList_getref(args, 0);
    rt_Data_assert_type(data, rt_DATA_TYPE_CHR, "arg 0");
    return rt_Data_bul(islower(data.data.chr));
}

rt_Data_t rt_fn_chr_isupper()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(1);
    const rt_Data_t data = *rt_DataList_getref(args, 0);
    rt_Data_assert_type(data, rt_DATA_TYPE_CHR, "arg 0");
    return rt_Data_bul(isupper(data.data.chr));
}

rt_Data_t rt_fn_chr_isspace()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(1);
    const rt_Data_t data = *rt_DataList_getref(args, 0);
    rt_Data_assert_type(data, rt_DATA_TYPE_CHR, "arg 0");
    return rt_Data_bul(isspace(data.data.chr));
}

rt_Data_t rt_fn_chr_max()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(0);
    /* if no args are passed, return max char */
    if (rt_DataList_length(args) == 0)
        return rt_Data_chr(CHAR_MAX);
    /* else return max of args */
    char max = CHAR_MIN;
    for (int i = 0; i < rt_DataList_length(args); ++i) {
        const rt_Data_t data = *rt_DataList_getref(args, i);
        char val = 0;
        switch (data.type) {
            case rt_DATA_TYPE_BUL:
                val = data.data.bul ? 1 : 0;
                break;
            case rt_DATA_TYPE_CHR:
                val = data.data.chr;
                break;
            case rt_DATA_TYPE_I64:
                val = (char) data.data.i64;
                break;
            case rt_DATA_TYPE_F64:
                val = (char) data.data.f64;
                break;
            default:
                continue;
        }
        max = val > max ? val : max;
    }
    return rt_Data_chr(max);
}

rt_Data_t rt_fn_chr_min()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(0);
    /* if no args are passed, return min char */
    if (rt_DataList_length(args) == 0)
        return rt_Data_chr(CHAR_MIN);
    /* else return min of args */
    char min = CHAR_MAX;
    for (int i = 0; i < rt_DataList_length(args); ++i) {
        const rt_Data_t data = *rt_DataList_getref(args, i);
        char val = 0;
        switch (data.type) {
            case rt_DATA_TYPE_BUL:
                val = data.data.bul ? 1 : 0;
                break;
            case rt_DATA_TYPE_CHR:
                val = data.data.chr;
                break;
            case rt_DATA_TYPE_I64:
                val = (char) data.data.i64;
                break;
            case rt_DATA_TYPE_F64:
                val = (char) data.data.f64;
                break;
            default:
                continue;
        }
        min = val < min ? val : min;
    }
    return rt_Data_chr(min);
}

#else
    #warning re-inclusion of module 'functions/module_chr.c.h'
#endif
