#ifdef AST_NODES_H
    #error either of 'ast/api.h' or 'ast/nodes.h' should be included
#endif

#ifndef AST_API_H
#define AST_API_H

#include <stdbool.h>

/* the following includes are absolutely needed as this
   file acts as an all-in-one header for all ast functions
   - #include "ast.h"
   - #include "lexer.h"
   - #include "nodes/constructors.h"
   - #include "nodes/destructors.h"
   - #include "nodes/enums.h"
   - #include "util/ModuleStack.h"
   - #include "util/ModuleAndProcTable.h"
   even if your IDE screams of unused-includes, DO NOT remove them */

#include "ast.h"
#include "lexer.h"
#include "ast/nodes/constructors.h"
#include "ast/nodes/destructors.h"
#include "ast/nodes/enums.h"
#include "ast/util/ModuleStack.h"
#include "ast/util/ModuleAndProcTable.h"

typedef lex_Token_t ast_Operator_t;

struct ast_Statements_t {
    const ast_Statements_t *statements;
    const ast_Statement_t *statement;
};

struct ast_Statement_t {
    const union {
       const ast_Expression_t *expression;
       const ast_Assignment_t *assignment;
       const ast_CompoundSt_t *compound_statement;
    } statement;
    const int line_no;
    const enum ast_StatementType_t type;
};

struct ast_Assignment_t {
    const ast_Identifier_t *lhs;
    const ast_Expression_t *rhs;
    const bool is_const;
    const bool is_weak;
    const enum ast_AssignmentType_t type;
};

struct ast_CompoundSt_t {
    const union {
        const ast_IfBlock_t *if_block;
        const ast_WhileBlock_t *while_block;
        const ast_ForBlock_t *for_block;
        const ast_Block_t *block;
    } compound_statement;
    const enum ast_CompoundStType_t type;
};

struct ast_IfBlock_t {
    const ast_Condition_t *condition;
    const ast_Statements_t *if_st;
    const ast_ElseBlock_t *else_block;
};

struct ast_ElseBlock_t {
    /** if condition is not NULL, it's an
        else if block, otherwise it's an else block */
    const ast_Condition_t *condition;
    /** if condition is NULL, it's an else block
        else it's an if else block */
    const ast_Statements_t *else_if_st;
    const ast_ElseBlock_t *else_block;
};

struct ast_WhileBlock_t {
    const ast_Condition_t *condition;
    const ast_Statements_t *statements;
};

struct ast_ForBlock_t {
    const ast_Identifier_t *idx;
    const ast_Identifier_t *val;
    const union {
        const struct {
            const ast_Expression_t *start;
            const ast_Expression_t *end;
            const ast_Expression_t *by;
        } range;
        const ast_Expression_t *iterable;
    } it;
    const ast_Statements_t *statements;
    const enum ast_ForBlockType_t type;
};

struct ast_Block_t {
    const ast_Statements_t *statements;
};

union ast_ExpressionUnion_t {
    const ast_Expression_t *expr;
    const ast_Literal_t *literal;
    const ast_Identifier_t *variable;
};

struct ast_Expression_t {
    ast_Operator_t op;
    /** lhs or if part of ternary expression */
    const union ast_ExpressionUnion_t lhs;
    const enum ast_ExpressionType_t lhs_type;
    /** rhs or else part of ternary expression */
    const union ast_ExpressionUnion_t rhs;
    const enum ast_ExpressionType_t rhs_type;
    /** optional condition for ternary operators,
        set to NULL if not used */
    const union ast_ExpressionUnion_t condition;
    const enum ast_ExpressionType_t condition_type;
};

struct ast_FnArgsList_t {
    const ast_FnArgsList_t *args_list;
    const ast_Identifier_t *identifier;
};

struct ast_CommaSepList_t {
    const ast_CommaSepList_t *comma_list;
    const ast_Expression_t *expression;
};

struct ast_AssociativeList_t {
    ast_AssociativeList_t *assoc_list;
    ast_Literal_t *key;
    ast_Expression_t *value;
};

struct ast_LambdaLiteral_nonnative_t {
    const ast_FnArgsList_t *args_list;
    const union {
        const ast_Statements_t *statements;
        const ast_Expression_t *expression;
    } body;
    /**
     * if true, the lambda is an expression
     * if false, the lambda is a block of statements
     */
    const bool is_expr;
};

struct ast_LambdaLiteral_t {
    const union {
        const ast_LambdaLiteral_nonnative_t *nonnative;
        const void *native;
    } fnptr;
    const ast_Identifier_t *module_name;
    const char *file_name;
    const enum ast_LambdaLiteralType_t type;
};

struct ast_Literal_t {
    union {
        const bool bul;
        const char chr;
        const int64_t i64;
        const double f64;
        const char *str;
        const ast_CommaSepList_t *lst;
        const ast_AssociativeList_t *mp;
        const ast_LambdaLiteral_t *lambda;
        const void *any;
    }  data;
    const enum ast_DataType_t type;
};

#endif
