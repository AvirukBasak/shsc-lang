#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "runtime/data/Data.h"

/**
 fn_<module>_FUNCTION
 for example, if the function descriptor is fn_DBG_REFCNT then
 the actual function will be dbg:refcnt i.e. refcnt of module dbg */
typedef enum {
    fn_ISNULL,        /* isnull */
    fn_TOSTR,         /* tostr */
    fn_TYPE,          /* type */

    fn_DBG_TYPENAME,  /* dbg:typename */
    fn_DBG_RTSIZE,    /* dbg:rtsize */
    fn_DBG_REFCNT,    /* dbg:refcnt */
    fn_DBG_FILENAME,  /* dbg:filename */
    fn_DBG_LINENO,    /* dbg:lineno */

    fn_IO_PRINT,      /* io:print */
    fn_IO_INPUT,      /* io:input */

    fn_IT_LEN,        /* it:len */

    fn_CHR_ISDIGIT,   /* chr:isdigit */
    fn_CHR_ISALPHA,   /* chr:isalpha */
    fn_CHR_ISALNUM,   /* chr:isalnum */

    fn_I64_MAXVAL,    /* i64:maxval */
    fn_I64_MINVAL,    /* i64:minval */

    fn_F64_MAXVAL,    /* f64:maxval */
    fn_F64_MINVAL,    /* f64:minval */

    fn_STR_APPEND,    /* str:append */
    fn_STR_INSERT,    /* str:insert */
    fn_STR_ERASE,     /* str:erase */
    fn_STR_CONCAT,    /* str:concat */
    fn_STR_REVERSE,   /* str:reverse */
    fn_STR_SUBSTR,    /* str:substr */
    fn_STR_FIND,      /* str:find */
    fn_STR_SPLIT,     /* str:split */
    fn_STR_TOI64,     /* str:toi64 */
    fn_STR_TOF64,     /* str:tof64 */

    fn_LST_APPEND,    /* lst:append */
    fn_LST_INSERT,    /* lst:insert */
    fn_LST_ERASE,     /* lst:erase */
    fn_LST_CONCAT,    /* lst:concat */
    fn_LST_REVERSE,   /* lst:reverse */
    fn_LST_SUBLST,    /* lst:sublst */
    fn_LST_FIND,      /* lst:find */
    fn_LST_JOIN,      /* lst:join */
    fn_LST_SORT,      /* lst:sort */

    fn_MAP_INSERT,    /* map:insert */
    fn_MAP_ERASE,     /* map:erase */
    fn_MAP_CONCAT,    /* map:concat */
    fn_MAP_FIND,      /* map:find */
    fn_MAP_KEYS,      /* map:keys */

    fn_UNDEFINED,
} fn_FunctionDescriptor_t;

fn_FunctionDescriptor_t fn_FunctionsList_getfn(const char *module, const char *fname);
rt_Data_t fn_FunctionsList_call(fn_FunctionDescriptor_t fn);

#endif
