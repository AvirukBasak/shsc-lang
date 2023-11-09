#ifndef RT_DATA_LIST_C_H
#define RT_DATA_LIST_C_H

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "errcodes.h"
#include "runtime/data/Data.h"
#include "runtime/data/DataList.h"
#include "runtime/data/DataStr.h"
#include "runtime/data/GarbageColl.h"
#include "runtime/io.h"

rt_DataList_t *rt_DataList_init()
{
    rt_DataList_t *lst = (rt_DataList_t*) malloc(sizeof(rt_DataList_t));
    if (!lst) io_errndie("rt_DataList_init:" ERR_MSG_MALLOCFAIL);
    lst->var = NULL;
    lst->length = 0;
    lst->capacity = 0;
    /* rc is kept at 0 unless the runtime assigns
       a variable to the data */
    lst->rc = 0;
    return lst;
}

rt_DataList_t *rt_DataList_clone(const rt_DataList_t *lst)
{
    rt_DataList_t *lst2 = rt_DataList_init();
    for (int64_t i = 0; i < lst->length; i++)
        rt_DataList_append(lst2, lst->var[i]);
    return lst2;
}

int64_t rt_DataList_length(const rt_DataList_t *lst)
{
    return lst->length;
}

void rt_DataList_increfc(rt_DataList_t *lst)
{
    ++lst->rc;
}

void rt_DataList_decrefc(rt_DataList_t *lst)
{
    --lst->rc;
    if (lst->rc < 0) lst->rc = 0;
}

void rt_DataList_destroy_circular(rt_DataList_t **ptr, bool flag)
{
    if (!ptr || !*ptr) return;
    rt_DataList_t *lst = *ptr;
    /* ref counting */
    --lst->rc;
    if (lst->rc < 0) lst->rc = 0;
    if (lst->rc > 0) {
        /* if rc > 0, check if the data has only cyclic references
           if so, set rc to 0 to free the data */
        if (flag && rt_data_GC_has_only_cyclic_refcnt(rt_Data_list(lst))) {
            rt_data_GC_break_cycle(rt_Data_list(lst), rt_Data_list(lst));
            lst->rc = 0;
        }
        else return;
    }
    /* free if rc 0 */
    for (int64_t i = 0; i < lst->length; i++)
        rt_Data_destroy_circular(&lst->var[i], flag);
    free(lst->var);
    lst->var = NULL;
    free(lst);
    *ptr = NULL;
}

void rt_DataList_destroy(rt_DataList_t **ptr)
{
    rt_DataList_destroy_circular(ptr, false);
}

void rt_DataList_append(rt_DataList_t *lst, rt_Data_t var)
{
    rt_Data_increfc(&var);
    if (lst->length >= lst->capacity) {
        lst->capacity = lst->capacity * 2 +1;
        lst->var = (rt_Data_t*) realloc(lst->var, lst->capacity * sizeof(rt_Data_t));
        if (!lst->var) io_errndie("rt_DataList_append:" ERR_MSG_REALLOCFAIL);
    }
    lst->var[lst->length++] = (rt_Data_t) {
        .type = var.type,
        .data = var.data,
        .is_const = false,
        .is_weak = false,
    };
}

void rt_DataList_concat(rt_DataList_t *lst, const rt_DataList_t *lst2)
{
    for (int64_t i = 0; i < lst2->length; i++)
        rt_DataList_append(lst, lst2->var[i]);
}

void rt_DataList_insert(rt_DataList_t *lst, int64_t idx, rt_Data_t var)
{
    if (!(idx >= 0 && idx < lst->length))
        rt_throw("list out of bounds for index '%" PRId64 "'", idx);
    rt_Data_increfc(&var);
    if (lst->length >= lst->capacity) {
        lst->capacity = lst->capacity * 2 +1;
        lst->var = (rt_Data_t*) realloc(lst->var, lst->capacity * sizeof(rt_Data_t));
        if (!lst->var) io_errndie("rt_DataList_insert:" ERR_MSG_REALLOCFAIL);
    }
    for (int64_t i = lst->length; i > idx; i--)
        lst->var[i] = lst->var[i-1];
    lst->var[idx] = (rt_Data_t) {
        .type = var.type,
        .data = var.data,
        .is_const = false,
        .is_weak = false,
    };
    ++lst->length;
}

void rt_DataList_erase(rt_DataList_t *lst, int64_t idx, int64_t len)
{
    if (!(idx >= 0 && idx < lst->length))
        rt_throw("list out of bounds for index '%" PRId64 "'", idx);
    if (len < 0) len = 0;
    if (idx + len > lst->length) len = lst->length - idx;
    for (int64_t i = idx; i < idx + len; i++)
        rt_Data_destroy(&lst->var[i]);
    for (int64_t i = idx + len; i < lst->length; i++)
        lst->var[i - len] = lst->var[i];
    lst->length -= len;
}

void rt_DataList_reverse(rt_DataList_t *lst)
{
    for (int64_t i = 0; i < lst->length / 2; i++) {
        rt_Data_t tmp = lst->var[i];
        lst->var[i] = lst->var[lst->length - i - 1];
        lst->var[lst->length - i - 1] = tmp;
    }
}

int64_t rt_DataList_find(const rt_DataList_t *lst, rt_Data_t var)
{
    for (int64_t i = 0; i < lst->length; i++) {
        if (rt_Data_isequal(lst->var[i], var))
            return i;
    }
    return -1;
}

rt_DataList_t *rt_DataList_sublist(const rt_DataList_t *lst, int64_t idx, int64_t len)
{
    if (!(idx >= 0 && idx < lst->length))
        rt_throw("list out of bounds for index '%" PRId64 "'", idx);
    if (len < 0) len = 0;
    if (idx + len > lst->length) len = lst->length - idx;
    rt_DataList_t *sublist = rt_DataList_init();
    for (int64_t i = idx; i < idx + len; i++)
        rt_DataList_append(sublist, lst->var[i]);
    return sublist;
}

rt_DataStr_t *rt_DataList_join(const rt_DataList_t *lst, const rt_DataStr_t *sep)
{
    /* for each element, convert using rt_Data_tostr and create a new string object
       along with the seperator */
    rt_DataStr_t *str = rt_DataStr_init("");
    for (int64_t i = 0; i < lst->length; i++) {
        char *lst_el = rt_Data_tostr(lst->var[i]);
        rt_DataStr_concat(str, rt_DataStr_init(lst_el));
        free(lst_el);
        lst_el = NULL;
        if (i < lst->length - 1)
            rt_DataStr_concat(str, sep);
    }
    return str;
}

rt_DataList_t *rt_DataList_sort(rt_DataList_t *lst)
{
    /* implement quick sort algorithm, use rt_Data_compare */
    if (lst->length <= 1) return lst;
    rt_Data_t pivot = lst->var[lst->length - 1];
    rt_DataList_t *left = rt_DataList_init();
    rt_DataList_t *right = rt_DataList_init();
    for (int64_t i = 0; i < lst->length - 1; i++) {
        if (rt_Data_compare(lst->var[i], pivot) <= 0)
            rt_DataList_append(left, lst->var[i]);
        else rt_DataList_append(right, lst->var[i]);
    }
    rt_DataList_t *sorted_left = rt_DataList_sort(left);
    rt_DataList_t *sorted_right = rt_DataList_sort(right);
    rt_DataList_destroy(&left);
    rt_DataList_destroy(&right);
    rt_DataList_append(sorted_left, pivot);
    rt_DataList_concat(sorted_left, sorted_right);
    rt_DataList_destroy(&sorted_right);
    return sorted_left;
}

rt_Data_t *rt_DataList_getref_errnull(const rt_DataList_t *lst, int64_t idx)
{
    if (idx >= 0 && idx < lst->length)
        return &lst->var[idx];
    return NULL;
}

rt_Data_t *rt_DataList_getref(const rt_DataList_t *lst, int64_t idx)
{
    rt_Data_t *data = rt_DataList_getref_errnull(lst, idx);
    if (!data) rt_throw("list out of bounds for index '%" PRId64 "'", idx);
    return data;
}

void rt_DataList_del_index(rt_DataList_t *lst, int64_t idx)
{
    if (idx >= 0 && idx < lst->length) {
        rt_Data_destroy(&lst->var[idx]);
        for (int64_t i = idx + 1; i < lst->length; i++)
            lst->var[i-1] = lst->var[i];
        --lst->length;
    } else rt_throw("list out of bounds for index '%" PRId64 "'", idx);
}

void rt_DataList_del_val(rt_DataList_t *lst, rt_Data_t var)
{
    for (int64_t i = 0; i < lst->length; i++) {
        if (memcmp(&lst->var[i], &var, sizeof(rt_Data_t)) == 0) {
            rt_DataList_del_index(lst, i);
            --i;
        }
    }
}

char *rt_DataList_tostr(const rt_DataList_t *lst)
{
    size_t size = 3;
    char *str = (char*) malloc(size * sizeof(char));
    if (!str) io_errndie("rt_DataList_tostr:" ERR_MSG_MALLOCFAIL);
    int p = 0;
    sprintf(&str[p++], "[");
    for (int64_t i = 0; i < lst->length; ++i) {
        const rt_Data_t data_val = lst->var[i];
        char *lst_el = rt_Data_tostr(data_val);
        char *lst_el_escaped = io_partial_escape_string(lst_el);
        free(lst_el);
        lst_el = NULL;

        char *delim = "";
        if (lst->var[i].type == rt_DATA_TYPE_CHR) delim = "'";
        else if (data_val.type == rt_DATA_TYPE_STR
              || data_val.type == rt_DATA_TYPE_INTERP_STR) delim = "\"";

        /** size values:  "   <delim>               %s               <delim>     \x00 */
        const size_t sz = strlen(delim) + strlen(lst_el_escaped) + strlen(delim) + 1;
        str = (char*) realloc(str, (size += sz) * sizeof(char));
        if (!str) io_errndie("rt_DataList_tostr:" ERR_MSG_REALLOCFAIL);

        sprintf(&str[p], "%s%s%s", delim, lst_el_escaped, delim);

        free(lst_el_escaped);
        lst_el_escaped = NULL;
        p += sz -1;
        if (i < lst->length - 1) {
            str = (char*) realloc(str, (size += 2) * sizeof(char));
            if (!str) io_errndie("rt_DataList_tostr:" ERR_MSG_REALLOCFAIL);
            sprintf(&str[p], ", ");
            p += 2;
        }
    }
    sprintf(&str[p++], "]");
    return str;
}

#else
    #warning re-inclusion of module 'runtime/data/DataList.c.h'
#endif
