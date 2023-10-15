#ifndef RT_EVAL_IDENTIFIER_C_H
#define RT_EVAL_IDENTIFIER_C_H

#include "ast.h"
#include "ast/api.h"
#include "runtime/eval.h"
#include "runtime/VarTable.h"

void rt_eval_Identifier(const ast_Identifier_t *identifier)
{
    if (!identifier) {
        rt_VarTable_acc_setval(rt_Data_null());
        return;
    }
    rt_VarTable_acc_setadr(
        rt_VarTable_getref(identifier->identifier_name));
}

#else
    #warning re-inclusion of module 'runtime/eval/identifier.c.h'
#endif
