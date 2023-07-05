#ifndef AST_UTIL_PROCEDURE_MAP_C_H
#define AST_UTIL_PROCEDURE_MAP_C_H

#include <stdlib.h>
#include "tlib/khash/khash.h"

#include "ast/nodes.h"
#include "ast/util.h"
#include "parser.h"

// Define the hash map types
KHASH_MAP_INIT_STR(procedure_t, const AST_Statements_t*)
KHASH_MAP_INIT_STR(module_t, khash_t(procedure_t)*)

// AST_ProcedureMap_t structure
typedef struct
{
    khash_t(module_t) *map;
} AST_ProcedureMap_t;

// Global AST_ProcedureMap_t object
AST_ProcedureMap_t *ast_procmap_root = NULL;

// Function to create a new AST_ProcedureMap_t object
void AST_ProcedureMap_create(void)
{
    ast_procmap_root = (AST_ProcedureMap_t*) malloc(sizeof(AST_ProcedureMap_t));
    ast_procmap_root->map = kh_init(module_t);
}

/** Set code to map of procedures */
void AST_ProcedureMap_add(const AST_Identifier_t *module, const AST_Identifier_t *procedure, const AST_Statements_t *code)
{
    if (!module)
        parse_throw("AST_ProcedureMap_add: null pointer error for `module`");
    else if (!procedure)
        parse_throw("AST_ProcedureMap_add: null pointer error for `procedure`");
    if (!ast_procmap_root) AST_ProcedureMap_create();
    int ret;
    khash_t(procedure_t) *submap;
    // Check if the module already exists in the top-level map
    khint_t k = kh_get(module_t, ast_procmap_root->map, module->identifier_name);
    if (k == kh_end(ast_procmap_root->map)) {
        // Create a new sub map if the module does not exist
        submap = kh_init(procedure_t);
        k = kh_put(module_t, ast_procmap_root->map, module->identifier_name, &ret);
        kh_value(ast_procmap_root->map, k) = submap;
    } else {
        // Get the existing sub map
        submap = kh_value(ast_procmap_root->map, k);
    }
    // Insert the procedure_name and code into the sub map
    k = kh_put(procedure_t, submap, procedure->identifier_name, &ret);
    kh_value(submap, k) = code;
}

/** Get procedure code by module and procedure name */
const AST_Statements_t *AST_ProcedureMap_get(const AST_Identifier_t *module, const AST_Identifier_t *procedure)
{
    if (!ast_procmap_root) {
        parse_throw("AST_procedure_get: null pointer error for `ast_procmap_root`");
        return NULL;
    } else if (!module) {
        parse_throw("AST_procedure_get: null pointer error for `module`");
        return NULL;
    } else if (!procedure) {
        parse_throw("AST_procedure_get: null pointer error for `procedure`");
        return NULL;
    }
    khash_t(procedure_t) *submap;
    // Check if the module exists in the top-level map
    khint_t k = kh_get(module_t, ast_procmap_root->map, module->identifier_name);
    if (k == kh_end(ast_procmap_root->map)) return NULL;
    // Get the sub map
    submap = kh_value(ast_procmap_root->map, k);
    // Check if the procedure exists in the sub map
    k = kh_get(procedure_t, submap, procedure->identifier_name);
    if (k == kh_end(submap)) return NULL;
    // Return the code associated with the procedure
    return kh_value(submap, k);
}

/** Clear the map by calling AST_Identifier_free() and AST_Statements_free() on each key and value */
void AST_ProcedureMap_clear(void)
{
    if (!ast_procmap_root) return;
    khash_t(procedure_t) *submap = NULL;
    // Iterate over the top-level map
    for (khint_t k1 = kh_begin(ast_procmap_root->map); k1 != kh_end(ast_procmap_root->map); ++k1) {
        if (!kh_exist(ast_procmap_root->map, k1)) continue;
        submap = kh_value(ast_procmap_root->map, k1);
        // Iterate over the sub map
        for (khint_t k2 = kh_begin(submap); k2 != kh_end(submap); ++k2) {
            if (!kh_exist(submap, k2)) continue;
            // Free procedure name and statements
            free((void*) kh_key(submap, k2));
            AST_Statements_free((void*) kh_value(submap, k2));
        }
        kh_destroy(procedure_t, submap);
    }
    kh_destroy(module_t, ast_procmap_root->map);
    free(ast_procmap_root);
    ast_procmap_root = NULL;
}

#else
    #warning re-inclusion of module 'ast/util/procedure_map.c.h'
#endif
