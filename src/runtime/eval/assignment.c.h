#ifndef RT_EVAL_ASSIGNMENT_C_H
#define RT_EVAL_ASSIGNMENT_C_H

#include <inttypes.h>

#include "ast.h"
#include "ast/api.h"
#include "runtime/eval.h"
#include "runtime/io.h"
#include "runtime/data/DataList.h"
#include "runtime/data/DataMap.h"
#include "runtime/VarTable.h"

void rt_eval_Assignment(const ast_Assignment_t *assignment)
{
    if (!assignment) return;
    switch (assignment->type) {
        case ASSIGNMENT_TYPE_TOVOID:
            rt_eval_Expression(assignment->rhs);
            break;
        case ASSIGNMENT_TYPE_CREATE: {
            const char *idf = assignment->lhs.variable;
            rt_eval_Expression(assignment->rhs);
            rt_VarTable_create(idf, *RT_VTABLE_ACC, assignment->is_const, assignment->is_weak);
            break;
        }
        case ASSIGNMENT_TYPE_DESTRUCTURE: {
            const ast_FnArgsList_t *args_list = assignment->lhs.args_list;
            rt_eval_Expression(assignment->rhs);
            const rt_Data_t data = *RT_VTABLE_ACC;

            switch (data.type) {
                case DATA_TYPE_LST: {
                    int64_t i = 0;

                    const ast_FnArgsList_t *bkp_ptr = args_list;

                    int64_t argslen = 0;
                    int64_t listlen = rt_DataList_length(data.data.lst);

                    while (args_list) {
                        args_list = args_list->args_list;
                        ++argslen;
                    }

                    if (argslen > listlen) {
                        rt_throw("cannot destructure %" PRId64 " elements into %" PRId64, listlen, argslen);
                    }

                    args_list = bkp_ptr;

                    while (args_list) {
                        const char *idf = args_list->identifier;
                        rt_Data_t *elem = rt_DataList_getref(data.data.lst, i);
                        rt_VarTable_create(idf, *elem, assignment->is_const, assignment->is_weak);
                        args_list = args_list->args_list;
                        ++i;
                    }
                    break;
                }
                case DATA_TYPE_MAP: {
                    while (args_list) {
                        const char *idf = args_list->identifier;
                        rt_Data_t *elem = rt_DataMap_getref_errnull(data.data.mp, idf);
                        if (!elem) {
                            rt_throw("key '%s' not found in map", idf);
                        }
                        rt_VarTable_create(idf, *elem, assignment->is_const, assignment->is_weak);
                        args_list = args_list->args_list;
                    }
                    break;
                }
                case rt_DATA_TYPE_BUL:
                case rt_DATA_TYPE_CHR:
                case rt_DATA_TYPE_I64:
                case rt_DATA_TYPE_F64:
                case rt_DATA_TYPE_STR:
                case rt_DATA_TYPE_INTERP_STR:
                case rt_DATA_TYPE_ANY:
                case rt_DATA_TYPE_PROC:
                case rt_DATA_TYPE_LAMBDA:
                case rt_DATA_TYPE_LIBHANDLE:
                    rt_throw("destructuring expects 'lst' or 'map' in rhs, received '%s'", rt_Data_typename(data));
                    break;
            }
            break;
        }
    }
}

#else
    #warning re-inclusion of module 'runtime/eval/assignment.c.h'
#endif
