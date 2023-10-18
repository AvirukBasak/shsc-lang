#ifndef RT_DATA_MAP_H
#define RT_DATA_MAP_H

#include <stddef.h>

#include "tlib/khash/khash.h"
#include "runtime/data/Data.h"

typedef struct {
    char *key;
    rt_Data_t value;
} rt_DataMapEntry_t;

KHASH_MAP_INIT_STR(rt_DataMap_t, rt_DataMapEntry_t)

struct rt_DataMap_t {
    khash_t(rt_DataMap_t) *data_map;
    int64_t length;
    int64_t rc;
};

typedef khiter_t rt_DataMap_iter_t;

rt_DataMap_t *rt_DataMap_init();
int64_t rt_DataMap_length(const rt_DataMap_t *mp);
void rt_DataMap_copy(rt_DataMap_t *mp);
void rt_DataMap_destroy(rt_DataMap_t **ptr);
void rt_DataMap_insert(rt_DataMap_t *mp, const char *key, rt_Data_t value);
const char *rt_DataMap_getkey_copy(const rt_DataMap_t *mp, const char *key);
/** unlike rt_DataMap_getref, returns NULL if key not found */
rt_Data_t *rt_DataMap_getref_errnull(const rt_DataMap_t *mp, const char *key);
/** unlike rt_DataMap_getref_errnull, CRASHES using rt_throw if key not found.
    data should be updated only by calling
    `void rt_VarTable_modf(rt_Data_t *dest, rt_Data_t src)`
    on the returned data pointer, that'll take care of reference counts */
rt_Data_t *rt_DataMap_getref(const rt_DataMap_t *mp, const char *key);
void rt_DataMap_del(rt_DataMap_t *mp, const char *key);
char *rt_DataMap_tostr(const rt_DataMap_t *mp);

rt_DataMap_iter_t rt_DataMap_begin(rt_DataMap_t *mp);
rt_DataMap_iter_t rt_DataMap_end(rt_DataMap_t *mp);
bool rt_DataMap_exists(rt_DataMap_t *mp, rt_DataMap_iter_t it);
const rt_DataMapEntry_t *rt_DataMap_get(rt_DataMap_t *mp, rt_DataMap_iter_t it);

#endif
