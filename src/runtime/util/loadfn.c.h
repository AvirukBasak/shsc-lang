#ifndef RT_UTIL_LOADFN_C_H
#define RT_UTIL_LOADFN_C_H

#ifdef _WIN32
    #include <windows.h>
#else
    #include <dlfcn.h>
#endif

#include "runtime/io.h"

void *rt_util_loadfn(const void *handle, const char *fn_name)
{
#ifdef _WIN32
    // On Windows, use GetProcAddress to get the symbol from the library handle.
    void *fnptr = GetProcAddress((HMODULE) handle, fn_name);
    if (!fnptr) {
        rt_throw("failed to get symbol '%s'", fn_name);
    }
#else
    // On Unix-like systems, use dlsym to get the symbol from the library handle.
    void *fnptr = dlsym(handle, fn_name);
    if (!fnptr) {
        rt_throw("%s", dlerror());
    }
#endif

    return fnptr;
}

#else
    #warning "re-inclusion of src/runtime/util/loadfn.c.h"
#endif
