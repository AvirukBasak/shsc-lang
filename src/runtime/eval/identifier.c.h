#ifndef RT_EVAL_IDENTIFIER_C_H
#define RT_EVAL_IDENTIFIER_C_H

#include "ast.h"
#include "ast/api.h"
#include "runtime/eval.h"
#include "runtime/functions.h"
#include "runtime/io.h"
#include "runtime/VarTable.h"

void rt_eval_Identifier(const ast_Identifier_t *identifier)
{
    if (!identifier) {
        rt_VarTable_acc_setval(rt_Data_null());
        return;
    }
    /* get a possible variable reference from VarTable */
    rt_Data_t *ref = rt_VarTable_getref_errnull(identifier->identifier_name);
    /* if there's a variable reference, return the reference */
    if (ref) {
        rt_VarTable_acc_setadr(ref);
        return;
    }
    /* get code as AST from user defined function */
    const ast_Statements_t *code = ast_util_ModuleAndProcTable_get_code(
        rt_VarTable_top_proc()->modulename,
        identifier
    );
    /* if not null, return procedure type data */
    if (code) {
        rt_VarTable_acc_setval(rt_Data_proc(
            rt_VarTable_top_proc()->modulename,
            identifier
        ));
        return;
    }
    /* get a descriptor to in-built function */
    const rt_fn_FunctionDescriptor_t fn = rt_fn_FunctionsList_getfn(
        rt_VarTable_top_proc()->modulename->identifier_name,
        identifier->identifier_name
    );
    /* if defined, return procedure type data */
    if (fn != rt_fn_UNDEFINED) {
        rt_VarTable_acc_setval(rt_Data_proc(
            rt_VarTable_top_proc()->modulename,
            identifier
        ));
        return;
    }
    /* if neither variable, procedure or built-in function */
    rt_throw("undefined identifier '%s'", identifier->identifier_name);
}

#else
    #warning re-inclusion of module 'runtime/eval/identifier.c.h'
#endif
