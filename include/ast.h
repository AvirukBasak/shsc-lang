#ifndef AST_H
#define AST_H

#include <inttypes.h>
#include <stdbool.h>

typedef struct AST_Statements_t     AST_Statements_t;
typedef struct AST_Statement_t      AST_Statement_t;
typedef struct AST_Assignment_t     AST_Assignment_t;
typedef struct AST_CompoundSt_t     AST_CompoundSt_t;
typedef struct AST_IfBlock_t        AST_IfBlock_t;
typedef struct AST_IfElseBlock_t    AST_IfElseBlock_t;
typedef struct AST_IfElseIfBlock_t  AST_IfElseIfBlock_t;
typedef struct AST_ElseIfBlock_t    AST_ElseIfBlock_t;
typedef struct AST_WhileBlock_t     AST_WhileBlock_t;
typedef struct AST_ForBlock_t       AST_ForBlock_t;
typedef struct AST_Block_t          AST_Block_t;
typedef struct AST_Condition_t      AST_Condition_t;
typedef struct AST_Expression_t     AST_Expression_t;
typedef struct AST_Operand_t        AST_Operand_t;
typedef struct AST_Literal_t        AST_Literal_t;
typedef struct AST_Identifier_t     AST_Identifier_t;

#endif
