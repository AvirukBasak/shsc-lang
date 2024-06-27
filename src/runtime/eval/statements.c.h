#ifndef RT_EVAL_STATEMENTS_C_H
#define RT_EVAL_STATEMENTS_C_H

#include <string.h>

#include "ast.h"
#include "ast/api.h"
#include "runtime.h"
#include "runtime/data/Data.h"
#include "runtime/eval.h"
#include "runtime/VarTable.h"

rt_ControlStatus_t rt_eval_Statements(const ast_Statements_t *code)
{
    if (!code) {
        /* if there is no statement, return null */
        rt_VarTable_acc_setval(rt_Data_null());
        return rt_CTRL_PASS;
    }

    const ast_Statements_t *ptr = code;
    while (ptr) {
        /* during execution of last statement, if current proc is main:main
           and the last statement is not a return statement then set exit_code
           to rt_Data_i64(0) */
        rt_Data_t exit_code = rt_Data_null();
        if (   !ptr->statements
            && !strcmp(rt_VarTable_top_proc()->module_name, "main")
            && !strcmp(rt_VarTable_top_proc()->proc_name, "main")
            && ptr->statement && ptr->statement->type != STATEMENT_TYPE_RETURN) {
            exit_code = rt_Data_i64(0);
        }

        rt_ControlStatus_t ctrl = rt_eval_Statement(ptr->statement);
        if (!rt_Data_isnull(exit_code))
            rt_VarTable_acc_setval(exit_code);
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
