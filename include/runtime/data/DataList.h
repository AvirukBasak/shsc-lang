#ifndef RT_DATA_LIST_H
#define RT_DATA_LIST_H

#include <stddef.h>

#include "runtime/data/Data.h"

struct RT_DataList_t {
    RT_Data_t *var;
    int64_t length;
    size_t capacity;
    int64_t rc;
};

RT_DataList_t *RT_DataList_init();
int64_t RT_DataList_length(const RT_DataList_t *lst);
void RT_DataList_copy(RT_DataList_t *lst);
void RT_DataList_destroy(RT_DataList_t **ptr);
void RT_DataList_append(RT_DataList_t *lst, RT_Data_t var);
/** data should be updated only by calling
    `void RT_VarTable_modf(RT_Data_t *dest, RT_Data_t src)`
    on the returned data pointer, that'll take care of reference counts */
RT_Data_t *RT_DataList_getref(const RT_DataList_t *lst, int64_t idx);
void RT_DataList_del_index(RT_DataList_t *lst, int64_t idx);
void RT_DataList_del_val(RT_DataList_t *lst, RT_Data_t var);
char *RT_DataList_tostr(const RT_DataList_t *lst);

#endif
