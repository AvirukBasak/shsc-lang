#ifndef RT_FN_MODULE_STR_C_H
#define RT_FN_MODULE_STR_C_H

#include "runtime/data/Data.h"
#include "runtime/data/DataList.h"
#include "runtime/data/DataStr.h"
#include "runtime/functions.h"
#include "runtime/functions/module_str.h"
#include "runtime/io.h"

rt_Data_t rt_fn_str_append()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(2);
    const rt_Data_t data1 = *rt_DataList_getref(args, 0);
    const rt_Data_t data2 = *rt_DataList_getref(args, 1);
    /* if data2 is chr, concat and return */
    if (data2.type == rt_DATA_TYPE_CHR) {
        rt_DataStr_t *str = rt_DataStr_clone(data1.data.str);
        rt_DataStr_append(str, data2.data.chr);
        return rt_Data_str(str);
    }
    /* make sure both are valid types and if not throw an error */
    rt_Data_assert_type(data1, rt_DATA_TYPE_STR, "arg 0");
    rt_Data_assert_type(data2, rt_DATA_TYPE_STR, "arg 1");
    /* get the string objects out of the data */
    const rt_DataStr_t *str1 = data1.data.str;
    const rt_DataStr_t *str2 = data2.data.str;
    /* clone 1st string and append */
    rt_DataStr_t *str3 = rt_DataStr_clone(str1);
    rt_DataStr_concat(str3, str2);
    /* return the new string */
    return rt_Data_str(str3);
}

rt_Data_t rt_fn_str_insert()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(3);
    const rt_Data_t data1 = *rt_DataList_getref(args, 0);
    const rt_Data_t data2 = *rt_DataList_getref(args, 1);
    const rt_Data_t data3 = *rt_DataList_getref(args, 2);
    /* make sure all are valid types and if not throw an error */
    rt_Data_assert_type(data1, rt_DATA_TYPE_STR, "arg 0");
    rt_Data_assert_type(data2, rt_DATA_TYPE_I64, "arg 1");
    /* if data3 is chr, insert and return */
    if (data3.type == rt_DATA_TYPE_CHR) {
        rt_DataStr_insert(data1.data.str, data2.data.i64, data3.data.chr);
        return data1;
    }
    rt_Data_assert_type(data3, rt_DATA_TYPE_STR, "arg 2");
    /* insert in place */
    rt_DataStr_insert_str(data1.data.str, data2.data.i64, data3.data.str);
    return data1;
}

rt_Data_t rt_fn_str_erase()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(3);
    const rt_Data_t data1 = *rt_DataList_getref(args, 0);
    const rt_Data_t data2 = *rt_DataList_getref(args, 1);
    const rt_Data_t data3 = *rt_DataList_getref(args, 2);
    /* make sure all are valid types and if not throw an error */
    rt_Data_assert_type(data1, rt_DATA_TYPE_STR, "arg 0");
    rt_Data_assert_type(data2, rt_DATA_TYPE_I64, "arg 1");
    rt_Data_assert_type(data3, rt_DATA_TYPE_I64, "arg 2");
    /* erase in place */
    rt_DataStr_erase(data1.data.str, data2.data.i64, data3.data.i64);
    return data1;
}

rt_Data_t rt_fn_str_concat()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(2);
    const rt_Data_t data1 = *rt_DataList_getref(args, 0);
    const rt_Data_t data2 = *rt_DataList_getref(args, 1);
    /* make sure both are valid types and if not throw an error */
    rt_Data_assert_type(data1, rt_DATA_TYPE_STR, "arg 0");
    rt_Data_assert_type(data2, rt_DATA_TYPE_STR, "arg 1");
    /* call append */
    return rt_fn_call_handler(
        rt_Data_null(),
        "str", "append",
        rt_DataList_from(data1, data2)
    );
}

rt_Data_t rt_fn_str_reverse()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(1);
    const rt_Data_t data1 = *rt_DataList_getref(args, 0);
    /* make sure both are valid types and if not throw an error */
    rt_Data_assert_type(data1, rt_DATA_TYPE_STR, "arg 0");
    /* reverse in place */
    rt_DataStr_reverse(data1.data.str);
    return data1;
}

rt_Data_t rt_fn_str_substr()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(3);
    const rt_Data_t data1 = *rt_DataList_getref(args, 0);
    const rt_Data_t data2 = *rt_DataList_getref(args, 1);
    const rt_Data_t data3 = *rt_DataList_getref(args, 2);
    /* make sure all are valid types and if not throw an error */
    rt_Data_assert_type(data1, rt_DATA_TYPE_STR, "arg 0");
    rt_Data_assert_type(data2, rt_DATA_TYPE_I64, "arg 1");
    rt_Data_assert_type(data3, rt_DATA_TYPE_I64, "arg 2");
    /* get substr */
    rt_DataStr_t *str2 = rt_DataStr_substr(
        data1.data.str,
        data2.data.i64,
        data3.data.i64
    );
    return rt_Data_str(str2);
}

rt_Data_t rt_fn_str_find()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(2);
    const rt_Data_t data1 = *rt_DataList_getref(args, 0);
    const rt_Data_t data2 = *rt_DataList_getref(args, 1);
    /* make sure both are valid types and if not throw an error */
    rt_Data_assert_type(data1, rt_DATA_TYPE_STR, "arg 0");
    /* if data2 is chr, find and return */
    if (data2.type == rt_DATA_TYPE_CHR) {
        const int64_t pos = rt_DataStr_find(data1.data.str, data2.data.chr);
        return rt_Data_i64(pos);
    }
    rt_Data_assert_type(data2, rt_DATA_TYPE_STR, "arg 1");
    /* find and return */
    int64_t pos = rt_DataStr_find_str(data1.data.str, data2.data.str);
    return rt_Data_i64(pos);
}

rt_Data_t rt_fn_str_split()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(2);
    const rt_Data_t data1 = *rt_DataList_getref(args, 0);
    const rt_Data_t data2 = *rt_DataList_getref(args, 1);
    /* make sure both are valid types and if not throw an error */
    rt_Data_assert_type(data1, rt_DATA_TYPE_STR, "arg 0");
    /* if data2 is chr, split and return */
    if (data2.type == rt_DATA_TYPE_CHR) {
        rt_DataList_t *list = rt_DataStr_split(data1.data.str, data2.data.chr);
        return rt_Data_list(list);
    }
    rt_Data_assert_type(data2, rt_DATA_TYPE_STR, "arg 1");
    /* split and return */
    rt_DataList_t *list = rt_DataStr_split_str(data1.data.str, data2.data.str);
    return rt_Data_list(list);
}

rt_Data_t rt_fn_str_toi64()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(1);
    const rt_Data_t data1 = *rt_DataList_getref(args, 0);
    /* make sure both are valid types and if not throw an error */
    rt_Data_assert_type(data1, rt_DATA_TYPE_STR, "arg 0");
    /* convert and return */
    return rt_DataStr_toi64(data1.data.str);
}

rt_Data_t rt_fn_str_tof64()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(1);
    const rt_Data_t data1 = *rt_DataList_getref(args, 0);
    /* make sure both are valid types and if not throw an error */
    rt_Data_assert_type(data1, rt_DATA_TYPE_STR, "arg 0");
    /* convert and return */
    return rt_DataStr_tof64(data1.data.str);
}

rt_Data_t rt_fn_str_sort()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(1);
    const rt_Data_t data1 = *rt_DataList_getref(args, 0);
    /* make sure both are valid types and if not throw an error */
    rt_Data_assert_type(data1, rt_DATA_TYPE_STR, "arg 0");
    /* sort in place */
    rt_DataStr_sort(data1.data.str);
    return data1;
}

#else
    #warning re-inclusion of module 'functions/module_str.c.h'
#endif
