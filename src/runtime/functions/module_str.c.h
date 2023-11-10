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
    /* make sure both are valid types and if not throw an error */
    rt_Data_assert_type(data1, rt_DATA_TYPE_STR, "arg 0");
    rt_Data_assert_type(data2, rt_DATA_TYPE_STR, "arg 1");
}

#else
    #warning re-inclusion of module 'functions/module_str.c.h'
#endif
