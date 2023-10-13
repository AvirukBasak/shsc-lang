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
#include "runtime/data.h"

FN_FunctionDescriptor_t FN_FunctionsList_getfn(const char *module, const char *fname)
{
    /* if module matched but procedure didn't match, it should cascade down.
       this is done so that if all matches fail, you can still match the procedures
       that don't have a module name */
    if (!strcmp(module, "dbg")) {
        if (!strcmp(fname, "typename")) return FN_DBG_TYPENAME;
        if (!strcmp(fname, "refcnt"))   return FN_DBG_REFCNT;
    }
    if (!strcmp(module, "io")) {
        if (!strcmp(fname, "print"))    return FN_IO_PRINT;
        if (!strcmp(fname, "input"))    return FN_IO_INPUT;
    }
    if (!strcmp(module, "it")) {
        if (!strcmp(fname, "len"))      return FN_IT_LEN;
    }

    if (!strcmp(fname, "isnull"))       return FN_ISNULL;
    if (!strcmp(fname, "tostr"))        return FN_TOSTR;
    if (!strcmp(fname, "type"))         return FN_TYPE;

    return FN_UNDEFINED;
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

RT_Data_t FN_FunctionsList_call(FN_FunctionDescriptor_t fn)
{
    switch (fn) {
        case FN_ISNULL:        return FN_isnull();
        case FN_TOSTR:         return FN_tostr();
        case FN_TYPE:          return FN_type();

        case FN_DBG_TYPENAME:  return FN_dbg_typename();
        case FN_DBG_REFCNT:    return FN_dbg_refcnt();

        case FN_IO_PRINT:      return FN_io_print();
        case FN_IO_INPUT:      return FN_io_input();

        case FN_IT_LEN:        return FN_it_len();

        case FN_UNDEFINED:
            io_errndie("FN_FunctionsList_call: undefined procedure for desc: '%d'", fn);
            break;
    }
    return RT_Data_null();
}
