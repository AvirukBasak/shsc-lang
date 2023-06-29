#include <stdlib.h>

#include "ast/syntax.h"
#include "ast/syntax/statements.h"

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
