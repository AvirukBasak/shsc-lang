#ifndef AST_NODES_DESTROY_H
#define AST_NODES_DESTROY_H

#include "ast.h"

void AST_Statements_free(AST_Statements_t **ptr);
void AST_Statement_free(AST_Statement_t **ptr);
void AST_Assignment_free(AST_Assignment_t **ptr);
void AST_CompoundSt_free(AST_CompoundSt_t **ptr);
void AST_IfBlock_free(AST_IfBlock_t **ptr);
void AST_ElseIfBlock_free(AST_ElseIfBlock_t **ptr);
void AST_ElseIfSt_free(AST_ElseIfSt_t **ptr);
void AST_WhileBlock_free(AST_WhileBlock_t **ptr);
void AST_ForBlock_free(AST_ForBlock_t **ptr);
void AST_Block_free(AST_Block_t **ptr);
void AST_Expression_free(AST_Expression_t **ptr);
void AST_CommaSepList_free(AST_CommaSepList_t **ptr);
void AST_Literal_free(AST_Literal_t **ptr);
void AST_Identifier_free(AST_Identifier_t **ptr);

#endif
