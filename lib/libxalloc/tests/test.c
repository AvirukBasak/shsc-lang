#include <stdio.h>
#include <unistd.h>

#include "libxalloc.h"
#define SZ (256*1024*1024)

int main(int argc, char *argv[])
{
    void *p0, *p1;
    printf("brk init = %p\n", p0 = sbrk(0));
    for (int i = 0; i < 7; i++) {
        char *s0 = xmalloc(SZ);
        for (int i = 0; i < SZ; i++) {
            s0[i] = i%26 + 0x61;
        }
        char *s1 = xmalloc(SZ);
        for (int i = 0; i < SZ; i++) {
            s1[i] = i%26 + 0x61;
        }
        char *s2 = xmalloc(SZ);
        for (int i = 0; i < SZ; i++) {
            s2[i] = i%26 + 0x61;
        }
        char *s3 = xmalloc(SZ);
        for (int i = 0; i < SZ; i++) {
            s3[i] = i%26 + 0x61;
        }
        s3[26] = 0; printf("%d: %s\n", i, s3);
        xfree(s0);
        xfree(s1);
        xfree(s2);
        xfree(s3);
    }
    printf("brk exit = %p\n", p1 = sbrk(0));
    printf("brk difference = %zu B\n", (size_t) (p1 - p0));
    return 0;
}
