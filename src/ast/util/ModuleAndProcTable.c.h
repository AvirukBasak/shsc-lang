/**
 * TO WHOM IT MAY CONCERN
 * A procedure is nothing but `code` of type (AST_Statements_t *)
 * A `module` is defined as a map of ( proc_name, code ), aka a procmap
 * The `ast_util_mptable` is defined as map of ( module_name, module )
 * An AST_util_ModuleAndProcTable_t is (finally) a 2D map which is
    defined as a map of ( module_name, proc_name ) -> code
 */

#ifndef AST_UTIL_MODULE_AND_PROC_TABLE_C_H
#define AST_UTIL_MODULE_AND_PROC_TABLE_C_H

#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "ast/nodes.h"
#include "ast/nodes/constructors.h"
#include "ast/util/ModuleStack.h"
#include "ast/util/ModuleAndProcTable.h"
#include "errcodes.h"
#include "globals.h"
#include "io.h"
#include "parser.h"
#include "runtime/io.h"
#include "tlib/khash/khash.h"


ast_util_ModuleAndProcTable_t ast_util_mptable = NULL;


const AST_Identifier_t *AST_util_ModuleAndProcTable_main_idf = NULL;
const AST_Identifier_t *AST_util_ModuleAndProcTable_idfmain(void)
{
    if (!AST_util_ModuleAndProcTable_main_idf) AST_util_ModuleAndProcTable_main_idf = AST_Identifier(strdup("main"));
    return AST_util_ModuleAndProcTable_main_idf;
}

/* Function to create a new AST_util_ModuleAndProcTable_t object */
void AST_util_ModuleAndProcTable_create(void)
{
    if (ast_util_mptable) return;
    ast_util_mptable = kh_init(AST_module_t);
}

bool AST_util_ModuleAndProcTable_empty(void)
{
    return !ast_util_mptable;
}

/** Maps ( module_name, proc_name ) -> code */
void AST_util_ModuleAndProcTable_add(const AST_Identifier_t *module_name, const AST_Identifier_t *proc_name, AST_Statements_t *code)
{
    if (!module_name)
        io_errndie("AST_util_ModuleAndProcTable_add:" ERR_MSG_NULLPTR " for `module_name`");
    else if (!proc_name)
        io_errndie("AST_util_ModuleAndProcTable_add:" ERR_MSG_NULLPTR " for `proc_name`");
    if (!ast_util_mptable) AST_util_ModuleAndProcTable_create();

    int ret;
    ast_util_ModuleAndProcTable_module_t *module = NULL;
    khash_t(AST_procedure_t) *procmap = NULL;

    /* Check if the module already exists in the top-level map */
    khint_t mk = kh_get(AST_module_t, ast_util_mptable, module_name->identifier_name);
    if (mk != kh_end(ast_util_mptable)) {
        module = &kh_value(ast_util_mptable, mk);
        procmap = module->procmap;
    } else {
        /* else create a module object */
        char *key = strdup(module_name->identifier_name);
        mk = kh_put(AST_module_t, ast_util_mptable, key, &ret);
        module = &kh_value(ast_util_mptable, mk);
        module->procmap = procmap = kh_init(AST_procedure_t);
        module->modulename = key;
    }

    /* If procedure exists, throw an error and exit */
    khint_t pk = kh_get(AST_procedure_t, procmap, proc_name->identifier_name);
    if (pk != kh_end(procmap)) {
        size_t sz = snprintf(NULL, 0, "duplicate method '%s:%s'", module_name->identifier_name, proc_name->identifier_name);
        char *errmsg = (char*) malloc((sz +1) * sizeof(char));
        if (!errmsg) io_errndie("AST_util_ModuleAndProcTable_add:" ERR_MSG_MALLOCFAIL);
        sprintf(errmsg, "duplicate method '%s:%s'", module_name->identifier_name, proc_name->identifier_name);
        parse_throw(errmsg, false);
        free(errmsg);
    }

    /* Insert the proc_name and code into the sub map */
    char *key = strdup(proc_name->identifier_name);
    khint_t k = kh_put(AST_procedure_t, procmap, key, &ret);
    kh_value(procmap, k).src_filename = strdup(global_currfile);
    kh_value(procmap, k).procname = key;
    kh_value(procmap, k).code = code;
}

/** Get procedure by a module and a procedure name */
const ast_util_ModuleAndProcTable_procedure_t AST_util_ModuleAndProcTable_get(const AST_Identifier_t *module_name, const AST_Identifier_t *proc_name)
{
    if (!ast_util_mptable)
        io_errndie("AST_procedure_get:" ERR_MSG_NULLPTR " for `ast_util_mptable`");
    else if (!module_name)
        io_errndie("AST_procedure_get:" ERR_MSG_NULLPTR " for `module_name`");
    else if (!proc_name)
        io_errndie("AST_procedure_get:" ERR_MSG_NULLPTR " for `proc_name`");
    khash_t(AST_procedure_t) *procmap;
    /* Check if the module exists in the top-level map */
    khint_t k = kh_get(AST_module_t, ast_util_mptable, module_name->identifier_name);
    if (k == kh_end(ast_util_mptable))
        return (ast_util_ModuleAndProcTable_procedure_t) { NULL, NULL, NULL };
    /* Get the sub map */
    procmap = kh_value(ast_util_mptable, k).procmap;
    /* Check if the procedure exists in the sub map */
    k = kh_get(AST_procedure_t, procmap, proc_name->identifier_name);
    if (k == kh_end(procmap))
        return (ast_util_ModuleAndProcTable_procedure_t) { NULL, NULL, NULL };
    /* Return the code associated with the procedure */
    return kh_value(procmap, k);
}

/** Get code by a module and a procedure name */
const AST_Statements_t *AST_util_ModuleAndProcTable_get_code(const AST_Identifier_t *module_name, const AST_Identifier_t *proc_name)
{
    const ast_util_ModuleAndProcTable_procedure_t proc = AST_util_ModuleAndProcTable_get(module_name, proc_name);
    /* if (!proc.proc_name)
        rt_throw("undefined procedure '%s:%s'", module_name->identifier_name, proc_name->identifier_name); */
    return proc.code;
}

/** Get filename by a module and a procedure name */
const char *AST_util_ModuleAndProcTable_get_filename(const AST_Identifier_t *module_name, const AST_Identifier_t *proc_name)
{
    const ast_util_ModuleAndProcTable_procedure_t proc = AST_util_ModuleAndProcTable_get(module_name, proc_name);
    if (!proc.procname)
        rt_throw("AST_util_ModuleAndProcTable_get_filename: undefined procedure '%s:%s'", module_name->identifier_name, proc_name->identifier_name);
    return proc.src_filename;
}

/** Clears the entire runtime representation of code,
    i.e. everything the parser generated */
void AST_util_ModuleAndProcTable_clear(void)
{
    const char *key = NULL;
    ast_util_ModuleAndProcTable_module_t module;
    /* Iterate over the top-level map */
    kh_foreach(ast_util_mptable, key, module, {
        free(module.modulename);
        module.modulename = NULL;
        khash_t(AST_procedure_t) *procmap = module.procmap;
        /* Iterate over the sub map */
        ast_util_ModuleAndProcTable_procedure_t proc;
        kh_foreach(procmap, key, proc, {
            /* Free procedure name and statements */
            free(proc.procname);
            proc.procname = NULL;
            free(proc.src_filename);
            proc.src_filename = NULL;
            AST_Statements_destroy(&proc.code);
        });
        kh_destroy(AST_procedure_t, procmap);
    });
    kh_destroy(AST_module_t, ast_util_mptable);
    ast_util_mptable = NULL;
    AST_ModuleStack_clear();
}

#else
    #warning re-inclusion of module 'ast/util/ModuleAndProcTable.c.h'
#endif