#include <unistd.h>    // function: write

#include "stdhead.h"
#include "stdfunc.h"
#include "io.h"

void __xalloc_print_str(int fd, const char *s)
{
    if (!s) return;
    size_t len = strlen(s);
    write(fd, s, len);
}

void __xalloc_print_ui64(int fd, const ui64_t n)
{
    ui64_t nb = n;
    char s[21];
    s[20] = 0;    // null termination
    s[19] = '0';  // default number 0
    int i = 19;   // location from where string starts
    while (nb && i >= 0) {
        s[i--] = (nb % 10) + '0';
        nb /= 10;
    }
    if (i < 19) i++;
    __xalloc_print_str(fd, &s[i]);
}

void __xalloc_print_i64(int fd, const i64_t n)
{
    ui64_t nb = n < 0 ? -n : n;
    if (n < 0) __xalloc_print_str(fd, "-");
    __xalloc_print_ui64(fd, nb);
}

void __xalloc_print_ptr(int fd, const ptr_t p)
{
    char *b = (char*)(&p);
    char s[16];
    size_t len = 0;
    // most significant byte
    bool msbyte_zero = true;
    bool is_liend = __xalloc_std_is_litle_endian();
    int i = is_liend ? 7 : 0;
    for (int j = 0; (is_liend ? (i >= 0) : (i < 8)) && j < 16;) {
        const ui8_t byte = b[i];
        char halfbyte0 = __xalloc_std_to_hex(byte >> 4);
        char halfbyte1 = __xalloc_std_to_hex(byte);
        if (halfbyte0 != '0' || halfbyte1 != '0')
            msbyte_zero = false;
        if (!msbyte_zero) {
            s[j] = halfbyte0;
            s[j+1] = halfbyte1;
            j+=2;
            len++;
        }
        is_liend ? i-- : i++;
    }
    write(fd, "0x", 2);
    if (len < 1) write(fd, "00", 2);
    else write(fd, s, 2*len);
}

void __xalloc_print_err(const char *s)
{
    __xalloc_print_str(2, "libxalloc: aborted");
    if (!s) goto abort;
    __xalloc_print_str(2, ": ");
    __xalloc_print_str(2, s);
    __xalloc_print_str(2, "\n");
    abort: abort();
}
