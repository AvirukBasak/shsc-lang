#ifndef RT_VARTABLE_C_H
#define RT_VARTABLE_C_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "tlib/khash/khash.h"

#include "ast/api.h"
#include "io.h"
#include "errcodes.h"
#include "runtime/data.h"
#include "runtime/data/list.h"
#include "runtime/data/string.h"
#include "runtime/io.h"
#include "runtime/vartable.h"

#define RT_VTABLE_TEMPORARY_SIZE (32)

int rt_vtable_get_tempvar(const char *varname);
void rt_vtable_refcnt_incr(RT_Data_t *value);
void rt_vtable_refcnt_decr(RT_Data_t *value);

KHASH_MAP_INIT_STR(RT_Data_t, RT_Data_t)

/** local scope, stores a map of variables */
typedef struct {
    khash_t(RT_Data_t) *scope;
} RT_VarTable_Scope_t;

/** scope of a procedure that stores local scopes,
    return address of last procedure and name of
    the current procedure */
typedef struct {
    RT_VarTable_Scope_t *scopes;
    int64_t top;
    size_t capacity;
    const char *procname;
    const AST_Statement_t *ret_addr;
} RT_VarTable_Proc_t;

typedef struct {
    RT_VarTable_Proc_t *procs;
    int64_t top;
    size_t capacity;
} RT_VarTable_t;

/** gloablly allocated stack pointer */
RT_VarTable_t *rt_vtable = NULL;

/** accumulator stores procedure return values */
RT_Data_t rt_vtable_accumulator = { .data.any = NULL, RT_DATA_TYPE_ANY };
RT_Data_t rt_vtable_temporary[RT_VTABLE_TEMPORARY_SIZE];

void RT_VarTable_push_proc(const char *procname, const AST_Statement_t *ret_addr)
{
    /* check if the stack is already initialized */
    if (rt_vtable == NULL) {
        rt_vtable = (RT_VarTable_t*) malloc(sizeof(RT_VarTable_t));
        if (!rt_vtable) io_errndie("RT_VarTable_push_proc:" ERR_MSG_MALLOCFAIL);
        rt_vtable->procs = NULL;
        rt_vtable->top = -1;
        rt_vtable->capacity = 0;
    }
    /* increase the capacity if needed */
    if (rt_vtable->top == rt_vtable->capacity - 1) {
        rt_vtable->capacity = rt_vtable->capacity == rt_vtable->capacity * 2 +1;
        rt_vtable->procs = (RT_VarTable_Proc_t*) realloc(rt_vtable->procs, rt_vtable->capacity * sizeof(RT_VarTable_Proc_t));
        if (!rt_vtable->procs) io_errndie("RT_VarTable_push_proc:" ERR_MSG_REALLOCFAIL);
    }
    /* push the new procedure scope */
    rt_vtable->top++;
    rt_vtable->procs[rt_vtable->top].scopes = NULL;
    rt_vtable->procs[rt_vtable->top].top = -1;
    rt_vtable->procs[rt_vtable->top].capacity = 0;
    rt_vtable->procs[rt_vtable->top].procname = procname;
    rt_vtable->procs[rt_vtable->top].ret_addr = ret_addr;
    /* push a new local scope */
    RT_VarTable_push_scope();
}

void RT_VarTable_push_scope()
{
    RT_VarTable_Proc_t *current_proc = &(rt_vtable->procs[rt_vtable->top]);
    /* increase the capacity if needed */
    if (current_proc->top == current_proc->capacity - 1) {
        current_proc->capacity = current_proc->capacity == current_proc->capacity * 2 +1;
        current_proc->scopes = (RT_VarTable_Scope_t*) realloc(current_proc->scopes, current_proc->capacity * sizeof(RT_VarTable_Scope_t));
        if (!current_proc->scopes) io_errndie("RT_VarTable_push_scope:" ERR_MSG_REALLOCFAIL);
    }
    /* push the new local scope */
    current_proc->top++;
    current_proc->scopes[current_proc->top].scope = kh_init(RT_Data_t);
}

#include <errno.h>

/** convert an integer variable name to an index */
int rt_vtable_get_tempvar(const char *varname)
{
    /* variables to store the converted integer and the end
       pointer after conversion */
    char *endptr;
    int converted_int;
    /* convert the string to an integer using strtol */
    errno = 0; /* Set errno to 0 before the call to strtol */
    converted_int = (int) strtol(varname, &endptr, 10);
    /* check if there was an error during conversion */
    if ((errno == ERANGE && (converted_int == INT_MAX
        || converted_int == INT_MIN))
        || (errno != 0 && converted_int == 0)) {
        /* conversion error occurred */
        return -1;
    }
    /* check if the string is fully consumed (i.e., there are no
       non-integer characters after the number) */
    bool fully_consumed = (*endptr == '\0');
    return fully_consumed && (converted_int >= 0) ? converted_int : -1;
}

/** increment reference count of composite data */
void rt_vtable_refcnt_incr(RT_Data_t *value)
{
    if (value->type == RT_DATA_TYPE_STR
     || value->type == RT_DATA_TYPE_INTERP_STR) {
        ++value->data.str->rc;
    } else if (value->type == RT_DATA_TYPE_LST) {
        ++value->data.lst->rc;
    }
}

/** decrement reference count of composite data
    and free data if rc is 0 */
void rt_vtable_refcnt_decr(RT_Data_t *value)
{
    if (value->type == RT_DATA_TYPE_STR
     || value->type == RT_DATA_TYPE_INTERP_STR) {
         --value->data.str->rc;
         if (value->data.str->rc <= 0)
             RT_Data_destroy(value);
    } else if (value->type == RT_DATA_TYPE_LST) {
        --value->data.lst->rc;
         if (value->data.lst->rc <= 0)
             RT_Data_destroy(value);
    }
    if (value->data.lst->rc < 0)
        value->data.lst->rc = 0;
}

void RT_VarTable_create(const char *varname, RT_Data_t value)
{
    if (!strcmp(varname, "-"))
        rt_throw("RT_VarTable_create: invalid new variable name '%s'", varname);
    else {
        int tmp = rt_vtable_get_tempvar(varname);
        if (tmp >= 0) rt_throw("RT_VarTable_create: invalid new variable name '%s'", varname);
    }
    RT_VarTable_Proc_t *current_proc = &(rt_vtable->procs[rt_vtable->top]);
    RT_VarTable_Scope_t *current_scope = &(current_proc->scopes[current_proc->top]);
    khiter_t iter = kh_get(RT_Data_t, current_scope->scope, varname);
    /* variable exists, reduce reference count and replace
       it with the new data */
    if (iter != kh_end(current_scope->scope)) {
        rt_vtable_refcnt_decr(&kh_value(current_scope->scope, iter));
        rt_vtable_refcnt_incr(&value);
        kh_value(current_scope->scope, iter) = value;
    } else {
        /* variable doesn't exist, add a new entry */
        int ret;
        iter = kh_put(RT_Data_t, current_scope->scope, strdup(varname), &ret);
        /* create variable, increase reference count to 1 and set new data */
        rt_vtable_refcnt_incr(&value);
        kh_value(current_scope->scope, iter) = value;
    }
}

void RT_VarTable_update(const char *varname, RT_Data_t value)
{
    if (!strcmp(varname, "-")) {
        rt_vtable_refcnt_decr(&rt_vtable_accumulator);
        rt_vtable_refcnt_incr(&value);
        rt_vtable_accumulator = value;
        return;
    } else {
        int tmp = rt_vtable_get_tempvar(varname);
        if (tmp >= 32) rt_throw("no argument at '%d': valid arguments are $[0] to $[31]", tmp);
        if (tmp >= 0) {
            rt_vtable_refcnt_decr(&rt_vtable_temporary[tmp]);
            rt_vtable_refcnt_incr(&value);
            rt_vtable_temporary[tmp] = value;
            return;
        }
    }
    RT_VarTable_Proc_t *current_proc = &(rt_vtable->procs[rt_vtable->top]);
    /* search for variable in current and higher scopes and
       update its value (and reference counts) */
    for (int64_t i = current_proc->top; i >= 0; i--) {
        RT_VarTable_Scope_t *current_scope = &(current_proc->scopes[i]);
        khiter_t iter = kh_get(RT_Data_t, current_scope->scope, varname);
        /* variable found, update its value */
        if (iter != kh_end(current_scope->scope)) {
            rt_vtable_refcnt_decr(&kh_value(current_scope->scope, iter));
            rt_vtable_refcnt_incr(&value);
            kh_value(current_scope->scope, iter) = value;
            return;
        }
    }
    /* variable not found, throw an error */
    rt_throw("undefined variable '%s'", varname);
}

void RT_VarTable_modf(RT_Data_t *dest, RT_Data_t src)
{
    rt_vtable_refcnt_decr(dest);
    rt_vtable_refcnt_incr(&src);
    *dest = src;
}

RT_Data_t *RT_VarTable_get(const char *varname)
{
    if (!strcmp(varname, "-")) return &rt_vtable_accumulator;
    else {
        int tmp = rt_vtable_get_tempvar(varname);
        if (tmp >= 32) rt_throw("no argument at '%d': valid arguments are $[0] to $[31]", tmp);
        if (tmp >= 0) return &rt_vtable_temporary[tmp];
    }
    RT_VarTable_Proc_t *current_proc = &(rt_vtable->procs[rt_vtable->top]);
    for (int64_t i = current_proc->top; i >= 0; i--) {
        RT_VarTable_Scope_t *current_scope = &(current_proc->scopes[i]);
        khiter_t iter = kh_get(RT_Data_t, current_scope->scope, varname);
        /* variable found, return its value */
        if (iter != kh_end(current_scope->scope)) {
            return &kh_value(current_scope->scope, iter);
        }
    }
    /* variable not found, throw an error */
    rt_throw("undefined variable '%s'", varname);
    return NULL;
}

const AST_Statement_t *RT_VarTable_pop_proc()
{
    if (rt_vtable == NULL || rt_vtable->top == -1)
        /* nothing to pop, return NULL */
        return NULL;
    RT_VarTable_Proc_t *current_proc = &(rt_vtable->procs[rt_vtable->top]);
    for (int64_t i = current_proc->top; i >= 0; i--) {
        /* free all the scopes and their variables in the current procedure */
        RT_VarTable_Scope_t *current_scope = &(current_proc->scopes[i]);
        khiter_t iter;
        for (iter = kh_begin(current_scope->scope); iter != kh_end(current_scope->scope); ++iter) {
            if (kh_exist(current_scope->scope, iter))
                /* decrement refcnt, if 0, data gets destroyed */
                rt_vtable_refcnt_decr(&(kh_value(current_scope->scope, iter)));
        }
        kh_destroy(RT_Data_t, current_scope->scope);
    }
    rt_vtable->top--;
    return current_proc->ret_addr;
}

RT_Data_t RT_VarTable_pop_scope()
{
    if (rt_vtable == NULL || rt_vtable->top == -1)
        return RT_Data_null();
    RT_VarTable_Proc_t *current_proc = &(rt_vtable->procs[rt_vtable->top]);
    if (current_proc->top >= 0) {
        RT_VarTable_Scope_t *current_scope = &(current_proc->scopes[current_proc->top]);
        RT_Data_t last_expr = *RT_VarTable_get("-");
        khiter_t iter;
        for (iter = kh_begin(current_scope->scope); iter != kh_end(current_scope->scope); ++iter) {
            if (kh_exist(current_scope->scope, iter))
                /* decrement refcnt, if 0, data gets destroyed */
                rt_vtable_refcnt_decr(&(kh_value(current_scope->scope, iter)));
        }
        kh_destroy(RT_Data_t, current_scope->scope);
        current_proc->top--;
        return last_expr;
    }
    /* if there are no scopes left in the current procedure, pop the procedure */
    RT_VarTable_pop_proc();
    return *RT_VarTable_get("-");
}

/** clear memory of the vartable */
void RT_VarTable_destroy()
{
    rt_throw("unimplemented");
    return;
}

void RT_VarTable_test()
{
    /* push first scope */
    RT_VarTable_push_proc("main", NULL);
    /* set a variable in the current scope */
    RT_Data_t var1 = RT_Data_i64(42);
    RT_VarTable_create("var1", var1);
    /* get a variable from the current scope */
    RT_Data_t var1_ = *RT_VarTable_get("var1");
    if (!RT_Data_isnull(var1_))
        RT_Data_print(var1_);
    /* pop the current scope */
    RT_VarTable_pop_proc();
    RT_VarTable_destroy();
}

#else
    #warning re-inclusion of module 'runtime/vartable.c.h'
#endif
