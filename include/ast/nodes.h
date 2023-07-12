#ifndef AST_NODES_H
#define AST_NODES_H

#include "lexer.h"
#include "ast.h"
#include "nodes/create.h"
#include "nodes/destroy.h"

struct AST_Statements_t {
    AST_Statements_t *statements;
    AST_Statement_t *statement;
};

enum AST_StatementType_t {
    STATEMENT_TYPE_EMPTY,
    STATEMENT_TYPE_ASSIGNMENT,
    STATEMENT_TYPE_COMPOUND,
};

struct AST_Statement_t {
    union {
       AST_Assignment_t *assignment;
       AST_CompoundSt_t *compound_statement;
    } statement;
    int line_no;
    enum AST_StatementType_t type;
};

enum AST_AssignmentType_t {
    /** Return value of RHS discarded */
    ASSIGNMENT_TYPE_TOVOID,
    /** Create or shadow existing variable */
    ASSIGNMENT_TYPE_CREATE,
    /** Update existing variable */
    ASSIGNMENT_TYPE_UPDATE,
};

struct AST_Assignment_t {
    AST_Identifier_t *lhs;
    AST_Expression_t *rhs;
    enum AST_AssignmentType_t type;
};

enum AST_CompoundStType_t {
    COMPOUNDST_TYPE_IF,
    COMPOUNDST_TYPE_WHILE,
    COMPOUNDST_TYPE_FOR,
    COMPOUNDST_TYPE_BLOCK,
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
    AST_ElseIfBlock_t *else_if_block;
    AST_Statements_t *else_st;
};

struct AST_ElseIfBlock_t {
    AST_ElseIfBlock_t *else_if_block;
    AST_ElseIfSt_t *else_if_st;
};

struct AST_ElseIfSt_t {
    AST_Condition_t *condition;
    AST_Statements_t *statements;
};

struct AST_WhileBlock_t {
    AST_Condition_t *condition;
    AST_Statements_t *statements;
};

enum AST_ForBlockType_t {
    FORBLOCK_TYPE_RANGE,
    FORBLOCK_TYPE_LIST,
};

struct AST_ForBlock_t {
    AST_Identifier_t *iter;
    union {
        struct {
            AST_Operand_t *start;
            AST_Operand_t *end;
            AST_Operand_t *by;
        } range;
        AST_Operand_t *oprnd;
    } iterable;
    AST_Statements_t *statements;
    enum AST_ForBlockType_t type;
};

struct AST_Block_t {
    AST_Statements_t *statements;
};

enum AST_ExpressionType_t {
    EXPR_TYPE_EXPRESSION,
    EXPR_TYPE_OPERAND,
    EXPR_TYPE_LIST,
    EXPR_TYPE_NULL,
};

struct AST_Expression_t {
    AST_Operator_t op;
    /** lhs or if part of ternary expression */
    union {
        AST_Expression_t *expr;
        AST_Operand_t *oprnd;
        AST_CommaSepList_t *lst;
    } lhs;
    enum AST_ExpressionType_t lhs_type;
    /** rhs or else part of ternary expression */
    union {
        AST_Expression_t *expr;
        AST_Operand_t *oprnd;
        AST_CommaSepList_t *lst;
    } rhs;
    enum AST_ExpressionType_t rhs_type;
    /** optional condition for ternary operators,
        set to NULL if not used */
    union {
        AST_Expression_t *expr;
        AST_Operand_t *oprnd;
        AST_CommaSepList_t *lst;
    } condition;
    enum AST_ExpressionType_t condition_type;
};

enum AST_OperandType_t {
    OPERAND_TYPE_LITERAL,
    OPERAND_TYPE_IDENTIFIER,
};

struct AST_CommaSepList_t {
    AST_CommaSepList_t *comma_list;
    AST_Expression_t *expression;
};

struct AST_Operand_t {
    union {
        AST_Literal_t *literal;
        AST_Identifier_t *variable;
    } operand;
    enum AST_OperandType_t type;
};

enum AST_DataType_t {
    DATA_TYPE_BUL,
    DATA_TYPE_CHR,
    DATA_TYPE_I64,
    DATA_TYPE_F64,
    DATA_TYPE_STR,
    DATA_TYPE_INTERP_STR,
    DATA_TYPE_LST,
    DATA_TYPE_ANY,
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
