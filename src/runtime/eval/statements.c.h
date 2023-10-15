#ifndef RT_EVAL_STATEMENTS_C_H
#define RT_EVAL_STATEMENTS_C_H

#include "ast.h"
#include "ast/api.h"
#include "runtime/eval.h"
#include "runtime/VarTable.h"

rt_ControlStatus_t rt_eval_Statements(const ast_Statements_t *code)
{
    if (!code) return rt_CTRL_PASS;
    const ast_Statements_t *ptr = code;
    while (ptr) {
        rt_ControlStatus_t ctrl = rt_eval_Statement(ptr->statement);
        if (ctrl != rt_CTRL_PASS) return ctrl;
        ptr = ptr->statements;
    }
    return rt_CTRL_PASS;
}

rt_ControlStatus_t rt_eval_Statements_newscope(const ast_Statements_t *code)
{
    if (!code) return rt_CTRL_PASS;
    rt_VarTable_push_scope();
    rt_ControlStatus_t ctrl = rt_eval_Statements(code);
    rt_VarTable_pop_scope();
    return ctrl;
}

#else
    #warning re-inclusion of module 'runtime/eval/statements.c.h'
#endif
