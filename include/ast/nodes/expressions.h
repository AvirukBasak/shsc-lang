#ifndef AST_NODES_EXPRESSIONS_H
#define AST_NODES_EXPRESSIONS_H

#include "ast.h"

enum AST_ExpressionType_t {
    EXPR_TYPE_CONDITIONAL,
    EXPR_TYPE_ASSIGNMENT,
};

enum AST_ConditionalExprType_t {
    CONDITIONAL_EXPR_TYPE_TERNARY,
    CONDITIONAL_EXPR_TYPE_BINARY,
};

enum AST_BinaryExprType_t {
    BINARY_EXPR_TYPE_OP_BINARY,
    BINARY_EXPR_TYPE_OP_UNARY,
    BINARY_EXPR_TYPE_UNARY_OP,
};

enum AST_UnaryExprType_t {
    UNARY_EXPR_TYPE_POSTFIX,
    UNARY_EXPR_TYPE_UNARY,
};

enum AST_PostfixExprType_t {
    POSTFIX_EXPR_TYPE_PRIMARY,
    POSTFIX_EXPR_TYPE_FNCALL,
    POSTFIX_EXPR_TYPE_INDEXING,
    POSTFIX_EXPR_TYPE_POSTFIX,
    POSTFIX_EXPR_TYPE_MEMBER_ACCESS,
};

enum AST_PrimaryExprType_t {
    PRIMARY_EXPR_TYPE_EXPR,
    PRIMARY_EXPR_TYPE_OPERAND,
};

enum AST_OperatorAssocType_t {
    OPASSOC_LEFT,
    OPASSOC_RIGHT,
};

/* Various expressions: --------------------------------- */



/* End of various expressions --------------------------- */

#endif
