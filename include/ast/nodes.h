#ifndef AST_NODES_H
#define AST_NODES_H

/* the following includes are absolutely needed
   - #include "ast.h"
   - #include "lexer.h"
   - #include "nodes/create.h"
   - #include "nodes/destroy.h"
   - #include "nodes/enums.h"
   even if your IDE screams of unused-includes, DO NOT remove them */

#include "ast.h"
#include "lexer.h"
#include "ast/nodes/constructors.h"
#include "ast/nodes/destructors.h"
#include "ast/nodes/enums.h"

typedef lex_Token_t ast_Operator_t;

struct ast_Statements_t {
    ast_Statements_t *statements;
    ast_Statement_t *statement;
};

struct ast_Statement_t {
    union {
       ast_Expression_t *expression;
       ast_Assignment_t *assignment;
       ast_CompoundSt_t *compound_statement;
    } statement;
    int line_no;
    enum ast_StatementType_t type;
};

struct ast_Assignment_t {
    ast_Identifier_t *lhs;
    ast_Expression_t *rhs;
    enum ast_AssignmentType_t type;
};

struct ast_CompoundSt_t {
    union {
        ast_IfBlock_t *if_block;
        ast_WhileBlock_t *while_block;
        ast_ForBlock_t *for_block;
        ast_Block_t *block;
    } compound_statement;
   enum ast_CompoundStType_t type;
};

struct ast_IfBlock_t {
    ast_Condition_t *condition;
    ast_Statements_t *if_st;
    ast_ElseBlock_t *else_block;
};

struct ast_ElseBlock_t {
    /** if condition is not NULL, it's an
        else if block, otherwise it's an else block */
    ast_Condition_t *condition;
    /** if condition is NULL, it's an else block
        else it's an if else block */
    ast_Statements_t *else_if_st;
    ast_ElseBlock_t *else_block;
};

struct ast_WhileBlock_t {
    ast_Condition_t *condition;
    ast_Statements_t *statements;
};

struct ast_ForBlock_t {
    ast_Identifier_t *idx;
    ast_Identifier_t *val;
    union {
        struct {
            ast_Expression_t *start;
            ast_Expression_t *end;
            ast_Expression_t *by;
        } range;
        ast_Expression_t *iterable;
    } it;
    ast_Statements_t *statements;
    enum ast_ForBlockType_t type;
};

struct ast_Block_t {
    ast_Statements_t *statements;
};

union ast_ExpressionUnion_t {
    ast_Expression_t *expr;
    ast_Literal_t *literal;
    ast_Identifier_t *variable;
    ast_CommaSepList_t *lst;
};

struct ast_Expression_t {
    ast_Operator_t op;
    /** lhs or if part of ternary expression */
    union ast_ExpressionUnion_t lhs;
    enum ast_ExpressionType_t lhs_type;
    /** rhs or else part of ternary expression */
    union ast_ExpressionUnion_t rhs;
    enum ast_ExpressionType_t rhs_type;
    /** optional condition for ternary operators,
        set to NULL if not used */
    union ast_ExpressionUnion_t condition;
    enum ast_ExpressionType_t condition_type;
};

struct ast_CommaSepList_t {
    ast_CommaSepList_t *comma_list;
    ast_Expression_t *expression;
};

struct ast_AssociativeList_t {
    ast_AssociativeList_t *assoc_list;
    ast_Literal_t *key;
    ast_Expression_t *value;
};

struct ast_Literal_t {
    union {
        bool bul;
        char chr;
        int64_t i64;
        double f64;
        char *str;
        ast_CommaSepList_t *lst;
        ast_AssociativeList_t *mp;
        void *any;
    }  data;
    enum ast_DataType_t type;
};

struct ast_Identifier_t {
    char *identifier_name;
};

#endif
