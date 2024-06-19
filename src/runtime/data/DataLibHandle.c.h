#ifndef RT_DATA_LIBHANDLE_C_H
#define RT_DATA_LIBHANDLE_C_H

#include <stdlib.h>
#include <string.h>

#include "runtime/data/Data.h"
#include "runtime/data/DataLibHandle.h"
#include "runtime/io.h"

#ifdef _WIN32
    #include <windows.h>
#else
    #include <dlfcn.h>
#endif

rt_DataLibHandle_t *rt_DataLibHandle_init(char *file_name)
{
#ifdef _WIN32
    void *handle = LoadLibrary(file_name);
    if (!handle) {
        rt_throw("failed to open library '%s'", file_name);
    }
#else
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
    int result = FreeLibrary((HMODULE) libhandle->handle);
    if (!result) rt_throw("failed to close library '%s'", libhandle->file_name);
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
#ifdef _WIN32
    // On Windows, use GetProcAddress to get the symbol from the library handle.
    void *fnptr = GetProcAddress((HMODULE) handle->handle, fname);
    if (!fnptr) {
        rt_throw("failed to get symbol '%s' from '%s'", fname, handle->file_name);
    }
#else
    // On Unix-like systems, use dlsym to get the symbol from the library handle.
    void *fnptr = dlsym(handle->handle, fname);
    if (!fnptr) {
        rt_throw("%s", dlerror());
    }
#endif

    return fnptr;
}

char *rt_DataLibHandle_tostr(const rt_DataLibHandle_t *handle)
{
    return strdup(handle->file_name);
}

#else
    #warning re-inclusion of module 'runtime/data/DataLibHandle.c.h'
#endif
