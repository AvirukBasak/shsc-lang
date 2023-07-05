#ifndef AST_NODES_STATEMENTS_C_H
#define AST_NODES_STATEMENTS_C_H

#include <stdlib.h>

#include "ast/nodes.h"
#include "ast/nodes/statements.h"

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

#else
    #warning re-inclusion of module 'ast/nodes/statements.c.h'
#endif
