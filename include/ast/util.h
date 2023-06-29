#include "ast.h"

#ifndef ASTFUNCTIONS_H
#define ASTFUNCTIONS_H

/* Modules stack, top stores name of currently parsing module (file) */
void AST_ModuleStack_push(AST_Identifier_t *module);
AST_Identifier_t *AST_ModuleStack_top(void);
AST_Identifier_t *AST_ModuleStack_pop(void);
void AST_ModuleStack_clear(void);

/** Set code to map of procedures */
void AST_ProcedureMap_add(AST_Identifier_t *module, AST_Identifier_t *procedure, AST_Statements_t *code);

/** Get procedure code by module and procedure name */
AST_Statements_t *AST_ProcedureMap_get(AST_Identifier_t *module, AST_Identifier_t *procedure);

/** Clear the map by calling AST_Identifier_free() and AST_Statements_free() on each key and value */
void AST_ProcedureMap_clear();

#endif
