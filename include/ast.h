#ifndef AST_H
#define AST_H

#include <stdbool.h>

typedef struct ast_Statements_t           ast_Statements_t;
typedef struct ast_Statement_t            ast_Statement_t;
typedef struct ast_Assignment_t           ast_Assignment_t;
typedef struct ast_CompoundSt_t           ast_CompoundSt_t;
typedef struct ast_IfBlock_t              ast_IfBlock_t;
typedef struct ast_ElseBlock_t            ast_ElseBlock_t;
typedef struct ast_WhileBlock_t           ast_WhileBlock_t;
typedef struct ast_ForBlock_t             ast_ForBlock_t;
typedef struct ast_Block_t                ast_Block_t;

typedef struct ast_Expression_t           ast_Expression_t;
typedef struct ast_Expression_t           ast_Condition_t;
typedef struct ast_FnArgsList_t           ast_FnArgsList_t;
typedef struct ast_CommaSepList_t         ast_CommaSepList_t;
typedef struct ast_AssociativeList_t      ast_AssociativeList_t;

typedef struct ast_Literal_t              ast_Literal_t;
typedef char                              ast_Identifier_t;

#endif
