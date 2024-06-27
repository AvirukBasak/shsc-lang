#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "ast.h"
#include "ast/api.h"
#include "io.h"
#include "runtime/data/Data.h"
#include "runtime/data/DataList.h"
#include "runtime/eval.h"
#include "runtime/functions.h"
#include "runtime/io.h"

rt_fn_FunctionDescriptor_t rt_fn_FunctionsList_getfn(const char *module, const char *fname)
{
    /* if module matched but procedure didn't match, it should cascade down.
       this is done so that if all matches fail, you can still match the procedures
       that don't have a module name */
    if (!strcmp(module, "sys")) {
        if (!strcmp(fname, "exit"))     return rt_fn_SYS_EXIT;
        if (!strcmp(fname, "sleep"))    return rt_fn_SYS_SLEEP;
        if (!strcmp(fname, "getenv"))   return rt_fn_SYS_GETENV;
        if (!strcmp(fname, "platform")) return rt_fn_SYS_PLATFORM;
        if (!strcmp(fname, "system"))   return rt_fn_SYS_SYSTEM;
    }
    if (!strcmp(module, "assert")) {
        if (!strcmp(fname, "type"))     return rt_fn_ASSERT_TYPE;
        if (!strcmp(fname, "equals"))   return rt_fn_ASSERT_EQUALS;
        if (!strcmp(fname, "notnull"))  return rt_fn_ASSERT_NOTNULL;
    }
    if (!strcmp(module, "dbg")) {
        if (!strcmp(fname, "typename")) return rt_fn_DBG_TYPENAME;
        if (!strcmp(fname, "rtsize"))   return rt_fn_DBG_RTSIZE;
        if (!strcmp(fname, "refcnt"))   return rt_fn_DBG_REFCNT;
        if (!strcmp(fname, "id"))       return rt_fn_DBG_ID;
        if (!strcmp(fname, "callproc")) return rt_fn_DBG_CALLPROC;
        if (!strcmp(fname, "filename")) return rt_fn_DBG_FILENAME;
        if (!strcmp(fname, "lineno"))   return rt_fn_DBG_LINENO;
        if (!strcmp(fname, "timenow"))  return rt_fn_DBG_TIMENOW;
        if (!strcmp(fname, "timenow_param")) return rt_fn_DBG_TIMENOW_PARAM;
    }
    if (!strcmp(module, "io")) {
        if (!strcmp(fname, "print"))    return rt_fn_IO_PRINT;
        if (!strcmp(fname, "println"))  return rt_fn_IO_PRINTLN;
        if (!strcmp(fname, "input"))    return rt_fn_IO_INPUT;
        if (!strcmp(fname, "fexists"))  return rt_fn_IO_FEXISTS;
        if (!strcmp(fname, "fread"))    return rt_fn_IO_FREAD;
        if (!strcmp(fname, "fwrite"))   return rt_fn_IO_FWRITE;
        if (!strcmp(fname, "fappend"))  return rt_fn_IO_FAPPEND;
        if (!strcmp(fname, "libopen"))  return rt_fn_IO_LIBOPEN;
        if (!strcmp(fname, "libsym"))   return rt_fn_IO_LIBSYM;
    }
    if (!strcmp(module, "it")) {
        if (!strcmp(fname, "len"))      return rt_fn_IT_LEN;
        if (!strcmp(fname, "clone"))    return rt_fn_IT_CLONE;
    }
    if (!strcmp(module, "chr")) {
        if (!strcmp(fname, "isdigit"))  return rt_fn_CHR_ISDIGIT;
        if (!strcmp(fname, "isalpha"))  return rt_fn_CHR_ISALPHA;
        if (!strcmp(fname, "isalnum"))  return rt_fn_CHR_ISALNUM;
        if (!strcmp(fname, "islower"))  return rt_fn_CHR_ISLOWER;
        if (!strcmp(fname, "isupper"))  return rt_fn_CHR_ISUPPER;
        if (!strcmp(fname, "isspace"))  return rt_fn_CHR_ISSPACE;
        if (!strcmp(fname, "max"))      return rt_fn_CHR_MAX;
        if (!strcmp(fname, "min"))      return rt_fn_CHR_MIN;
    }
    if (!strcmp(module, "i64")) {
        if (!strcmp(fname, "max"))      return rt_fn_I64_MAX;
        if (!strcmp(fname, "min"))      return rt_fn_I64_MIN;
    }
    if (!strcmp(module, "f64")) {
        if (!strcmp(fname, "max"))      return rt_fn_F64_MAX;
        if (!strcmp(fname, "min"))      return rt_fn_F64_MIN;
    }
    if (!strcmp(module, "str")) {
        if (!strcmp(fname, "equals"))   return rt_fn_STR_EQUALS;
        if (!strcmp(fname, "compare"))  return rt_fn_STR_COMPARE;
        if (!strcmp(fname, "tolower"))  return rt_fn_STR_TOLOWER;
        if (!strcmp(fname, "toupper"))  return rt_fn_STR_TOUPPER;
        if (!strcmp(fname, "append"))   return rt_fn_STR_APPEND;
        if (!strcmp(fname, "insert"))   return rt_fn_STR_INSERT;
        if (!strcmp(fname, "erase"))    return rt_fn_STR_ERASE;
        if (!strcmp(fname, "concat"))   return rt_fn_STR_CONCAT;
        if (!strcmp(fname, "reverse"))  return rt_fn_STR_REVERSE;
        if (!strcmp(fname, "substr"))   return rt_fn_STR_SUBSTR;
        if (!strcmp(fname, "find"))     return rt_fn_STR_FIND;
        if (!strcmp(fname, "split"))    return rt_fn_STR_SPLIT;
        if (!strcmp(fname, "toi64"))    return rt_fn_STR_TOI64;
        if (!strcmp(fname, "tof64"))    return rt_fn_STR_TOF64;
        if (!strcmp(fname, "sort"))     return rt_fn_STR_SORT;
    }
    if (!strcmp(module, "lst")) {
        if (!strcmp(fname, "equals"))   return rt_fn_LST_EQUALS;
        if (!strcmp(fname, "compare"))  return rt_fn_LST_COMPARE;
        if (!strcmp(fname, "append"))   return rt_fn_LST_APPEND;
        if (!strcmp(fname, "insert"))   return rt_fn_LST_INSERT;
        if (!strcmp(fname, "erase"))    return rt_fn_LST_ERASE;
        if (!strcmp(fname, "concat"))   return rt_fn_LST_CONCAT;
        if (!strcmp(fname, "reverse"))  return rt_fn_LST_REVERSE;
        if (!strcmp(fname, "find"))     return rt_fn_LST_FIND;
        if (!strcmp(fname, "sublist"))  return rt_fn_LST_SUBLIST;
        if (!strcmp(fname, "join"))     return rt_fn_LST_JOIN;
        if (!strcmp(fname, "sort"))     return rt_fn_LST_SORT;
    }

    if (!strcmp(module, "map")) {
        if (!strcmp(fname, "set"))      return rt_fn_MAP_SET;
        if (!strcmp(fname, "get"))      return rt_fn_MAP_GET;
        if (!strcmp(fname, "erase"))    return rt_fn_MAP_ERASE;
        if (!strcmp(fname, "concat"))   return rt_fn_MAP_CONCAT;
        if (!strcmp(fname, "find"))     return rt_fn_MAP_FIND;
        if (!strcmp(fname, "keys"))     return rt_fn_MAP_KEYS;
        if (!strcmp(fname, "lockonce")) return rt_fn_MAP_LOCKONCE;
    }

    if (!strcmp(fname, "isnull"))       return rt_fn_ISNULL;
    if (!strcmp(fname, "tostr"))        return rt_fn_TOSTR;
    if (!strcmp(fname, "type"))         return rt_fn_TYPE;
    if (!strcmp(fname, "cast"))         return rt_fn_CAST;
    if (!strcmp(fname, "errndie"))      return rt_fn_ERRNDIE;
    if (!strcmp(fname, "max"))          return rt_fn_MAX;
    if (!strcmp(fname, "min"))          return rt_fn_MIN;

    return rt_fn_UNDEFINED;
}

#include "runtime/functions/module_sys.c.h"
#include "runtime/functions/module_assert.c.h"
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
        case rt_fn_CAST:          return rt_fn_cast();
        case rt_fn_ERRNDIE:       return rt_fn_errndie();
        case rt_fn_MAX:           return rt_fn_max();
        case rt_fn_MIN:           return rt_fn_min();

        case rt_fn_SYS_EXIT:      return rt_fn_sys_exit();
        case rt_fn_SYS_SLEEP:     return rt_fn_sys_sleep();
        case rt_fn_SYS_GETENV:    return rt_fn_sys_getenv();
        case rt_fn_SYS_PLATFORM:  return rt_fn_sys_platform();
        case rt_fn_SYS_SYSTEM:    return rt_fn_sys_system();

        case rt_fn_ASSERT_TYPE:   return rt_fn_assert_type();
        case rt_fn_ASSERT_EQUALS: return rt_fn_assert_equals();
        case rt_fn_ASSERT_NOTNULL:return rt_fn_assert_notnull();

        case rt_fn_DBG_TYPENAME:  return rt_fn_dbg_typename();
#if 0
        case rt_fn_DBG_RTSIZE:    return rt_fn_dbg_rtsize();
#endif
        case rt_fn_DBG_REFCNT:    return rt_fn_dbg_refcnt();
        case rt_fn_DBG_ID:        return rt_fn_dbg_id();
        case rt_fn_DBG_CALLPROC:  return rt_fn_dbg_callproc();
        case rt_fn_DBG_FILENAME:  return rt_fn_dbg_filename();
        case rt_fn_DBG_LINENO:    return rt_fn_dbg_lineno();
        case rt_fn_DBG_TIMENOW:   return rt_fn_dbg_timenow();
        case rt_fn_DBG_TIMENOW_PARAM: return rt_fn_dbg_timenow_parameterized();

        case rt_fn_IO_PRINT:      return rt_fn_io_print();
        case rt_fn_IO_PRINTLN:    return rt_fn_io_println();
        case rt_fn_IO_INPUT:      return rt_fn_io_input();
        case rt_fn_IO_FEXISTS:    return rt_fn_io_fexists();
        case rt_fn_IO_FREAD:      return rt_fn_io_fread();
        case rt_fn_IO_FWRITE:     return rt_fn_io_fwrite();
        case rt_fn_IO_FAPPEND:    return rt_fn_io_fappend();
        case rt_fn_IO_LIBOPEN:    return rt_fn_io_libopen();
        case rt_fn_IO_LIBSYM:     return rt_fn_io_libsym();

        case rt_fn_IT_LEN:        return rt_fn_it_len();
        case rt_fn_IT_CLONE:      return rt_fn_it_clone();

        case rt_fn_CHR_ISDIGIT:   return rt_fn_chr_isdigit();
        case rt_fn_CHR_ISALPHA:   return rt_fn_chr_isalpha();
        case rt_fn_CHR_ISALNUM:   return rt_fn_chr_isalnum();
        case rt_fn_CHR_ISLOWER:   return rt_fn_chr_islower();
        case rt_fn_CHR_ISUPPER:   return rt_fn_chr_isupper();
        case rt_fn_CHR_ISSPACE:   return rt_fn_chr_isspace();
        case rt_fn_CHR_MAX:       return rt_fn_chr_max();
        case rt_fn_CHR_MIN:       return rt_fn_chr_min();

        case rt_fn_I64_MAX:       return rt_fn_i64_max();
        case rt_fn_I64_MIN:       return rt_fn_i64_min();

        case rt_fn_F64_MAX:       return rt_fn_f64_max();
        case rt_fn_F64_MIN:       return rt_fn_f64_min();

        case rt_fn_STR_EQUALS:    return rt_fn_str_equals();
        case rt_fn_STR_COMPARE:   return rt_fn_str_compare();
        case rt_fn_STR_TOLOWER:   return rt_fn_str_tolower();
        case rt_fn_STR_TOUPPER:   return rt_fn_str_toupper();
        case rt_fn_STR_APPEND:    return rt_fn_str_append();
        case rt_fn_STR_INSERT:    return rt_fn_str_insert();
        case rt_fn_STR_ERASE:     return rt_fn_str_erase();
        case rt_fn_STR_CONCAT:    return rt_fn_str_concat();
        case rt_fn_STR_REVERSE:   return rt_fn_str_reverse();
        case rt_fn_STR_SUBSTR:    return rt_fn_str_substr();
        case rt_fn_STR_FIND:      return rt_fn_str_find();
        case rt_fn_STR_SPLIT:     return rt_fn_str_split();
        case rt_fn_STR_TOI64:     return rt_fn_str_toi64();
        case rt_fn_STR_TOF64:     return rt_fn_str_tof64();
        case rt_fn_STR_SORT:      return rt_fn_str_sort();

        case rt_fn_LST_EQUALS:    return rt_fn_lst_equals();
        case rt_fn_LST_COMPARE:   return rt_fn_lst_compare();
        case rt_fn_LST_APPEND:    return rt_fn_lst_append();
        case rt_fn_LST_INSERT:    return rt_fn_lst_insert();
        case rt_fn_LST_ERASE:     return rt_fn_lst_erase();
        case rt_fn_LST_CONCAT:    return rt_fn_lst_concat();
        case rt_fn_LST_REVERSE:   return rt_fn_lst_reverse();
        case rt_fn_LST_SUBLIST:   return rt_fn_lst_sublst();
        case rt_fn_LST_FIND:      return rt_fn_lst_find();
        case rt_fn_LST_JOIN:      return rt_fn_lst_join();
        case rt_fn_LST_SORT:      return rt_fn_lst_sort();

        case rt_fn_MAP_SET:       return rt_fn_map_set();
        case rt_fn_MAP_GET:       return rt_fn_map_get();
        case rt_fn_MAP_ERASE:     return rt_fn_map_erase();
        case rt_fn_MAP_CONCAT:    return rt_fn_map_concat();
        case rt_fn_MAP_FIND:      return rt_fn_map_find();
        case rt_fn_MAP_KEYS:      return rt_fn_map_keys();
        case rt_fn_MAP_LOCKONCE:  return rt_fn_map_lockonce();

        case rt_fn_DBG_RTSIZE:
        case rt_fn_UNDEFINED:
            break;
    }

    io_errndie("rt_fn_FunctionsList_call: undefined procedure for desc: '%d'", fn);
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
    const char *module_name,
    const char *proc_name,
    rt_DataList_t *args
) {
    const ast_Identifier_t *module = (const ast_Identifier_t*) module_name;
    const ast_Identifier_t *proc = (const ast_Identifier_t*) proc_name;

    /* get a descriptor to in-built function */
    const rt_fn_FunctionDescriptor_t builtin_fn_desc = rt_fn_FunctionsList_getfn(
        module_name, proc_name);

    const char *currfile = NULL;

    /* update metadata to new module and function */
    if (ast_util_ModuleAndProcTable_exists(module, proc)) {
        currfile = ast_util_ModuleAndProcTable_get_filename(module, proc);
    } else if (builtin_fn_desc != rt_fn_UNDEFINED) {
        currfile = module_name;
    } else {
        rt_throw("undefined procedure '%s:%s'", module_name, proc_name);
    }

    rt_VarTable_push_proc(module, proc, currfile);

    /* store fn args into agrs location */
    rt_VarTable_create(RT_VTABLE_ARGSVAR, rt_Data_list(args), true, false);
    rt_VarTable_create(RT_VTABLE_CONTEXTVAR, context, true, false);

    /* count number of fnargs present in fnargs_list */
    int64_t fnargs_count = 0;
    const ast_FnArgsList_t *fnargs_list = ast_util_ModuleAndProcTable_get_args(module, proc);
    while (fnargs_list) {
        ++fnargs_count;
        fnargs_list = fnargs_list->args_list;
    }

    // /* if no of named args is more that whats passed, throw error */
    // if (fnargs_count > rt_DataList_length(args))
    //     rt_throw(
    //         "expected at least %" PRId64 " arguments, received %" PRId64,
    //         fnargs_count, rt_DataList_length(args)
    //     );

    /* create named args list */
    fnargs_list = ast_util_ModuleAndProcTable_get_args(module, proc);
    for  (int64_t i = 0; i < rt_DataList_length(args) && fnargs_list; ++i) {
        rt_VarTable_create(fnargs_list->identifier,
            *rt_DataList_getref(args, i), false, false);
        fnargs_list = fnargs_list->args_list;
    }

    /* make remaining fnargs null */
    while (fnargs_list) {
        rt_VarTable_create(fnargs_list->identifier, rt_Data_null(), false, false);
        fnargs_list = fnargs_list->args_list;
    }

    if (ast_util_ModuleAndProcTable_exists(module, proc)) {
        /* get code as AST from user defined function */
        const ast_Statements_t *code = ast_util_ModuleAndProcTable_get_code(module, proc);
        /* call user defined function */
        rt_ControlStatus_t ctrl = rt_eval_Statements(code);
        if (ctrl == rt_CTRL_BREAK)
            rt_throw("unexpected `break` statement outside loop");
        if (ctrl == rt_CTRL_CONTINUE)
            rt_throw("unexpected `continue` statement outside loop");
    } else {
        /* call in-built function */
        rt_VarTable_acc_setval(rt_fn_FunctionsList_call(builtin_fn_desc));
    }

    rt_Data_t ret = rt_VarTable_pop_proc();
    return ret;
}

rt_Data_t rt_fn_lambda_call_handler(
    const rt_Data_t context,
    const rt_DataLambda_t lambda,
    rt_DataList_t *args
) {
    const ast_Identifier_t *module = (lambda.type == rt_DATA_LAMBDA_TYPE_NATIVE)
        ? (const ast_Identifier_t*) lambda.fnptr.native.handle->file_name
        : (const ast_Identifier_t*) lambda.fnptr.nonnative->module_name;

    const ast_Identifier_t *proc = (lambda.type == rt_DATA_LAMBDA_TYPE_NATIVE)
        ? (const ast_Identifier_t*) rt_DataStr_tostr(lambda.fnptr.native.fn_name)
        : (const ast_Identifier_t*) rt_DATA_LAMBDA_DEFAULT_NAME;

    const char *currfile = (lambda.type == rt_DATA_LAMBDA_TYPE_NATIVE)
        ? (const ast_Identifier_t*) lambda.fnptr.native.handle->file_name
        : (const ast_Identifier_t*) lambda.fnptr.nonnative->file_name;

    /* push lambda to stack */
    rt_VarTable_push_proc(module, proc, currfile);

    /* store fn args into agrs location */
    rt_VarTable_create(RT_VTABLE_ARGSVAR, rt_Data_list(args), true, false);

    /* store context into context location */
    rt_VarTable_create(RT_VTABLE_CONTEXTVAR, context, true, false);

    switch (lambda.type) {

        case rt_DATA_LAMBDA_TYPE_NATIVE: {
            const rt_fn_NativeFunction_t fn = lambda.fnptr.native.fn;
            rt_VarTable_acc_setval(fn(context, args));
            break;
        }

        case rt_DATA_LAMBDA_TYPE_NONNATIVE: {

            /* count number of fnargs present in fnargs_list */
            int64_t fnargs_count = 0;
            const ast_FnArgsList_t *fnargs_list = lambda.fnptr.nonnative->args_list;
            while (fnargs_list) {
                ++fnargs_count;
                fnargs_list = fnargs_list->args_list;
            }

            // /* if no of named args is more that whats passed, throw error */
            // if (fnargs_count > rt_DataList_length(args))
            //     rt_throw(
            //         "expected at least %" PRId64 " arguments, received %" PRId64,
            //         fnargs_count, rt_DataList_length(args)
            //     );

            /* create named args list */
            fnargs_list = lambda.fnptr.nonnative->args_list;
            for  (int64_t i = 0; i < rt_DataList_length(args) && fnargs_list; ++i) {
                rt_VarTable_create(fnargs_list->identifier,
                    *rt_DataList_getref(args, i), false, false);
                fnargs_list = fnargs_list->args_list;
            }

            /* make remaining fnargs null */
            while (fnargs_list) {
                rt_VarTable_create(fnargs_list->identifier, rt_Data_null(), false, false);
                fnargs_list = fnargs_list->args_list;
            }

            if (lambda.fnptr.nonnative->is_expr) {
                /* evaluate lambda expression */
                rt_eval_Expression(lambda.fnptr.nonnative->body.expression);
            } else {
                /* call user defined function */
                rt_ControlStatus_t ctrl = rt_eval_Statements(lambda.fnptr.nonnative->body.statements);
                if (ctrl == rt_CTRL_BREAK)
                    rt_throw("unexpected `break` statement outside loop");
                if (ctrl == rt_CTRL_CONTINUE)
                    rt_throw("unexpected `continue` statement outside loop");
            }

            break;
        }
    }

    /* pop lambda from stack */
    rt_Data_t ret = rt_VarTable_pop_proc();

    if (lambda.type == rt_DATA_LAMBDA_TYPE_NATIVE) {
        free((void*) proc);
    }

    return ret;
}
