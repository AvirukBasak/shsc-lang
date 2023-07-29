#ifndef RT_EVALSTACK_H
#define RT_EVALSTACK_H

#include <stdbool.h>
#include "ast/api.h"

/** function to push a node onto the stack */
void RT_EvalStack_push(const RT_StackEntry_t node);

/** function to pop a node from the stack */
RT_StackEntry_t RT_EvalStack_pop();

/** function to get the top node from the stack without popping it */
RT_StackEntry_t RT_EvalStack_top();

/** function to check if the stack is empty */
bool RT_EvalStack_isempty();

/** function to free the stack if it's fully empty */
void RT_EvalStack_free();

#endif
