#ifndef AST_UTIL_MODULE_STACK_H
#define AST_UTIL_MODULE_STACK_H

#include "ast.h"

/** Push name of current module to module stack.
    Doesn't take ownership of the (AST_Identifier*), so it can't free it */
void AST_ModuleStack_push(const AST_Identifier_t *module_name);

/** Function to get the top module name from the stack */
const AST_Identifier_t *AST_ModuleStack_top(void);

/** Pop top module name from stack */
const AST_Identifier_t *AST_ModuleStack_pop(void);

/** Empty the stack (doesn't free the (AST_Identifier*)) */
void AST_ModuleStack_clear(void);

#endif
