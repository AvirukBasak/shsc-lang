#ifndef RT_DATA_MAP_C_H
#define RT_DATA_MAP_C_H

#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "errcodes.h"
#include "runtime/data.h"
#include "runtime/data/map.h"
#include "runtime/data/string.h"
#include "runtime/io.h"
#include "tlib/khash/khash.h"

RT_DataMap_t *RT_DataMap_init()
{
    RT_DataMap_t *mp = (RT_DataMap_t*) malloc(sizeof(RT_DataMap_t));
    if (!mp) io_errndie("RT_DataMap_init:" ERR_MSG_MALLOCFAIL);
    mp->data_map = NULL;
    mp->length = 0;
    /* rc is kept at 0 unless the runtime assigns
       a variable to the data */
    mp->rc = 0;
    return mp;
}

int64_t RT_DataMap_length(const RT_DataMap_t *mp)
{
    return mp->length;
}

void RT_DataMap_copy(RT_DataMap_t *mp)
{
    ++mp->rc;
}

void RT_DataMap_destroy(RT_DataMap_t **ptr)
{
    if (!ptr || !*ptr) return;
    RT_DataMap_t *mp = *ptr;
    /* ref counting */
    --mp->rc;
    if (mp->rc < 0) mp->rc = 0;
    if (mp->rc > 0) return;
    /* free if rc 0, iterate through each entry and destroy it */
    for (khiter_t entry_it = kh_begin(mp->data_map); entry_it != kh_end(mp->data_map); ++entry_it) {
        if (kh_exist(mp->data_map, entry_it))
            /* decrement refcnt, if 0, data gets destroyed */
            RT_Data_destroy(&(kh_value(mp->data_map, entry_it)));
    }
    kh_destroy(RT_DataMap_t, mp->data_map);
    mp->data_map = NULL;
    free(mp);
    *ptr = NULL;
}

void RT_DataMap_insert(RT_DataMap_t *mp, const char *key, RT_Data_t value)
{
    RT_Data_copy(&value);
    if (!mp->data_map) mp->data_map = kh_init(RT_DataMap_t);
    khiter_t entry_it = kh_get(RT_DataMap_t, mp->data_map, key);
    if (entry_it != kh_end(mp->data_map)) {
        /* key exists, reduce original value ref count */
        RT_Data_destroy(&kh_value(mp->data_map, entry_it));
    } else {
        int ret;
        /* key doesn't exist, create key */
        entry_it = kh_put(RT_DataMap_t, mp->data_map, key, &ret);
        ++mp->length;
    }
    kh_value(mp->data_map, entry_it) = value;
}

RT_Data_t *RT_DataMap_getref__n(const RT_DataMap_t *mp, const char *key)
{
    khiter_t entry_it = kh_get(RT_DataMap_t, mp->data_map, key);
    /* key found, return its value */
    if (entry_it != kh_end(mp->data_map))
        return &kh_value(mp->data_map, entry_it);
    return NULL;
}

RT_Data_t *RT_DataMap_getref(const RT_DataMap_t *mp, const char *key)
{
    RT_Data_t *data = RT_DataMap_getref__n(mp, key);
    if (!data) rt_throw("map has no key '%s'", key);
    return NULL;
}

void RT_DataMap_del(RT_DataMap_t *mp, const char *key)
{
    khiter_t entry_it = kh_get(RT_DataMap_t, mp->data_map, key);
    if (entry_it == kh_end(mp->data_map)) rt_throw("map has no key '%s'", key);
    RT_Data_destroy(&kh_value(mp->data_map, entry_it));
    --mp->length;
    if (mp->length == 0) {
        kh_destroy(RT_DataMap_t, mp->data_map);
        mp->data_map = NULL;
    }
}

char *RT_DataMap_tostr(const RT_DataMap_t *mp)
{
    size_t size = 3;
    char *str = (char*) malloc(size * sizeof(char));
    if (!str) io_errndie("RT_DataMap_tostr:" ERR_MSG_MALLOCFAIL);
    int p = 0;
    sprintf(&str[p++], "{");
    for (khiter_t entry_it = kh_begin(mp->data_map); entry_it != kh_end(mp->data_map); ++entry_it) {
        const char *mp_ky = kh_key(mp->data_map, entry_it);
        char *mp_el = RT_Data_tostr(kh_value(mp->data_map, entry_it));
        /** size values:  "        %s         "   : \x20       %s       \x00 */
        const size_t sz = 1 + strlen(mp_ky) + 1 + 1 + 1 + strlen(mp_el) + 1;
        str = (char*) realloc(str, (size += sz) * sizeof(char));
        if (!str) io_errndie("RT_DataMap_tostr:" ERR_MSG_REALLOCFAIL);
        sprintf(&str[p], "\"%s\": %s", mp_ky, mp_el);
        free(mp_el);
        mp_ky = mp_el = NULL;
        p += sz -1;
        if (entry_it != kh_end(mp->data_map) - 1) {
            str = (char*) realloc(str, (size += 2) * sizeof(char));
            if (!str) io_errndie("RT_DataMap_tostr:" ERR_MSG_REALLOCFAIL);
            sprintf(&str[p], ", ");
            p += 2;
        }
    }
    sprintf(&str[p++], "}");
    return str;
}

#else
    #warning re-inclusion of module 'runtime/data/map.c.h'
#endif
