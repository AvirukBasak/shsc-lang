#ifndef RT_DATA_LIST_H
#define RT_DATA_LIST_H

#include <stdbool.h>
#include <stddef.h>

#include "runtime/data/Data.h"

struct rt_DataList_t {
    rt_Data_t *var;
    int64_t length;
    size_t capacity;
    int64_t rc;
};


/* macro that takes a variable number of rt_Data_t type arguments
   and calls rt_DataList_append for each item */
#define rt_DataList_from(...)                                \
    ({                                                       \
        rt_Data_t _args[] = { __VA_ARGS__ };                 \
        size_t args_len = sizeof(_args) / sizeof(rt_Data_t); \
        rt_DataList_t *lst = rt_DataList_init();             \
        for (size_t i = 0; i < args_len; i++) {              \
            rt_DataList_append(lst, _args[i]);               \
        }                                                    \
        lst;                                                 \
    })


rt_DataList_t *rt_DataList_init();
rt_DataList_t *rt_DataList_clone(const rt_DataList_t *lst);

int64_t rt_DataList_length(const rt_DataList_t *lst);
void rt_DataList_increfc(rt_DataList_t *lst);
void rt_DataList_decrefc(rt_DataList_t *lst);

void rt_DataList_destroy_circular(rt_DataList_t **ptr, bool flag);
void rt_DataList_destroy(rt_DataList_t **ptr);

void rt_DataList_append(rt_DataList_t *lst, rt_Data_t var);
void rt_DataList_concat(rt_DataList_t *lst, const rt_DataList_t *lst2);
void rt_DataList_insert(rt_DataList_t *lst, int64_t idx, rt_Data_t var);
void rt_DataList_erase(rt_DataList_t *lst, int64_t idx, int64_t len);
void rt_DataList_reverse(rt_DataList_t *lst);
int64_t rt_DataList_find(const rt_DataList_t *lst, rt_Data_t var);
rt_DataList_t *rt_DataList_sublist(const rt_DataList_t *lst, int64_t idx, int64_t len);
rt_DataStr_t *rt_DataList_join(const rt_DataList_t *lst, const rt_DataStr_t *sep);
rt_DataList_t *rt_DataList_sort(rt_DataList_t *lst);

rt_Data_t *rt_DataList_getref_errnull(const rt_DataList_t *lst, int64_t idx);
/** data should be updated only by calling
    `void rt_VarTable_modf(rt_Data_t *dest, rt_Data_t src)`
    on the returned data pointer, that'll take care of reference counts */
rt_Data_t *rt_DataList_getref(const rt_DataList_t *lst, int64_t idx);
void rt_DataList_del_index(rt_DataList_t *lst, int64_t idx);
void rt_DataList_del_val(rt_DataList_t *lst, rt_Data_t var);
char *rt_DataList_tostr(const rt_DataList_t *lst);

#endif
