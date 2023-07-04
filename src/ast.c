#include <stdlib.h>
#include "ast.h"

#include "ast/syntax/identifier.c.h"
#include "ast/syntax/statements.c.h"
#include "ast/modules.c.h"
#include "ast/syntax.c.h"

typedef struct ModuleStack_t ModuleStack_t;

struct ModuleStack_t {
    const AST_Identifier_t *data;
    ModuleStack_t *next;
};

// Global variable representing the top of the stack
struct ModuleStack_t *top = NULL;

// Function to push an AST identifier onto the stack
void AST_ModuleStack_push(const AST_Identifier_t *module_name)
{
    ModuleStack_t *newNode = (ModuleStack_t*) malloc(sizeof(ModuleStack_t));
    newNode->data = module_name;
    newNode->next = top;
    top = newNode;
}

// Function to get the top AST identifier from the stack
const AST_Identifier_t *AST_ModuleStack_top(void)
{
    if (top == NULL) return NULL;
    return top->data;
}

// Function to pop the top AST identifier from the stack
const AST_Identifier_t *AST_ModuleStack_pop(void)
{
    if (top == NULL) return NULL;
    const AST_Identifier_t *poppedData = top->data;
    ModuleStack_t *temp = top;
    top = top->next;
    free(temp);
    return poppedData;
}

// Function to clear the stack
void AST_ModuleStack_clear(void)
{
    while (top != NULL) {
        ModuleStack_t *temp = top;
        top = top->next;
        free(temp);
    }
}
