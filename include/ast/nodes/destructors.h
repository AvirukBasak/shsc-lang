#ifndef AST_NODES_DESTRUCTORS_H
#define AST_NODES_DESTRUCTORS_H

#include "ast.h"

void AST_Statements_destroy(AST_Statements_t **ptr);
void AST_Statement_destroy(AST_Statement_t **ptr);
void AST_Assignment_destroy(AST_Assignment_t **ptr);
void AST_CompoundSt_destroy(AST_CompoundSt_t **ptr);
void AST_IfBlock_destroy(AST_IfBlock_t **ptr);
void AST_ElseBlock_destroy(AST_ElseBlock_t **ptr);
void AST_WhileBlock_destroy(AST_WhileBlock_t **ptr);
void AST_ForBlock_destroy(AST_ForBlock_t **ptr);
void AST_Block_destroy(AST_Block_t **ptr);
void AST_Expression_destroy(AST_Expression_t **ptr);
void AST_CommaSepList_destroy(AST_CommaSepList_t **ptr);
void AST_AssociativeList_destroy(AST_AssociativeList_t **ptr);
void AST_Literal_destroy(AST_Literal_t **ptr);
void AST_Identifier_destroy(AST_Identifier_t **ptr);

#endif
