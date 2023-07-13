#ifndef IO_H
#define IO_H

#include <stdio.h>

long long io_get_filesize(FILE *file);
void io_errndie(const char *fmt, ...) __attribute__((format(printf, 1, 2)));
void io_print_srcerr(int line_no, int char_no, const char *fmt, ...) __attribute__((format(printf, 3, 4)));

#endif
