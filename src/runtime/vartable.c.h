#ifndef RT_VARTABLE_C_H
#define RT_VARTABLE_C_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "ast/nodes/enums.h"
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

RT_VarTable_Acc_t rt_vtable_accumulator = {
    .val = { .data.any = NULL, RT_DATA_TYPE_ANY },
    .adr = NULL
};

RT_Data_t rt_vtable_temporary[RT_VTABLE_TEMPORARY_SIZE];

/* few globally defined variables */
RT_Data_t rt_vtable_lf         = { .data.chr = '\n',                    .type = RT_DATA_TYPE_CHR },
/* list of globally defined typename variables */
          rt_vtable_bul        = { .data.chr = RT_DATA_TYPE_BUL,        .type = RT_DATA_TYPE_I64 },
          rt_vtable_chr        = { .data.chr = RT_DATA_TYPE_CHR,        .type = RT_DATA_TYPE_I64 },
          rt_vtable_i64        = { .data.chr = RT_DATA_TYPE_I64,        .type = RT_DATA_TYPE_I64 },
          rt_vtable_f64        = { .data.chr = RT_DATA_TYPE_F64,        .type = RT_DATA_TYPE_I64 },
          rt_vtable_str        = { .data.chr = RT_DATA_TYPE_STR,        .type = RT_DATA_TYPE_I64 },
          rt_vtable_interp_str = { .data.chr = RT_DATA_TYPE_INTERP_STR, .type = RT_DATA_TYPE_I64 },
          rt_vtable_lst        = { .data.chr = RT_DATA_TYPE_LST,        .type = RT_DATA_TYPE_I64 },
          rt_vtable_any        = { .data.chr = RT_DATA_TYPE_ANY,        .type = RT_DATA_TYPE_I64 },
          rt_vtable_null       = { .data.any = NULL ,                   .type = RT_DATA_TYPE_ANY };

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
    if (rt_vtable->top >= rt_vtable->capacity -1) {
        rt_vtable->capacity = rt_vtable->capacity * 2 +1;
        rt_vtable->procs = (RT_VarTable_Proc_t*) realloc(rt_vtable->procs, rt_vtable->capacity * sizeof(RT_VarTable_Proc_t));
        if (!rt_vtable->procs) io_errndie("RT_VarTable_push_proc:" ERR_MSG_REALLOCFAIL);
    }
    /* push the new procedure scope */
    ++rt_vtable->top;
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
    if (current_proc->top >= current_proc->capacity -1) {
        current_proc->capacity = current_proc->capacity * 2 +1;
        current_proc->scopes = (RT_VarTable_Scope_t*) realloc(current_proc->scopes, current_proc->capacity * sizeof(RT_VarTable_Scope_t));
        if (!current_proc->scopes) io_errndie("RT_VarTable_push_scope:" ERR_MSG_REALLOCFAIL);
    }
    /* push the new local scope */
    ++current_proc->top;
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

RT_Data_t *rt_vtable_get_globvar(const char *varname)
{
    if (!strcmp("lf", varname))         return &rt_vtable_lf;
    if (!strcmp("bul", varname))        return &rt_vtable_bul;
    if (!strcmp("chr", varname))        return &rt_vtable_chr;
    if (!strcmp("i64", varname))        return &rt_vtable_i64;
    if (!strcmp("f64", varname))        return &rt_vtable_f64;
    if (!strcmp("str", varname))        return &rt_vtable_str;
    if (!strcmp("interp_str", varname)) return &rt_vtable_interp_str;
    if (!strcmp("lst", varname))        return &rt_vtable_lst;
    if (!strcmp("null", varname))       return &rt_vtable_null;
    return NULL;
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
         if (value->data.str->rc < 0)
             value->data.str->rc = 0;
         if (value->data.str->rc == 0)
             RT_Data_destroy(value);
    } else if (value->type == RT_DATA_TYPE_LST) {
        --value->data.lst->rc;
        if (value->data.lst->rc < 0)
            value->data.lst->rc = 0;
        if (value->data.lst->rc == 0)
            RT_Data_destroy(value);
    }
}

void RT_VarTable_create(const char *varname, RT_Data_t value)
{
    if (!strcmp(varname, "-"))
        io_errndie("RT_VarTable_create: invalid new variable name '%s'", varname);
    else {
        RT_Data_t *globvar = rt_vtable_get_globvar(varname);
        if (globvar) rt_throw("cannot use 'var' with reserved identifier '%s'", varname);
        int tmp = rt_vtable_get_tempvar(varname);
        if (tmp >= 0) io_errndie("RT_VarTable_create: invalid new variable name '%s'", varname);
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

RT_Data_t *RT_VarTable_modf(RT_Data_t *dest, RT_Data_t src)
{
    if (!dest) return NULL;
    if (dest == &rt_vtable_null) rt_throw("cannot assign to reserved identifier 'null'");
    rt_vtable_refcnt_decr(dest);
    rt_vtable_refcnt_incr(&src);
    *dest = src;
    return dest;
}

RT_Data_t *RT_VarTable_getref(const char *varname)
{
    if (!strcmp(varname, "-"))
        io_errndie("RT_VarTable_getref: accumulator must be accessed via 'RT_VarTable_acc_get' or 'RT_VarTable_acc_set'");
    else {
        RT_Data_t *globvar = rt_vtable_get_globvar(varname);
        if (globvar) return globvar;
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

RT_VarTable_Acc_t *RT_VarTable_acc_get(void)
{
    return &rt_vtable_accumulator;
}

void RT_VarTable_acc_setval(RT_Data_t val)
{
    rt_vtable_refcnt_incr(&val);
    if (!rt_vtable_accumulator.adr) rt_vtable_refcnt_decr(&rt_vtable_accumulator.val);
    else rt_vtable_refcnt_decr(rt_vtable_accumulator.adr);
    rt_vtable_accumulator.val = val;
    rt_vtable_accumulator.adr = NULL;
}

void RT_VarTable_acc_setadr(RT_Data_t *adr)
{
    if (!adr) io_errndie("RT_VarTable_acc_setadr:" ERR_MSG_NULLPTR);
    rt_vtable_refcnt_incr(adr);
    if (!rt_vtable_accumulator.adr) rt_vtable_refcnt_decr(&rt_vtable_accumulator.val);
    else rt_vtable_refcnt_decr(rt_vtable_accumulator.adr);
    rt_vtable_accumulator.val = RT_Data_null();
    rt_vtable_accumulator.adr = adr;
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
    --rt_vtable->top;
    return current_proc->ret_addr;
}

RT_Data_t RT_VarTable_pop_scope()
{
    if (rt_vtable == NULL || rt_vtable->top == -1)
        return RT_Data_null();
    RT_VarTable_Proc_t *current_proc = &(rt_vtable->procs[rt_vtable->top]);
    if (current_proc->top >= 0) {
        RT_VarTable_Scope_t *current_scope = &(current_proc->scopes[current_proc->top]);
        RT_Data_t last_expr = RT_VarTable_acc_get()->val;
        khiter_t iter;
        for (iter = kh_begin(current_scope->scope); iter != kh_end(current_scope->scope); ++iter) {
            if (kh_exist(current_scope->scope, iter))
                /* decrement refcnt, if 0, data gets destroyed */
                rt_vtable_refcnt_decr(&(kh_value(current_scope->scope, iter)));
        }
        kh_destroy(RT_Data_t, current_scope->scope);
        --current_proc->top;
        return last_expr;
    }
    /* if there are no scopes left in the current procedure, pop the procedure */
    RT_VarTable_pop_proc();
    return RT_VarTable_acc_get()->val;
}

/** clear memory of the vartable */
void RT_VarTable_destroy()
{
    io_errndie("RT_VarTable_destroy: unimplemented");
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
    RT_Data_t var1_ = *RT_VarTable_getref("var1");
    if (!RT_Data_isnull(var1_))
        RT_Data_print(var1_);
    /* pop the current scope */
    RT_VarTable_pop_proc();
    RT_VarTable_destroy();
}

#else
    #warning re-inclusion of module 'runtime/vartable.c.h'
#endif
