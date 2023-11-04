#ifndef RT_EVAL_ASSIGNMENT_C_H
#define RT_EVAL_ASSIGNMENT_C_H

#include "ast.h"
#include "ast/api.h"
#include "runtime/eval.h"
#include "runtime/VarTable.h"

void rt_eval_Assignment(const ast_Assignment_t *assignment)
{
    if (!assignment) return;
    switch (assignment->type) {
        case ASSIGNMENT_TYPE_TOVOID:
            rt_eval_Expression(assignment->rhs);
            break;
        case ASSIGNMENT_TYPE_CREATE: {
            const char *idf = assignment->lhs->identifier_name;
            rt_eval_Expression(assignment->rhs);
            rt_VarTable_create(idf, *RT_VTABLE_ACC, assignment->is_const, assignment->is_weak);
            break;
        }
    }
}

#else
    #warning re-inclusion of module 'runtime/eval/assignment.c.h'
#endif
