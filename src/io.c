#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

#include "globals.h"
#include "io.h"

void io_errndie(const char *fmt, ...)
{
    fprintf(stderr, "scsh: ");
    fflush(stderr);
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fflush(stderr);
    fprintf(stderr, "\n");
    exit(1);
}

void io_print_srcerr(int line_no, int char_no, const char *fmt, ...)
{
    fprintf(stderr, "scsh: %s:%d:%d: ", global_currfile, line_no, char_no);
    fflush(stderr);
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fflush(stderr);
    fprintf(stderr, "\n");
}
