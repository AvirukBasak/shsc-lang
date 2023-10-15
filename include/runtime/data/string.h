#ifndef RT_DATA_STRING_H
#define RT_DATA_STRING_H

#include <stddef.h>
#include <stdint.h>

#include "runtime/data.h"

struct RT_DataStr_t {
    char *var;
    int64_t length;
    size_t capacity;
    int64_t rc;
};

RT_DataStr_t *RT_DataStr_init(const char *s);
int64_t RT_DataStr_length(const RT_DataStr_t *str);
void RT_DataStr_copy(RT_DataStr_t *str);
void RT_DataStr_destroy(RT_DataStr_t **ptr);
void RT_DataStr_append(RT_DataStr_t *str, char ch);
/** data can be updated by assigning a char to the returned pointer */
char *RT_DataStr_getref(const RT_DataStr_t *str, int64_t idx);
void RT_DataStr_del_index(RT_DataStr_t *str, int64_t idx);
void RT_DataStr_del_char(RT_DataStr_t *str, char ch);

#endif
