#include <inttypes.h>
#include <string.h>

#include "ast.h"
#include "ast/api.h"
#include "io.h"
#include "runtime/data/Data.h"
#include "runtime/eval.h"
#include "runtime/functions.h"
#include "runtime/io.h"

rt_fn_FunctionDescriptor_t rt_fn_FunctionsList_getfn(const char *module, const char *fname)
{
    /* if module matched but procedure didn't match, it should cascade down.
       this is done so that if all matches fail, you can still match the procedures
       that don't have a module name */
    if (!strcmp(module, "dbg")) {
        if (!strcmp(fname, "typename")) return rt_fn_DBG_TYPENAME;
        if (!strcmp(fname, "refcnt"))   return rt_fn_DBG_REFCNT;
        if (!strcmp(fname, "id"))       return rt_fn_DBG_ID;
        if (!strcmp(fname, "callproc")) return rt_fn_DBG_CALLPROC;
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
        case rt_fn_DBG_ID:        return rt_fn_dbg_id();
        case rt_fn_DBG_CALLPROC:  return rt_fn_dbg_callproc();

        case rt_fn_IO_PRINT:      return rt_fn_io_print();
        case rt_fn_IO_INPUT:      return rt_fn_io_input();

        case rt_fn_IT_LEN:        return rt_fn_it_len();

        case rt_fn_UNDEFINED:
            io_errndie("rt_fn_FunctionsList_call: undefined procedure for desc: '%d'", fn);
            break;
    }
    return rt_Data_null();
}

const rt_DataList_t *rt_fn_get_valid_args(int64_t min_expected_argc)
{
    rt_Data_t args = *rt_VarTable_getref(RT_VTABLE_ARGSVAR);
    if (args.type != rt_DATA_TYPE_LST)
        io_errndie("rt_fn_get_valid_args: "
                   "received arguments list as type '%s'", rt_Data_typename(args));
    if (rt_DataList_length(args.data.lst) < min_expected_argc)
        rt_throw(
            "expected at least %" PRId64 " arguments, received %" PRId64,
            min_expected_argc, rt_DataList_length(args.data.lst)
        );
    return args.data.lst;
}

rt_Data_t rt_fn_call_handler(
    const rt_Data_t context,
    const char *modulename,
    const char *procname,
    rt_DataList_t *args
) {
    ast_Identifier_t *module = ast_Identifier(strdup(modulename));
    ast_Identifier_t *proc = ast_Identifier(strdup(procname));

    /* get code as AST from user defined function */
    const ast_Statements_t *code = ast_util_ModuleAndProcTable_get_code(module, proc);

    /* get a descriptor to in-built function */
    const rt_fn_FunctionDescriptor_t fn = rt_fn_FunctionsList_getfn(
        modulename, procname);

    const char *currfile = NULL;

    /* update metadata to new module and function */
    if (code) {
        currfile = ast_util_ModuleAndProcTable_get_filename(module, proc);
    } else if (fn != rt_fn_UNDEFINED) {
        currfile = modulename;
    } else {
        rt_throw("undefined procedure '%s:%s'", modulename, procname);
    }

    rt_VarTable_push_proc(module, proc, currfile);

    /* store fn args into agrs location */
    rt_VarTable_create(RT_VTABLE_ARGSVAR, rt_Data_list(args), true, false);
    rt_VarTable_create(RT_VTABLE_CONTEXTVAR, context, true, false);

    if (code) {
        /* call user defined function */
        rt_ControlStatus_t ctrl = rt_eval_Statements(code);
        if (ctrl == rt_CTRL_BREAK)
            rt_throw("unexpected `break` statement outside loop");
        if (ctrl == rt_CTRL_CONTINUE)
            rt_throw("unexpected `continue` statement outside loop");
    } else {
        /* call in-built function */
        rt_VarTable_acc_setval(rt_fn_FunctionsList_call(fn));
    }

    ast_Identifier_destroy(&module);
    ast_Identifier_destroy(&proc);
    return rt_VarTable_pop_proc();
}
