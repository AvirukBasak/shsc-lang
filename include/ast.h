#ifndef AST_H
#define AST_H

#include <inttypes.h>
#include <stdbool.h>

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
    // TODO: 2D Hash map mapping module names & procedure names to (AST_Statements*)
};

struct AST_Statements {
    AST_Statements *statements;
    AST_Statement *statement;
};

enum StatementType {
    STATEMENT_TYPE_EMPTY,
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
    AST_Identifier *iter;
    AST_Operand *start;
    AST_Operand *end;
    AST_Operand *by;
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
    OPERAND_TYPE_IDENTIFIER,
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
    DATA_TYPE_INTERP_STR,
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

/* Modules stack, top stores name of currently parsing module (file) */
void AST_module_stack_push(AST_Identifier *module_name);
AST_Identifier *AST_module_stack_top(void);
AST_Identifier *AST_module_stack_pop(void);
void AST_module_stack_clear(void);

/** Adds currently parsing procedure to currently parsing module (map data structure) */
void AST_procedure_add(AST_Identifier *module_name, AST_Identifier *procedure_name, AST_Statements *statements);

AST_Statements        *AST_statements(AST_Statements *statements, AST_Statement *statement);
AST_Statement         *AST_statement_empty(void);
AST_Statement         *AST_statement_assignment(AST_Assignment *assignment);
AST_Statement         *AST_statement_compound(AST_CompoundStatement *compund);
AST_Assignment        *AST_assignment_create(AST_Identifier *identifier, AST_Expression *expression);
AST_Assignment        *AST_assignment_update(AST_Identifier *identifier, AST_Expression *expression);
AST_Assignment        *AST_assignment_tovoid(AST_Expression *expression);
AST_CompoundStatement *AST_compoundst_if_block(AST_IfBlock *block);
AST_CompoundStatement *AST_compoundst_if_else_block(AST_IfElseBlock *block);
AST_CompoundStatement *AST_compoundst_if_else_if_block(AST_IfElseIfBlock *block);
AST_CompoundStatement *AST_compoundst_while_block(AST_WhileBlock *block);
AST_CompoundStatement *AST_compoundst_for_block(AST_ForBlock *block);
AST_CompoundStatement *AST_compoundst_block(AST_Block *block);
AST_IfBlock           *AST_if_block(AST_Condition *condition, AST_Statements *if_st);
AST_IfElseBlock       *AST_if_else_block(AST_Condition *condition, AST_Statements *if_st, AST_Statements *else_st);
AST_IfElseIfBlock     *AST_if_else_if_block(AST_Condition *condition, AST_Statements *if_st, AST_ElseIfBlock *block);
AST_ElseIfBlock       *AST_else_if_block(AST_IfElseIfBlock *block);
AST_WhileBlock        *AST_while_block(AST_Condition *condition, AST_Statements *while_st);
AST_ForBlock          *AST_for_block(AST_Identifier *iter, AST_Operand *start, AST_Operand *end, AST_Operand *by, AST_Statements *for_st);
AST_Block             *AST_block(AST_Statements *statements);
AST_Condition         *AST_condition(AST_Expression *expression);
AST_Operand           *AST_operand_literal(AST_Literal *literal);
AST_Operand           *AST_operand_identifier(AST_Identifier *identifier);
AST_Literal           *AST_literal_bul(bool literal);
AST_Literal           *AST_literal_chr(char literal);
AST_Literal           *AST_literal_f64(double literal);
AST_Literal           *AST_literal_i64(int64_t literal);
AST_Literal           *AST_literal_str(char *literal);
AST_Literal           *AST_literal_interp_str(char *literal);
AST_Identifier        *AST_identifier(char *identifier_name);

#endif
