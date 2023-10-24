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

rt_ControlStatus_t rt_eval_ForBlock(const ast_ForBlock_t *for_block)
{
    if (!for_block) return rt_CTRL_PASS;
    switch (for_block->type) {
        case FORBLOCK_TYPE_RANGE: {
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
            /* start for loop */
            for (int64_t i = start_i;
                    (start_i <= end_i && i < end_i) || i > end_i; i += by_i) {
                rt_VarTable_push_scope();
                rt_VarTable_create(for_block->val->identifier_name,
                    rt_Data_i64(i), true);
                rt_ControlStatus_t ctrl = rt_eval_Statements(for_block->statements);
                rt_VarTable_pop_scope();
                if (ctrl == rt_CTRL_PASS)
                    /* do nothing in pass */;
                if (ctrl == rt_CTRL_RETURN)   return ctrl;
                if (ctrl == rt_CTRL_BREAK)    break;
                if (ctrl == rt_CTRL_CONTINUE) continue;
            }
            break;
        }
        case FORBLOCK_TYPE_LIST: {
            /* convert expression to a data list */
            rt_eval_Expression(for_block->it.iterable);
            rt_Data_t iterable = *RT_VTABLE_ACC;
            rt_Data_copy(&iterable);
            int64_t length = 0;
            switch (iterable.type) {
                case rt_DATA_TYPE_LST:
                    length = rt_DataList_length(iterable.data.lst);
                    break;
                case rt_DATA_TYPE_STR:
                    length = rt_DataStr_length(iterable.data.str);
                    break;
                case rt_DATA_TYPE_MAP:
                    length = rt_DataMap_length(iterable.data.mp);
                    break;
                default:
                    rt_throw("not a for loop iterable type: '%s'", rt_Data_typename(iterable));
            }
            if (iterable.type == rt_DATA_TYPE_MAP) {
                for (rt_DataMap_iter_t entry_it = rt_DataMap_begin(iterable.data.mp);
                        entry_it != rt_DataMap_end(iterable.data.mp); ++entry_it) {
                    if (!rt_DataMap_exists(iterable.data.mp, entry_it)) continue;
                    rt_DataMapEntry_t entry = *rt_DataMap_get(iterable.data.mp, entry_it);
                    rt_VarTable_push_scope();
                    if (for_block->idx) rt_VarTable_create(for_block->idx->identifier_name,
                        rt_Data_str(rt_DataStr_init(entry.key)), true);
                    rt_VarTable_create(for_block->val->identifier_name, entry.value, true);
                    rt_ControlStatus_t ctrl = rt_eval_Statements(for_block->statements);
                    rt_VarTable_pop_scope();
                    if (ctrl == rt_CTRL_PASS)
                        /* do nothing in pass */;
                    if (ctrl == rt_CTRL_RETURN)   return ctrl;
                    if (ctrl == rt_CTRL_BREAK)    break;
                    if (ctrl == rt_CTRL_CONTINUE) continue;
                }
            }
            else for (int64_t i = 0; i < length; ++i) {
                rt_VarTable_push_scope();
                switch (iterable.type) {
                    case rt_DATA_TYPE_LST:
                        if (for_block->idx) rt_VarTable_create(for_block->idx->identifier_name,
                            rt_Data_i64(i), true);
                        rt_VarTable_create(for_block->val->identifier_name,
                            *rt_DataList_getref(iterable.data.lst, i), true);
                        break;
                    case rt_DATA_TYPE_STR:
                        if (for_block->idx) rt_VarTable_create(for_block->idx->identifier_name,
                            rt_Data_i64(i), true);
                        rt_VarTable_create(for_block->val->identifier_name,
                            *rt_DataStr_getref(iterable.data.str, i), true);
                        break;
                    default:
                        rt_throw("not a for loop iterable type: '%s'", rt_Data_typename(iterable));
                }
                rt_ControlStatus_t ctrl = rt_eval_Statements(for_block->statements);
                rt_VarTable_pop_scope();
                if (ctrl == rt_CTRL_PASS)
                    /* do nothing in pass */;
                if (ctrl == rt_CTRL_RETURN)   return ctrl;
                if (ctrl == rt_CTRL_BREAK)    break;
                if (ctrl == rt_CTRL_CONTINUE) continue;
            }
            /* destroy iterable object */
            rt_Data_destroy(&iterable);
            break;
        }
    }
    return rt_CTRL_PASS;
}

#else
    #warning re-inclusion of module 'runtime/eval/forblock.c.h'
#endif
