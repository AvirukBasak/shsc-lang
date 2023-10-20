#include <stdio.h>
#include <unistd.h>

#include "libxalloc.h"
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

#ifdef DEBUG

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

/* overriding libc allocators with custom functions.
 * note that if printf calls a heap allocator, it'll
 * call one of the following
 */

void *malloc(size_t size)
{
    void *ptr = xmalloc(size);
#ifdef DEBUG
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
#ifdef DEBUG
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
#ifdef DEBUG
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
#ifdef DEBUG
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

int main(int argc, char *argv[])
{
    /* Because of differences in when malloc is called in different architectures,
     * this malloc call is meant to explicitly initialize the allocator.
     * This will result in an intial allocation of some KB, and brk will be shifted.
     * This is done to get a consistent reading of brk init across all architectures.
     * NOTE that malloc(0) does nothing except when allocator is not initialized.
     * In such a case, it'll call the initializer.
     */
    malloc(0);
    void *p0 = sbrk(0);
    printf("brk init = %p\n", p0);
    for (int i = 0; i < 7; i++) {
        char *s0 = malloc(SZ);
        for (int i = 0; i < SZ; i++) {
            s0[i] = i%26 + 0x61;
        }
        char *s1 = malloc(SZ);
        for (int i = 0; i < SZ; i++) {
            s1[i] = i%26 + 0x61;
        }
        char *s2 = malloc(SZ);
        for (int i = 0; i < SZ; i++) {
            s2[i] = i%26 + 0x61;
        }
        char *s3 = malloc(SZ);
        for (int i = 0; i < SZ; i++) {
            s3[i] = i%26 + 0x61;
        }
        s3[26] = 0; printf("%d: %s\n", i, s3);
        free(s0);
        free(s1);
        free(s2);
        free(s3);
    }
    void *p1 = sbrk(0);
    printf("brk exit = %p\n", p1);
    printf("brk difference = %zu B\n", (size_t) (p1 - p0));
    return 0;
}
