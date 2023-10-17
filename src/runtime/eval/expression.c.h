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
    rt_Data_t *oprnd_data,
    bool is_lhs
) {
    /* during function call, if lhs is a single identifier only
       then skip normal lhs evaluation to prevent conflict with
       rt_VarTable_getref during identifier value resolution.
       intead generate a procedure type data and return */
    if (is_lhs && op == TOKOP_FNCALL && oprnd_type == EXPR_TYPE_IDENTIFIER) {
        rt_VarTable_acc_setval((rt_Data_t) {
            .data.proc = {
                .modulename = rt_modulename_get(),
                .procname = oprnd.variable,
            },
            .type = rt_DATA_TYPE_PROC
        });
    } else {
        /* evaluate operand normally */
        switch (oprnd_type) {
            case EXPR_TYPE_EXPRESSION:
                rt_eval_Expression(oprnd.expr);
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
    }

rt_eval_Expression_operand_return:
    /* copy accumulator value into temporary memory as accumulator gets
       modified when evaluating other operands */
    *oprnd_data = *RT_ACC_DATA;
    return rt_VarTable_acc_get()->adr ? rt_VarTable_acc_get()->adr : oprnd_data;
}

void rt_eval_Expression(const ast_Expression_t *expr)
{
    if (!expr) {
        rt_VarTable_acc_setval(rt_Data_null());
        return;
    }

    /* take care pf fn calls and membership operations */
    switch (expr->op) {
        case TOKEN_DOT:
            rt_throw("unimplemented operators");
            break;
        case TOKEN_DCOLON: {
            if (expr->lhs_type != EXPR_TYPE_IDENTIFIER
                || expr->rhs_type != EXPR_TYPE_IDENTIFIER)
                    rt_throw("invalid use of module membership operator");
            /* instead of evaluating the lhs and RHS, directly generate a
               procedure type literal and return it via accumulator */
            rt_VarTable_acc_setval((rt_Data_t) {
                .data.proc = {
                    .modulename = expr->lhs.variable,
                    .procname = expr->rhs.variable,
                },
                .type = rt_DATA_TYPE_PROC
            });
            return;
        }
        default: break;
    }

    /* handle lhs and evaluate it */
    rt_Data_t lhs_;
    rt_Data_t *lhs = rt_eval_Expression_operand(
        expr->op, expr->lhs, expr->lhs_type, &lhs_, true);

    /* handle rhs and evaluate it */
    rt_Data_t rhs_;
    rt_Data_t *rhs = rt_eval_Expression_operand(
        expr->op, expr->rhs, expr->rhs_type, &rhs_, false);

    /* handle rhs and evaluate it */
    rt_Data_t condition_;
    rt_Data_t *condition = rt_eval_Expression_operand(
        expr->op, expr->condition, expr->condition_type, &condition_, false);

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
        /* remaining operators */
        case TOKEN_AMPERSAND:
        case TOKEN_ARITH_RSHIFT:
            rt_throw("unimplemented operators");
            break;
        case TOKEN_ASSIGN:
            rt_VarTable_acc_setval(*rt_VarTable_modf(lhs, *rhs));
            break;
        case TOKEN_ASTERIX:
        case TOKEN_BANG:
        case TOKEN_BITWISE_LSHIFT:
        case TOKEN_BITWISE_RSHIFT:
        case TOKEN_CARET:
        case TOKEN_DCOLON:
        case TOKEN_DECREMENT:
        case TOKEN_DOT:
        case TOKEN_EXPONENT:
        case TOKEN_FLOOR_DIVIDE:
        case TOKEN_FSLASH:
        case TOKEN_INCREMENT:
        case TOKEN_LBRACE_ANGULAR:
        case TOKEN_LOGICAL_AND:
        case TOKEN_LOGICAL_EQUAL:
        case TOKEN_LOGICAL_GREATER_EQUAL:
        case TOKEN_LOGICAL_LESSER_EQUAL:
        case TOKEN_LOGICAL_OR:
        case TOKEN_LOGICAL_UNEQUAL:
        case TOKEN_MINUS:
        case TOKEN_PERCENT:
        case TOKEN_PIPE:
        case TOKEN_PLUS:
        case TOKEN_RBRACE_ANGULAR:
        case TOKEN_TILDE:
            rt_throw("unimplemented operators");
            break;
        case TOKOP_FNARGS_INDEXING: rt_op_fnargs_indexing(lhs, rhs); break;
        case TOKOP_FNCALL:          rt_op_fncall(lhs, rhs); break;
        case TOKOP_INDEXING:
            rt_throw("unimplemented operators");
            break;
        case TOKOP_NOP:
            rt_VarTable_acc_setval(*lhs);
            break;
        case TOKOP_TERNARY_COND:
        /* stuff that doesn't form an operation */
        default:
            io_errndie("rt_eval_Expression: invalid operation '%s'",
                lex_Token_getcode(expr->op));
    }
}

#include "runtime/operators/ampersand.c.h"
#include "runtime/operators/arith_rshift.c.h"
#include "runtime/operators/assign.c.h"
#include "runtime/operators/asterix.c.h"
#include "runtime/operators/bang.c.h"
#include "runtime/operators/bitwise_lshift.c.h"
#include "runtime/operators/bitwise_rshift.c.h"
#include "runtime/operators/caret.c.h"
#include "runtime/operators/dcolon.c.h"
#include "runtime/operators/decrement.c.h"
#include "runtime/operators/dot.c.h"
#include "runtime/operators/exponent.c.h"
#include "runtime/operators/floor_divide.c.h"
#include "runtime/operators/fncall.c.h"
#include "runtime/operators/fslash.c.h"
#include "runtime/operators/increment.c.h"
#include "runtime/operators/lbrace_angular.c.h"
#include "runtime/operators/logical_and.c.h"
#include "runtime/operators/logical_equal.c.h"
#include "runtime/operators/logical_greater_equal.c.h"
#include "runtime/operators/logical_lesser_equal.c.h"
#include "runtime/operators/logical_or.c.h"
#include "runtime/operators/logical_unequal.c.h"
#include "runtime/operators/minus.c.h"
#include "runtime/operators/percent.c.h"
#include "runtime/operators/pipe.c.h"
#include "runtime/operators/plus.c.h"
#include "runtime/operators/rbrace_angular.c.h"
#include "runtime/operators/tilde.c.h"
#include "runtime/operators/tokop_fnargs_indexing.c.h"
#include "runtime/operators/tokop_fncall.c.h"
#include "runtime/operators/tokop_indexing.c.h"
#include "runtime/operators/tokop_nop.c.h"
#include "runtime/operators/tokop_ternary_cond.c.h"

#else
    #warning re-inclusion of module 'runtime/eval/expression.c.h'
#endif
