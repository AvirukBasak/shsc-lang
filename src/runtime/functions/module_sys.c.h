#ifndef RT_FN_MODULE_SYS_C_H
#define RT_FN_MODULE_SYS_C_H

#include <stdlib.h>

#include "runtime.h"
#include "runtime/data/Data.h"
#include "runtime/data/DataList.h"
#include "runtime/data/DataStr.h"
#include "runtime/functions.h"
#include "runtime/functions/module_sys.h"
#include "runtime/io.h"

rt_Data_t rt_fn_sys_exit()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(0);
    rt_Data_t data = *rt_DataList_getref(args, 0);
    if (rt_Data_isnull(data)) data = rt_Data_i64(0);
    rt_Data_assert_type(data, rt_DATA_TYPE_I64, "arg 0");
    exit(data.data.i64);
    return data;
}

rt_Data_t rt_fn_sys_getenv()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(1);
    const rt_Data_t data = *rt_DataList_getref(args, 0);
    rt_Data_assert_type(data, rt_DATA_TYPE_STR, "arg 0");

    char *envvar = rt_Data_tostr(data);

    /* while getenv() returns char* the standard says it should neither be
     * modified nor freed. So we copy it to a const char* buffer */
    const char *env = getenv(envvar);

    free(envvar);
    if (!env) return rt_Data_null();
    return rt_Data_str(rt_DataStr_init(env));

}

rt_Data_t rt_fn_sys_platform()
{
    return rt_Data_str(rt_DataStr_init(rt_PLATFORM));
}

rt_Data_t rt_fn_sys_system()
{
    rt_throw("function 'system' is not yet implemented");

    const rt_DataList_t *args = rt_fn_get_valid_args(1);
    const rt_Data_t data = *rt_DataList_getref(args, 0);
    rt_Data_assert_type(data, rt_DATA_TYPE_STR, "arg 0");

    char *cmd = rt_Data_tostr(data);
    int ret = system(cmd);
    free(cmd);
    return rt_Data_i64(ret);

}

#else
    #warning re-incldue of module 'functions/module_sys.c.h'
#endif
