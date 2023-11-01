#ifndef RT_DATA_STRING_H
#define RT_DATA_STRING_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "runtime/data/Data.h"

struct rt_DataStr_t {
    rt_DataList_t *var;
};

rt_DataStr_t *rt_DataStr_init(const char *s);
int64_t rt_DataStr_length(const rt_DataStr_t *str);
void rt_DataStr_copy(rt_DataStr_t *str);
void rt_DataStr_destroy_circular(rt_DataStr_t **ptr, bool flag);
void rt_DataStr_destroy(rt_DataStr_t **ptr);
void rt_DataStr_append(rt_DataStr_t *str, char ch);
char *rt_DataStr_getref_errnull(const rt_DataStr_t *str, int64_t idx);
/** data can be updated by assigning a char to the returned pointer */
rt_Data_t *rt_DataStr_getref(const rt_DataStr_t *str, int64_t idx);
void rt_DataStr_del_index(rt_DataStr_t *str, int64_t idx);
void rt_DataStr_del_char(rt_DataStr_t *str, char ch);
char *rt_DataStr_tostr(const rt_DataStr_t *str);

#endif
