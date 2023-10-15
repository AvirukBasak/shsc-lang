#include <string.h>

#include "functions.h"
#include "functions/module_chr.h"
#include "functions/module_dbg.h"
#include "functions/module_f64.h"
#include "functions/module_i64.h"
#include "functions/module_io.h"
#include "functions/module_it.h"
#include "functions/module_lst.h"
#include "functions/module_map.h"
#include "functions/module_str.h"
#include "functions/nomodule.h"
#include "io.h"
#include "runtime/data/Data.h"

fn_FunctionDescriptor_t fn_FunctionsList_getfn(const char *module, const char *fname)
{
    /* if module matched but procedure didn't match, it should cascade down.
       this is done so that if all matches fail, you can still match the procedures
       that don't have a module name */
    if (!strcmp(module, "dbg")) {
        if (!strcmp(fname, "typename")) return fn_DBG_TYPENAME;
        if (!strcmp(fname, "refcnt"))   return fn_DBG_REFCNT;
    }
    if (!strcmp(module, "io")) {
        if (!strcmp(fname, "print"))    return fn_IO_PRINT;
        if (!strcmp(fname, "input"))    return fn_IO_INPUT;
    }
    if (!strcmp(module, "it")) {
        if (!strcmp(fname, "len"))      return fn_IT_LEN;
    }

    if (!strcmp(fname, "isnull"))       return fn_ISNULL;
    if (!strcmp(fname, "tostr"))        return fn_TOSTR;
    if (!strcmp(fname, "type"))         return fn_TYPE;

    return fn_UNDEFINED;
}

#include "functions/module_chr.c.h"
#include "functions/module_dbg.c.h"
#include "functions/module_f64.c.h"
#include "functions/module_i64.c.h"
#include "functions/module_io.c.h"
#include "functions/module_it.c.h"
#include "functions/module_lst.c.h"
#include "functions/module_map.c.h"
#include "functions/module_str.c.h"
#include "functions/nomodule.c.h"

rt_Data_t fn_FunctionsList_call(fn_FunctionDescriptor_t fn)
{
    switch (fn) {
        case fn_ISNULL:        return fn_isnull();
        case fn_TOSTR:         return fn_tostr();
        case fn_TYPE:          return fn_type();

        case fn_DBG_TYPENAME:  return fn_dbg_typename();
        case fn_DBG_REFCNT:    return fn_dbg_refcnt();

        case fn_IO_PRINT:      return fn_io_print();
        case fn_IO_INPUT:      return fn_io_input();

        case fn_IT_LEN:        return fn_it_len();

        case fn_UNDEFINED:
            io_errndie("fn_FunctionsList_call: undefined procedure for desc: '%d'", fn);
            break;
    }
    return rt_Data_null();
}
