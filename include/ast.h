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

struct AST_Root {
    AST_Procedure *procedure;
    AST_Root *program;
};

struct AST_Procedure {
    AST_Identifier *procedure_name;
    AST_Statements *statements;
};

struct AST_Statements {
    AST_Statement *statement;
    AST_Statements *statements;
};

enum StatementType {
    STATEMENT_TYPE_ASSIGNMENT,
    STATEMENT_TYPE_COMPOUND,
};

struct AST_Statement {
    union {
       AST_Assignment *assignment;
       AST_CompoundStatement *compound_statement;
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

struct AST_Assignment {
    AST_Identifier *lhs;
    AST_Expression *rhs;
    enum AssignmentType type;
};

enum CompoundStatementType {
    COMPOUNDST_TYPE_IF,
    COMPOUNDST_TYPE_IF_ELSE,
    COMPOUNDST_TYPE_IF_ELSE_IF,
    COMPOUNDST_TYPE_WHILE,
    COMPOUNDST_TYPE_FOR,
    COMPOUNDST_TYPE_BLOCK,
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
   enum CompoundStatementType type;
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
    OPERAND_TYPE_LITERAL,
    OPERAND_TYPE_VARIABLE,
};

struct AST_Operand {
    union {
        AST_Literal *literal;
        AST_Identifier *variable;
    } operand;
    enum OperandType type;
};

enum DataType {
    DATA_TYPE_BUL,
    DATA_TYPE_CHR,
    DATA_TYPE_I64,
    DATA_TYPE_F64,
    DATA_TYPE_STR,
    DATA_TYPE_ANY,
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
};

#endif

#ifndef ASTFUNCTIONS_H
#define ASTFUNCTIONS_H

AST_program($1, NULL);
AST_program($1, $2);
AST_procedure($2, $5);
AST_statements($1, NULL);
AST_statements($1, $2);
AST_statement_empty();
AST_statement_assignment($1);
AST_statement_compound($1);
AST_assignment_create($2, $4);
AST_assignment_update($2, $4);
AST_assignment_tovoid($1);
AST_compoundst_if_block($1);
AST_compoundst_if_else_block($1);
AST_compoundst_if_else_if_block($1);
AST_compoundst_while_block($1);
AST_compoundst_for_block($1);
AST_compoundst_block($1);
AST_if_block($2, $5);
AST_if_else_block($2, $5, $7);
AST_if_else_if_block($2, $5, $6);
AST_else_if_block($2);
AST_else_if_block(NULL);
AST_while_block($2, $5);
AST_for_block($2, $4, $6, $8);
AST_block($2);
AST_condition($1);
AST_literal_bul($1);
AST_literal_chr($1);
AST_literal_f64($1);
AST_literal_i64($1);
AST_literal_str($1);
AST_identifier($1);

#endif
