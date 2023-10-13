#ifndef AST_UTIL_MODULE_STACK_C_H
#define AST_UTIL_MODULE_STACK_C_H

#include <stdlib.h>

#include "ast.h"
#include "ast/nodes/destroy.h"
#include "ast/util/procedure_map.h"
#include "errcodes.h"
#include "io.h"

typedef struct ast_ModuleStack_t ast_ModuleStack_t;
struct ast_ModuleStack_t {
    AST_Identifier_t *data;
    ast_ModuleStack_t *next;
};

// Global variable representing the top of the stack
ast_ModuleStack_t *ast_modstack_top = NULL;

/** Push name of current module to module stack.
    Takes ownership of the (AST_Identifier*), and frees on pop */
void AST_ModuleStack_push(AST_Identifier_t *module_name)
{
    ast_ModuleStack_t *new_node = (ast_ModuleStack_t*) malloc(sizeof(ast_ModuleStack_t));
    if (!new_node) io_errndie("AST_ModuleStack_push:" ERR_MSG_MALLOCFAIL);
    new_node->data = module_name;
    new_node->next = ast_modstack_top;
    ast_modstack_top = new_node;
}

/** Function to get the top module name from the stack */
const AST_Identifier_t *AST_ModuleStack_top(void)
{
    if (ast_modstack_top == NULL) return NULL;
    return ast_modstack_top->data;
}

/** Pop top module name from stack */
void AST_ModuleStack_pop(void)
{
    if (ast_modstack_top == NULL) return;
    ast_ModuleStack_t *temp = ast_modstack_top;
    ast_modstack_top = ast_modstack_top->next;
    AST_Identifier_free(&temp->data);
    temp->data = NULL;
    free(temp);
}

/** Empty the stack and free all (AST_Identifier*) */
void AST_ModuleStack_clear(void)
{
    while (ast_modstack_top != NULL) {
        ast_ModuleStack_t *temp = ast_modstack_top;
        ast_modstack_top = ast_modstack_top->next;
        AST_Identifier_free(&temp->data);
        temp->data = NULL;
        free(temp);
    }
}

#else
    #warning re-inclusion of module 'ast/util/module_stack.c.h'
#endif
