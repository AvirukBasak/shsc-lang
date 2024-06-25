#ifndef RT_FN_MODULE_SYS_C_H
#define RT_FN_MODULE_SYS_C_H

#include <stdlib.h>

#include "platform.h"
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

#ifdef WIN32
    #include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
    #include <time.h>   // for nanosleep
#else
    #include <unistd.h> // for usleep
#endif

/* cross-platform sleep function */
void sleep_ms(int milliseconds){
#ifdef WIN32
    Sleep(milliseconds);
#elif _POSIX_C_SOURCE >= 199309L
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
#else
    if (milliseconds >= 1000)
    sleep(milliseconds / 1000);
    usleep((milliseconds % 1000) * 1000);
#endif
}

rt_Data_t rt_fn_sys_sleep()
{
    const rt_DataList_t *args = rt_fn_get_valid_args(1);
    const rt_Data_t data = *rt_DataList_getref(args, 0);
    rt_Data_assert_type(data, rt_DATA_TYPE_I64, "arg 0");
    sleep_ms(data.data.i64);
    return rt_Data_null();
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
