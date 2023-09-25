#ifndef IO_H
#define IO_H

#include <stddef.h>

/** read string contains trailing new line.
    size_t n is the number of bytes allocated.
    return value is the length of string read. */
ssize_t io_getline(char **lineptr, size_t *n, FILE *stream);

long long io_get_filesize(const char *filepath);
char **io_read_lines(const char *filepath, size_t *line_cnt);
void io_errnexit(const char *fmt, ...) __attribute__((format(printf, 1, 2)));
void io_errndie(const char *fmt, ...) __attribute__((format(printf, 1, 2)));
void io_print_srcerr(int line_no, int char_no, const char *fmt, ...) __attribute__((format(printf, 3, 4)));

#endif
