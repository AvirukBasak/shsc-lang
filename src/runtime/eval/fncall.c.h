#ifndef RT_EVAL_FNCALL_C_H
#define RT_EVAL_FNCALL_C_H

#include "ast.h"
#include "ast/api.h"
#include "functions.h"
#include "runtime/eval.h"
#include "runtime/io.h"
#include "runtime/VarTable.h"

void rt_call_function(const ast_Identifier_t *module, const ast_Identifier_t *proc)
{
    /* get code as AST from user defined function */
    const ast_Statements_t *code = ast_util_ModuleAndProcTable_get_code(module, proc);
    /* get a descriptor to in-built function */
    const fn_FunctionDescriptor_t fn = fn_FunctionsList_getfn(
        module->identifier_name, proc->identifier_name);
    /* backup metadata on current module and function */
    const char *currfile_bkp = rt_currfile;
    const ast_Identifier_t *currmodule_bkp = rt_current_module;
    const ast_Identifier_t *currproc_bkp = rt_current_proc;
    /* update metadata to new module and function */
    if (code) {
        rt_currfile = ast_util_ModuleAndProcTable_get_filename(module, proc);
        rt_current_module = module;
        rt_current_proc = proc;
    } else if (fn != fn_UNDEFINED) {
        rt_currfile = "<built-in>";
        rt_current_module = module;
        rt_current_proc = proc;
    }
    if (code) {
        /* call user defined function */
        rt_VarTable_push_proc(proc->identifier_name);
        rt_eval_Statements(code);
        rt_VarTable_pop_proc();
    } else {
        /* attempt to call in-built function */
        if (fn == fn_UNDEFINED)
            rt_throw("undefined procedure '%s:%s'",
                module->identifier_name, proc->identifier_name);
        rt_VarTable_acc_setval(fn_FunctionsList_call(fn));
    }
    /* restore metadata to previous module and function */
    rt_currfile = currfile_bkp;
    rt_current_module = currmodule_bkp;
    rt_current_proc = currproc_bkp;
}

#else
    #warning re-inclusion of module 'runtime/eval/fncall.c.h'
#endif
