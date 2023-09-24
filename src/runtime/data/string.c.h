#ifndef RT_DATA_STRING_C_H
#define RT_DATA_STRING_C_H

#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "errcodes.h"
#include "runtime/data.h"
#include "runtime/data/string.h"
#include "runtime/io.h"

RT_DataStr_t *RT_DataStr_init(const char *s)
{
    RT_DataStr_t *str = (RT_DataStr_t*) malloc(sizeof(RT_DataStr_t));
    if (!str) io_errndie("RT_DataStr_init:" ERR_MSG_MALLOCFAIL);
    str->length = !s ? 0 : strlen(s);
    str->capacity = !s ? 0 : (str->length +1);
    if (s) {
        str->var = (char*) malloc(str->capacity * sizeof(char) +1);
        if (!str->var) io_errndie("RT_DataStr_init:" ERR_MSG_MALLOCFAIL);
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

int64_t RT_DataStr_length(const RT_DataStr_t *str)
{
    return str->length;
}

void RT_DataStr_destroy(RT_DataStr_t **ptr)
{
    if (!ptr || !*ptr) return;
    RT_DataStr_t *str = *ptr;
    free(str->var);
    str->var = NULL;
    free(str);
    *ptr = NULL;
}

void RT_DataStr_append(RT_DataStr_t *str, char var)
{
    if (str->length >= str->capacity) {
        str->capacity = str->capacity * 2 +2;
        str->var = (char*) realloc(str->var, str->capacity * sizeof(char));
        if (!str->var) io_errndie("RT_DataStr_append:" ERR_MSG_REALLOCFAIL);
    }
    str->var[str->length++] = var;
    str->var[str->length] = '\0';
}

char *RT_DataStr_getref(const RT_DataStr_t *str, int64_t idx)
{
    if (idx >= 0 && idx < str->length)
        return &str->var[idx];
    else rt_throw("string out of bounds for index '%" PRId64 "'", idx);
    return NULL;
}

void RT_DataStr_del_index(RT_DataStr_t *str, int64_t idx)
{
    if (idx >= 0 && idx < str->length) {
        for (int64_t i = idx + 1; i < str->length; i++)
            str->var[i-1] = str->var[i];
        --str->length;
        str->var[str->length] = '\0';
    } else rt_throw("string out of bounds for index '%" PRId64 "'", idx);
}

void RT_DataStr_del_val(RT_DataStr_t *str, char var)
{
    for (int64_t i = 0; i < str->length; i++) {
        if (str->var[i] == var) {
            RT_DataStr_del_index(str, i);
            --i;
        }
    }
}

#else
    #warning re-inclusion of module 'runtime/data/string.c.h'
#endif
