#ifndef RT_DATA_STRING_C_H
#define RT_DATA_STRING_C_H

#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "globals.h"
#include "io.h"
#include "errcodes.h"
#include "runtime/data/Data.h"
#include "runtime/data/DataStr.h"
#include "runtime/io.h"

rt_DataStr_t *rt_DataStr_init(const char *s)
{
    rt_DataStr_t *str = (rt_DataStr_t*) shsc_malloc(sizeof(rt_DataStr_t));
    if (!str) io_errndie("rt_DataStr_init:" ERR_MSG_MALLOCFAIL);
    str->length = !s ? 0 : strlen(s);
    str->capacity = !s ? 0 : (str->length +1);
    if (s) {
        str->var = (char*) shsc_malloc(str->capacity * sizeof(char) +1);
        if (!str->var) io_errndie("rt_DataStr_init:" ERR_MSG_MALLOCFAIL);
        strncpy(str->var, s, str->length);
        str->var[str->length] = 0;
    } else {
        str->var = NULL;
    }
    /* rc is kept at 0 unless the runtime assigns
       a variable to the data */
    str->rc = 0;
    return str;
}

int64_t rt_DataStr_length(const rt_DataStr_t *str)
{
    return str->length;
}

void rt_DataStr_copy(rt_DataStr_t *str)
{
    ++str->rc;
}

void rt_DataStr_destroy(rt_DataStr_t **ptr)
{
    if (!ptr || !*ptr) return;
    rt_DataStr_t *str = *ptr;
    /* ref counting */
    --str->rc;
    if (str->rc < 0) str->rc = 0;
    if (str->rc > 0) return;
    /* free if rc 0 */
    shsc_free(str->var);
    str->var = NULL;
    shsc_free(str);
    *ptr = NULL;
}

void rt_DataStr_append(rt_DataStr_t *str, char var)
{
    if (str->length >= str->capacity) {
        str->capacity = str->capacity * 2 +2;
        str->var = (char*) shsc_realloc(str->var, str->capacity * sizeof(char));
        if (!str->var) io_errndie("rt_DataStr_append:" ERR_MSG_REALLOCFAIL);
    }
    str->var[str->length++] = var;
    str->var[str->length] = '\0';
}

char *rt_DataStr_getref(const rt_DataStr_t *str, int64_t idx)
{
    if (idx >= 0 && idx < str->length)
        return &str->var[idx];
    else rt_throw("string out of bounds for index '%" PRId64 "'", idx);
    return NULL;
}

void rt_DataStr_del_index(rt_DataStr_t *str, int64_t idx)
{
    if (idx >= 0 && idx < str->length) {
        for (int64_t i = idx + 1; i < str->length; i++)
            str->var[i-1] = str->var[i];
        --str->length;
        str->var[str->length] = '\0';
    } else rt_throw("string out of bounds for index '%" PRId64 "'", idx);
}

void rt_DataStr_del_val(rt_DataStr_t *str, char var)
{
    for (int64_t i = 0; i < str->length; i++) {
        if (str->var[i] == var) {
            rt_DataStr_del_index(str, i);
            --i;
        }
    }
}

#else
    #warning re-inclusion of module 'runtime/data/DataStr.c.h'
#endif
