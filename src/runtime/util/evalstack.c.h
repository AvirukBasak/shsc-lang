#ifndef RT_EVALSTACK_C_H
#define RT_EVALSTACK_C_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "errcodes.h"
#include "runtime.h"
#include "runtime/util/evalstack.h"

typedef struct {
    RT_StackEntry_t *entries;
    int64_t top;
    size_t capacity;
} RT_EvalStack_t;

RT_EvalStack_t rt_eval_stack = { NULL, -1, 0 };

/** function to push a entry onto the stack */
void RT_EvalStack_push(const RT_StackEntry_t entry)
{
    if (rt_eval_stack.top + 1 >= rt_eval_stack.capacity) {
        rt_eval_stack.capacity = rt_eval_stack.capacity * 2 + 1;
        RT_StackEntry_t *new_entries = (RT_StackEntry_t*) realloc(rt_eval_stack.entries, rt_eval_stack.capacity * sizeof(RT_StackEntry_t));
        if (!new_entries) io_errndie("RT_EvalStack_push:" ERR_MSG_REALLOCFAIL);
        rt_eval_stack.entries = new_entries;
    }
    ++rt_eval_stack.top;
    rt_eval_stack.entries[rt_eval_stack.top] = entry;
}

/** function to pop a entry from the stack */
RT_StackEntry_t RT_EvalStack_pop()
{
    if (rt_eval_stack.top < 0)
        io_errndie("RT_EvalStack_pop: stack underflow");
    RT_StackEntry_t entry = rt_eval_stack.entries[rt_eval_stack.top];
    --rt_eval_stack.top;
    if (rt_eval_stack.top == -1) {
        free(rt_eval_stack.entries);
        rt_eval_stack.entries = NULL;
        rt_eval_stack.capacity = 0;
    }
    return entry;
}

/** function to get the top entry from the stack without popping it */
RT_StackEntry_t RT_EvalStack_top()
{
    if (rt_eval_stack.top < 0)
        io_errndie("RT_EvalStack_top: stack underflow");
    return rt_eval_stack.entries[rt_eval_stack.top];
}

/** function to check if the stack is empty */
bool RT_EvalStack_isempty()
{
    return rt_eval_stack.top == -1;
}

/** function to free the stack if it's fully empty */
void RT_EvalStack_free()
{
    if (rt_eval_stack.entries != NULL) {
        free(rt_eval_stack.entries);
        rt_eval_stack.entries = NULL;
        rt_eval_stack.top = -1;
        rt_eval_stack.capacity = 0;
    }
}

#else
    #warning re-inclusion of module 'runtime/util/dfs_stack.c.h'
#endif
