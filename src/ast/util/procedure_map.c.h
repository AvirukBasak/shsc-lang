/**
 * TO WHOM IT MAY CONCERN
 * A procedure is nothing but `code` of type (AST_Statements_t *)
 * A `module` is defined as a map of ( proc_name, code ), aka a procmap
 * The `ast_procedure_map` is defined as map of ( module_name, module )
 * An ast_ProcedureMap_t is (finally) a 2D map which is
    defined as a map of ( module_name, proc_name ) -> code
 */

#ifndef AST_UTIL_PROCEDURE_MAP_C_H
#define AST_UTIL_PROCEDURE_MAP_C_H

#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "ast/nodes.h"
#include "ast/nodes/create.h"
#include "ast/util/module_stack.h"
#include "ast/util/procedure_map.h"
#include "errcodes.h"
#include "globals.h"
#include "io.h"
#include "parser.h"
#include "runtime/io.h"
#include "tlib/khash/khash.h"

ast_ProcedureMap_t ast_procedure_map = NULL;

const AST_Identifier_t *AST_ProcedureMap_main_idf = NULL;
const AST_Identifier_t *AST_ProcedureMap_idfmain(void)
{
    if (!AST_ProcedureMap_main_idf) AST_ProcedureMap_main_idf = AST_Identifier(strdup("main"));
    return AST_ProcedureMap_main_idf;
}

/* Function to create a new ast_ProcedureMap_t object */
void AST_ProcedureMap_create(void)
{
    if (ast_procedure_map) return;
    ast_procedure_map = kh_init(module_t);
}

bool AST_ProcedureMap_empty(void)
{
    return !ast_procedure_map;
}

/** Maps ( module_name, proc_name ) -> code */
void AST_ProcedureMap_add(const AST_Identifier_t *module_name, const AST_Identifier_t *proc_name, AST_Statements_t *code)
{
    if (!module_name)
        io_errndie("AST_ProcedureMap_add:" ERR_MSG_NULLPTR " for `module_name`");
    else if (!proc_name)
        io_errndie("AST_ProcedureMap_add:" ERR_MSG_NULLPTR " for `proc_name`");
    if (!ast_procedure_map) AST_ProcedureMap_create();

    int ret;
    ast_ProcedureMap_module_t *module = NULL;
    khash_t(procedure_t) *procmap = NULL;

    /* Check if the module already exists in the top-level map */
    khint_t mk = kh_get(module_t, ast_procedure_map, module_name->identifier_name);
    if (mk != kh_end(ast_procedure_map)) {
        module = &kh_value(ast_procedure_map, mk);
        procmap = module->procmap;
    } else {
        /* else create a module object */
        char *key = strdup(module_name->identifier_name);
        mk = kh_put(module_t, ast_procedure_map, key, &ret);
        module = &kh_value(ast_procedure_map, mk);
        module->procmap = procmap = kh_init(procedure_t);
        module->modulename = key;
    }

    /* If procedure exists, throw an error and exit */
    khint_t pk = kh_get(procedure_t, procmap, proc_name->identifier_name);
    if (pk != kh_end(procmap)) {
        size_t sz = snprintf(NULL, 0, "duplicate method '%s:%s'", module_name->identifier_name, proc_name->identifier_name);
        char *errmsg = (char*) malloc((sz +1) * sizeof(char));
        if (!errmsg) io_errndie("AST_ProcedureMap_add:" ERR_MSG_MALLOCFAIL);
        sprintf(errmsg, "duplicate method '%s:%s'", module_name->identifier_name, proc_name->identifier_name);
        parse_throw(errmsg, false);
        free(errmsg);
    }

    /* Insert the proc_name and code into the sub map */
    char *key = strdup(proc_name->identifier_name);
    khint_t k = kh_put(procedure_t, procmap, key, &ret);
    kh_value(procmap, k).src_filename = strdup(global_currfile);
    kh_value(procmap, k).procname = key;
    kh_value(procmap, k).code = code;
}

/** Get procedure by a module and a procedure name */
const ast_ProcedureMap_procedure_t AST_ProcedureMap_get(const AST_Identifier_t *module_name, const AST_Identifier_t *proc_name)
{
    if (!ast_procedure_map)
        io_errndie("AST_procedure_get:" ERR_MSG_NULLPTR " for `ast_procedure_map`");
    else if (!module_name)
        io_errndie("AST_procedure_get:" ERR_MSG_NULLPTR " for `module_name`");
    else if (!proc_name)
        io_errndie("AST_procedure_get:" ERR_MSG_NULLPTR " for `proc_name`");
    khash_t(procedure_t) *procmap;
    /* Check if the module exists in the top-level map */
    khint_t k = kh_get(module_t, ast_procedure_map, module_name->identifier_name);
    if (k == kh_end(ast_procedure_map))
        return (ast_ProcedureMap_procedure_t) { NULL, NULL, NULL };
    /* Get the sub map */
    procmap = kh_value(ast_procedure_map, k).procmap;
    /* Check if the procedure exists in the sub map */
    k = kh_get(procedure_t, procmap, proc_name->identifier_name);
    if (k == kh_end(procmap))
        return (ast_ProcedureMap_procedure_t) { NULL, NULL, NULL };
    /* Return the code associated with the procedure */
    return kh_value(procmap, k);
}

/** Get code by a module and a procedure name */
const AST_Statements_t *AST_ProcedureMap_get_code(const AST_Identifier_t *module_name, const AST_Identifier_t *proc_name)
{
    const ast_ProcedureMap_procedure_t proc = AST_ProcedureMap_get(module_name, proc_name);
    /* if (!proc.proc_name)
        rt_throw("undefined procedure '%s:%s'", module_name->identifier_name, proc_name->identifier_name); */
    return proc.code;
}

/** Get filename by a module and a procedure name */
const char *AST_ProcedureMap_get_filename(const AST_Identifier_t *module_name, const AST_Identifier_t *proc_name)
{
    const ast_ProcedureMap_procedure_t proc = AST_ProcedureMap_get(module_name, proc_name);
    if (!proc.procname)
        rt_throw("AST_ProcedureMap_get_filename: undefined procedure '%s:%s'", module_name->identifier_name, proc_name->identifier_name);
    return proc.src_filename;
}

/** Clears the entire runtime representation of code,
    i.e. everything the parser generated */
void AST_ProcedureMap_clear(void)
{
    const char *key = NULL;
    ast_ProcedureMap_module_t module;
    /* Iterate over the top-level map */
    kh_foreach(ast_procedure_map, key, module, {
        free(module.modulename);
        module.modulename = NULL;
        khash_t(procedure_t) *procmap = module.procmap;
        /* Iterate over the sub map */
        ast_ProcedureMap_procedure_t proc;
        kh_foreach(procmap, key, proc, {
            /* Free procedure name and statements */
            free(proc.procname);
            proc.procname = NULL;
            free(proc.src_filename);
            proc.src_filename = NULL;
            AST_Statements_free(&proc.code);
        });
        kh_destroy(procedure_t, procmap);
    });
    kh_destroy(module_t, ast_procedure_map);
    ast_procedure_map = NULL;
    AST_ModuleStack_clear();
}

#else
    #warning re-inclusion of module 'ast/util/procedure_map.c.h'
#endif
