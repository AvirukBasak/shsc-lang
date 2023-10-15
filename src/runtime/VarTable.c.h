#ifndef RT_VARTABLE_C_H
#define RT_VARTABLE_C_H

#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "ast/api.h"
#include "ast/nodes/enums.h"
#include "io.h"
#include "errcodes.h"
#include "runtime/data/Data.h"
#include "runtime/data/DataList.h"
#include "runtime/data/DataStr.h"
#include "runtime/data/DataMap.h"
#include "runtime/io.h"
#include "runtime/VarTable.h"
#include "tlib/khash/khash.h"

typedef RT_DataMap_t *RT_VarTable_Scope_t;

/** the scopes stack of a procedure */
typedef struct {
    RT_VarTable_Scope_t *scopes;
    int64_t curr_scope_ptr;
    size_t capacity;
} RT_VarTable_proc_t;

/** the VarTable is basically the call stack */
typedef struct {
    RT_VarTable_proc_t *procs;
    int64_t curr_proc_ptr;
    size_t capacity;
} RT_VarTable_t;

/** gloablly allocated stack pointer */
RT_VarTable_t *rt_vtable = NULL;

/** the accumulator */
RT_VarTable_Acc_t rt_vtable_accumulator = {
    .val = { .data.any = NULL, RT_DATA_TYPE_ANY },
    .adr = NULL
};

/** arguments list */
RT_Data_t rt_vtable_argslist;

/* few globally defined variables */
RT_Data_t RT_VarTable_rsv_lf            = { .data.chr = '\n',                    .type = RT_DATA_TYPE_CHR },
/* list of globally defined typename variables */
          RT_VarTable_typeid_bul        = { .data.i64 = RT_DATA_TYPE_BUL,        .type = RT_DATA_TYPE_I64 },
          RT_VarTable_typeid_chr        = { .data.i64 = RT_DATA_TYPE_CHR,        .type = RT_DATA_TYPE_I64 },
          RT_VarTable_typeid_i64        = { .data.i64 = RT_DATA_TYPE_I64,        .type = RT_DATA_TYPE_I64 },
          RT_VarTable_typeid_f64        = { .data.i64 = RT_DATA_TYPE_F64,        .type = RT_DATA_TYPE_I64 },
          RT_VarTable_typeid_str        = { .data.i64 = RT_DATA_TYPE_STR,        .type = RT_DATA_TYPE_I64 },
          RT_VarTable_typeid_interp_str = { .data.i64 = RT_DATA_TYPE_INTERP_STR, .type = RT_DATA_TYPE_I64 },
          RT_VarTable_typeid_lst        = { .data.i64 = RT_DATA_TYPE_LST,        .type = RT_DATA_TYPE_I64 },
          RT_VarTable_typeid_any        = { .data.i64 = RT_DATA_TYPE_ANY,        .type = RT_DATA_TYPE_I64 },
          RT_VarTable_typeid_map        = { .data.i64 = RT_DATA_TYPE_MAP,        .type = RT_DATA_TYPE_I64 },
          RT_VarTable_typeid_proc       = { .data.i64 = RT_DATA_TYPE_PROC,       .type = RT_DATA_TYPE_I64 },
          RT_VarTable_rsv_null          = { .data.any = NULL,                    .type = RT_DATA_TYPE_ANY };

RT_Data_t *rt_vtable_get_globvar(const char *varname)
{
    if (!strcmp("lf", varname))         return &RT_VarTable_rsv_lf;
    if (!strcmp("bul", varname))        return &RT_VarTable_typeid_bul;
    if (!strcmp("chr", varname))        return &RT_VarTable_typeid_chr;
    if (!strcmp("i64", varname))        return &RT_VarTable_typeid_i64;
    if (!strcmp("f64", varname))        return &RT_VarTable_typeid_f64;
    if (!strcmp("str", varname))        return &RT_VarTable_typeid_str;
    if (!strcmp("interp_str", varname)) return &RT_VarTable_typeid_interp_str;
    if (!strcmp("lst", varname))        return &RT_VarTable_typeid_lst;
    if (!strcmp("null", varname))       return &RT_VarTable_rsv_null;
    return NULL;
}

void RT_VarTable_create(const char *varname, RT_Data_t value)
{
    if ( (!isalpha(varname[0]) && varname[0] != '_') || isdigit(varname[0]) )
        io_errndie("RT_VarTable_create: invalid new variable name '%s'", varname);
    else {
        RT_Data_t *globvar = rt_vtable_get_globvar(varname);
        if (globvar) rt_throw("cannot use 'var' with reserved global identifier '%s'", varname);
    }
    RT_VarTable_proc_t *current_proc = &(rt_vtable->procs[rt_vtable->curr_proc_ptr]);
    RT_VarTable_Scope_t *current_scope = &(current_proc->scopes[current_proc->curr_scope_ptr]);
    RT_DataMap_insert(*current_scope, varname, value);
}

RT_Data_t *RT_VarTable_modf(RT_Data_t *dest, RT_Data_t src)
{
    if (!dest) return NULL;
    if (dest == &RT_VarTable_rsv_null) rt_throw("cannot assign to reserved identifier 'null'");
    RT_Data_copy(&src);
    RT_Data_destroy(dest);
    *dest = src;
    return dest;
}

RT_Data_t *RT_VarTable_getref__n(const char *varname)
{
    if ( (!isalpha(varname[0]) && varname[0] != '_' && varname[0] != '$') || isdigit(varname[0]) )
        io_errndie("RT_VarTable_getref: invalid variable name '%s'", varname);
    else {
        if (!strcmp(varname, "$")) return &rt_vtable_argslist;
        RT_Data_t *globvar = rt_vtable_get_globvar(varname);
        if (globvar) return globvar;
    }
    RT_VarTable_proc_t *current_proc = &(rt_vtable->procs[rt_vtable->curr_proc_ptr]);
    /* go down the scopes stack to find the right local variable */
    for (int64_t i = current_proc->curr_scope_ptr; i >= 0; i--) {
        RT_VarTable_Scope_t *current_scope = &(current_proc->scopes[i]);
        RT_Data_t *data = RT_DataMap_getref__n(*current_scope, varname);
        if (data) return data;
    }
    return NULL;
}

RT_Data_t *RT_VarTable_getref(const char *varname)
{
    RT_Data_t *data = RT_VarTable_getref__n(varname);
    /* variable not found, throw an error */
    if (!data) rt_throw("undefined variable '%s'", varname);
    return data;
}

RT_VarTable_Acc_t *RT_VarTable_acc_get(void)
{
    return &rt_vtable_accumulator;
}

void RT_VarTable_acc_setval(RT_Data_t val)
{
    RT_Data_copy(&val);
    if (!rt_vtable_accumulator.adr) RT_Data_destroy(&rt_vtable_accumulator.val);
    else RT_Data_destroy(rt_vtable_accumulator.adr);
    rt_vtable_accumulator.val = val;
    rt_vtable_accumulator.adr = NULL;
}

void RT_VarTable_acc_setadr(RT_Data_t *adr)
{
    if (!adr) io_errndie("RT_VarTable_acc_setadr:" ERR_MSG_NULLPTR);
    RT_Data_copy(adr);
    if (!rt_vtable_accumulator.adr) RT_Data_destroy(&rt_vtable_accumulator.val);
    else RT_Data_destroy(rt_vtable_accumulator.adr);
    rt_vtable_accumulator.val = RT_Data_null();
    rt_vtable_accumulator.adr = adr;
}

void RT_VarTable_push_proc(const char *procname)
{
    /* check if the stack is already initialized */
    if (rt_vtable == NULL) {
        rt_vtable = (RT_VarTable_t*) malloc(sizeof(RT_VarTable_t));
        if (!rt_vtable) io_errndie("RT_VarTable_push_proc:" ERR_MSG_MALLOCFAIL);
        rt_vtable->procs = NULL;
        rt_vtable->curr_proc_ptr = -1;
        rt_vtable->capacity = 0;
    }
    /* increase the capacity if needed */
    if (rt_vtable->curr_proc_ptr >= rt_vtable->capacity -1) {
        rt_vtable->capacity = rt_vtable->capacity * 2 +1;
        rt_vtable->procs = (RT_VarTable_proc_t*) realloc(rt_vtable->procs, rt_vtable->capacity * sizeof(RT_VarTable_proc_t));
        if (!rt_vtable->procs) io_errndie("RT_VarTable_push_proc:" ERR_MSG_REALLOCFAIL);
    }
    /* push the new procedure scope */
    ++rt_vtable->curr_proc_ptr;
    rt_vtable->procs[rt_vtable->curr_proc_ptr].scopes = NULL;
    rt_vtable->procs[rt_vtable->curr_proc_ptr].curr_scope_ptr = -1;
    rt_vtable->procs[rt_vtable->curr_proc_ptr].capacity = 0;
    /* push a new local scope */
    RT_VarTable_push_scope();
}

RT_Data_t RT_VarTable_pop_proc(void)
{
    if (rt_vtable == NULL || rt_vtable->curr_proc_ptr == -1)
        /* nothing to pop, return NULL */
        return RT_VarTable_rsv_null;
    RT_VarTable_proc_t *current_proc = &(rt_vtable->procs[rt_vtable->curr_proc_ptr]);
    /* pop all scopes in that proc */
    while (current_proc->curr_scope_ptr >= 0) {
        RT_VarTable_pop_scope();
    }
    // for (int64_t i = current_proc->top; i >= 0; i--) {
    //     /* free all the scopes and their variables in the current procedure */
    //     RT_VarTable_Scope_t *current_scope = &(current_proc->scopes[i]);
    //     khiter_t iter;
    //     for (iter = kh_begin(current_scope->var_map); iter != kh_end(current_scope->var_map); ++iter) {
    //         if (kh_exist(current_scope->var_map, iter))
    //             /* decrement refcnt, if 0, data gets destroyed */
    //             RT_Data_destroy(&(kh_value(current_scope->var_map, iter)));
    //     }
    //     kh_destroy(RT_Data_t, current_scope->var_map);
    // }
    --rt_vtable->curr_proc_ptr;
    if (rt_vtable->curr_proc_ptr == -1) {
        free(rt_vtable->procs);
        rt_vtable->procs = NULL;
        rt_vtable->capacity = 0;
    }
    return *RT_ACC_DATA;
}

void RT_VarTable_push_scope()
{
    RT_VarTable_proc_t *current_proc = &(rt_vtable->procs[rt_vtable->curr_proc_ptr]);
    /* increase the capacity if needed */
    if (current_proc->curr_scope_ptr >= current_proc->capacity -1) {
        current_proc->capacity = current_proc->capacity * 2 +1;
        current_proc->scopes = (RT_VarTable_Scope_t*) realloc(current_proc->scopes, current_proc->capacity * sizeof(RT_VarTable_Scope_t));
        if (!current_proc->scopes) io_errndie("RT_VarTable_push_scope:" ERR_MSG_REALLOCFAIL);
    }
    /* push the new local scope */
    ++current_proc->curr_scope_ptr;
    current_proc->scopes[current_proc->curr_scope_ptr] = RT_DataMap_init();
}

RT_Data_t RT_VarTable_pop_scope(void)
{
    if (!rt_vtable || rt_vtable->curr_proc_ptr == -1)
        return RT_Data_null();
    RT_VarTable_proc_t *current_proc = &(rt_vtable->procs[rt_vtable->curr_proc_ptr]);
    if (!current_proc || current_proc->curr_scope_ptr == -1)
        return RT_Data_null();
    RT_VarTable_Scope_t *current_scope = &(current_proc->scopes[current_proc->curr_scope_ptr]);
    /* destroy map of values */
    RT_DataMap_destroy(current_scope);
    --current_proc->curr_scope_ptr;
    /* if there are no scopes left in the current procedure free the stack */
    if (current_proc->curr_scope_ptr == -1) {
        free(current_proc->scopes);
        current_proc->scopes = NULL;
        current_proc->capacity = 0;
    }
    return *RT_ACC_DATA;
}

/** clear memory of the VarTable */
void RT_VarTable_destroy()
{
    io_errndie("RT_VarTable_destroy: unimplemented");
    return;
}

#else
    #warning re-inclusion of module 'runtime/VarTable.c.h'
#endif