#ifndef AST_UTIL_PROCEDURE_MAP_H
#define AST_UTIL_PROCEDURE_MAP_H

#include <stdbool.h>
#include "ast.h"
#include "tlib/khash/khash.h"

/** A wrapper for procedure (represents a procedure)
    Serves the purpose of storing the (AST_Identifier_t *)
    so that it may be later freed without causing a leak */
typedef struct
{
    char *src_filename;
    char *procname;
    AST_Statements_t *code;
} ast_ProcedureMap_procedure_t;

KHASH_MAP_INIT_STR(procedure_t, ast_ProcedureMap_procedure_t)

/** A wrapper for module (represents a module)
    Serves the purpose of storing the (AST_Identifier_t *)
    so that it may be later freed without causing a leak */
typedef struct {
    char *modulename;
    khash_t(procedure_t) *procmap;
} ast_ProcedureMap_module_t;

KHASH_MAP_INIT_STR(module_t, ast_ProcedureMap_module_t)

/** Map of module_name -> module */
typedef khash_t(module_t) *ast_ProcedureMap_t;
extern ast_ProcedureMap_t ast_procedure_map;

/** Loop over each module */
#define AST_ProcedureMap_foreach_module(modulename, procmap, _code) do { \
    if (!ast_procedure_map) break;                                       \
    const char *modulename = NULL;                                       \
    const khash_t(procedure_t) *procmap = NULL;                          \
    const char *key = NULL;                                              \
    ast_ProcedureMap_module_t module;                                    \
    kh_foreach(ast_procedure_map, key, module, {                         \
        /* Store the module name and procmap */                          \
        modulename = module.modulename;                                  \
        procmap = module.procmap;                                        \
        /* Run user given code */                                        \
        { _code; }                                                       \
    });                                                                  \
} while (0);

/** Loop over each procedure in a module */
#define AST_ProcedureMap_foreach_procedure(procmap, procname, filename, code, _code) do { \
    if (!ast_procedure_map) break;                                       \
    const char *procname = NULL;                                         \
    const char *filename = NULL;                                         \
    const AST_Statements_t *code = NULL;                                 \
    const char *key = NULL;                                              \
    ast_ProcedureMap_procedure_t proc;                                   \
    kh_foreach(procmap, key, proc, {                                     \
        procname = proc.procname;                                        \
        filename = proc.src_filename;                                    \
        code = proc.code;                                                \
        { _code; }                                                       \
    });                                                                  \
} while (0);

bool AST_ProcedureMap_empty(void);

const AST_Identifier_t *AST_ProcedureMap_idfmain(void);

/** Maps ( module_name, proc_name ) -> code */
void AST_ProcedureMap_add(const AST_Identifier_t *module_name, const AST_Identifier_t *proc_name, AST_Statements_t *code);

/** Get code by a module and a procedure name */
const AST_Statements_t *AST_ProcedureMap_get_code(const AST_Identifier_t *module_name, const AST_Identifier_t *proc_name);

/** Get filename by a module and a procedure name */
const char *AST_ProcedureMap_get_filename(const AST_Identifier_t *module_name, const AST_Identifier_t *proc_name);

/** Clears the entire runtime representation of code,
    i.e. everything the parser generated */
void AST_ProcedureMap_clear(void);

#endif
