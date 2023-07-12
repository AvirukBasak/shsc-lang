#ifndef AST_NODES_DESTROY_C_H
#define AST_NODES_DESTROY_C_H

#include <stdlib.h>
#include "ast/nodes.h"

void AST_Statements_free(AST_Statements_t *statements)
{
    AST_Statements_t *node = statements;
    while (node) {
        // TODO: AST_Statement_free(node->statement);
        free(node->statement);
        AST_Statements_t *tmp = node;
        node = node->statements;
        free(tmp);
    }
}

void AST_Identifier_free(AST_Identifier_t *identifier)
{
    free(identifier->identifier_name);
    free(identifier);
}

#else
    #warning re-inclusion of module 'ast/nodes/destroy.c.h'
#endif
