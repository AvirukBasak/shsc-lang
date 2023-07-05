#ifndef AST_NODES_IDENTIFIER_C_H
#define AST_NODES_IDENTIFIER_C_H

#include <stdlib.h>

#include "ast/nodes.h"
#include "ast/nodes/identifier.h"

void AST_Identifier_free(AST_Identifier_t *identifier)
{
    free(identifier->identifier_name);
    free(identifier);
}

#else
    #warning re-inclusion of module 'ast/nodes/identifier.c.h'
#endif
