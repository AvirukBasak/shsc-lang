#ifndef RT_VARTABLE_C_H
#define RT_VARTABLE_C_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>

#include "errcodes.h"
#include "tlib/khash/khash.h"
#include "runtime.h"
#include "runtime/variable.h"
#include "runtime/vartable.h"
#include "ast.h"
#include "io.h"

KHASH_MAP_INIT_STR(var, RT_Variable_t)

typedef struct {
    khash_t(var) *scope;
    const char *procname;
    const AST_Statement_t *ret_addr;
} RT_VartableScope_t;

typedef struct {
    RT_VartableScope_t **scopes;
    int64_t top;
    size_t capacity;
} RT_Vartable_t;

/* vartable pointer */
RT_Vartable_t *rt_vtable = NULL;

/** initialize the global vartable */
void vartable_init()
{
    if (rt_vtable) return;
    rt_vtable = (RT_Vartable_t*) malloc(sizeof(RT_Vartable_t));
    if (!rt_vtable) io_errndie("vartable_init:" ERR_MSG_MALLOCFAIL);
    rt_vtable->scopes = NULL;
    rt_vtable->top = -1;
    rt_vtable->capacity = 0;
}

/** destroy the global vartable and free memory */
void vartable_destroy()
{
    if (!rt_vtable) return;
    for (int64_t i = 0; i <= rt_vtable->top; i++) {
        kh_destroy(var, rt_vtable->scopes[i]->scope);
        free(rt_vtable->scopes[i]);
        rt_vtable->scopes[i] = NULL;
    }
    free(rt_vtable->scopes);
    rt_vtable->scopes = NULL;
    free(rt_vtable);
    rt_vtable = NULL;
}

/** create a new variable or modify an existing one in the current scope */
void vartable_set(const char *varname, RT_Variable_t value)
{
    if (!rt_vtable) vartable_init();
    if (rt_vtable->top < 0) abort();
    if (!rt_vtable->scopes) abort();
    RT_VartableScope_t *current_scope = rt_vtable->scopes[rt_vtable->top];
    int ret;
    khint_t k = kh_put(var, current_scope->scope, varname, &ret);
    kh_value(current_scope->scope, k) = value;
}

/** get the variable from the current scope if it exists, else return NULL */
RT_Variable_t vartable_get(const char *varname)
{
    if (!rt_vtable) vartable_init();
    if (rt_vtable->top < 0) return rt_variable_null();
    if (!rt_vtable->scopes) abort();
    RT_VartableScope_t *current_scope = rt_vtable->scopes[rt_vtable->top];
    khint_t k = kh_get(var, current_scope->scope, varname);
    if (k != kh_end(current_scope->scope))
        return kh_value(current_scope->scope, k);
    return rt_variable_null();
}

/** push a new scope into the stack and store the procedure name and return address */
void vartable_pushscope(const char *procname, const AST_Statement_t *ret_addr)
{
    if (!rt_vtable) vartable_init();
    if (rt_vtable->top + 1 >= rt_vtable->capacity) {
        rt_vtable->capacity = rt_vtable->capacity * 2 + 1;
        rt_vtable->scopes = (RT_VartableScope_t**) realloc(rt_vtable->scopes, rt_vtable->capacity * sizeof(RT_VartableScope_t*));
        if (!rt_vtable->scopes) io_errndie("vartable_pushscope:" ERR_MSG_REALLOCFAIL);
    }
    rt_vtable->scopes[++rt_vtable->top] = ({
        RT_VartableScope_t *scope = (RT_VartableScope_t*) malloc(sizeof(RT_VartableScope_t));
        if (!scope) io_errndie("vartable_pushscope:" ERR_MSG_MALLOCFAIL);
        scope->scope = kh_init(var);
        scope->procname = procname;
        scope->ret_addr = ret_addr;
        scope;
    });
}

/** pop the scope off the stack and return the return address, clear the scope from memory */
const AST_Statement_t *vartable_popscope()
{
    if (!rt_vtable) vartable_init();
    if (rt_vtable->top < 0) return NULL;
    RT_VartableScope_t *current_scope = rt_vtable->scopes[rt_vtable->top];
    const AST_Statement_t *ret_addr = current_scope->ret_addr;
    khash_t(var) *scope_map = current_scope->scope;
    for (khint_t it = kh_begin(scope_map); it != kh_end(scope_map); ++it) {
        if (kh_exist(scope_map, it)) {
            RT_Variable_t var = kh_value(scope_map, it);
            rt_variable_destroy(&var);
        }
    }
    kh_destroy(var, scope_map);
    free(current_scope);
    current_scope = NULL;
    --rt_vtable->top;
    return ret_addr;
}

void vartable_test()
{
    /* push first scope */
    vartable_pushscope("main", NULL);
    /* set a variable in the current scope */
    RT_Variable_t var1 = rt_variable_i64(42);
    vartable_set("var1", var1);
    /* get a variable from the current scope */
    RT_Variable_t var1_ = vartable_get("var1");
    if (!rt_variable_isnull(var1_))
        rt_variable_print(var1_);
    /* pop the current scope */
    vartable_popscope();
    vartable_destroy();
}

#else
    #warning re-inclusion of module 'runtime/vartable.c.h'
#endif
