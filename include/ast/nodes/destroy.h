#ifndef AST_NODES_DESTROY_H
#define AST_NODES_DESTROY_H

#include "ast.h"

void AST_Statements_free(AST_Statements_t *statements);
void AST_Identifier_free(AST_Identifier_t *identifier);

#endif
