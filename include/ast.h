#ifndef AST_H
#define AST_H

#include <inttypes.h>
#include <stdbool.h>

typedef struct AST_Root                AST_Root;
typedef struct AST_Procedure           AST_Procedure;
typedef struct AST_Statements          AST_Statements;
typedef struct AST_Statement           AST_Statement;
typedef struct AST_Assignment          AST_Assignment;
typedef struct AST_CompoundStatement   AST_CompoundStatement;
typedef struct AST_IfBlock             AST_IfBlock;
typedef struct AST_IfElseBlock         AST_IfElseBlock;
typedef struct AST_IfElseIfBlock       AST_IfElseIfBlock;
typedef struct AST_ElseIfBlock         AST_ElseIfBlock;
typedef struct AST_WhileBlock          AST_WhileBlock;
typedef struct AST_ForBlock            AST_ForBlock;
typedef struct AST_Block               AST_Block;
typedef struct AST_Condition           AST_Condition;
typedef struct AST_Expression          AST_Expression;
typedef struct AST_Operand             AST_Operand;
typedef struct AST_Literal             AST_Literal;
typedef struct AST_Identifier          AST_Identifier;

/** Linked list of multiple procedures */
struct AST_Root {
    AST_Root *head_procedure;
};

struct AST_Procedure {
    AST_Statements *statements;
    /** Generally set to NULL. Useful in case of
        AST_Root which is basically a linked list head */
    AST_Procedure *next_procedure;
};

/** Linked list of multiple statements */
struct AST_Statements {
    AST_Statement *head_statement;
};

struct AST_Statement {
    /** If both NULL, it indicates an empty statement */
    union {
       AST_Assignment *assignment;
       AST_CompoundStatement *compound_statement;
    } statement;
    /** Generally set to NULL. Useful in case of
        AST_Statements which is basically a linked list head */
    AST_Statement *next_statement;
};

enum AssignmentType {
    /** Return value of RHS discarded */
    ASSIGNMENTTYPE_TOVOID,
    /** Create or shadow existing variable */
    ASSIGNMENTTYPE_CREATE,
    /** Update existing variable */
    ASSIGNMENTTYPE_UPDATE,
};

struct AST_Assignment {
    AST_Identifier *lhs;
    AST_Expression *rhs;
    enum AssignmentType type;
};

struct AST_CompoundStatement {
    union {
        AST_IfBlock *if_block;
        AST_IfElseBlock *if_else_block;
        AST_IfElseIfBlock *if_else_if_block;
        AST_WhileBlock *while_block;
        AST_ForBlock *for_block;
        AST_Block *block;
    } compound_statement;
};

struct AST_IfBlock {
    AST_Condition *condition;
    AST_Statements *statements;
};

struct AST_IfElseBlock {
    AST_Condition *condition;
    AST_Statements *if_statements;
    AST_Statements *else_statements;
};

struct AST_IfElseIfBlock {
    AST_Condition *condition;
    AST_Statements *if_statements;
    AST_ElseIfBlock *else_if_block;
};

struct AST_ElseIfBlock {
    /** Set to NULL if ladder ends */
    AST_IfElseIfBlock *if_else_if_block;
};

struct AST_WhileBlock {
    AST_Condition *condition;
    AST_Statements *statements;
};

struct AST_ForBlock {
    AST_Identifier *iterator;
    AST_Operand *start;
    AST_Operand *end;
    AST_Statements *statements;
};

struct AST_Block {
    AST_Statements *statements;
};

struct AST_Condition {
    AST_Expression *expression;
};

/** TODO: Yet to be fully implemented */
struct AST_Expression {
    union {
        AST_Operand *operand;
        AST_Expression *expression;
    } expression;
};

enum OperandType {
    OPERANDTYPE_LITERAL,
    OPERANDTYPE_VARIABLE,
};

struct AST_Operand {
    union {
        AST_Literal *literal;
        AST_Identifier *variable;
    } operand;
    enum OperandType type;
};

enum DataType {
    DATATYPE_BUL,
    DATATYPE_CHR,
    DATATYPE_I64,
    DATATYPE_F64,
    DATATYPE_STR,
    DATATYPE_ANY,
};

struct AST_Literal {
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

struct AST_Identifier {
    char *identifier_name;
    enum DataType type;
};

#endif
