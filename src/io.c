#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

#include "globals.h"
#include "io.h"

long long io_get_filesize(FILE *file)
{
    long long fileSize;

    if (fseek(file, 0, SEEK_END) != 0) {
        fprintf(stderr, "scsh: io_get_filesize: error seeking to end of file\n");
        return -1;
    }
    fileSize = ftell(file);
    if (fileSize == -1L) {
        fprintf(stderr, "scsh: io_get_filesize: error getting the file size\n");
        return -1;
    }
    if (fseek(file, 0, SEEK_SET) != 0) {
        fprintf(stderr, "scsh: io_get_filesize: error seeking to the beginning of the file\n");
        return -1;
    }
    return fileSize;
}

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
    /* fprintf(stderr, "scsh: %s:%d:%d: ", global_currfile, line_no, char_no); */
    fprintf(stderr, "scsh: %s:%d: ", global_currfile, line_no);
    fflush(stderr);
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fflush(stderr);
    fprintf(stderr, "\n");
}
