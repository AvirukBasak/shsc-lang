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
rt_DataStr_t *rt_DataStr_clone(const rt_DataStr_t *str);

int64_t rt_DataStr_length(const rt_DataStr_t *str);
void rt_DataStr_increfc(rt_DataStr_t *str);
void rt_DataStr_decrefc(rt_DataStr_t *str);

void rt_DataStr_destroy_circular(rt_DataStr_t **ptr, bool flag);
void rt_DataStr_destroy(rt_DataStr_t **ptr);

void rt_DataStr_toupper              (rt_DataStr_t *str);
void rt_DataStr_tolower              (rt_DataStr_t *str);
void rt_DataStr_append               (rt_DataStr_t *str, char ch);
void rt_DataStr_concat               (rt_DataStr_t *str, const rt_DataStr_t *str2);
void rt_DataStr_insert               (rt_DataStr_t *str, int64_t idx, char ch);
void rt_DataStr_insert_str           (rt_DataStr_t *str, int64_t idx, const rt_DataStr_t *str2);
void rt_DataStr_erase                (rt_DataStr_t *str, int64_t idx, int64_t len);
void rt_DataStr_reverse              (rt_DataStr_t *str);
bool rt_DataStr_isequal              (const rt_DataStr_t *str, const rt_DataStr_t *str2);
int64_t rt_DataStr_compare           (const rt_DataStr_t *str, const rt_DataStr_t *str2);
int64_t rt_DataStr_find              (const rt_DataStr_t *str, char ch);
int64_t rt_DataStr_find_str          (const rt_DataStr_t *str, const rt_DataStr_t *str2);
rt_DataStr_t *rt_DataStr_substr      (const rt_DataStr_t *str, int64_t idx, int64_t len);
rt_DataList_t *rt_DataStr_split      (const rt_DataStr_t *str, char ch);
rt_DataList_t *rt_DataStr_split_str  (const rt_DataStr_t *str, const rt_DataStr_t *str2);
rt_DataStr_t *rt_DataStr_sort        (rt_DataStr_t *str);

rt_Data_t rt_DataStr_toi64           (const rt_DataStr_t *str);
rt_Data_t rt_DataStr_tof64           (const rt_DataStr_t *str);

char *rt_DataStr_getref_errnull(const rt_DataStr_t *str, int64_t idx);
/** data can be updated by assigning a char to the returned pointer */
rt_Data_t *rt_DataStr_getref(const rt_DataStr_t *str, int64_t idx);
void rt_DataStr_del_index(rt_DataStr_t *str, int64_t idx);
void rt_DataStr_del_val(rt_DataStr_t *str, char var);
char *rt_DataStr_tostr(const rt_DataStr_t *str);

#endif
