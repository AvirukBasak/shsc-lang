#ifndef AST_NODES_H
#define AST_NODES_H

#include "ast.h"
#include "lexer.h"
#include "nodes/create.h"
#include "nodes/destroy.h"
#include "nodes/enums.h"

typedef int AST_Operator_t;

struct AST_Statements_t {
    AST_Statements_t *statements;
    AST_Statement_t *statement;
};

struct AST_Statement_t {
    union {
       AST_Expression_t *expression;
       AST_Assignment_t *assignment;
       AST_CompoundSt_t *compound_statement;
    } statement;
    int line_no;
    enum AST_StatementType_t type;
};

struct AST_Assignment_t {
    AST_Identifier_t *lhs;
    AST_Expression_t *rhs;
    enum AST_AssignmentType_t type;
};

struct AST_CompoundSt_t {
    union {
        AST_IfBlock_t *if_block;
        AST_WhileBlock_t *while_block;
        AST_ForBlock_t *for_block;
        AST_Block_t *block;
    } compound_statement;
   enum AST_CompoundStType_t type;
};

struct AST_IfBlock_t {
    AST_Condition_t *condition;
    AST_Statements_t *if_st;
    AST_ElseBlock_t *else_block;
};

struct AST_ElseBlock_t {
    /** if condition is not NULL, it's an
        else if block, otherwise it's an else block */
    AST_Condition_t *condition;
    /** if condition is NULL, it's an else block
        else it's an if else block */
    AST_Statements_t *else_if_st;
    AST_ElseBlock_t *else_block;
};

struct AST_WhileBlock_t {
    AST_Condition_t *condition;
    AST_Statements_t *statements;
};

struct AST_ForBlock_t {
    AST_Identifier_t *iter;
    union {
        struct {
            AST_Expression_t *start;
            AST_Expression_t *end;
            AST_Expression_t *by;
        } range;
        AST_Expression_t *lst;
    } iterable;
    AST_Statements_t *statements;
    enum AST_ForBlockType_t type;
};

struct AST_Block_t {
    AST_Statements_t *statements;
};

union AST_ExpressionUnion_t {
    AST_Expression_t *expr;
    AST_Literal_t *literal;
    AST_Identifier_t *variable;
    AST_CommaSepList_t *lst;
};

struct AST_Expression_t {
    AST_Operator_t op;
    /** lhs or if part of ternary expression */
    union AST_ExpressionUnion_t lhs;
    enum AST_ExpressionType_t lhs_type;
    /** rhs or else part of ternary expression */
    union AST_ExpressionUnion_t rhs;
    enum AST_ExpressionType_t rhs_type;
    /** optional condition for ternary operators,
        set to NULL if not used */
    union AST_ExpressionUnion_t condition;
    enum AST_ExpressionType_t condition_type;
};

struct AST_CommaSepList_t {
    AST_CommaSepList_t *comma_list;
    AST_Expression_t *expression;
};

struct AST_Literal_t {
    union {
        bool bul;
        char chr;
        int64_t i64;
        double f64;
        char *str;
        AST_CommaSepList_t *lst;
        void *any;
    }  data;
    enum AST_DataType_t type;
};

struct AST_Identifier_t {
    char *identifier_name;
};

#endif
