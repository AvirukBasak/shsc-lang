#include <string.h>

#include "io.h"
#include "runtime/data/Data.h"
#include "runtime/functions.h"

rt_fn_FunctionDescriptor_t rt_fn_FunctionsList_getfn(const char *module, const char *fname)
{
    /* if module matched but procedure didn't match, it should cascade down.
       this is done so that if all matches fail, you can still match the procedures
       that don't have a module name */
    if (!strcmp(module, "dbg")) {
        if (!strcmp(fname, "typename")) return rt_fn_DBG_TYPENAME;
        if (!strcmp(fname, "refcnt"))   return rt_fn_DBG_REFCNT;
    }
    if (!strcmp(module, "io")) {
        if (!strcmp(fname, "print"))    return rt_fn_IO_PRINT;
        if (!strcmp(fname, "input"))    return rt_fn_IO_INPUT;
    }
    if (!strcmp(module, "it")) {
        if (!strcmp(fname, "len"))      return rt_fn_IT_LEN;
    }

    if (!strcmp(fname, "isnull"))       return rt_fn_ISNULL;
    if (!strcmp(fname, "tostr"))        return rt_fn_TOSTR;
    if (!strcmp(fname, "type"))         return rt_fn_TYPE;

    return rt_fn_UNDEFINED;
}

#include "runtime/functions/module_chr.c.h"
#include "runtime/functions/module_dbg.c.h"
#include "runtime/functions/module_f64.c.h"
#include "runtime/functions/module_i64.c.h"
#include "runtime/functions/module_io.c.h"
#include "runtime/functions/module_it.c.h"
#include "runtime/functions/module_lst.c.h"
#include "runtime/functions/module_map.c.h"
#include "runtime/functions/module_str.c.h"
#include "runtime/functions/nomodule.c.h"

rt_Data_t rt_fn_FunctionsList_call(rt_fn_FunctionDescriptor_t fn)
{
    switch (fn) {
        case rt_fn_ISNULL:        return rt_fn_isnull();
        case rt_fn_TOSTR:         return rt_fn_tostr();
        case rt_fn_TYPE:          return rt_fn_type();

        case rt_fn_DBG_TYPENAME:  return rt_fn_dbg_typename();
        case rt_fn_DBG_REFCNT:    return rt_fn_dbg_refcnt();

        case rt_fn_IO_PRINT:      return rt_fn_io_print();
        case rt_fn_IO_INPUT:      return rt_fn_io_input();

        case rt_fn_IT_LEN:        return rt_fn_it_len();

        case rt_fn_UNDEFINED:
            io_errndie("rt_fn_FunctionsList_call: undefined procedure for desc: '%d'", fn);
            break;
    }
    return rt_Data_null();
}
