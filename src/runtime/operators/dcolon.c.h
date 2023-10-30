#ifndef RT_OP_DCOLON_C_H
#define RT_OP_DCOLON_C_H

#include "runtime/data/Data.h"
#include "runtime/operators.h"

void rt_op_dcolon(const ast_Expression_t *expr)
{
    if (expr->lhs_type != EXPR_TYPE_IDENTIFIER
        || expr->rhs_type != EXPR_TYPE_IDENTIFIER)
            rt_throw("invalid use of module membership operator");
    /* instead of evaluating the LHS and RHS, directly generate a
       procedure type literal and return it via accumulator */
    rt_VarTable_acc_setval(rt_Data_proc(
        expr->lhs.variable,
        expr->rhs.variable
    ));
}

#else
    #warning re-inclusion of module 'runtime/operators/dcolon.c.h'
#endif
