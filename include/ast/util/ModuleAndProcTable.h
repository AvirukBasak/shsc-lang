#ifndef AST_UTIL_MODULE_AND_PROC_TABLE_H
#define AST_UTIL_MODULE_AND_PROC_TABLE_H

#include <stdbool.h>

#include "ast.h"
#include "tlib/khash/khash.h"

#define ast_util_MODULEANDPROCTABLE_IDFMAIN "main"

/** A wrapper for procedure (represents a procedure)
    Serves the purpose of storing the (ast_Identifier_t *)
    so that it may be later freed without causing a leak */
typedef struct
{
    char *src_filename;
    ast_Identifier_t *proc_name;
    ast_FnArgsList_t *fnargs_list;
    ast_Statements_t *code;
} ast_util_ModuleAndProcTable_procedure_t;

KHASH_MAP_INIT_STR(ast_procedure_t, ast_util_ModuleAndProcTable_procedure_t)

/** A wrapper for module (represents a module)
    Serves the purpose of storing the (ast_Identifier_t *)
    so that it may be later freed without causing a leak */
typedef struct {
    ast_Identifier_t *module_name;
    khash_t(ast_procedure_t) *procmap;
} ast_util_ModuleAndProcTable_module_t;

KHASH_MAP_INIT_STR(ast_module_t, ast_util_ModuleAndProcTable_module_t)

/** Map of module_name -> module */
typedef khash_t(ast_module_t) *ast_util_ModuleAndProcTable_t;


extern ast_util_ModuleAndProcTable_t ast_util_mptable;

/** Loop over each module */
#define ast_util_ModuleAndProcTable_foreach_module(module_name, procmap, _code) do { \
    if (!ast_util_mptable) break;                                        \
    const ast_Identifier_t *module_name = NULL;                          \
    const khash_t(ast_procedure_t) *procmap = NULL;                      \
    const char *key = NULL;                                              \
    ast_util_ModuleAndProcTable_module_t module;                         \
    kh_foreach(ast_util_mptable, key, module, {                          \
        /* Store the module name and procmap */                          \
        module_name = module.module_name;                                \
        procmap = module.procmap;                                        \
        /* Run user given code */                                        \
        { _code; }                                                       \
    });                                                                  \
} while (0);

/** Loop over each procedure in a module */
#define ast_util_ModuleAndProcTable_foreach_procedure(                   \
    procmap,                                                             \
    proc_name,                                                           \
    filename,                                                            \
    fnargs_list,                                                         \
    code,                                                                \
    _code                                                                \
) do {                                                                   \
    if (!ast_util_mptable) break;                                        \
    const ast_Identifier_t *proc_name = NULL;                            \
    const char *filename = NULL;                                         \
    const ast_FnArgsList_t *fnargs_list = NULL;                          \
    const ast_Statements_t *code = NULL;                                 \
    const char *key = NULL;                                              \
    ast_util_ModuleAndProcTable_procedure_t proc;                        \
    kh_foreach(procmap, key, proc, {                                     \
        proc_name = proc.proc_name;                                      \
        filename = proc.src_filename;                                    \
        fnargs_list = proc.fnargs_list;                                  \
        code = proc.code;                                                \
        { _code; }                                                       \
    });                                                                  \
} while (0);

bool ast_util_ModuleAndProcTable_empty(void);

/** Maps ( module_name, proc_name ) -> code */
void ast_util_ModuleAndProcTable_add(
    const ast_Identifier_t *module_name,
    const ast_Identifier_t *proc_name,
    ast_FnArgsList_t *fnargs_list,
    ast_Statements_t *code
);

/** Get code by a module and a procedure name */
const ast_Statements_t *ast_util_ModuleAndProcTable_get_code(const ast_Identifier_t *module_name, const ast_Identifier_t *proc_name);

/** Get code by a module and a procedure name */
const ast_FnArgsList_t *ast_util_ModuleAndProcTable_get_args(const ast_Identifier_t *module_name, const ast_Identifier_t *proc_name);

/** Get filename by a module and a procedure name */
const char *ast_util_ModuleAndProcTable_get_filename(const ast_Identifier_t *module_name, const ast_Identifier_t *proc_name);

/** Check if a module and a procedure name is defined */
bool ast_util_ModuleAndProcTable_exists(const ast_Identifier_t *module_name, const ast_Identifier_t *proc_name);

/** Throw an error if a module and a procedure name is invalid */
void ast_util_ModuleAndProcTable_erron_invalid(const ast_Identifier_t *module_name, const ast_Identifier_t *proc_name);

/** Clears the entire runtime representation of code,
    i.e. everything the parser generated */
void ast_util_ModuleAndProcTable_clear(void);

#endif
