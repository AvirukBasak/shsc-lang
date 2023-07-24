#ifndef AST_UTIL_MODULE_STACK_C_H
#define AST_UTIL_MODULE_STACK_C_H

#include <stdlib.h>
#include "errcodes.h"
#include "ast/nodes.h"
#include "ast/util.h"

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
    ModuleStack_t *new_node = (ModuleStack_t*) malloc(sizeof(ModuleStack_t));
    if (!new_node) parse_throw("AST_ModuleStack_push:" ERR_MSG_MALLOCFAIL);
    new_node->data = module_name;
    new_node->next = top;
    top = new_node;
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
    ModuleStack_t *temp = top;
    const AST_Identifier_t *data = temp->data;
    top = top->next;
    if (AST_ProcedureMap_empty()) {
        AST_Identifier_free((AST_Identifier_t**) &temp->data);
        temp->data = NULL;
        free(temp);
        return NULL;
    }
    free(temp);
    return data;
}

/** Empty the stack (doesn't free the (AST_Identifier*)) */
void AST_ModuleStack_clear(void)
{
    while (top != NULL) {
        ModuleStack_t *temp = top;
        top = top->next;
        temp->data = NULL;
        free(temp);
    }
}

#else
    #warning re-inclusion of module 'ast/util/module_stack.c.h'
#endif
