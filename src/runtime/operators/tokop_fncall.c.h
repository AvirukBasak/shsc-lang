#ifndef RT_OP_TOKOP_FNCALL_C_H
#define RT_OP_TOKOP_FNCALL_C_H

#include "ast.h"
#include "ast/api.h"
#include "functions.h"
#include "io.h"
#include "runtime.h"
#include "runtime/data/Data.h"
#include "runtime/data/DataList.h"
#include "runtime/eval.h"
#include "runtime/io.h"
#include "runtime/operators.h"
#include "runtime/VarTable.h"

void rt_op_fncall_handler(const ast_Identifier_t *module, const ast_Identifier_t *proc, rt_Data_t args);

void rt_op_fncall(const rt_Data_t *lhs, const rt_Data_t *rhs) {
    if (lhs->type != rt_DATA_TYPE_PROC)
        rt_throw("cannot make procedure call to type '%s'", rt_Data_typename(*lhs));
    /** temporary data variable for rhs */
    rt_Data_t rhs_;
    if (!rhs) {
        rhs_ = rt_Data_list(rt_DataList_init());
        rhs = &rhs_;
    }
    if (rhs->type != rt_DATA_TYPE_LST)
        rt_throw("cannot pass type '%s' as procedure argument", rt_Data_typename(*rhs));
    /* get fn code and push code to stack */
    rt_op_fncall_handler(lhs->data.proc.modulename, lhs->data.proc.procname, *rhs);
    /* set no data to accumulator as data is already set by procedure called above
       return early to prevent accumulator being modified by some other code */
    return;
}

void rt_op_fncall_handler(const ast_Identifier_t *module, const ast_Identifier_t *proc, rt_Data_t args)
{
    /* get code as AST from user defined function */
    const ast_Statements_t *code = ast_util_ModuleAndProcTable_get_code(module, proc);
    /* get a descriptor to in-built function */
    const fn_FunctionDescriptor_t fn = fn_FunctionsList_getfn(
        module->identifier_name, proc->identifier_name);

    const char *currfile = NULL;
    /* update metadata to new module and function */
    if (code) {
        currfile = ast_util_ModuleAndProcTable_get_filename(module, proc);
    } else if (fn != fn_UNDEFINED) {
        currfile = rt_VarTable_top_proc()->filepath;
    }
    rt_VarTable_push_proc(module, proc, currfile);
    /* store fn args into agrs location */
    rt_VarTable_create(RT_VTABLE_ARGSVAR, args, true);
    if (code) {
        /* call user defined function */
        rt_eval_Statements(code);
    } else {
        /* attempt to call in-built function */
        if (fn == fn_UNDEFINED)
            rt_throw("undefined procedure '%s:%s'",
                module->identifier_name, proc->identifier_name);
        rt_VarTable_acc_setval(fn_FunctionsList_call(fn));
    }
    rt_VarTable_pop_proc();
}

#else
    #warning re-inclusion of module 'runtime/operators/tokop_fncall.c.h'
#endif
