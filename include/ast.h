#ifndef AST_H
#define AST_H

#include <inttypes.h>
#include <stdbool.h>

typedef struct AST_Statements_t           AST_Statements_t;
typedef struct AST_Statement_t            AST_Statement_t;
typedef struct AST_Assignment_t           AST_Assignment_t;
typedef struct AST_CompoundSt_t           AST_CompoundSt_t;
typedef struct AST_IfBlock_t              AST_IfBlock_t;
typedef struct AST_ElseIfBlock_t          AST_ElseIfBlock_t;
typedef struct AST_ElseIfSt_t             AST_ElseIfSt_t;
typedef struct AST_WhileBlock_t           AST_WhileBlock_t;
typedef struct AST_ForBlock_t             AST_ForBlock_t;
typedef struct AST_Block_t                AST_Block_t;

typedef struct AST_Expression_t           AST_Expression_t;
typedef struct AST_ConditonalExpr_t       AST_ConditonalExpr_t;
typedef struct AST_PrimaryExpr_t          AST_PrimaryExpr_t;
typedef struct AST_UnaryExpr_t            AST_UnaryExpr_t;
typedef struct AST_BinaryExpr_t           AST_BinaryExpr_t;
typedef struct AST_TernaryExpr_t          AST_TernaryExpr_t;
typedef struct AST_IndexingExpr_t         AST_IndexingExpr_t;
typedef struct AST_FunctionCallExpr_t     AST_FunctionCallExpr_t;
typedef struct AST_ArgumentList_t         AST_ArgumentList_t;
typedef struct AST_MemberAccessExpr_t     AST_MemberAccessExpr_t;
typedef struct AST_PostfixExpr_t          AST_PostfixExpr_t;

typedef struct AST_Operand_t              AST_Operand_t;
typedef struct AST_Literal_t              AST_Literal_t;
typedef struct AST_Identifier_t           AST_Identifier_t;

#endif
