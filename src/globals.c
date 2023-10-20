#include <stddef.h>
#include "globals.h"

const char *global_currfile = NULL;

#include "libxalloc.h"

void *malloc(size_t size)
{
    void *ptr = xmalloc(size);
#ifdef _MEM_DEBUG
    __xalloc_print_str(2, "    malloc: ptr = '");
    __xalloc_print_ptr(2, ptr);
    __xalloc_print_str(2, "', size = ");
    __xalloc_print_ui64(2, size);
    __xalloc_print_str(2, " B\n");
#endif
    return ptr;
}

void *calloc(size_t count, size_t size)
{
    void *ptr = xcalloc(count, size);
#ifdef _MEM_DEBUG
    __xalloc_print_str(2, "    calloc: ptr = '");
    __xalloc_print_ptr(2, ptr);
    __xalloc_print_str(2, "', size = ");
    __xalloc_print_ui64(2, size);
    __xalloc_print_str(2, " B\n");
#endif
    return ptr;
}

void *realloc(void *p, size_t size)
{
    void *ptr = xrealloc(p, size);
#ifdef _MEM_DEBUG
    __xalloc_print_str(2, "    relloc: ptr = '");
    __xalloc_print_ptr(2, ptr);
    __xalloc_print_str(2, "', size = ");
    __xalloc_print_ui64(2, size);
    __xalloc_print_str(2, " B\n");
#endif
    return ptr;
}

void free(void *ptr)
{
#ifdef _MEM_DEBUG
    size_t mark_sz = ptr ? __xalloc_mbloc_find(ptr)->size : 0;
    size_t freed_size = xfree(ptr);
    __xalloc_print_str(2, "    free: ptr = '");
    __xalloc_print_ptr(2, ptr);
    __xalloc_print_str(2, "', size = ");
    __xalloc_print_ui64(2, mark_sz);
    __xalloc_print_str(2, " B, freed = ");
    __xalloc_print_ui64(2, freed_size);
    __xalloc_print_str(2, " B\n");
#else
    xfree(ptr);
#endif
}
