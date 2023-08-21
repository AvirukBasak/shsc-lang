#ifndef RT_VARTABLE_H
#define RT_VARTABLE_H

#include <stdbool.h>

#include "ast.h"
#include "data.h"

/** create a new variable in the current scope */
void RT_VarTable_create(const char *varname, RT_Data_t value);

/** modify data directly by address instead of querying via identifier */
RT_Data_t *RT_VarTable_modf(RT_Data_t *dest, RT_Data_t src);

/** get the variable from the current scope if it exists, else return NULL.
    other than the accumulator, data should be updated only by calling
    `void RT_VarTable_modf(RT_Data_t *dest, RT_Data_t src)`
    on the returned data pointer, that'll take care of reference counts */
RT_Data_t *RT_VarTable_getref(const char *varname);

/** this is used to update the accumulator */
void RT_VarTable_acc_set(RT_Data_t val, RT_Data_t *adr);

/** push a new function scope into the stack and store the procedure name and return address */
void RT_VarTable_push_proc(const char *procname, const AST_Statement_t *ret_addr);

/** pop the procedure off the stack, return the return address and clear the scope from memory */
const AST_Statement_t *RT_VarTable_pop_proc();

/** push a new local scope into the stack */
void RT_VarTable_push_scope();

/** pop local scope and return result of last expression */
RT_Data_t RT_VarTable_pop_scope();

/** clear memory of the vartable */
void RT_VarTable_destroy();

#endif
