#ifndef RT_DATA_STRING_C_H
#define RT_DATA_STRING_C_H

#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "errcodes.h"
#include "runtime/data/Data.h"
#include "runtime/data/DataList.h"
#include "runtime/data/DataStr.h"
#include "runtime/io.h"

rt_DataStr_t *rt_DataStr_init(const char *s)
{
    rt_DataStr_t *str = (rt_DataStr_t*) malloc(sizeof(rt_DataStr_t));
    if (!str) io_errndie("rt_DataStr_init:" ERR_MSG_MALLOCFAIL);
    str->var = rt_DataList_init();
    int64_t length = strlen(s);
    for (int64_t i = 0; i < length; i++)
        rt_DataList_append(str->var, rt_Data_chr(s[i]));
    return str;
}

int64_t rt_DataStr_length(const rt_DataStr_t *str)
{
    return rt_DataList_length(str->var);
}

void rt_DataStr_increfc(rt_DataStr_t *str)
{
    rt_DataList_increfc(str->var);
}

void rt_DataStr_decrefc(rt_DataStr_t *str)
{
    rt_DataList_decrefc(str->var);
}

void rt_DataStr_destroy_circular(rt_DataStr_t **ptr, bool flag)
{
    if (!ptr || !*ptr) return;
    rt_DataList_destroy_circular(&(*ptr)->var, flag);
    /* free wrapper only if the list inside was freed and nulled */
    if ((*ptr)->var) return;
    free(*ptr);
    *ptr = NULL;
}

void rt_DataStr_destroy(rt_DataStr_t **ptr)
{
    rt_DataStr_destroy_circular(ptr, false);
}

void rt_DataStr_append(rt_DataStr_t *str, char var)
{
    rt_DataList_append(str->var, rt_Data_chr(var));
}

char *rt_DataStr_getref_errnull(const rt_DataStr_t *str, int64_t idx)
{
    if (idx >= 0 && idx < rt_DataStr_length(str))
        return &rt_DataList_getref_errnull(str->var, idx)->data.chr;
    return NULL;
}

rt_Data_t *rt_DataStr_getref(const rt_DataStr_t *str, int64_t idx)
{
    if (idx >= 0 && idx < rt_DataStr_length(str))
        return rt_DataList_getref(str->var, idx);
    else rt_throw("string out of bounds for index '%" PRId64 "'", idx);
    return NULL;
}

void rt_DataStr_del_index(rt_DataStr_t *str, int64_t idx)
{
    if (idx >= 0 && idx < rt_DataStr_length(str)) {
        rt_DataList_del_index(str->var, idx);
    }
    else rt_throw("string out of bounds for index '%" PRId64 "'", idx);
}

void rt_DataStr_del_val(rt_DataStr_t *str, char var)
{
    rt_DataList_del_val(str->var, rt_Data_chr(var));
}

char *rt_DataStr_tostr(const rt_DataStr_t *str)
{
    int64_t length = rt_DataStr_length(str);
    char *s = (char*) malloc((length + 1) * sizeof(char));
    if (!s) io_errndie("rt_DataStr_tostr:" ERR_MSG_MALLOCFAIL);
    for (int64_t i = 0; i < length; i++)
        s[i] = rt_DataList_getref(str->var, i)->data.chr;
    s[length] = '\0';
    return s;
}

#else
    #warning re-inclusion of module 'runtime/data/DataStr.c.h'
#endif
