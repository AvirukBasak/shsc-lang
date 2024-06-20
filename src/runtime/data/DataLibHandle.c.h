#ifndef RT_DATA_LIBHANDLE_C_H
#define RT_DATA_LIBHANDLE_C_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "errcodes.h"
#include "runtime/data/Data.h"
#include "runtime/data/DataLibHandle.h"
#include "runtime/io.h"
#include "runtime/util/libloader.h"
#include "runtime/util/loadfn.h"

#ifdef _WIN32
    #include <windows.h>
#else
    #include <dlfcn.h>
#endif

rt_DataLibHandle_t *rt_DataLibHandle_init(char *file_name)
{
    const char *dot = strrchr(file_name, '.');

    /* if filename ends with .dll or .so throw error */
    if (dot && ( !strcmp(dot, ".dll") || !strcmp(dot, ".so") )) {
        rt_throw("library file name should not end with '%s'", dot);
    }

    file_name = realloc(file_name, strlen(file_name) + 16);
    if (!file_name) io_errndie("rt_DataLibHandle_init:" ERR_MSG_MALLOCFAIL);

#ifdef _WIN32
    strcat(file_name, ".dll");
    void *handle = LoadLibrary(file_name);
    if (!handle) {
        rt_throw("failed to open library '%s'", file_name);
    }
#else
    strcat(file_name, ".so");
    void *handle = dlopen(file_name, RTLD_LAZY);
    if (!handle) {
        rt_throw("%s", dlerror());
    }
#endif
    rt_DataLibHandle_t *libhandle = malloc(sizeof(rt_DataLibHandle_t));
    libhandle->handle = handle;
    libhandle->file_name = file_name;
    /* rc is kept at 0 unless the runtime assigns
       a variable to the data */
    libhandle->rc = 0;

    // call libloader to intilize function pointers
    rt_util_libloader(libhandle->handle);

    return libhandle;
}

rt_DataLibHandle_t *rt_DataLibHandle_clone(const rt_DataLibHandle_t *handle)
{
    rt_DataLibHandle_t *libhandle = rt_DataLibHandle_init(strdup(handle->file_name));
    return libhandle;
}

void rt_DataLibHandle_increfc(rt_DataLibHandle_t *handle)
{
    ++handle->rc;
}

void rt_DataLibHandle_decrefc(rt_DataLibHandle_t *handle)
{
    --handle->rc;
    if (handle->rc < 0) handle->rc = 0;
}

void rt_DataLibHandle_destroy(rt_DataLibHandle_t **ptr)
{
    if (!ptr || !*ptr) return;
    rt_DataLibHandle_t *handle = *ptr;

    /* ref counting */
    --handle->rc;
    if (handle->rc < 0) handle->rc = 0;
    if (handle->rc > 0) return;

#ifdef _WIN32
    // On Windows, use FreeLibrary to close the library.
    int result = FreeLibrary((HMODULE) handle->handle);
    if (!result) rt_throw("failed to close library '%s'", handle->file_name);
#else
    // On Unix-like systems, use dlclose to close the library.
    int result = !dlclose(handle->handle);
    if (!result) rt_throw("%s", dlerror());
#endif

    free(handle->file_name);

    handle->handle = NULL;
    handle->file_name = NULL;

    free(handle);
    *ptr = NULL;
}

rt_fn_NativeFunction_t rt_DataLibHandle_lookup(const rt_DataLibHandle_t *handle, const char *fname)
{
    void *fnptr = rt_util_loadfn(handle->handle, fname);
    return fnptr;
}

char *rt_DataLibHandle_tostr(const rt_DataLibHandle_t *handle)
{
    return strdup(handle->file_name);
}

#else
    #warning re-inclusion of module 'runtime/data/DataLibHandle.c.h'
#endif
