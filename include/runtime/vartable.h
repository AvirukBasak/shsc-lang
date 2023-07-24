#ifndef RT_VARTABLE_H
#define RT_VARTABLE_H

#include <stdbool.h>
#include <inttypes.h>

#include "variable.h"
#include "ast.h"

/** create a new variable or modify an existing one in the current scope */
void vartable_set(const char *varname, RT_Variable_t value);

/** get the variable from the current scope if it exists, else return NULL */
RT_Variable_t vartable_get(const char *varname);

/** push a new scope into the stack and store the procedure name and return address */
void vartable_pushscope(const char *procname, const AST_Statement_t *ret_addr);

/** pop the scope off the stack and return the return address, clear the scope from memory */
const AST_Statement_t *vartable_popscope();

#endif
