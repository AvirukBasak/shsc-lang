#include <stdlib.h>
#include "tlib/khash/khash.h"

#include "ast.h"
#include "ast/syntax.h"
#include "ast/util.h"
#include "parser.h"

// Define the hash map types
KHASH_MAP_INIT_STR(procedure_t, AST_Statements_t*)
KHASH_MAP_INIT_STR(module_t, khash_t(procedure_t)*)

// AST_ProcedureMap_t structure
typedef struct
{
    khash_t(module_t) *map;
} AST_ProcedureMap_t;

// Global AST_ProcedureMap_t object
AST_ProcedureMap_t *ast_root_node = NULL;

// Function to create a new AST_ProcedureMap_t object
void AST_ProcedureMap_create()
{
    ast_root_node = (AST_ProcedureMap_t*) malloc(sizeof(AST_ProcedureMap_t));
    ast_root_node->map = kh_init(module_t);
}

/** Set code to map of procedures */
void AST_ProcedureMap_add(AST_Identifier_t *module, AST_Identifier_t *procedure, AST_Statements_t *code)
{
    if (!module)
        parse_throw("AST_ProcedureMap_add: null pointer error for `module`");
    else if (!procedure)
        parse_throw("AST_ProcedureMap_add: null pointer error for `procedure`");
    if (!ast_root_node) AST_ProcedureMap_create();
    int ret;
    khash_t(procedure_t) *submap;
    // Check if the module already exists in the top-level map
    khint_t k = kh_get(module_t, ast_root_node->map, module->identifier_name);
    if (k == kh_end(ast_root_node->map)) {
        // Create a new sub map if the module does not exist
        submap = kh_init(procedure_t);
        k = kh_put(module_t, ast_root_node->map, module->identifier_name, &ret);
        kh_value(ast_root_node->map, k) = submap;
    } else {
        // Get the existing sub map
        submap = kh_value(ast_root_node->map, k);
    }
    // Insert the procedure_name and code into the sub map
    k = kh_put(procedure_t, submap, procedure->identifier_name, &ret);
    kh_value(submap, k) = code;
}

/** Get procedure code by module and procedure name */
AST_Statements_t *AST_ProcedureMap_get(AST_Identifier_t *module, AST_Identifier_t *procedure)
{
    if (!ast_root_node) {
        parse_throw("AST_procedure_get: null pointer error for `ast_root_node`");
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
    khint_t k = kh_get(module_t, ast_root_node->map, module->identifier_name);
    if (k == kh_end(ast_root_node->map)) return NULL;
    // Get the sub map
    submap = kh_value(ast_root_node->map, k);
    // Check if the procedure exists in the sub map
    k = kh_get(procedure_t, submap, procedure->identifier_name);
    if (k == kh_end(submap)) return NULL;
    // Return the code associated with the procedure
    return kh_value(submap, k);
}

/** Clear the map by calling AST_Identifier_free() and AST_Statements_free() on each key and value */
void AST_ProcedureMap_clear()
{
    if (!ast_root_node) return;
    khash_t(procedure_t) *submap = NULL;
    // Iterate over the top-level map
    for (khint_t k1 = kh_begin(ast_root_node->map); k1 != kh_end(ast_root_node->map); ++k1) {
        if (!kh_exist(ast_root_node->map, k1)) continue;
        submap = kh_value(ast_root_node->map, k1);
        // Iterate over the sub map
        for (khint_t k2 = kh_begin(submap); k2 != kh_end(submap); ++k2) {
            if (!kh_exist(submap, k2)) continue;
            // Free procedure name and statements
            AST_Identifier_free(kh_key(submap, k2));
            AST_Statements_free(kh_value(submap, k2));
        }
        kh_destroy(procedure_t, submap);
    }
    kh_destroy(module_t, ast_root_node->map);
    free(ast_root_node);
    ast_root_node = NULL;
}
