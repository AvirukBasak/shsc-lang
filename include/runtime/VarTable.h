#ifndef RT_VARTABLE_H
#define RT_VARTABLE_H

#include <stdbool.h>

#include "ast.h"
#include "data.h"

#define __RT_TMPVAR_CNT (32)
#define RT_ACC_DATA (RT_VarTable_acc_get()->adr ? RT_VarTable_acc_get()->adr : &RT_VarTable_acc_get()->val)

/** accumulator stores procedure return values
    and also the address from which the value was obtained
    if the value is temporary (no place in variable), it's set
    to .adr = NULL */
typedef struct {
    RT_Data_t val;
    RT_Data_t *adr;
} RT_VarTable_Acc_t;

/* few globally defined variables */
extern
RT_Data_t RT_VarTable_rsv_lf,
/* list of globally defined typename variables */
          RT_VarTable_typeid_bul,
          RT_VarTable_typeid_chr,
          RT_VarTable_typeid_i64,
          RT_VarTable_typeid_f64,
          RT_VarTable_typeid_str,
          RT_VarTable_typeid_interp_str,
          RT_VarTable_typeid_lst,
          RT_VarTable_typeid_any,
          RT_VarTable_typeid_map,
          RT_VarTable_typeid_proc,
          RT_VarTable_rsv_null;

/** create a new variable in the current scope */
void RT_VarTable_create(const char *varname, RT_Data_t value);

/** modify data directly by address instead of querying via identifier */
RT_Data_t *RT_VarTable_modf(RT_Data_t *dest, RT_Data_t src);

RT_Data_t *RT_VarTable_getref__n(const char *varname);

/** get the variable from the current scope if it exists, else error.
    other than the accumulator, data should be updated only by calling
    `void RT_VarTable_modf(RT_Data_t *dest, RT_Data_t src)`
    on the returned data pointer, that'll take care of reference counts */
RT_Data_t *RT_VarTable_getref(const char *varname);

/** this is used to get the accumulator data and address */
RT_VarTable_Acc_t *RT_VarTable_acc_get(void);

/** this is used to update the accumulator val, nulls adr */
void RT_VarTable_acc_setval(RT_Data_t val);

/** this is used to update the accumulator adr, nulls val */
void RT_VarTable_acc_setadr(RT_Data_t *adr);

/** push a new function scope into the stack and store the procedure name and return address */
void RT_VarTable_push_proc(const char *procname);

/** pop the procedure off the stack, return the return address and clear the scope from memory */
RT_Data_t RT_VarTable_pop_proc(void);

/** push a new local scope into the stack */
void RT_VarTable_push_scope();

/** pop local scope and return result of last expression */
RT_Data_t RT_VarTable_pop_scope(void);

/** clear memory of the VarTable */
void RT_VarTable_destroy();

#endif
