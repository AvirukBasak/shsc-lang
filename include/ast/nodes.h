#ifndef AST_NODES_H
#define AST_NODES_H

#include "ast.h"
#include "nodes/create.h"
#include "nodes/destroy.h"

struct AST_Statements_t {
    AST_Statements_t *statements;
    AST_Statement_t *statement;
};

enum StatementType {
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
    enum StatementType type;
};

enum AssignmentType {
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
    enum AssignmentType type;
};

enum CompoundStType {
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
   enum CompoundStType type;
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

struct AST_ForBlock_t {
    AST_Identifier_t *iter;
    AST_Operand_t *start;
    AST_Operand_t *end;
    AST_Operand_t *by;
    AST_Statements_t *statements;
};

struct AST_Block_t {
    AST_Statements_t *statements;
};

struct AST_Condition_t {
    AST_Expression_t *expression;
};

/** TODO: Yet to be fully implemented */
struct AST_Expression_t {
    union {
        AST_Operand_t *operand;
        AST_Expression_t *expression;
    } expression;
};

enum OperandType {
    OPERAND_TYPE_LITERAL,
    OPERAND_TYPE_IDENTIFIER,
};

struct AST_Operand_t {
    union {
        AST_Literal_t *literal;
        AST_Identifier_t *variable;
    } operand;
    enum OperandType type;
};

enum DataType {
    DATA_TYPE_BUL,
    DATA_TYPE_CHR,
    DATA_TYPE_I64,
    DATA_TYPE_F64,
    DATA_TYPE_STR,
    DATA_TYPE_INTERP_STR,
    DATA_TYPE_ANY,
};

struct AST_Literal_t {
    union {
        bool bul;
        char chr;
        int64_t i64;
        double f64;
        char *str;
        void *any;
    }  data;
    enum DataType type;
};

struct AST_Identifier_t {
    char *identifier_name;
};

#endif
