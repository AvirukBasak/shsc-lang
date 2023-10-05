#ifndef RT_DATA_MAP_H
#define RT_DATA_MAP_H

#include <stddef.h>
#include "tlib/khash/khash.h"
#include "runtime/data.h"

KHASH_MAP_INIT_STR(RT_DataMap_t, RT_Data_t)

struct RT_DataMap_t {
    khash_t(RT_DataMap_t) *data_map;
    int64_t length;
    int64_t rc;
};

RT_DataMap_t *RT_DataMap_init();
int64_t RT_DataMap_length(const RT_DataMap_t *mp);
void RT_DataMap_copy(RT_DataMap_t *mp);
void RT_DataMap_destroy(RT_DataMap_t **ptr);
void RT_DataMap_insert(RT_DataMap_t *mp, const char *key, RT_Data_t value);
/** unlike RT_DataMap_getref, returns NULL if key not found */
RT_Data_t *RT_DataMap_getref__n(const RT_DataMap_t *mp, const char *key);
/** unlike RT_DataMap_getref__n, CRASHES using rt_throw if key not found.
    data should be updated only by calling
    `void RT_VarTable_modf(RT_Data_t *dest, RT_Data_t src)`
    on the returned data pointer, that'll take care of reference counts */
RT_Data_t *RT_DataMap_getref(const RT_DataMap_t *mp, const char *key);
void RT_DataMap_del(RT_DataMap_t *mp, const char *key);
char *RT_DataMap_tostr(const RT_DataMap_t *mp);

#endif
