#ifndef RT_FUNCTIONS_H
#define RT_FUNCTIONS_H

#include "runtime/data/Data.h"
#include "runtime/functions/module_assert.h"
#include "runtime/functions/module_chr.h"
#include "runtime/functions/module_dbg.h"
#include "runtime/functions/module_f64.h"
#include "runtime/functions/module_i64.h"
#include "runtime/functions/module_io.h"
#include "runtime/functions/module_it.h"
#include "runtime/functions/module_lst.h"
#include "runtime/functions/module_map.h"
#include "runtime/functions/module_str.h"
#include "runtime/functions/nomodule.h"

/**
 rt_fn_<module>_FUNCTION
 for example, if the function descriptor is rt_fn_DBG_REFCNT then
 the actual function will be dbg:refcnt i.e. refcnt of module dbg */
typedef enum {
    rt_fn_ISNULL,        /* isnull */
    rt_fn_TOSTR,         /* tostr */
    rt_fn_TYPE,          /* type */
    rt_fn_CAST,          /* cast */
    rt_fn_MAX,           /* max */
    rt_fn_MIN,           /* min */

    rt_fn_ASSERT_TYPE,   /* assert:type */
    rt_fn_ASSERT_EQUALS, /* assert:equals */
    rt_fn_ASSERT_NOTNULL,/* assert:notnull */

    rt_fn_DBG_TYPENAME,  /* dbg:typename */
    rt_fn_DBG_RTSIZE,    /* dbg:rtsize */
    rt_fn_DBG_REFCNT,    /* dbg:refcnt */
    rt_fn_DBG_ID,        /* dbg:id */
    rt_fn_DBG_CALLPROC,  /* dbg:callproc */
    rt_fn_DBG_FILENAME,  /* dbg:filename */
    rt_fn_DBG_LINENO,    /* dbg:lineno */
    rt_fn_DBG_TIMENOW,   /* dbg:timenow */
    rt_fn_DBG_TIMENOW_PARAM, /* dbg:timenow_param */

    rt_fn_IO_PRINT,      /* io:print */
    rt_fn_IO_INPUT,      /* io:input */
    rt_fn_IO_FEXISTS,    /* io:exists */
    rt_fn_IO_FREAD,      /* io:fread */
    rt_fn_IO_FWRITE,     /* io:fwrite */
    rt_fn_IO_FAPPEND,    /* io:fappend */
    rt_fn_IO_LIBOPEN,    /* io:libopen */
    rt_fn_IO_LIBSYM,     /* io:libsym */

    rt_fn_IT_LEN,        /* it:len */
    rt_fn_IT_CLONE,      /* it:clone */

    rt_fn_CHR_ISDIGIT,   /* chr:isdigit */
    rt_fn_CHR_ISALPHA,   /* chr:isalpha */
    rt_fn_CHR_ISALNUM,   /* chr:isalnum */
    rt_fn_CHR_ISLOWER,   /* chr:islower */
    rt_fn_CHR_ISUPPER,   /* chr:isupper */
    rt_fn_CHR_ISSPACE,   /* chr:isspace */
    rt_fn_CHR_MAX,       /* chr:max */
    rt_fn_CHR_MIN,       /* chr:min */

    rt_fn_I64_MAX,       /* i64:max */
    rt_fn_I64_MIN,       /* i64:min */

    rt_fn_F64_MAX,       /* f64:max */
    rt_fn_F64_MIN,       /* f64:min */

    rt_fn_STR_EQUALS,    /* str:equals */
    rt_fn_STR_COMPARE,   /* str:compare */
    rt_fn_STR_TOLOWER,   /* str:tolower */
    rt_fn_STR_TOUPPER,   /* str:toupper */
    rt_fn_STR_APPEND,    /* str:append */
    rt_fn_STR_INSERT,    /* str:insert */
    rt_fn_STR_ERASE,     /* str:erase */
    rt_fn_STR_CONCAT,    /* str:concat */
    rt_fn_STR_REVERSE,   /* str:reverse */
    rt_fn_STR_SUBSTR,    /* str:substr */
    rt_fn_STR_FIND,      /* str:find */
    rt_fn_STR_SPLIT,     /* str:split */
    rt_fn_STR_TOI64,     /* str:toi64 */
    rt_fn_STR_TOF64,     /* str:tof64 */
    rt_fn_STR_SORT,      /* str:sort */

    rt_fn_LST_EQUALS,    /* lst:equals */
    rt_fn_LST_COMPARE,   /* lst:compare */
    rt_fn_LST_APPEND,    /* lst:append */
    rt_fn_LST_INSERT,    /* lst:insert */
    rt_fn_LST_ERASE,     /* lst:erase */
    rt_fn_LST_CONCAT,    /* lst:concat */
    rt_fn_LST_REVERSE,   /* lst:reverse */
    rt_fn_LST_SUBLIST,   /* lst:sublst */
    rt_fn_LST_FIND,      /* lst:find */
    rt_fn_LST_JOIN,      /* lst:join */
    rt_fn_LST_SORT,      /* lst:sort */

    rt_fn_MAP_SET,       /* map:set */
    rt_fn_MAP_GET,       /* map:get */
    rt_fn_MAP_ERASE,     /* map:erase */
    rt_fn_MAP_CONCAT,    /* map:concat */
    rt_fn_MAP_FIND,      /* map:find */
    rt_fn_MAP_KEYS,      /* map:keys */

    rt_fn_UNDEFINED,
} rt_fn_FunctionDescriptor_t;

rt_fn_FunctionDescriptor_t rt_fn_FunctionsList_getfn(const char *module, const char *fname);
rt_Data_t rt_fn_FunctionsList_call(rt_fn_FunctionDescriptor_t fn);

const rt_DataList_t *rt_fn_get_valid_args(int64_t min_expected_argc);

rt_Data_t rt_fn_call_handler(
    const rt_Data_t context,
    const char *module_name,
    const char *proc_name,
    rt_DataList_t *args
);

rt_Data_t rt_fn_lambda_call_handler(
    const rt_Data_t context,
    const rt_DataLambda_t lambda,
    rt_DataList_t *args
);

#endif
