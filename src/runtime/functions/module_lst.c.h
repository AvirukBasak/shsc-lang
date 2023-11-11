#ifndef RT_FN_MODULE_LST_C_H
#define RT_FN_MODULE_LST_C_H

#include "runtime/data/Data.h"
#include "runtime/data/DataList.h"
#include "runtime/functions.h"
#include "runtime/functions/module_lst.h"
#include "runtime/io.h"

rt_Data_t rt_fn_lst_equals()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(2);
    const rt_Data_t data1 = *rt_DataList_getref(args, 0);
    const rt_Data_t data2 = *rt_DataList_getref(args, 1);

    /* make sure both are valid types and if not throw an error */
    rt_Data_assert_type(data1, rt_DATA_TYPE_LST, "arg 0");
    rt_Data_assert_type(data2, rt_DATA_TYPE_LST, "arg 1");

    /* compare and return */
    return rt_Data_bul(rt_DataList_isequal(data1.data.lst, data2.data.lst));
}

rt_Data_t rt_fn_lst_compare()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(2);
    const rt_Data_t data1 = *rt_DataList_getref(args, 0);
    const rt_Data_t data2 = *rt_DataList_getref(args, 1);

    /* make sure both are valid types and if not throw an error */
    rt_Data_assert_type(data1, rt_DATA_TYPE_LST, "arg 0");
    rt_Data_assert_type(data2, rt_DATA_TYPE_LST, "arg 1");

    /* compare and return */
    return rt_Data_i64(rt_DataList_compare(data1.data.lst, data2.data.lst));
}

rt_Data_t rt_fn_lst_append()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(2);
    const rt_Data_t data1 = *rt_DataList_getref(args, 0);
    const rt_Data_t data2 = *rt_DataList_getref(args, 1);
    /* make sure both are valid types and if not throw an error */
    rt_Data_assert_type(data1, rt_DATA_TYPE_LST, "arg 0");
    /* append inplace */
    rt_DataList_append(data1.data.lst, data2);
    /* return the new string */
    return data1;
}

rt_Data_t rt_fn_lst_insert()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(3);
    const rt_Data_t data1 = *rt_DataList_getref(args, 0);
    const rt_Data_t data2 = *rt_DataList_getref(args, 1);
    const rt_Data_t data3 = *rt_DataList_getref(args, 2);
    /* make sure both are valid types and if not throw an error */
    rt_Data_assert_type(data1, rt_DATA_TYPE_LST, "arg 0");
    rt_Data_assert_type(data2, rt_DATA_TYPE_I64, "arg 1");
    /* insert inplace */
    rt_DataList_insert(data1.data.lst, data2.data.i64, data3);
    /* return the new string */
    return data1;
}

rt_Data_t rt_fn_lst_erase()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(3);
    const rt_Data_t data1 = *rt_DataList_getref(args, 0);
    const rt_Data_t data2 = *rt_DataList_getref(args, 1);
    const rt_Data_t data3 = *rt_DataList_getref(args, 2);
    /* make sure both are valid types and if not throw an error */
    rt_Data_assert_type(data1, rt_DATA_TYPE_LST, "arg 0");
    rt_Data_assert_type(data2, rt_DATA_TYPE_I64, "arg 1");
    rt_Data_assert_type(data3, rt_DATA_TYPE_I64, "arg 2");
    /* erase inplace */
    rt_DataList_erase(data1.data.lst, data2.data.i64, data3.data.i64);
    /* return the new string */
    return data1;
}

rt_Data_t rt_fn_lst_concat()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(2);
    const rt_Data_t data1 = *rt_DataList_getref(args, 0);
    const rt_Data_t data2 = *rt_DataList_getref(args, 1);
    /* make sure both are valid types and if not throw an error */
    rt_Data_assert_type(data1, rt_DATA_TYPE_LST, "arg 0");
    rt_Data_assert_type(data2, rt_DATA_TYPE_LST, "arg 1");
    /* concat by creating new list */
    rt_DataList_t *lst = rt_DataList_clone(data1.data.lst);
    rt_DataList_concat(lst, data2.data.lst);
    /* return the new string */
    return rt_Data_list(lst);
}

rt_Data_t rt_fn_lst_sublst()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(3);
    const rt_Data_t data1 = *rt_DataList_getref(args, 0);
    const rt_Data_t data2 = *rt_DataList_getref(args, 1);
    const rt_Data_t data3 = *rt_DataList_getref(args, 2);
    /* make sure both are valid types and if not throw an error */
    rt_Data_assert_type(data1, rt_DATA_TYPE_LST, "arg 0");
    rt_Data_assert_type(data2, rt_DATA_TYPE_I64, "arg 1");
    rt_Data_assert_type(data3, rt_DATA_TYPE_I64, "arg 2");
    /* create new list */
    rt_DataList_t *lst = rt_DataList_sublist(data1.data.lst, data2.data.i64, data3.data.i64);
    /* return the new string */
    return rt_Data_list(lst);
}

rt_Data_t rt_fn_lst_reverse()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(1);
    const rt_Data_t data1 = *rt_DataList_getref(args, 0);
    /* make sure both are valid types and if not throw an error */
    rt_Data_assert_type(data1, rt_DATA_TYPE_LST, "arg 0");
    /* reverse inplace */
    rt_DataList_reverse(data1.data.lst);
    /* return the new string */
    return data1;
}

rt_Data_t rt_fn_lst_find()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(2);
    const rt_Data_t data1 = *rt_DataList_getref(args, 0);
    const rt_Data_t data2 = *rt_DataList_getref(args, 1);
    /* make sure both are valid types and if not throw an error */
    rt_Data_assert_type(data1, rt_DATA_TYPE_LST, "arg 0");
    /* find and return */
    return rt_Data_i64(rt_DataList_find(data1.data.lst, data2));
}

rt_Data_t rt_fn_lst_join()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(2);
    const rt_Data_t data1 = *rt_DataList_getref(args, 0);
    const rt_Data_t data2 = *rt_DataList_getref(args, 1);
    /* make sure both are valid types and if not throw an error */
    rt_Data_assert_type(data1, rt_DATA_TYPE_LST, "arg 0");
    rt_Data_assert_type(data2, rt_DATA_TYPE_STR, "arg 1");
    /* join and return */
    return rt_Data_str(rt_DataList_join(data1.data.lst, data2.data.str));
}

rt_Data_t rt_fn_lst_sort()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(1);
    const rt_Data_t data1 = *rt_DataList_getref(args, 0);
    /* make sure both are valid types and if not throw an error */
    rt_Data_assert_type(data1, rt_DATA_TYPE_LST, "arg 0");
    /* sort inplace */
    rt_DataList_sort(data1.data.lst);
    /* return the new string */
    return data1;
}


#else
    #warning re-inclusion of module 'functions/module_lst.c.h'
#endif
