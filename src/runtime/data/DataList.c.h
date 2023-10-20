#ifndef RT_DATA_LIST_C_H
#define RT_DATA_LIST_C_H

#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "globals.h"
#include "io.h"
#include "errcodes.h"
#include "runtime/data/Data.h"
#include "runtime/data/DataList.h"
#include "runtime/data/DataStr.h"
#include "runtime/io.h"

rt_DataList_t *rt_DataList_init()
{
    rt_DataList_t *lst = (rt_DataList_t*) shsc_malloc(sizeof(rt_DataList_t));
    if (!lst) io_errndie("rt_DataList_init:" ERR_MSG_MALLOCFAIL);
    lst->var = NULL;
    lst->length = 0;
    lst->capacity = 0;
    /* rc is kept at 0 unless the runtime assigns
       a variable to the data */
    lst->rc = 0;
    return lst;
}

int64_t rt_DataList_length(const rt_DataList_t *lst)
{
    return lst->length;
}

void rt_DataList_copy(rt_DataList_t *lst)
{
    ++lst->rc;
}

void rt_DataList_destroy(rt_DataList_t **ptr)
{
    if (!ptr || !*ptr) return;
    rt_DataList_t *lst = *ptr;
    /* ref counting */
    --lst->rc;
    if (lst->rc < 0) lst->rc = 0;
    if (lst->rc > 0) return;
    /* free if rc 0 */
    for (int64_t i = 0; i < lst->length; i++)
        rt_Data_destroy(&lst->var[i]);
    shsc_free(lst->var);
    lst->var = NULL;
    shsc_free(lst);
    *ptr = NULL;
}

void rt_DataList_append(rt_DataList_t *lst, rt_Data_t var)
{
    rt_Data_copy(&var);
    if (lst->length >= lst->capacity) {
        lst->capacity = lst->capacity * 2 +1;
        lst->var = (rt_Data_t*) shsc_realloc(lst->var, lst->capacity * sizeof(rt_Data_t));
        if (!lst->var) io_errndie("rt_DataList_append:" ERR_MSG_REALLOCFAIL);
    }
    lst->var[lst->length++] = var;
}

rt_Data_t *rt_DataList_getref(const rt_DataList_t *lst, int64_t idx)
{
    if (idx >= 0 && idx < lst->length)
        return &lst->var[idx];
    else rt_throw("list out of bounds for index '%" PRId64 "'", idx);
    return NULL;
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
    char *str = (char*) shsc_malloc(size * sizeof(char));
    if (!str) io_errndie("rt_DataList_tostr:" ERR_MSG_MALLOCFAIL);
    int p = 0;
    sprintf(&str[p++], "[");
    for (int64_t i = 0; i < lst->length; ++i) {
        const rt_Data_t data_val = lst->var[i];
        char *lst_el = rt_Data_tostr(data_val);
        char *lst_el_escaped = io_partial_escape_string(lst_el);
        shsc_free(lst_el);
        lst_el = NULL;

        char *delim = "";
        if (lst->var[i].type == rt_DATA_TYPE_CHR) delim = "'";
        else if (data_val.type == rt_DATA_TYPE_STR
              || data_val.type == rt_DATA_TYPE_INTERP_STR) delim = "\"";

        /** size values:  "   <delim>               %s               <delim>     \x00 */
        const size_t sz = strlen(delim) + strlen(lst_el_escaped) + strlen(delim) + 1;
        str = (char*) shsc_realloc(str, (size += sz) * sizeof(char));
        if (!str) io_errndie("rt_DataList_tostr:" ERR_MSG_REALLOCFAIL);

        sprintf(&str[p], "%s%s%s", delim, lst_el_escaped, delim);

        shsc_free(lst_el_escaped);
        lst_el_escaped = NULL;
        p += sz -1;
        if (i < lst->length - 1) {
            str = (char*) shsc_realloc(str, (size += 2) * sizeof(char));
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
