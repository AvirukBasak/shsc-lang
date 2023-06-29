#include <stdlib.h>

#include "ast/syntax.h"
#include "ast/syntax/identifier.h"

void AST_Identifier_free(AST_Identifier_t *identifier)
{
    free(identifier->identifier_name);
    free(identifier);
}
