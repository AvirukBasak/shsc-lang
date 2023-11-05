#ifndef RT_EVAL_FORBLOCK_C_H
#define RT_EVAL_FORBLOCK_C_H

#include <inttypes.h>
#include <stdbool.h>

#include "ast.h"
#include "ast/api.h"
#include "runtime/data/Data.h"
#include "runtime/data/DataList.h"
#include "runtime/data/DataStr.h"
#include "runtime/data/DataMap.h"
#include "runtime/eval.h"
#include "runtime/io.h"
#include "runtime/VarTable.h"

void rt_eval_ForBlock_get_range_params(
    const ast_ForBlock_t *for_block,
    int64_t *start_ptr,
    int64_t *end_ptr,
    int64_t *by_ptr
);

rt_ControlStatus_t rt_eval_ForBlock_range(
    const ast_ForBlock_t *for_block,
    const int64_t start_i,
    const int64_t end_i,
    const int64_t by_i
);

void rt_eval_ForBlock_get_iterable_len(
    const ast_ForBlock_t *for_block,
    const rt_Data_t iterable,
    int64_t *length
);

rt_ControlStatus_t rt_eval_ForBlock_str(
    const ast_ForBlock_t *for_block,
    const rt_Data_t iterable,
    int64_t length
);

rt_ControlStatus_t rt_eval_ForBlock_lst(
    const ast_ForBlock_t *for_block,
    const rt_Data_t iterable,
    int64_t length
);

rt_ControlStatus_t rt_eval_ForBlock_map(
    const ast_ForBlock_t *for_block,
    const rt_Data_t iterable,
    int64_t length
);

rt_ControlStatus_t rt_eval_ForBlock(const ast_ForBlock_t *for_block)
{
    if (!for_block) return rt_CTRL_PASS;
    switch (for_block->type) {
        case FORBLOCK_TYPE_RANGE: {
            int64_t start_i;
            int64_t end_i;
            int64_t by_i;
            rt_eval_ForBlock_get_range_params(for_block, &start_i, &end_i, &by_i);

            /* start for loop */
            rt_ControlStatus_t ctrl = rt_eval_ForBlock_range(for_block, start_i, end_i, by_i);
            if (ctrl == rt_CTRL_RETURN)
                return ctrl;
            break;
        }
        case FORBLOCK_TYPE_LIST: {
            /* convert expression to a data list */
            rt_eval_Expression(for_block->it.iterable);
            rt_Data_t iterable = *RT_VTABLE_ACC;

            /* increase iterable object rc */
            rt_Data_increfc(&iterable);

            int64_t length = 0;
            rt_eval_ForBlock_get_iterable_len(for_block, iterable, &length);

            rt_ControlStatus_t ctrl = rt_CTRL_PASS;
            rt_VarTable_push_scope();
            switch (iterable.type) {
                case rt_DATA_TYPE_STR:
                    ctrl = rt_eval_ForBlock_str(for_block, iterable, length);
                    break;
                case rt_DATA_TYPE_LST:
                    ctrl = rt_eval_ForBlock_lst(for_block, iterable, length);
                    break;
                case rt_DATA_TYPE_MAP:
                    ctrl = rt_eval_ForBlock_map(for_block, iterable, length);
                    break;
                case rt_DATA_TYPE_BUL:
                case rt_DATA_TYPE_CHR:
                case rt_DATA_TYPE_I64:
                case rt_DATA_TYPE_F64:
                case rt_DATA_TYPE_INTERP_STR:
                case rt_DATA_TYPE_ANY:
                case rt_DATA_TYPE_PROC:
                    rt_throw("not a for loop iterable type: '%s'", rt_Data_typename(iterable));
            }
            rt_VarTable_pop_scope();

            /* reduce iterable object rc */
            rt_Data_destroy(&iterable);

            if (ctrl == rt_CTRL_RETURN)
                return ctrl;
            break;
        }
    }
    return rt_CTRL_PASS;
}

void rt_eval_ForBlock_get_range_params(
    const ast_ForBlock_t *for_block,
    int64_t *start_ptr,
    int64_t *end_ptr,
    int64_t *by_ptr
) {
    /* calculate start, end and by */
    rt_eval_Expression(for_block->it.range.start);
    rt_Data_t start = *RT_VTABLE_ACC;
    if (start.type != rt_DATA_TYPE_I64)
        rt_throw("for loop range start should be an i64, not '%s'", rt_Data_typename(start));
    rt_eval_Expression(for_block->it.range.end);
    rt_Data_t end = *RT_VTABLE_ACC;
    if (end.type != rt_DATA_TYPE_I64)
        rt_throw("for loop range end should be an i64, not '%s'", rt_Data_typename(start));
    rt_Data_t by = rt_Data_null();
    if (for_block->it.range.by) {
        rt_eval_Expression(for_block->it.range.by);
        by = *RT_VTABLE_ACC;
        if (by.type != rt_DATA_TYPE_I64)
            rt_throw("for loop by value should be an i64, not '%s'", rt_Data_typename(start));
    }
    const int64_t start_i = start.data.i64;
    const int64_t end_i = end.data.i64;
    const int64_t by_i = rt_Data_isnull(by) ?
        (start_i <= end_i ? +1 : -1) : by.data.i64;
    if (!by_i) rt_throw("for loop by value cannot be 0");
    if ( (start_i < end_i && by_i < 0) || (start_i > end_i && by_i > 0) )
        rt_throw("possible infinite for loop for by value '%" PRId64 "'", by_i);
    *start_ptr = start_i;
    *end_ptr = end_i;
    *by_ptr = by_i;
}

rt_ControlStatus_t rt_eval_ForBlock_range(
    const ast_ForBlock_t *for_block,
    const int64_t start_i,
    const int64_t end_i,
    const int64_t by_i
) {
    rt_ControlStatus_t ctrl = rt_CTRL_PASS;
    rt_VarTable_push_scope();
    for (int64_t i = start_i;
            (start_i <= end_i && i < end_i) || i > end_i; i += by_i) {
        rt_VarTable_create(for_block->val->identifier_name,
            rt_Data_i64(i), false, false);
        ctrl = rt_eval_Statements(for_block->statements);
        if (ctrl == rt_CTRL_PASS)
            /* do nothing in pass */;
        if (ctrl == rt_CTRL_RETURN)   break;
        if (ctrl == rt_CTRL_BREAK)    break;
        if (ctrl == rt_CTRL_CONTINUE) continue;
    }
    rt_VarTable_pop_scope();
    return ctrl;
}

void rt_eval_ForBlock_get_iterable_len(
    const ast_ForBlock_t *for_block,
    const rt_Data_t iterable,
    int64_t *length
) {
    *length = 0;
    switch (iterable.type) {
        case rt_DATA_TYPE_LST:
            *length = rt_DataList_length(iterable.data.lst);
            break;
        case rt_DATA_TYPE_STR:
            *length = rt_DataStr_length(iterable.data.str);
            break;
        case rt_DATA_TYPE_MAP:
            *length = rt_DataMap_length(iterable.data.mp);
            break;
        case rt_DATA_TYPE_BUL:
        case rt_DATA_TYPE_CHR:
        case rt_DATA_TYPE_I64:
        case rt_DATA_TYPE_F64:
        case rt_DATA_TYPE_INTERP_STR:
        case rt_DATA_TYPE_ANY:
        case rt_DATA_TYPE_PROC:
            rt_throw("not a for loop iterable type: '%s'", rt_Data_typename(iterable));
    }
}

rt_ControlStatus_t rt_eval_ForBlock_str(
    const ast_ForBlock_t *for_block,
    const rt_Data_t iterable,
    int64_t length
) {
    rt_ControlStatus_t ctrl = rt_CTRL_PASS;
    for (int64_t i = 0; i < length; ++i) {
        if (for_block->idx) rt_VarTable_create(for_block->idx->identifier_name,
            rt_Data_i64(i), false, false);
        rt_VarTable_create(for_block->val->identifier_name,
            *rt_DataStr_getref(iterable.data.str, i), false, false);
        /* execute code */
        ctrl = rt_eval_Statements(for_block->statements);
        if (ctrl == rt_CTRL_PASS)
            /* do nothing in pass */;
        if (ctrl == rt_CTRL_RETURN)   break;
        if (ctrl == rt_CTRL_BREAK)    break;
        if (ctrl == rt_CTRL_CONTINUE) continue;
    }
    return ctrl;
}

rt_ControlStatus_t rt_eval_ForBlock_lst(
    const ast_ForBlock_t *for_block,
    const rt_Data_t iterable,
    int64_t length
) {
    rt_ControlStatus_t ctrl = rt_CTRL_PASS;
    for (int64_t i = 0; i < length; ++i) {
        if (for_block->idx) rt_VarTable_create(for_block->idx->identifier_name,
            rt_Data_i64(i), false, false);
        rt_VarTable_create(for_block->val->identifier_name,
            *rt_DataList_getref(iterable.data.lst, i), false, false);
        /* execute code */
        ctrl = rt_eval_Statements(for_block->statements);
        if (ctrl == rt_CTRL_PASS)
            /* do nothing in pass */;
        if (ctrl == rt_CTRL_RETURN)   break;
        if (ctrl == rt_CTRL_BREAK)    break;
        if (ctrl == rt_CTRL_CONTINUE) continue;
    }
    return ctrl;
}

rt_ControlStatus_t rt_eval_ForBlock_map(
    const ast_ForBlock_t *for_block,
    const rt_Data_t iterable,
    int64_t length
) {
    rt_ControlStatus_t ctrl = rt_CTRL_PASS;
    for (rt_DataMap_iter_t entry_it = rt_DataMap_begin(iterable.data.mp);
            entry_it != rt_DataMap_end(iterable.data.mp); ++entry_it) {
        if (!rt_DataMap_exists(iterable.data.mp, entry_it)) continue;
        rt_DataMap_Entry_t entry = *rt_DataMap_get(iterable.data.mp, entry_it);
        if (for_block->idx) rt_VarTable_create(for_block->idx->identifier_name,
            rt_Data_str(rt_DataStr_init(entry.key)), false, false);
        rt_VarTable_create(for_block->val->identifier_name, entry.value, false, false);
        /* execute code */
        ctrl = rt_eval_Statements(for_block->statements);
        if (ctrl == rt_CTRL_PASS)
            /* do nothing in pass */;
        if (ctrl == rt_CTRL_RETURN)   break;
        if (ctrl == rt_CTRL_BREAK)    break;
        if (ctrl == rt_CTRL_CONTINUE) continue;
    }
    return ctrl;
}

#else
    #warning re-inclusion of module 'runtime/eval/forblock.c.h'
#endif
