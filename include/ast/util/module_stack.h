#ifndef AST_UTIL_MODULE_STACK_H
#define AST_UTIL_MODULE_STACK_H

#include "ast.h"

/** Push name of current module to module stack.
    Takes ownership of the (AST_Identifier*), and frees on pop */
void AST_ModuleStack_push(AST_Identifier_t *module_name);

/** Function to get the top module name from the stack */
const AST_Identifier_t *AST_ModuleStack_top(void);

/** Pop top module name from stack */
void AST_ModuleStack_pop(void);

/** Empty the stack and free all (AST_Identifier*) */
void AST_ModuleStack_clear(void);

#endif
