#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "runtime/data/Data.h"

/**
 FN_<module>_FUNCTION
 for example, if the function descriptor is FN_DBG_REFCNT then
 the actual function will be dbg:refcnt i.e. refcnt of module dbg */
typedef enum {
    FN_ISNULL,        /* isnull */
    FN_TOSTR,         /* tostr */
    FN_TYPE,          /* type */

    FN_DBG_TYPENAME,  /* dbg:typename */
    FN_DBG_RTSIZE,    /* dbg:rtsize */
    FN_DBG_REFCNT,    /* dbg:refcnt */
    FN_DBG_FILENAME,  /* dbg:filename */
    FN_DBG_LINENO,    /* dbg:lineno */

    FN_IO_PRINT,      /* io:print */
    FN_IO_INPUT,      /* io:input */

    FN_IT_LEN,        /* it:len */

    FN_CHR_ISDIGIT,   /* chr:isdigit */
    FN_CHR_ISALPHA,   /* chr:isalpha */
    FN_CHR_ISALNUM,   /* chr:isalnum */

    FN_I64_MAXVAL,    /* i64:maxval */
    FN_I64_MINVAL,    /* i64:minval */

    FN_F64_MAXVAL,    /* f64:maxval */
    FN_F64_MINVAL,    /* f64:minval */

    FN_STR_APPEND,    /* str:append */
    FN_STR_INSERT,    /* str:insert */
    FN_STR_ERASE,     /* str:erase */
    FN_STR_CONCAT,    /* str:concat */
    FN_STR_REVERSE,   /* str:reverse */
    FN_STR_SUBSTR,    /* str:substr */
    FN_STR_FIND,      /* str:find */
    FN_STR_SPLIT,     /* str:split */
    FN_STR_TOI64,     /* str:toi64 */
    FN_STR_TOF64,     /* str:tof64 */

    FN_LST_APPEND,    /* lst:append */
    FN_LST_INSERT,    /* lst:insert */
    FN_LST_ERASE,     /* lst:erase */
    FN_LST_CONCAT,    /* lst:concat */
    FN_LST_REVERSE,   /* lst:reverse */
    FN_LST_SUBLST,    /* lst:sublst */
    FN_LST_FIND,      /* lst:find */
    FN_LST_JOIN,      /* lst:join */
    FN_LST_SORT,      /* lst:sort */

    FN_MAP_INSERT,    /* map:insert */
    FN_MAP_ERASE,     /* map:erase */
    FN_MAP_CONCAT,    /* map:concat */
    FN_MAP_FIND,      /* map:find */
    FN_MAP_KEYS,      /* map:keys */

    FN_UNDEFINED,
} FN_FunctionDescriptor_t;

FN_FunctionDescriptor_t FN_FunctionsList_getfn(const char *module, const char *fname);
RT_Data_t FN_FunctionsList_call(FN_FunctionDescriptor_t fn);

#endif
