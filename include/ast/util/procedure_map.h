#ifndef AST_UTIL_PROCEDURE_MAP_H
#define AST_UTIL_PROCEDURE_MAP_H

#include <stdbool.h>
#include "ast.h"

typedef struct {
    struct {
        const AST_Identifier_t *module_name;
        const AST_Identifier_t **lst;
        int proc_cnt;
    } *module;
    int module_cnt;
} AST_ProcedureMapKeyList_t;

bool AST_ProcedureMap_empty(void);

const AST_Identifier_t *AST_ProcedureMap_main(void);

/** Get a list of map keys */
AST_ProcedureMapKeyList_t AST_ProcedureMap_KeyList_get();

/** Free the list of map keys */
void AST_ProcedureMap_KeyList_free(AST_ProcedureMapKeyList_t *ptr);

/** Maps ( module_name, proc_name ) -> code */
void AST_ProcedureMap_add(AST_Identifier_t *module_name, AST_Identifier_t *proc_name, AST_Statements_t *code);

/** Get code by a module and a procedure name */
const AST_Statements_t *AST_ProcedureMap_get_code(const AST_Identifier_t *module_name, const AST_Identifier_t *proc_name);

/** Get filename by a module and a procedure name */
const char *AST_ProcedureMap_get_filename(const AST_Identifier_t *module_name, const AST_Identifier_t *proc_name);

/** Clears the entire runtime representation of code,
    i.e. everything the parser generated */
void AST_ProcedureMap_clear(void);

#endif
