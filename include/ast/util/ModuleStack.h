#ifndef ast_UTIL_MODULE_STACK_H
#define ast_UTIL_MODULE_STACK_H

#include "ast.h"

/** Push name of current module to module stack.
    Takes ownership of the (ast_Identifier*), and frees on pop */
void ast_ModuleStack_push(ast_Identifier_t *module_name);

/** Function to get the top module name from the stack */
const ast_Identifier_t *ast_ModuleStack_top(void);

/** Pop top module name from stack */
void ast_ModuleStack_pop(void);

/** Empty the stack and free all (ast_Identifier*) */
void ast_ModuleStack_clear(void);

#endif
