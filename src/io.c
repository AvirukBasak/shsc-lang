#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

#include "globals.h"
#include "errcodes.h"
#include "io.h"

long long io_get_filesize(const char *filepath)
{
    FILE *file = fopen(filepath, "rb");
    if (!file) io_errndie("io_get_filesize: couldn't read file: '%s'", filepath);
    long long filesz = -1LL;
    if (fseek(file, 0, SEEK_END) != 0)
        io_errndie("io_get_filesize: error seeking to end of file");
    filesz = ftell(file);
    if (filesz == -1LL)
        io_errndie("io_get_filesize: error getting the file size");
    if (fseek(file, 0, SEEK_SET) != 0)
        io_errndie("io_get_filesize: error seeking to the beginning of the file");
    fclose(file);
    return filesz;
}

char **io_read_lines(const char *filepath, size_t *line_cnt)
{
    FILE *f = fopen(filepath, "r");
    if (!f) io_errndie("io_read_lines: couldn't read file: '%s'", filepath);
    char *line = NULL;
    *line_cnt = 0;
    size_t list_sz = 0,
           line_len = 0;
    char **ret_lines = NULL;
    while (getline(&line, &line_len, f) != -1) {
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
    exit(ERR_DIE);
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
