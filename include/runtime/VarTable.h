#ifndef RT_VARTABLE_H
#define RT_VARTABLE_H

#include <stdbool.h>

#include "ast.h"
#include "runtime/data/Data.h"

#define _rt_TMPVAR_CNT (32)
#define RT_ARGS_LIST_VARNAME "args"
#define RT_DEFAULT_CALL_STACK_LIMIT (1000)
#define RT_ACC_DATA (rt_VarTable_acc_get()->adr ? rt_VarTable_acc_get()->adr : &rt_VarTable_acc_get()->val)

/** accumulator stores procedure return values
    and also the address from which the value was obtained
    if the value is temporary (no place in variable), it's set
    to .adr = NULL */
typedef struct {
    rt_Data_t val;
    rt_Data_t *adr;
} rt_VarTable_Acc_t;

/* few globally defined variables */
extern
rt_Data_t rt_VarTable_rsv_lf,
/* list of globally defined typename variables */
          rt_VarTable_typeid_bul,
          rt_VarTable_typeid_chr,
          rt_VarTable_typeid_i64,
          rt_VarTable_typeid_f64,
          rt_VarTable_typeid_str,
          rt_VarTable_typeid_interp_str,
          rt_VarTable_typeid_lst,
          rt_VarTable_typeid_any,
          rt_VarTable_typeid_map,
          rt_VarTable_typeid_proc,
          rt_VarTable_rsv_null;

/** create a new variable in the current scope */
void rt_VarTable_create(const char *varname, rt_Data_t value);

/** modify data directly by address instead of querying via identifier */
rt_Data_t *rt_VarTable_modf(rt_Data_t *dest, rt_Data_t src);

rt_Data_t *rt_VarTable_getref_errnull(const char *varname);

/** get the variable from the current scope if it exists, else error.
    other than the accumulator, data should be updated only by calling
    `void rt_VarTable_modf(rt_Data_t *dest, rt_Data_t src)`
    on the returned data pointer, that'll take care of reference counts */
rt_Data_t *rt_VarTable_getref(const char *varname);

/** this is used to get the accumulator data and address */
rt_VarTable_Acc_t *rt_VarTable_acc_get(void);

/** this is used to update the accumulator val, nulls adr */
void rt_VarTable_acc_setval(rt_Data_t val);

/** this is used to update the accumulator adr, nulls val */
void rt_VarTable_acc_setadr(rt_Data_t *adr);

/** push a new function scope into the stack and store the procedure name and return address */
void rt_VarTable_push_proc(const char *procname);

/** pop the procedure off the stack, return the return address and clear the scope from memory */
rt_Data_t rt_VarTable_pop_proc(void);

/** push a new local scope into the stack */
void rt_VarTable_push_scope();

/** pop local scope and return result of last expression */
rt_Data_t rt_VarTable_pop_scope(void);

/** clear memory of the VarTable */
void rt_VarTable_destroy();

#endif
