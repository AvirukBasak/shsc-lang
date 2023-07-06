#ifndef AST_UTIL_H
#define AST_UTIL_H

#include "ast.h"

/* Modules stack, top stores name of currently parsing module (file) */
void AST_ModuleStack_push(const AST_Identifier_t *module_name);
const AST_Identifier_t *AST_ModuleStack_top(void);
const AST_Identifier_t *AST_ModuleStack_pop(void);
void AST_ModuleStack_clear(void);

/** Maps ( module_name, proc_name ) -> code */
void AST_ProcedureMap_add(AST_Identifier_t *module_name, AST_Identifier_t *proc_name, AST_Statements_t *code);

/** Get code by a module and a procedure name */
const AST_Statements_t *AST_ProcedureMap_get(const AST_Identifier_t *module_name, const AST_Identifier_t *proc_name);

/** Clears the entire runtime representation of code,
    i.e. everything the parser generated */
void AST_ProcedureMap_clear(void);

#endif
