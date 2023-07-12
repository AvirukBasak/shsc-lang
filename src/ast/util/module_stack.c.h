#ifndef AST_UTIL_MODULE_STACK_C_H
#define AST_UTIL_MODULE_STACK_C_H

#include <stdlib.h>
#include "ast/nodes.h"
#include "ast/util/module_stack.h"

typedef struct ModuleStack_t ModuleStack_t;

struct ModuleStack_t {
    const AST_Identifier_t *data;
    ModuleStack_t *next;
};

// Global variable representing the top of the stack
struct ModuleStack_t *top = NULL;

/** Push name of current module to module stack */
void AST_ModuleStack_push(const AST_Identifier_t *module_name)
{
    ModuleStack_t *newNode = (ModuleStack_t*) malloc(sizeof(ModuleStack_t));
    newNode->data = module_name;
    newNode->next = top;
    top = newNode;
}

/** Function to get the top module name from the stack */
const AST_Identifier_t *AST_ModuleStack_top(void)
{
    if (top == NULL) return NULL;
    return top->data;
}

/** Pop top module name from stack */
const AST_Identifier_t *AST_ModuleStack_pop(void)
{
    if (top == NULL) return NULL;
    const AST_Identifier_t *poppedData = top->data;
    ModuleStack_t *temp = top;
    top = top->next;
    free(temp);
    return poppedData;
}

/** Empty the stack (doesn't free the (AST_Identifier*)) */
void AST_ModuleStack_clear(void)
{
    while (top != NULL) {
        ModuleStack_t *temp = top;
        top = top->next;
        free(temp);
    }
}

#else
    #warning re-inclusion of module 'ast/util/module_stack.c.h'
#endif
