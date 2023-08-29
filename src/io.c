#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errcodes.h"
#include "globals.h"
#include "io.h"

#ifndef IO_GETLINE
#define IO_GETLINE

/* The original code is public domain -- Will Hartung 4/9/09 */
/* Modifications, public domain as well, by Antti Haapala, 11/10/17
   - Switched to getc on 5/23/19 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>

// if typedef doesn't exist (msvc, blah)
typedef intptr_t ssize_t;

ssize_t io_getline(char **lineptr, size_t *n, FILE *stream) {
    size_t pos;
    int c;

    if (lineptr == NULL || stream == NULL || n == NULL) {
        errno = EINVAL;
        return -1;
    }

    c = getc(stream);
    if (c == EOF) {
        return -1;
    }

    if (*lineptr == NULL) {
        *lineptr = malloc(128);
        if (*lineptr == NULL) {
            return -1;
        }
        *n = 128;
    }

    pos = 0;
    while(c != EOF) {
        if (pos + 1 >= *n) {
            size_t new_size = *n + (*n >> 2);
            if (new_size < 128) {
                new_size = 128;
            }
            char *new_ptr = realloc(*lineptr, new_size);
            if (new_ptr == NULL) {
                return -1;
            }
            *n = new_size;
            *lineptr = new_ptr;
        }

        ((unsigned char *)(*lineptr))[pos ++] = c;
        if (c == '\n') {
            break;
        }
        c = getc(stream);
    }

    (*lineptr)[pos] = '\0';
    return pos;
}

#endif

long long io_get_filesize(const char *filepath)
{
    FILE *file = fopen(filepath, "rb");
    if (!file) io_errnexit("io_get_filesize: couldn't read file: '%s'", filepath);
    long long filesz = -1LL;
    if (fseek(file, 0, SEEK_END) != 0)
        io_errnexit("io_get_filesize: error seeking to end of file");
    filesz = ftell(file);
    if (filesz == -1LL)
        io_errnexit("io_get_filesize: error getting the file size");
    if (fseek(file, 0, SEEK_SET) != 0)
        io_errnexit("io_get_filesize: error seeking to the beginning of the file");
    fclose(file);
    return filesz;
}

char **io_read_lines(const char *filepath, size_t *line_cnt)
{
    FILE *f = fopen(filepath, "r");
    if (!f) io_errnexit("io_read_lines: couldn't read file: '%s'", filepath);
    char *line = NULL;
    *line_cnt = 0;
    size_t list_sz = 0,
           line_len = 0;
    char **ret_lines = NULL;
    while (io_getline(&line, &line_len, f) != -1) {
        if (!line) io_errndie("io_read_lines:" ERR_MSG_MALLOCFAIL);
        const size_t line_len = strlen(line);
        if (line[line_len -1] == '\n') line[line_len -1] = '\0';
        if (*line_cnt >= list_sz) {
            ret_lines = (char**) realloc(ret_lines, (list_sz += list_sz *2 +1) * sizeof(char*));
            if (!ret_lines) io_errndie("io_read_lines:" ERR_MSG_REALLOCFAIL);
        }
        ret_lines[(*line_cnt)++] = line;
        line = NULL;
    }
    return ret_lines;
}

void io_errnexit(const char *fmt, ...)
{
    fprintf(stderr, "shsc: ");
    fflush(stderr);
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fflush(stderr);
    fprintf(stderr, "\n");
    exit(ERR_DIE);
}

void io_errndie(const char *fmt, ...)
{
    fprintf(stderr, "shsc: ");
    fflush(stderr);
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fflush(stderr);
    fprintf(stderr, "\n");
    abort();
}

void io_print_srcerr(int line_no, int char_no, const char *fmt, ...)
{
    /* fprintf(stderr, "shsc: %s:%d:%d: ", global_currfile, line_no, char_no); */
    fprintf(stderr, "shsc: %s:%d: ", global_currfile, line_no);
    fflush(stderr);
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fflush(stderr);
    fprintf(stderr, "\n");
}
