#include <stddef.h>
#include "globals.h"

const char *global_currfile = NULL;

#include "libxalloc.h"

#define _MEM_DEBUG

#define SZ (256*1024*1024)

/* These functions comes from libxalloc. Since libxalloc
 * doesn't provide the declarations of these functions, I've
 * put the declarations here.
 * These functions simply print a string or a number, but use Linux
 * system calls directly and don't need to allocate memory, which
 * prevent them from interfering with our memory allocation activities.
 */
void __xalloc_print_str(int fd, const char *s);
void __xalloc_print_ptr(int fd, const void *ptr);
void __xalloc_print_ui64(int fd, const size_t size);

#ifdef _MEM_DEBUG

/* the memory bloc management struct from libxalloc */
struct XALLOC_mbloc_t
{
    struct XALLOC_mbloc_t *prv;
    struct XALLOC_mbloc_t *nxt;
    void *ptr;
    size_t size;
    _Bool isfree;
};

/* the find function from libxalloc */
struct XALLOC_mbloc_t *__xalloc_mbloc_find(void *ptr);

#endif

void *shsc_malloc(size_t size)
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

void *shsc_calloc(size_t count, size_t size)
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

void *shsc_realloc(void *p, size_t size)
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

size_t shsc_free(void *ptr)
{
#ifdef _MEM_DEBUG
    __xalloc_print_str(2, "    free: ptr = '");
    __xalloc_print_ptr(2, ptr);
    __xalloc_print_str(2, "', size = ");
    size_t mark_sz = ptr ? __xalloc_mbloc_find(ptr)->size : 0;
    size_t freed_size = xfree(ptr);
    __xalloc_print_ui64(2, mark_sz);
    __xalloc_print_str(2, " B, freed = ");
    __xalloc_print_ui64(2, freed_size);
    __xalloc_print_str(2, " B\n");
    return freed_size;
#else
    return xfree(ptr);
#endif
}
