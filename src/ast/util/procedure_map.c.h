/**
 * TO WHOM IT MAY CONCERN
 * A procedure is nothing but `code` of type (AST_Statements_t *)
 * A `module` is defined as a map of ( proc_name, code ), aka a procmap
 * The `ast_modulemap` is defined as map of ( module_name, module )
 * An AST_ProcedureMap_t is (finally) a 2D map which is
    defined as a map of ( module_name, proc_name ) -> code
 */

#ifndef AST_UTIL_PROCEDURE_MAP_C_H
#define AST_UTIL_PROCEDURE_MAP_C_H

#include <stdlib.h>
#include "tlib/khash/khash.h"

#include "ast/nodes.h"
#include "ast/util/procedure_map.h"
#include "parser.h"

/* Define the hash map types */

/** A wrapper for procedure (represents a procedure)
    Serves the purpose of storing the (AST_Identifier_t *)
    so that it may be later freed without causing a leak */
typedef struct
{
    AST_Identifier_t *proc_name;
    AST_Statements_t *code;
} AST_ProcedureMap_procedure_t;

KHASH_MAP_INIT_STR(procedure_t, AST_ProcedureMap_procedure_t)

/** A wrapper for module (represents a module)
    Serves the purpose of storing the (AST_Identifier_t *)
    so that it may be later freed without causing a leak */
typedef struct
{
    AST_Identifier_t *module_name;
    /** One module i.e. map of proc_name -> code */
    khash_t(procedure_t) *procmap;
} AST_ProcedureMap_module_t;

KHASH_MAP_INIT_STR(module_t, AST_ProcedureMap_module_t)

typedef khash_t(module_t) AST_ProcedureMap_t;

/** Map of module_name -> module */
AST_ProcedureMap_t *ast_modulemap = NULL;

/* Function to create a new AST_ProcedureMap_t object */
void AST_ProcedureMap_create(void)
{
    if (ast_modulemap) return;
    ast_modulemap = kh_init(module_t);
}

/** Maps ( module_name, proc_name ) -> code */
void AST_ProcedureMap_add(AST_Identifier_t *module_name, AST_Identifier_t *proc_name, AST_Statements_t *code)
{
    if (!module_name)
        parse_throw("AST_ProcedureMap_add: null pointer error for `module_name`");
    else if (!proc_name)
        parse_throw("AST_ProcedureMap_add: null pointer error for `proc_name`");
    if (!ast_modulemap) AST_ProcedureMap_create();
    int ret;
    khash_t(procedure_t) *procmap;
    /* Check if the module already exists in the top-level map */
    khint_t k = kh_get(module_t, ast_modulemap, module_name->identifier_name);
    if (k == kh_end(ast_modulemap)) {
        /* Create a new sub map if the module does not exist */
        procmap = kh_init(procedure_t);
        k = kh_put(module_t, ast_modulemap, module_name->identifier_name, &ret);
        kh_value(ast_modulemap, k).module_name = module_name;
        kh_value(ast_modulemap, k).procmap = procmap;
    } else {
        /* Get the existing sub map */
        procmap = kh_value(ast_modulemap, k).procmap;
    }
    /* Insert the proc_name and code into the sub map */
    k = kh_put(procedure_t, procmap, proc_name->identifier_name, &ret);
    kh_value(procmap, k).proc_name = proc_name;
    kh_value(procmap, k).code = code;
}

/** Get code by a module and a procedure name */
const AST_Statements_t *AST_ProcedureMap_get(const AST_Identifier_t *module_name, const AST_Identifier_t *proc_name)
{
    if (!ast_modulemap) {
        parse_throw("AST_procedure_get: null pointer error for `ast_modulemap`");
        return NULL;
    } else if (!module_name) {
        parse_throw("AST_procedure_get: null pointer error for `module_name`");
        return NULL;
    } else if (!proc_name) {
        parse_throw("AST_procedure_get: null pointer error for `proc_name`");
        return NULL;
    }
    khash_t(procedure_t) *procmap;
    /* Check if the module exists in the top-level map */
    khint_t k = kh_get(module_t, ast_modulemap, module_name->identifier_name);
    if (k == kh_end(ast_modulemap)) return NULL;
    /* Get the sub map */
    procmap = kh_value(ast_modulemap, k).procmap;
    /* Check if the procedure exists in the sub map */
    k = kh_get(procedure_t, procmap, proc_name->identifier_name);
    if (k == kh_end(procmap)) return NULL;
    /* Return the code associated with the procedure */
    return kh_value(procmap, k).code;
}

/** Clears the entire runtime representation of code,
    i.e. everything the parser generated */
void AST_ProcedureMap_clear(void)
{
    if (!ast_modulemap) return;
    /* Iterate over the top-level map */
    for (khint_t k1 = kh_begin(ast_modulemap); k1 != kh_end(ast_modulemap); ++k1) {
        if (!kh_exist(ast_modulemap, k1)) continue;
        AST_Identifier_free(kh_value(ast_modulemap, k1).module_name);
        khash_t(procedure_t) *procmap = kh_value(ast_modulemap, k1).procmap;
        /* Iterate over the sub map */
        for (khint_t k2 = kh_begin(procmap); k2 != kh_end(procmap); ++k2) {
            if (!kh_exist(procmap, k2)) continue;
            /* Free procedure name and statements */
            AST_Identifier_free(kh_value(procmap, k2).proc_name);
            AST_Statements_free(kh_value(procmap, k2).code);
        }
        kh_destroy(procedure_t, procmap);
    }
    kh_destroy(module_t, ast_modulemap);
    ast_modulemap = NULL;
}

#else
    #warning re-inclusion of module 'ast/util/procedure_map.c.h'
#endif
