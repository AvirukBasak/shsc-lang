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
    rt_Data_t *ref = rt_VarTable_getref_errnull(identifier);
    /* if there's a variable reference, return the reference */
    if (ref) {
        rt_VarTable_acc_setadr(ref);
        return;
    }

    /* if user-defined procedure exists, return procedure type data */
    if (ast_util_ModuleAndProcTable_exists(rt_VarTable_top_proc()->module_name, identifier)) {
        rt_VarTable_acc_setval(rt_Data_proc(
            rt_VarTable_top_proc()->module_name,
            identifier
        ));
        return;
    }
    /* get a descriptor to in-built function */
    const rt_fn_FunctionDescriptor_t fn = rt_fn_FunctionsList_getfn(
        rt_VarTable_top_proc()->module_name,
        identifier
    );
    /* if defined, return procedure type data */
    if (fn != rt_fn_UNDEFINED) {
        rt_VarTable_acc_setval(rt_Data_proc(
            rt_VarTable_top_proc()->module_name,
            identifier
        ));
        return;
    }
    /* if neither variable, procedure or built-in function */
    rt_throw("undefined identifier '%s'", identifier);
}

#else
    #warning re-inclusion of module 'runtime/eval/identifier.c.h'
#endif
