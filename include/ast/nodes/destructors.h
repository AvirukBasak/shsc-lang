#ifndef AST_NODES_DESTRUCTORS_H
#define AST_NODES_DESTRUCTORS_H

#include "ast.h"

void ast_Statements_destroy(ast_Statements_t **ptr);
void ast_Statement_destroy(ast_Statement_t **ptr);
void ast_Assignment_destroy(ast_Assignment_t **ptr);
void ast_CompoundSt_destroy(ast_CompoundSt_t **ptr);
void ast_IfBlock_destroy(ast_IfBlock_t **ptr);
void ast_ElseBlock_destroy(ast_ElseBlock_t **ptr);
void ast_WhileBlock_destroy(ast_WhileBlock_t **ptr);
void ast_ForBlock_destroy(ast_ForBlock_t **ptr);
void ast_Block_destroy(ast_Block_t **ptr);
void ast_Expression_destroy(ast_Expression_t **ptr);
void ast_FnArgsList_destroy(ast_FnArgsList_t **ptr);
void ast_CommaSepList_destroy(ast_CommaSepList_t **ptr);
void ast_AssociativeList_destroy(ast_AssociativeList_t **ptr);
void ast_Literal_destroy(ast_Literal_t **ptr);
void ast_Identifier_destroy(ast_Identifier_t **ptr);

#endif
