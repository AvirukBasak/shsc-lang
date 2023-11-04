#ifndef RT_DATA_GARBAGECOLL_C_H
#define RT_DATA_GARBAGECOLL_C_H

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#include "runtime/data/Data.h"
#include "runtime/data/DataStr.h"
#include "runtime/data/DataList.h"
#include "runtime/data/DataMap.h"
#include "runtime/data/GarbageColl.h"


typedef union {
    rt_DataStr_t *str;
    rt_DataList_t *lst;
    rt_DataMap_t *mp;
} rt_data_GC_cyclic_count_target_t;


void rt_data_GC_cyclic_count_helper(
    rt_Data_t node,
    const rt_data_GC_cyclic_count_target_t target,
    int64_t *count,
    const bool break_ref
);


bool rt_data_GC_has_only_cyclic_refcnt(const rt_Data_t var)
{
    /* this function is disabled as weak pointers were
       added to make rcgc a lot simpler to implement */
    return false;

    if (var.type != rt_DATA_TYPE_STR && var.type != rt_DATA_TYPE_INTERP_STR
        && var.type != rt_DATA_TYPE_LST && var.type != rt_DATA_TYPE_MAP)
            return false;

    int64_t refcnt = 0;

    if (var.type == rt_DATA_TYPE_STR || var.type == rt_DATA_TYPE_INTERP_STR)
        refcnt = var.data.str->var->rc;
    else if (var.type == rt_DATA_TYPE_LST)
        refcnt = var.data.lst->rc;
    else if (var.type == rt_DATA_TYPE_MAP)
        refcnt = var.data.mp->rc;
    else return false;

    int64_t count = rt_data_GC_cyclic_count(var);
#ifdef GC_DEBUG
    printf(
        "type: %s, ref: %p, count: %ld, refcnt: %ld\n",
        rt_Data_typename(var),
        var.data.mp,
        count,
        refcnt
    );
#endif
    return count == refcnt;
}


void rt_data_GC_break_cycle(const rt_Data_t var, const rt_Data_t tg)
{
    /* this function is disabled as weak pointers were
       added to make rcgc a lot simpler to implement */
    return;

    if (var.type != rt_DATA_TYPE_STR && var.type != rt_DATA_TYPE_INTERP_STR
        && var.type != rt_DATA_TYPE_LST && var.type != rt_DATA_TYPE_MAP)
            return;

    rt_data_GC_cyclic_count_target_t target;

    if (var.type == rt_DATA_TYPE_STR || var.type == rt_DATA_TYPE_INTERP_STR)
        target.str = var.data.str;
    else if (var.type == rt_DATA_TYPE_LST)
        target.lst = var.data.lst;
    else if (var.type == rt_DATA_TYPE_MAP)
        target.mp = var.data.mp;
    else return;

    int64_t count = 0;
    rt_data_GC_cyclic_count_helper(var, target, &count, true);
}


int64_t rt_data_GC_cyclic_count(const rt_Data_t var)
{
    /* this function is disabled as weak pointers were
       added to make rcgc a lot simpler to implement */
    return 0;

    if (var.type != rt_DATA_TYPE_STR && var.type != rt_DATA_TYPE_INTERP_STR
        && var.type != rt_DATA_TYPE_LST && var.type != rt_DATA_TYPE_MAP)
            return 0;

    rt_data_GC_cyclic_count_target_t target;

    if (var.type == rt_DATA_TYPE_STR || var.type == rt_DATA_TYPE_INTERP_STR)
        target.str = var.data.str;
    else if (var.type == rt_DATA_TYPE_LST)
        target.lst = var.data.lst;
    else if (var.type == rt_DATA_TYPE_MAP)
        target.mp = var.data.mp;
    else return 0;

    int64_t count = 0;
    rt_data_GC_cyclic_count_helper(var, target, &count, false);
    return count;
}


void rt_data_GC_cyclic_count_helper(
    rt_Data_t node_,
    const rt_data_GC_cyclic_count_target_t target,
    int64_t *count,
    const bool break_ref
) {
    /* this function is disabled as weak pointers were
       added to make rcgc a lot simpler to implement */
    return;

    if (node_.type != rt_DATA_TYPE_STR && node_.type != rt_DATA_TYPE_INTERP_STR
        && node_.type != rt_DATA_TYPE_LST && node_.type != rt_DATA_TYPE_MAP)
            return;

    /* use incomming node as default node */
    rt_Data_t node = node_;

#ifdef GC_DEBUG
    printf("type: %s, node: %p, target: %p\n",
        rt_Data_typename(node),
        (void*) node.data.mp,
        (void*) target.mp
    );
#endif

    /* get inner list from string to prevent truncation into char
       in the process set node to the inner list */
    if (node.type == rt_DATA_TYPE_STR || node.type == rt_DATA_TYPE_INTERP_STR) {
        node.data.lst = node.data.str->var;
        node.type = rt_DATA_TYPE_LST;
    }

    /* go through all elements in the list and if the reference is a string
       or a list or map, check if it is the same as the target and increment the
       counter if it is */
    if (node.type == rt_DATA_TYPE_LST) {
        for (int64_t i = 0; i < rt_DataList_length(node.data.lst); ++i) {
            rt_Data_t *ref = rt_DataList_getref_errnull(node.data.lst, i);
            if (!ref) continue;
            if ( ref->type == rt_DATA_TYPE_STR
              || ref->type == rt_DATA_TYPE_INTERP_STR) {
                if (ref->data.str == target.str) {
                    ++(*count);
                    if (break_ref) *ref = rt_Data_null();
                }
                else rt_data_GC_cyclic_count_helper(*ref, target, count, break_ref);
            } else if (ref->type == rt_DATA_TYPE_LST) {
                if (ref->data.lst == target.lst) {
                    ++(*count);
                    if (break_ref) *ref = rt_Data_null();
                }
                else rt_data_GC_cyclic_count_helper(*ref, target, count, break_ref);
            } else if (ref->type == rt_DATA_TYPE_MAP) {
                if (ref->data.mp == target.mp) {
                    ++(*count);
                    if (break_ref) *ref = rt_Data_null();
                }
                else rt_data_GC_cyclic_count_helper(*ref, target, count, break_ref);
            }
        }
    }

    /* go through all values in the map and if the reference is a string
       or a list or map, check if it is the same as the target and increment the
       counter if it is */
    else if (node.type == rt_DATA_TYPE_MAP) {
        for (
            rt_DataMap_iter_t it = rt_DataMap_begin(node.data.mp);
            it != rt_DataMap_end(node.data.mp);
            ++it
        ) {
            if (!rt_DataMap_exists(node.data.mp, it)) continue;
            const rt_DataMap_Entry_t *entry = rt_DataMap_get(node.data.mp, it);
            if (!entry) continue;
            /* explicit cast to non-const */
            rt_Data_t *ref = (rt_Data_t*) &entry->value;
            if (!ref) continue;
#ifdef GC_DEBUG
            printf("    type: %s, ref: %p, target: %p\n",
                rt_Data_typename(*ref),
                (void*) ref->data.mp,
                (void*) target.mp
            );
#endif
            if ( ref->type == rt_DATA_TYPE_STR
              || ref->type == rt_DATA_TYPE_INTERP_STR) {
                if (ref->data.str == target.str) {
                    ++(*count);
                    if (break_ref) *ref = rt_Data_null();
                }
                else rt_data_GC_cyclic_count_helper(*ref, target, count, break_ref);
            } else if (ref->type == rt_DATA_TYPE_LST) {
                if (ref->data.lst == target.lst) {
                    ++(*count);
                    if (break_ref) *ref = rt_Data_null();
                }
                else rt_data_GC_cyclic_count_helper(*ref, target, count, break_ref);
            } else if (ref->type == rt_DATA_TYPE_MAP) {
                if (ref->data.mp == target.mp) {
                    ++(*count);
                    if (break_ref) *ref = rt_Data_null();
                }
                else rt_data_GC_cyclic_count_helper(*ref, target, count, break_ref);
            }
        }
    }
}

#else
    #warning re-inclusion of module 'runtime/data/GarbageColl.c.h'
#endif
