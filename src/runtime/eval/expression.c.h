#ifndef RT_EVAL_EXPRESSION_C_H
#define RT_EVAL_EXPRESSION_C_H

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

#include "ast.h"
#include "ast/api.h"
#include "io.h"
#include "runtime.h"
#include "runtime/data/Data.h"
#include "runtime/data/DataList.h"
#include "runtime/eval.h"
#include "runtime/io.h"
#include "runtime/operators.h"
#include "runtime/VarTable.h"

rt_Data_t *rt_eval_Expression_operand(
    const ast_Operator_t op,
    const union ast_ExpressionUnion_t oprnd,
    const enum ast_ExpressionType_t oprnd_type,
    rt_Data_t *oprnd_data
) {
    /* do not evaluate operands in case operator is a
       module membership operator */
    if (op == TOKEN_DCOLON) return NULL;

    switch (oprnd_type) {
        case EXPR_TYPE_EXPRESSION:
            rt_eval_Expression(oprnd.expr);
            break;
        case EXPR_TYPE_LITERAL:
            rt_eval_Literal(oprnd.literal);
            break;
        case EXPR_TYPE_IDENTIFIER:
            rt_eval_Identifier(oprnd.variable);
            break;
        case EXPR_TYPE_NULL:
            /* this makes sure that for TOKOP_NOP where rhs and condition are null,
               a new value is not assigned to the accumulator.
               otherwise, the accumulator will destroy its previous value, causing a
               potential heap-use-after-free bug */
            return NULL;
    }

    /* copy accumulator value into temporary memory as accumulator gets
       modified when evaluating other operands */
    *oprnd_data = *RT_VTABLE_ACC;
    return rt_VarTable_acc_get()->adr ? rt_VarTable_acc_get()->adr : oprnd_data;
}

void rt_eval_Expression(const ast_Expression_t *expr)
{
    if (!expr) {
        rt_VarTable_acc_setval(rt_Data_null());
        return;
    }

    /* handle lhs and evaluate it */
    rt_Data_t lhs_;
    rt_Data_t *lhs = rt_eval_Expression_operand(
        expr->op, expr->lhs, expr->lhs_type, &lhs_);

    /* handle rhs and evaluate it */
    rt_Data_t rhs_;
    rt_Data_t *rhs = rt_eval_Expression_operand(
        expr->op, expr->rhs, expr->rhs_type, &rhs_);

    /* handle rhs and evaluate it */
    rt_Data_t condition_;
    rt_Data_t *condition = rt_eval_Expression_operand(
        expr->op, expr->condition, expr->condition_type, &condition_);

    switch (expr->op) {
        /* shortcut assignment operators */
        case TOKEN_ADD_ASSIGN:
        case TOKEN_ARITH_RSHIFT_ASSIGN:
        case TOKEN_BITWISE_AND_ASSIGN:
        case TOKEN_BITWISE_LSHIFT_ASSIGN:
        case TOKEN_BITWISE_OR_ASSIGN:
        case TOKEN_BITWISE_RSHIFT_ASSIGN:
        case TOKEN_BITWISE_XOR_ASSIGN:
        case TOKEN_DIVIDE_ASSIGN:
        case TOKEN_EXPONENT_ASSIGN:
        case TOKEN_FLOOR_DIVIDE_ASSIGN:
        case TOKEN_LOGICAL_AND_ASSIGN:
        case TOKEN_LOGICAL_OR_ASSIGN:
        case TOKEN_MODULO_ASSIGN:
        case TOKEN_MULTIPLY_ASSIGN:
        case TOKEN_SUBSTRACT_ASSIGN:
            rt_throw("unimplemented operator");
            break;
        /* remaining operators */
        case TOKEN_AMPERSAND:                         rt_op_ampersand(lhs, rhs); break;
        case TOKEN_ARITH_RSHIFT:                   rt_op_arith_rshift(lhs, rhs); break;
        case TOKEN_ASSIGN:                               rt_op_assign(lhs, rhs); break;
        case TOKEN_ASTERIX:                             rt_op_asterix(lhs, rhs); break;
        case TOKEN_BANG:                                   rt_op_bang(lhs, rhs); break;
        case TOKEN_BITWISE_LSHIFT:               rt_op_bitwise_lshift(lhs, rhs); break;
        case TOKEN_BITWISE_RSHIFT:               rt_op_bitwise_rshift(lhs, rhs); break;
        case TOKEN_CARET:                                 rt_op_caret(lhs, rhs); break;
        case TOKEN_DCOLON:                               rt_op_dcolon(expr); break;
        case TOKEN_DECREMENT:                         rt_op_decrement(lhs, rhs); break;
        case TOKEN_DOT:                                     rt_op_dot(lhs, rhs); break;
        case TOKEN_EXPONENT:                           rt_op_exponent(lhs, rhs); break;
        case TOKEN_FLOOR_DIVIDE:                   rt_op_floor_divide(lhs, rhs); break;
        case TOKEN_FSLASH:                               rt_op_fslash(lhs, rhs); break;
        case TOKEN_INCREMENT:                         rt_op_increment(lhs, rhs); break;
        case TOKEN_LBRACE_ANGULAR:               rt_op_lbrace_angular(lhs, rhs); break;
        case TOKEN_LOGICAL_AND:                     rt_op_logical_and(lhs, rhs); break;
        case TOKEN_LOGICAL_EQUAL:                 rt_op_logical_equal(lhs, rhs); break;
        case TOKEN_LOGICAL_GREATER_EQUAL: rt_op_logical_greater_equal(lhs, rhs); break;
        case TOKEN_LOGICAL_LESSER_EQUAL:   rt_op_logical_lesser_equal(lhs, rhs); break;
        case TOKEN_LOGICAL_OR:                       rt_op_logical_or(lhs, rhs); break;
        case TOKEN_LOGICAL_UNEQUAL:             rt_op_logical_unequal(lhs, rhs); break;
        case TOKEN_MINUS:                                 rt_op_minus(lhs, rhs); break;
        case TOKEN_PERCENT:                             rt_op_percent(lhs, rhs); break;
        case TOKEN_PIPE:                                   rt_op_pipe(lhs, rhs); break;
        case TOKEN_PLUS:                                   rt_op_plus(lhs, rhs); break;
        case TOKEN_RBRACE_ANGULAR:               rt_op_rbrace_angular(lhs, rhs); break;
        case TOKEN_TILDE:                                 rt_op_tilde(lhs, rhs); break;
        case TOKOP_FNARGS_INDEXING:             rt_op_fnargs_indexing(lhs, rhs); break;
        case TOKOP_FNCALL:                               rt_op_fncall(lhs, rhs); break;
        case TOKOP_INDEXING:                           rt_op_indexing(lhs, rhs); break;
        case TOKOP_NOP:                                     rt_op_nop(lhs); break;
        case TOKOP_TERNARY_COND:                   rt_op_ternary_cond(lhs, rhs, condition); break;
        /* using default here coz there's a lot of cases
           the following are not operators */
        default:
            io_errndie("rt_eval_Expression: invalid operation '%s'",
                lex_Token_getcode(expr->op));
    }
}

#else
    #warning re-inclusion of module 'runtime/eval/expression.c.h'
#endif
