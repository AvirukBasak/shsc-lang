#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#undef new
#undef delete

/**
 * new function: returns a pointer to a struct type passed by allocating
 * memory using calloc
 */
#define new(struct_t) ({                                                             \
    struct struct_t *tmp = calloc(1, sizeof(struct struct_t));                       \
    if (!tmp) abort();                                                               \
    tmp;                                                                             \
})

/**
 * delete function: frees pointer and sets it to null
 */
#define delete(ptr) ({                                                               \
    if (ptr) {                                                                       \
        free(ptr);                                                                   \
        ptr = NULL;                                                                  \
    }                                                                                \
})

#define Stack(vtype) stack_##vtype
#define StackFunc(vtype, func, ...) stack_##vtype##_##func(__VA_ARGS__)

/**
 * Generates function prototype definitions and typedefs for the stack
 * vtype should be a primary datatype or typdefed (aliased) pointer
 * format: StackDeclarePrototypes(vtype)
 */
#define StackDeclarePrototypes(vtype)                                                \
                                                                                     \
typedef struct stack_##vtype##_node *stack_##vtype##_node;                           \
                                                                                     \
typedef struct stack_##vtype {                                                       \
    stack_##vtype##_node top_ptr;                                                    \
    vtype *top;                                                                      \
} *stack_##vtype;                                                                    \
                                                                                     \
stack_##vtype stack_##vtype##_newstack();                                            \
bool stack_##vtype##_isEmpty(stack_##vtype st);                                      \
vtype stack_##vtype##_peek(stack_##vtype st);                                        \
bool stack_##vtype##_push(stack_##vtype st, vtype val);                              \
vtype stack_##vtype##_pop(stack_##vtype st);                                         \
void stack_##vtype##_print(stack_##vtype st);                                        \
void stack_##vtype##_free(stack_##vtype *st_ptr);

/**
 * Defines the chosen stack from template: generates the necessary function definitions
 * vtype should be a primary datatype or typdefed (aliased) pointer
 * format: StackDefine(vtype, func_print(const value))
 * NOTE: requires StackDeclarePrototypes(vtype)
 */
#define StackDefine(vtype, func_print)                                               \
                                                                                     \
struct stack_##vtype##_node {                                                        \
    vtype val;                                                                       \
    stack_##vtype##_node next;                                                       \
};                                                                                   \
                                                                                     \
stack_##vtype stack_##vtype##_newstack()                                             \
{                                                                                    \
    stack_##vtype st = new(stack_##vtype);                                           \
    st->top_ptr = NULL;                                                              \
    st->top = NULL;                                                                  \
    return st;                                                                       \
}                                                                                    \
                                                                                     \
bool stack_##vtype##_isEmpty(stack_##vtype st)                                       \
{                                                                                    \
    if (!st) abort();                                                                \
    return !(st->top_ptr);                                                           \
}                                                                                    \
                                                                                     \
vtype stack_##vtype##_peek(stack_##vtype st)                                         \
{                                                                                    \
    if (!st) abort();                                                                \
    if (st->top_ptr) return st->top_ptr->val;                                        \
    else return (vtype) 0;                                                           \
}                                                                                    \
                                                                                     \
bool stack_##vtype##_push(stack_##vtype st, vtype val)                               \
{                                                                                    \
    if (!st) abort();                                                                \
    stack_##vtype##_node node = new(stack_##vtype##_node);                           \
    node->val = val;                                                                 \
    node->next = st->top_ptr;                                                        \
    st->top_ptr = node;                                                              \
    st->top = &st->top_ptr->val;                                                     \
    return true;                                                                     \
}                                                                                    \
                                                                                     \
vtype stack_##vtype##_pop(stack_##vtype st)                                          \
{                                                                                    \
     if (!st) abort();                                                               \
     if (!st->top_ptr) return (vtype) 0;                                             \
     stack_##vtype##_node tmp = st->top_ptr;                                         \
     st->top_ptr = tmp->next;                                                        \
     st->top = &st->top_ptr->val;                                                    \
     vtype retv = tmp->val;                                                          \
     free(tmp);                                                                      \
     return retv;                                                                    \
}                                                                                    \
                                                                                     \
void stack_##vtype##_print(stack_##vtype st)                                         \
{                                                                                    \
    if (!st) abort();                                                                \
    stack_##vtype##_node p = st->top_ptr;                                            \
    if (!p) { printf("{ }\n"); return; }                                             \
    printf("{\n");                                                                   \
    while (p) {                                                                      \
        const vtype value = p->val;                                                  \
        printf("    ");                                                              \
        {                                                                            \
            const stack_##vtype st = NULL;                                           \
            const stack_##vtype##_node p = NULL;                                     \
            (st, p);                                                                 \
            func_print;                                                              \
        }                                                                            \
        printf("\n");                                                                \
        p = p->next;                                                                 \
    }                                                                                \
    printf("}\n");                                                                   \
}                                                                                    \
                                                                                     \
void stack_##vtype##_free(stack_##vtype *st_ptr)                                     \
{                                                                                    \
    if (!st_ptr || !*st_ptr) return;                                                 \
    stack_##vtype##_node p = (*st_ptr)->top_ptr;                                     \
    while (p) {                                                                      \
        free(p);                                                                     \
        p = p->next;                                                                 \
    }                                                                                \
    free(*st_ptr);                                                                   \
    *st_ptr = NULL;                                                                  \
}
