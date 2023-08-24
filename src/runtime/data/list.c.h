#ifndef RT_DATA_LIST_C_H
#define RT_DATA_LIST_C_H

#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "errcodes.h"
#include "runtime/data.h"
#include "runtime/data/list.h"
#include "runtime/data/string.h"
#include "runtime/io.h"

RT_DataList_t *RT_DataList_init()
{
    RT_DataList_t *lst = (RT_DataList_t*) malloc(sizeof(RT_DataList_t));
    if (!lst) io_errndie("RT_DataList_init:" ERR_MSG_MALLOCFAIL);
    lst->var = NULL;
    lst->length = 0;
    lst->capacity = 0;
    /* rc is kept at 0 unless the runtime assigns
       a variable to the data */
    lst->rc = 0;
    return lst;
}

int64_t RT_DataList_length(const RT_DataList_t *lst)
{
    return lst->length;
}

void RT_DataList_destroy(RT_DataList_t **ptr)
{
    if (!ptr || !*ptr) return;
    RT_DataList_t *lst = *ptr;
    for (int64_t i = 0; i < lst->length; i++) {
        RT_Data_t var = lst->var[i];
        if (var.type == RT_DATA_TYPE_STR || var.type == RT_DATA_TYPE_INTERP_STR) {
            free(var.data.str);
            var.data.str = NULL;
            var.type = RT_DATA_TYPE_ANY;
        } else if (var.type == RT_DATA_TYPE_LST)
            RT_DataList_destroy(&var.data.lst);
    }
    free(lst->var);
    lst->var = NULL;
    free(lst);
    *ptr = NULL;
}

void RT_DataList_append(RT_DataList_t *lst, RT_Data_t var)
{
    if (lst->length >= lst->capacity) {
        lst->capacity = lst->capacity * 2 +1;
        lst->var = (RT_Data_t*) realloc(lst->var, lst->capacity * sizeof(RT_Data_t));
        if (!lst->var) io_errndie("RT_DataList_append:" ERR_MSG_REALLOCFAIL);
    }
    lst->var[lst->length++] = var;
}

RT_Data_t *RT_DataList_getref(const RT_DataList_t *lst, int64_t idx)
{
    if (idx >= 0 && idx < lst->length)
        return &lst->var[idx];
    else rt_throw("list out of bounds for index '%" PRId64 "'", idx);
    return NULL;
}

void RT_DataList_del_index(RT_DataList_t *lst, int64_t idx)
{
    if (idx >= 0 && idx < lst->length) {
        RT_Data_t var = lst->var[idx];
        if (var.type == RT_DATA_TYPE_STR || var.type == RT_DATA_TYPE_INTERP_STR)
            free(var.data.str);
        for (int64_t i = idx + 1; i < lst->length; i++)
            lst->var[i-1] = lst->var[i];
        --lst->length;
    } else rt_throw("list out of bounds for index '%" PRId64 "'", idx);
}

void RT_DataList_del_val(RT_DataList_t *lst, RT_Data_t var)
{
    for (int64_t i = 0; i < lst->length; i++) {
        if (memcmp(&lst->var[i], &var, sizeof(RT_Data_t)) == 0) {
            RT_DataList_del_index(lst, i);
            --i;
        }
    }
}

char *RT_DataList_tostr(const RT_DataList_t *lst)
{
    char *str = (char*) malloc(3 * sizeof(char));
    if (!str) io_errndie("RT_DataList_tostr:" ERR_MSG_MALLOCFAIL);
    int p = 0;
    size_t size = 3;
    sprintf(str + p++, "[");
    for (int64_t i = 0; i < lst->length; ++i) {
        char *lst_el = RT_Data_tostr(lst->var[i]);
        const size_t sz = strlen(lst_el) +1;
        str = (char*) realloc(str, (size += sz) * sizeof(char));
        if (!str) io_errndie("RT_DataList_tostr:" ERR_MSG_REALLOCFAIL);
        sprintf(str + p, "%s", lst_el);
        free(lst_el);
        lst_el = NULL;
        p += sz;
        if (i != lst->length - 1) {
            str = (char*) realloc(str, (size += 2) * sizeof(char));
            if (!str) io_errndie("RT_DataList_tostr:" ERR_MSG_REALLOCFAIL);
            sprintf(str + p, ", ");
            p += 2;
        }
    }
    sprintf(str + p++, "]");
    return str;
}

#else
    #warning re-inclusion of module 'runtime/data/list.c.h'
#endif
