#ifndef RT_DATA_MAP_C_H
#define RT_DATA_MAP_C_H

#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "errcodes.h"
#include "runtime/data/Data.h"
#include "runtime/data/DataMap.h"
#include "runtime/data/DataStr.h"
#include "runtime/io.h"
#include "tlib/khash/khash.h"

rt_DataMap_t *rt_DataMap_init()
{
    rt_DataMap_t *mp = (rt_DataMap_t*) malloc(sizeof(rt_DataMap_t));
    if (!mp) io_errndie("rt_DataMap_init:" ERR_MSG_MALLOCFAIL);
    mp->data_map = kh_init(rt_DataMap_t);
    mp->length = 0;
    /* rc is kept at 0 unless the runtime assigns
       a variable to the data */
    mp->rc = 0;
    return mp;
}

int64_t rt_DataMap_length(const rt_DataMap_t *mp)
{
    return mp->length;
}

void rt_DataMap_copy(rt_DataMap_t *mp)
{
    ++mp->rc;
}

void rt_DataMap_destroy(rt_DataMap_t **ptr)
{
    if (!ptr || !*ptr) return;
    rt_DataMap_t *mp = *ptr;
    /* ref counting */
    --mp->rc;
    if (mp->rc < 0) mp->rc = 0;
    if (mp->rc > 0) return;
    /* free if rc 0, iterate through each entry and destroy it */
    for (khiter_t entry_it = kh_begin(mp->data_map); entry_it != kh_end(mp->data_map); ++entry_it) {
        if (!kh_exist(mp->data_map, entry_it)) continue;
        /* decrement refcnt, if 0, data gets destroyed */
        rt_Data_destroy(&kh_value(mp->data_map, entry_it).value);
        /* free the key */
        free(kh_value(mp->data_map, entry_it).key);
    }
    kh_destroy(rt_DataMap_t, mp->data_map);
    mp->data_map = NULL;
    free(mp);
    *ptr = NULL;
}

void rt_DataMap_insert(rt_DataMap_t *mp, const char *key, rt_Data_t value)
{
    rt_Data_copy(&value);
    khiter_t entry_it = kh_get(rt_DataMap_t, mp->data_map, key);
    if (entry_it != kh_end(mp->data_map)) {
        /* key exists, reduce original value ref count */
        rt_Data_destroy(&kh_value(mp->data_map, entry_it).value);
    } else {
        int ret;
        /* key doesn't exist, create duplicate key and have kh keep a reference
           to it so that the key can be accessed via kh_key macro */
        char *key_internal = strdup(key);
        entry_it = kh_put(rt_DataMap_t, mp->data_map, key_internal, &ret);
        kh_value(mp->data_map, entry_it).key = key_internal;
        ++mp->length;
    }
    kh_value(mp->data_map, entry_it).value = value;
}

rt_Data_t *rt_DataMap_getref_errnull(const rt_DataMap_t *mp, const char *key)
{
    khiter_t entry_it = kh_get(rt_DataMap_t, mp->data_map, key);
    /* key found, return its value */
    if (entry_it != kh_end(mp->data_map))
        return &kh_value(mp->data_map, entry_it).value;
    return NULL;
}

rt_Data_t *rt_DataMap_getref(const rt_DataMap_t *mp, const char *key)
{
    rt_Data_t *data = rt_DataMap_getref_errnull(mp, key);
    if (!data) rt_throw("map has no key '%s'", key);
    return NULL;
}

void rt_DataMap_del(rt_DataMap_t *mp, const char *key)
{
    khiter_t entry_it = kh_get(rt_DataMap_t, mp->data_map, key);
    if (entry_it == kh_end(mp->data_map)) rt_throw("map has no key '%s'", key);
    rt_Data_destroy(&kh_value(mp->data_map, entry_it).value);
    free(kh_value(mp->data_map, entry_it).key);
    --mp->length;
}

char *rt_DataMap_tostr(const rt_DataMap_t *mp)
{
    size_t size = 3;
    char *str = (char*) malloc(size * sizeof(char));
    if (!str) io_errndie("rt_DataMap_tostr:" ERR_MSG_MALLOCFAIL);
    int p = 0,
        count_len = 0;
    sprintf(&str[p++], "{");
    for (khiter_t entry_it = kh_begin(mp->data_map); entry_it != kh_end(mp->data_map); ++entry_it) {
        if (!kh_exist(mp->data_map, entry_it)) continue;

        const char *mp_ky = kh_key(mp->data_map, entry_it);

        const rt_Data_t data_val = kh_value(mp->data_map, entry_it).value;
        char *mp_el = rt_Data_tostr(data_val);
        char *mp_el_escaped = io_partial_escape_string(mp_el);
        free(mp_el);
        mp_el = NULL;

        char *delim = "";
        if (data_val.type == rt_DATA_TYPE_CHR) delim = "'";
        else if (data_val.type == rt_DATA_TYPE_STR
              || data_val.type == rt_DATA_TYPE_INTERP_STR) delim = "\"";

        /** size values:  "        %s         "   : \x20     <delim>                 %s              <delim>    \x00 */
        const size_t sz = 1 + strlen(mp_ky) + 1 + 1 + 1 + strlen(delim) + strlen(mp_el_escaped) + strlen(delim) + 1;
        str = (char*) realloc(str, (size += sz) * sizeof(char));
        if (!str) io_errndie("rt_DataMap_tostr:" ERR_MSG_REALLOCFAIL);

        sprintf(&str[p], "\"%s\": %s%s%s", mp_ky, delim, mp_el_escaped, delim);

        free(mp_el_escaped);
        mp_ky = mp_el_escaped = NULL;
        p += sz -1;
        if (count_len++ < mp->length -1) {
            str = (char*) realloc(str, (size += 2) * sizeof(char));
            if (!str) io_errndie("rt_DataMap_tostr:" ERR_MSG_REALLOCFAIL);
            sprintf(&str[p], ", ");
            p += 2;
        }
    }
    sprintf(&str[p++], "}");
    return str;
}

rt_DataMap_iter_t rt_DataMap_begin(rt_DataMap_t *mp)
{
    return kh_begin(mp->data_map);
}

rt_DataMap_iter_t rt_DataMap_end(rt_DataMap_t *mp)
{
    return kh_end(mp->data_map);
}

bool rt_DataMap_exists(rt_DataMap_t *mp, rt_DataMap_iter_t it)
{
    return kh_exist(mp->data_map, it);
}

const rt_DataMapEntry_t *rt_DataMap_get(rt_DataMap_t *mp, rt_DataMap_iter_t it)
{
    if (!kh_exist(mp->data_map, it)) return NULL;
    return &kh_value(mp->data_map, it);
}

#else
    #warning re-inclusion of module 'runtime/data/DataMap.c.h'
#endif
