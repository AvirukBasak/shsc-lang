#ifndef RT_DATA_LIBHANDLE_H
#define RT_DATA_LIBHANDLE_H

#include <stdbool.h>
#include <stddef.h>

#include "runtime/data/Data.h"

struct rt_DataLibHandle_t {
    char *file_name;
    void *handle;
    int64_t rc;
};

rt_DataLibHandle_t *rt_DataLibHandle_init(char *file_name);
rt_DataLibHandle_t *rt_DataLibHandle_clone(const rt_DataLibHandle_t *handle);

void rt_DataLibHandle_increfc(rt_DataLibHandle_t *handle);
void rt_DataLibHandle_decrefc(rt_DataLibHandle_t *handle);

void rt_DataLibHandle_destroy(rt_DataLibHandle_t **ptr);

rt_fn_NativeFunction_t rt_DataLibHandle_lookup(const rt_DataLibHandle_t *handle, const char *fname);
char *rt_DataLibHandle_tostr(const rt_DataLibHandle_t *handle);

#endif
