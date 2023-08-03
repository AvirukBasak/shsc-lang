#ifdef AST_NODES_H
    #error either of 'ast/api.h' or 'ast/nodes.h' should be included
#endif

#ifndef AST_API_H
#define AST_API_H

#include <inttypes.h>
#include <stdbool.h>

#include "ast.h"
#include "lexer.h"
#include "nodes/create.h"
#include "nodes/destroy.h"
#include "nodes/enums.h"
#include "util/module_stack.h"
#include "util/procedure_map.h"

typedef enum LexToken AST_Operator_t;

struct AST_Statements_t {
    const AST_Statements_t *statements;
    const AST_Statement_t *statement;
};

struct AST_Statement_t {
    const union {
       const AST_Expression_t *expression;
       const AST_Assignment_t *assignment;
       const AST_CompoundSt_t *compound_statement;
    } statement;
    const int line_no;
    const enum AST_StatementType_t type;
};

struct AST_Assignment_t {
    const AST_Identifier_t *lhs;
    const AST_Expression_t *rhs;
    const enum AST_AssignmentType_t type;
};

struct AST_CompoundSt_t {
    const union {
        const AST_IfBlock_t *if_block;
        const AST_WhileBlock_t *while_block;
        const AST_ForBlock_t *for_block;
        const AST_Block_t *block;
    } compound_statement;
    const enum AST_CompoundStType_t type;
};

struct AST_IfBlock_t {
    const AST_Condition_t *condition;
    const AST_Statements_t *if_st;
    const AST_ElseBlock_t *else_block;
};

struct AST_ElseBlock_t {
    /** if condition is not NULL, it's an
        else if block, otherwise it's an else block */
    const AST_Condition_t *condition;
    /** if condition is NULL, it's an else block
        else it's an if else block */
    const AST_Statements_t *else_if_st;
    const AST_ElseBlock_t *else_block;
};

struct AST_WhileBlock_t {
    const AST_Condition_t *condition;
    const AST_Statements_t *statements;
};

struct AST_ForBlock_t {
    const AST_Identifier_t *iter;
    const union {
        const struct {
            const AST_Expression_t *start;
            const AST_Expression_t *end;
            const AST_Expression_t *by;
        } range;
        const AST_Expression_t *lst;
    } iterable;
    const AST_Statements_t *statements;
    const enum AST_ForBlockType_t type;
};

struct AST_Block_t {
    const AST_Statements_t *statements;
};

union AST_ExpressionUnion_t {
    const AST_Expression_t *expr;
    const AST_Literal_t *literal;
    const AST_Identifier_t *variable;
    const AST_CommaSepList_t *lst;
};

struct AST_Expression_t {
    AST_Operator_t op;
    /** lhs or if part of ternary expression */
    const union AST_ExpressionUnion_t lhs;
    const enum AST_ExpressionType_t lhs_type;
    /** rhs or else part of ternary expression */
    const union AST_ExpressionUnion_t rhs;
    const enum AST_ExpressionType_t rhs_type;
    /** optional condition for ternary operators,
        set to NULL if not used */
    const union AST_ExpressionUnion_t condition;
    const enum AST_ExpressionType_t condition_type;
};

struct AST_CommaSepList_t {
    const AST_CommaSepList_t *comma_list;
    const AST_Expression_t *expression;
};

struct AST_Literal_t {
    const union {
        const bool bul;
        const char chr;
        const int64_t i64;
        const double f64;
        const char *str;
        const AST_CommaSepList_t *lst;
        const void *any;
    }  data;
    const enum AST_DataType_t type;
};

struct AST_Identifier_t {
    const char *identifier_name;
};

#endif
