#ifndef RT_EVAL_EXPRESSION_C_H
#define RT_EVAL_EXPRESSION_C_H

#include <inttypes.h>
#include <stdbool.h>

#include "ast.h"
#include "ast/api.h"
#include "io.h"
#include "runtime.h"
#include "runtime/data/DataList.h"
#include "runtime/eval.h"
#include "runtime/io.h"
#include "runtime/VarTable.h"

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
    rt_Data_t lhs_, *lhs = NULL;

    /* during function call, if lhs is a single identifier only
       then skip normal lhs evaluation to prevent conflict with
       rt_VarTable_getref during identifier value resolution */
    if (expr->op == TOKOP_FNCALL && expr->lhs_type == EXPR_TYPE_IDENTIFIER) {
        rt_VarTable_acc_setval((rt_Data_t) {
            .data.proc = {
                .modulename = rt_modulename_get(),
                .procname = expr->lhs.variable,
            },
            .type = rt_DATA_TYPE_PROC
        });
        /* copy accumulator value into temporary memory as accumulator gets
           modified when evaluating other operands */
        lhs_ = *RT_ACC_DATA;
        lhs = rt_VarTable_acc_get()->adr ? rt_VarTable_acc_get()->adr : &lhs_;
        goto rt_eval_Expression_eval_skip_lhs;
    }

    switch (expr->lhs_type) {
        case EXPR_TYPE_EXPRESSION:
            rt_eval_Expression(expr->lhs.expr);
            /* copy accumulator value into temporary memory as accumulator gets
               modified when evaluating other operands */
            lhs_ = *RT_ACC_DATA;
            lhs = rt_VarTable_acc_get()->adr ? rt_VarTable_acc_get()->adr : &lhs_;
            break;
        case EXPR_TYPE_LITERAL:
            rt_eval_Literal(expr->lhs.literal);
            lhs_ = *RT_ACC_DATA;
            lhs = rt_VarTable_acc_get()->adr ? rt_VarTable_acc_get()->adr : &lhs_;
            break;
        case EXPR_TYPE_IDENTIFIER:
            rt_eval_Identifier(expr->lhs.variable);
            lhs_ = *RT_ACC_DATA;
            lhs = rt_VarTable_acc_get()->adr ? rt_VarTable_acc_get()->adr : &lhs_;
            break;
        case EXPR_TYPE_NULL: break;
    }

    /* handle rhs and evaluate it */
    rt_Data_t rhs_, *rhs = NULL;
rt_eval_Expression_eval_skip_lhs:
    switch (expr->rhs_type) {
        case EXPR_TYPE_EXPRESSION:
            rt_eval_Expression(expr->rhs.expr);
            rhs_ = *RT_ACC_DATA;
            rhs = rt_VarTable_acc_get()->adr ? rt_VarTable_acc_get()->adr : &rhs_;
            break;
        case EXPR_TYPE_LITERAL:
            rt_eval_Literal(expr->rhs.literal);
            rhs_ = *RT_ACC_DATA;
            rhs = rt_VarTable_acc_get()->adr ? rt_VarTable_acc_get()->adr : &rhs_;
            break;
        case EXPR_TYPE_IDENTIFIER:
            rt_eval_Identifier(expr->rhs.variable);
            rhs_ = *RT_ACC_DATA;
            rhs = rt_VarTable_acc_get()->adr ? rt_VarTable_acc_get()->adr : &rhs_;
            break;
        case EXPR_TYPE_NULL: break;
    }

    /* handle condition and evaluate it */
    rt_Data_t condition_, *condition = NULL;
rt_eval_Expression_eval_skip_lhs_and_rhs:
    switch (expr->condition_type) {
        case EXPR_TYPE_EXPRESSION:
            rt_eval_Expression(expr->condition.expr);
            condition_ = *RT_ACC_DATA;
            condition = rt_VarTable_acc_get()->adr ? rt_VarTable_acc_get()->adr : &condition_;
            break;
        case EXPR_TYPE_LITERAL:
            rt_eval_Literal(expr->condition.literal);
            condition_ = *RT_ACC_DATA;
            condition = rt_VarTable_acc_get()->adr ? rt_VarTable_acc_get()->adr : &condition_;
            break;
        case EXPR_TYPE_IDENTIFIER:
            rt_eval_Identifier(expr->condition.variable);
            condition_ = *RT_ACC_DATA;
            condition = rt_VarTable_acc_get()->adr ? rt_VarTable_acc_get()->adr : &condition_;
            break;
        case EXPR_TYPE_NULL: break;
    }

rt_eval_Expression_eval_skip_all_3_operands:
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
        case TOKOP_FNARGS_INDEXING: {
            if (!rhs || rhs->type != rt_DATA_TYPE_I64)
                rt_throw("argument index should evaluate to an `i64`");
            rt_Data_t args = *rt_VarTable_getref("$");
            if (args.type != rt_DATA_TYPE_LST)
                io_errndie("rt_eval_Expression: TOKOP_FNARGS_INDEXING: "
                           "received arguments list as type '%s'", rt_Data_typename(args));
            rt_VarTable_acc_setadr(
                rt_DataList_getref(args.data.lst, rhs->data.i64));
            break;
        }
        case TOKOP_FNCALL: {
            if (lhs->type != rt_DATA_TYPE_PROC)
                rt_throw("cannot make procedure call to type '%s'", rt_Data_typename(*lhs));
            if (!rhs) {
                rhs_ = rt_Data_list(rt_DataList_init());
                rhs = &rhs_;
            }
            if (rhs->type != rt_DATA_TYPE_LST)
                rt_throw("cannot pass type '%s' as procedure argument", rt_Data_typename(*rhs));
            /* copy fn args into temporary location */
            rt_VarTable_modf(rt_VarTable_getref("$"), *rhs);
            /* get fn code and push code to stack */
            rt_call_function(lhs->data.proc.modulename, lhs->data.proc.procname);
            /* set no data to accumulator as data is already set by procedure called above
               return early to prevent accumulator being modified by some other code */
            return;
        }
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

#else
    #warning re-inclusion of module 'runtime/eval/expression.c.h'
#endif
