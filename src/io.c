#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

#include "globals.h"
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
    size_t row_size = 0;
    size_t col_size = 0;
    int i = 0, j = 0;
    char c = 0;
    char **buffer = NULL;

    FILE *f = fopen(filepath, "rb");
    if (!f) io_errndie("io_read_lines: couldn't read file: '%s'", filepath);

    /* read characters from the file */
    while ((c = fgetc(f)) != (char) EOF) {
        /* check if matrix needs to be resized */
        if (i >= row_size) {
            row_size = row_size * 2 +1;
L_BUFFRZ1:  buffer = (char**) realloc(buffer, row_size * sizeof(char*));
            if (!buffer) io_errndie("io_read_lines: memory reallocation failed");
            /* set garbage to NULL or else realloc will fail at label L_BUFFRZ2 */
            buffer[i] = NULL;
        }
        if (j >= col_size) {
            col_size = col_size * 2 +1;
L_BUFFRZ2:  buffer[i] = (char*) realloc(buffer[i], col_size * sizeof(char));
            if (!buffer[i]) io_errndie("io_read_lines: memory reallocation failed");
        }
        if (c == '\n') {
            /* null-terminate the string and reset column size */
            buffer[i][j] = '\0';
            col_size = j = 0;
            /* set garbage to NULL or else realloc will fail at label L_BUFFRZ2
               the condition ensures is within range coz the buffer isn't resized
               before L_BUFFRZ1 */
            if (i < row_size -1) buffer[++i] = NULL;
            continue;
        }
        buffer[i][j] = c;
        ++j;
    }
    fclose(f);
    /* null-terminate the last string if j is pointing to its end */
    if (j == col_size -1) {
        buffer[i] = (char*) realloc(buffer[i], (j+1) * sizeof(char));
        if (!buffer[i]) io_errndie("io_read_lines: memory reallocation failed");
        buffer[i][j] = '\0';
    }
    /* update the number of lines */
    *line_cnt = i +1;
    return buffer;
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
