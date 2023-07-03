#include "ast.h"

#ifndef AST_SYNTAX_H
#define AST_SYNTAX_H

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
       AST_CompoundSt_t    *compound_statement;
    } statement;
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

AST_Statements_t    *AST_Statements(AST_Statements_t *statements, AST_Statement_t *statement);

AST_Statement_t     *AST_Statement_empty(void);
AST_Statement_t     *AST_Statement_Assignment(AST_Assignment_t *assignment);
AST_Statement_t     *AST_Statement_CompoundSt(AST_CompoundSt_t    *compund);

AST_Assignment_t    *AST_Assignment_create(AST_Identifier_t *identifier, AST_Expression_t *expression);
AST_Assignment_t    *AST_Assignment_update(AST_Identifier_t *identifier, AST_Expression_t *expression);
AST_Assignment_t    *AST_Assignment_tovoid(AST_Expression_t *expression);

AST_CompoundSt_t    *AST_CompoundSt_IfBlock(AST_IfBlock_t *block);
AST_CompoundSt_t    *AST_CompoundSt_WhileBlock(AST_WhileBlock_t *block);
AST_CompoundSt_t    *AST_CompoundSt_ForBlock(AST_ForBlock_t *block);
AST_CompoundSt_t    *AST_CompoundSt_Block(AST_Block_t *block);

AST_IfBlock_t       *AST_IfBlock(AST_Condition_t *condition, AST_Statements_t *if_st, AST_ElseIfBlock_t *else_if_block, AST_Statements_t *else_st);
AST_ElseIfBlock_t   *AST_ElseIfBlock(AST_ElseIfBlock_t *else_if_block, AST_ElseIfSt_t *else_if_st);
AST_ElseIfSt_t      *AST_ElseIfSt(AST_Condition_t *condition, AST_Statements_t *statements);

AST_WhileBlock_t    *AST_WhileBlock(AST_Condition_t *condition, AST_Statements_t *while_st);
AST_ForBlock_t      *AST_ForBlock(AST_Identifier_t *iter, AST_Operand_t *start, AST_Operand_t *end, AST_Operand_t *by, AST_Statements_t *for_st);
AST_Block_t         *AST_Block(AST_Statements_t *statements);

AST_Condition_t     *AST_Condition(AST_Expression_t *expression);

AST_Operand_t       *AST_Operand_Literal(AST_Literal_t *literal);
AST_Operand_t       *AST_Operand_Identifier(AST_Identifier_t *identifier);

AST_Literal_t       *AST_Literal_bul(bool literal);
AST_Literal_t       *AST_Literal_chr(char literal);
AST_Literal_t       *AST_Literal_f64(double literal);
AST_Literal_t       *AST_Literal_i64(int64_t literal);
AST_Literal_t       *AST_Literal_str(char *literal);
AST_Literal_t       *AST_Literal_interp_str(char *literal);

AST_Identifier_t    *AST_Identifier(char *identifier_name);

#endif