#ifndef RT_VARTABLE_C_H
#define RT_VARTABLE_C_H

#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "ast.h"
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


/** gloablly allocated stack pointer */
rt_VarTable_t *rt_vtable = NULL;


/** the accumulator */
rt_VarTable_Acc_t rt_vtable_accumulator = {
    .val = { .data.any = NULL, .type = rt_DATA_TYPE_ANY, .is_const = false, .is_weak = false },
    .adr = NULL
};


/* few globally defined variables */
rt_Data_t rt_VarTable_rsv_lf      = { .data.chr = '\n',             .type = rt_DATA_TYPE_CHR, .is_const = true, .is_weak = false, .lvalue = false },
/* list of globally defined typename variables */
          rt_VarTable_typeid_bul  = { .data.i64 = rt_DATA_TYPE_BUL, .type = rt_DATA_TYPE_I64, .is_const = true, .is_weak = false, .lvalue = false },
          rt_VarTable_typeid_chr  = { .data.i64 = rt_DATA_TYPE_CHR, .type = rt_DATA_TYPE_I64, .is_const = true, .is_weak = false, .lvalue = false },
          rt_VarTable_typeid_i64  = { .data.i64 = rt_DATA_TYPE_I64, .type = rt_DATA_TYPE_I64, .is_const = true, .is_weak = false, .lvalue = false },
          rt_VarTable_typeid_f64  = { .data.i64 = rt_DATA_TYPE_F64, .type = rt_DATA_TYPE_I64, .is_const = true, .is_weak = false, .lvalue = false },
          rt_VarTable_typeid_str  = { .data.i64 = rt_DATA_TYPE_STR, .type = rt_DATA_TYPE_I64, .is_const = true, .is_weak = false, .lvalue = false },
          rt_VarTable_typeid_lst  = { .data.i64 = rt_DATA_TYPE_LST, .type = rt_DATA_TYPE_I64, .is_const = true, .is_weak = false, .lvalue = false },
          rt_VarTable_typeid_any  = { .data.i64 = rt_DATA_TYPE_ANY, .type = rt_DATA_TYPE_I64, .is_const = true, .is_weak = false, .lvalue = false },
          rt_VarTable_typeid_map  = { .data.i64 = rt_DATA_TYPE_MAP, .type = rt_DATA_TYPE_I64, .is_const = true, .is_weak = false, .lvalue = false },
          rt_VarTable_typeid_proc = { .data.i64 = rt_DATA_TYPE_PROC,.type = rt_DATA_TYPE_I64, .is_const = true, .is_weak = false, .lvalue = false },
          rt_VarTable_typeid_lambda = { .data.i64 = rt_DATA_TYPE_LAMBDA,.type = rt_DATA_TYPE_I64, .is_const = true, .is_weak = false, .lvalue = false },
          rt_VarTable_rsv_null    = { .data.any = NULL,             .type = rt_DATA_TYPE_ANY, .is_const = true, .is_weak = false, .lvalue = false };


rt_Data_t *rt_VarTable_get_globvar(const char *varname)
{
    if (!strcmp("lf", varname))   return &rt_VarTable_rsv_lf;
    if (!strcmp("bul", varname))  return &rt_VarTable_typeid_bul;
    if (!strcmp("chr", varname))  return &rt_VarTable_typeid_chr;
    if (!strcmp("i64", varname))  return &rt_VarTable_typeid_i64;
    if (!strcmp("f64", varname))  return &rt_VarTable_typeid_f64;
    if (!strcmp("str", varname))  return &rt_VarTable_typeid_str;
    if (!strcmp("lst", varname))  return &rt_VarTable_typeid_lst;
    if (!strcmp("map", varname))  return &rt_VarTable_typeid_map;
    if (!strcmp("proc", varname)) return &rt_VarTable_typeid_proc;
    if (!strcmp("lambda", varname)) return &rt_VarTable_typeid_lambda;
    if (!strcmp("null", varname)) return &rt_VarTable_rsv_null;
    return NULL;
}


void rt_VarTable_create(const char *varname, rt_Data_t value, bool is_const, bool is_weak)
{
    if ( (!isalpha(varname[0]) && varname[0] != '_'
        && strcmp(varname, RT_VTABLE_ARGSVAR)) || isdigit(varname[0]) )
            io_errndie("rt_VarTable_create: invalid new variable name '%s'", varname);
    else {
        rt_Data_t *globvar = rt_VarTable_get_globvar(varname);
        if (globvar) rt_throw("cannot create new variable with reserved identifier '%s'", varname);
    }
    rt_VarTable_proc_t *current_proc = &(rt_vtable->procs[rt_vtable->curr_proc_ptr]);
    rt_VarTable_Scope_t *current_scope = &(current_proc->scopes[current_proc->curr_scope_ptr]);
    /* getref to the given key, this creates new data if it doesn't exist */
    rt_Data_t *data = rt_DataMap_getref(*current_scope, varname);
    if (!data)
        io_errndie("rt_VarTable_create:" ERR_MSG_NULLPTR);
    /* if data is const throw error */
    if (data->is_const) rt_throw("cannot modify const variable");
    data->lvalue = true;
    rt_VarTable_modf(data, value, is_const, is_weak);
}


rt_Data_t *rt_VarTable_modf(rt_Data_t *dest, rt_Data_t src, bool is_const, bool is_weak)
{
    if (!dest) return NULL;
    /* if data is one of the global built-in vars, throw appropriate error */
    {
        if (dest == &rt_VarTable_rsv_lf)      rt_throw("cannot modify reserved variable 'lf'");
        if (dest == &rt_VarTable_typeid_bul)  rt_throw("cannot modify reserved variable 'bul'");
        if (dest == &rt_VarTable_typeid_chr)  rt_throw("cannot modify reserved variable 'chr'");
        if (dest == &rt_VarTable_typeid_i64)  rt_throw("cannot modify reserved variable 'i64'");
        if (dest == &rt_VarTable_typeid_f64)  rt_throw("cannot modify reserved variable 'f64'");
        if (dest == &rt_VarTable_typeid_str)  rt_throw("cannot modify reserved variable 'str'");
        if (dest == &rt_VarTable_typeid_lst)  rt_throw("cannot modify reserved variable 'lst'");
        if (dest == &rt_VarTable_typeid_map)  rt_throw("cannot modify reserved variable 'map'");
        if (dest == &rt_VarTable_typeid_proc) rt_throw("cannot modify reserved variable 'proc'");
        if (dest == &rt_VarTable_typeid_lambda) rt_throw("cannot modify reserved variable 'lambda'");
        if (dest == &rt_VarTable_rsv_null)    rt_throw("cannot modify reserved variable 'null'");
    }

    /* if dest is not lvalue, throw error */
    if (!dest->lvalue) rt_throw("lhs of assignment is not an lvalue");

    /* if data is const, throw appropriate error */
    if (dest->is_const) rt_throw("cannot modify const variable");

    /* if dest doesn't become weak, increase src reference count,
       i.e. dest takes ownership */
    if (!is_weak) rt_Data_increfc(&src);

    /* if dest data was not weak, decrease its reference count */
    if (!dest->is_weak) rt_Data_destroy(dest);

    /* copy src data but set dest weak and const attributes to modifiers */
    *dest = (rt_Data_t) {
        .data = src.data,
        .type = src.type,
        .is_const = is_const,
        .is_weak = is_weak,
        .lvalue = false
    };
    return dest;
}

rt_Data_t *rt_VarTable_getref_errnull(const char *varname)
{
    if ( (!isalpha(varname[0]) && varname[0] != '_'
        && strcmp(varname, RT_VTABLE_ARGSVAR)) || isdigit(varname[0]) )
            io_errndie("rt_VarTable_getref: invalid variable name '%s'", varname);
    else {
        rt_Data_t *globvar = rt_VarTable_get_globvar(varname);
        if (globvar) return globvar;
    }
    rt_VarTable_proc_t *current_proc = &(rt_vtable->procs[rt_vtable->curr_proc_ptr]);
    /* go down the scopes stack to find the right local variable */
    for (int64_t i = current_proc->curr_scope_ptr; i >= 0; i--) {
        rt_VarTable_Scope_t *current_scope = &(current_proc->scopes[i]);
        rt_Data_t *data = rt_DataMap_getref_errnull(*current_scope, varname);
        if (data) return data;
    }
    return NULL;
}

rt_Data_t *rt_VarTable_getref(const char *varname)
{
    rt_Data_t *data = rt_VarTable_getref_errnull(varname);
    /* variable not found, throw an error */
    if (!data) rt_throw("undefined variable '%s'", varname);
    return data;
}


rt_VarTable_Acc_t *rt_VarTable_acc_get(void)
{
    return &rt_vtable_accumulator;
}

void rt_VarTable_acc_setval(rt_Data_t val)
{
    rt_Data_increfc(&val);
    if (!rt_vtable_accumulator.adr) rt_Data_destroy(&rt_vtable_accumulator.val);
    else rt_Data_decrefc(rt_vtable_accumulator.adr);
    /* copy src data and reset modifiers coz accumulator holding a value
       means the value is without a variable, and thus is does not have
       have any modifiers */
    rt_vtable_accumulator.val = (rt_Data_t) {
        .type = val.type,
        .data = val.data,
        .is_const = false,
        .is_weak = false,
        .lvalue = false
    };
    rt_vtable_accumulator.adr = NULL;
}

void rt_VarTable_acc_setadr(rt_Data_t *adr)
{
    if (!adr) io_errndie("rt_VarTable_acc_setadr:" ERR_MSG_NULLPTR);
    rt_Data_increfc(adr);
    if (!rt_vtable_accumulator.adr) rt_Data_destroy(&rt_vtable_accumulator.val);
    else rt_Data_decrefc(rt_vtable_accumulator.adr);
    rt_vtable_accumulator.val = rt_Data_null();
    rt_vtable_accumulator.adr = adr;
    rt_vtable_accumulator.adr->lvalue = true;
}


void rt_VarTable_push_proc(
    const ast_Identifier_t *module_name,
    const ast_Identifier_t *proc_name,
    const char *filepath
) {
    /* check if the stack is already initialized */
    if (rt_vtable == NULL) {
        rt_vtable = (rt_VarTable_t*) malloc(sizeof(rt_VarTable_t));
        if (!rt_vtable) io_errndie("rt_VarTable_push_proc:" ERR_MSG_MALLOCFAIL);
        rt_vtable->procs = NULL;
        rt_vtable->curr_proc_ptr = -1;
        rt_vtable->capacity = 0;
    }
    /* check if call stack has exceeded a default limit */
    if (rt_vtable->curr_proc_ptr >= RT_VTABLE_CALLSTACK_LIMIT)
        rt_throw("call stack limit exceeded");
    /* increase the capacity if needed */
    if (rt_vtable->curr_proc_ptr >= rt_vtable->capacity -1) {
        rt_vtable->capacity = rt_vtable->capacity * 2 +1;
        rt_vtable->procs = (rt_VarTable_proc_t*) realloc(rt_vtable->procs, rt_vtable->capacity * sizeof(rt_VarTable_proc_t));
        if (!rt_vtable->procs) io_errndie("rt_VarTable_push_proc:" ERR_MSG_REALLOCFAIL);
    }
    /* push the new procedure scope */
    ++rt_vtable->curr_proc_ptr;
    rt_vtable->procs[rt_vtable->curr_proc_ptr].scopes = NULL;
    rt_vtable->procs[rt_vtable->curr_proc_ptr].curr_scope_ptr = -1;
    rt_vtable->procs[rt_vtable->curr_proc_ptr].capacity = 0;
    rt_vtable->procs[rt_vtable->curr_proc_ptr].module_name = module_name;
    rt_vtable->procs[rt_vtable->curr_proc_ptr].proc_name = proc_name;
    rt_vtable->procs[rt_vtable->curr_proc_ptr].filepath = filepath;
    rt_vtable->procs[rt_vtable->curr_proc_ptr].current_line = -1;
    /* push a new local scope */
    rt_VarTable_push_scope();
}

rt_VarTable_proc_t *rt_VarTable_top_proc(void)
{
    if (rt_vtable == NULL || rt_vtable->curr_proc_ptr == -1)
        return NULL;
    return &(rt_vtable->procs[rt_vtable->curr_proc_ptr]);
}

rt_Data_t rt_VarTable_pop_proc(void)
{
    if (rt_vtable == NULL || rt_vtable->curr_proc_ptr == -1)
        /* nothing to pop, return NULL */
        return rt_VarTable_rsv_null;
    rt_VarTable_proc_t *current_proc = &(rt_vtable->procs[rt_vtable->curr_proc_ptr]);
    /* copy data in accumulator before pop so that it may be returned
       in the event that the accumulator data is not a val but an adr
       i.e. a ref to some value in the table.
       thus, we use this to convert the adr into a val */
    rt_VarTable_acc_setval(*RT_VTABLE_ACC);
    /* pop all scopes in that proc */
    while (current_proc->curr_scope_ptr >= 0) {
        rt_VarTable_pop_scope();
    }
    --rt_vtable->curr_proc_ptr;
    if (rt_vtable->curr_proc_ptr == -1) {
        free(rt_vtable->procs);
        rt_vtable->procs = NULL;
        rt_vtable->capacity = 0;
    }
    return *RT_VTABLE_ACC;
}


void rt_VarTable_push_scope()
{
    rt_VarTable_proc_t *current_proc = &(rt_vtable->procs[rt_vtable->curr_proc_ptr]);
    /* increase the capacity if needed */
    if (current_proc->curr_scope_ptr >= current_proc->capacity -1) {
        current_proc->capacity = current_proc->capacity * 2 +1;
        current_proc->scopes = (rt_VarTable_Scope_t*) realloc(current_proc->scopes, current_proc->capacity * sizeof(rt_VarTable_Scope_t));
        if (!current_proc->scopes) io_errndie("rt_VarTable_push_scope:" ERR_MSG_REALLOCFAIL);
    }
    /* push the new local scope */
    ++current_proc->curr_scope_ptr;
    current_proc->scopes[current_proc->curr_scope_ptr] = rt_DataMap_init();
}

rt_Data_t rt_VarTable_pop_scope(void)
{
    if (!rt_vtable || rt_vtable->curr_proc_ptr == -1)
        return rt_Data_null();
    rt_VarTable_proc_t *current_proc = &(rt_vtable->procs[rt_vtable->curr_proc_ptr]);
    if (!current_proc || current_proc->curr_scope_ptr == -1)
        return rt_Data_null();
    /* copy data in accumulator before pop so that it may be returned
       in the event that the accumulator data is not a val but an adr
       i.e. a ref to some value in the table.
       thus, we use this to convert the adr into a val */
    rt_VarTable_acc_setval(*RT_VTABLE_ACC);
    /* get the current scope */
    rt_VarTable_Scope_t *current_scope = &(current_proc->scopes[current_proc->curr_scope_ptr]);
    /* destroy map of values */
    rt_DataMap_destroy_circular(current_scope, true);
    --current_proc->curr_scope_ptr;
    /* if there are no scopes left in the current procedure free the stack */
    if (current_proc->curr_scope_ptr == -1) {
        free(current_proc->scopes);
        current_proc->scopes = NULL;
        current_proc->capacity = 0;
    }
    return *RT_VTABLE_ACC;
}


/** clear memory of the VarTable */
void rt_VarTable_destroy()
{
    io_errndie("rt_VarTable_destroy: unimplemented");
    return;
}

#else
    #warning re-inclusion of module 'runtime/VarTable.c.h'
#endif
