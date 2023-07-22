#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "globals.h"
#include "io.h"
#include "ast/util.h"
#include "parser.h"

#include "ast/to_json.h"

void main_parsefiles(const char **filepaths, int file_cnt);

int main(int argc, char **argv)
{
    if (argc < 2) io_errndie("no args provided");

    char **lines = NULL;
    size_t line_cnt = 0;
    char* ast_filename = NULL;
    bool ast_format = false;

    /* start from 1 to skip program name */
    int index = 1;

    /* check if -h or --help is present */
    if (!strcmp(argv[index], "-h") || !strcmp(argv[index], "--help")) {
        printf("USAGE:\n"
               "  scsh [FILENAMES]               execute files listed as args\n"
               "  scsh -b or --build [FILENAME]  execute files listed in file\n"
               "  scsh -t or --ast [FILENAME]    save AST as JSON to file\n"
               "  scsh -tf or --astf [FILENAME]  produce formatted JSON\n"
               "  scsh -h or --help              view this message\n"
        );
        exit(0);
    }

    /* check if -t or --ast is present */
    if (!strcmp(argv[index], "-t") || !strcmp(argv[index], "--ast")) {
        if (argc < 3) io_errndie("ast file path not provided");
        ast_filename = argv[++index];
        ++index;
    }

    /* check if -tf or --astf is present */
    else if (!strcmp(argv[index], "-tf") || !strcmp(argv[index], "--astf")) {
        if (argc < 3) io_errndie("ast file path not provided");
        ast_filename = argv[++index];
        ast_format = true;
        ++index;
    }

    /* check if -b or --build is present */
    if (!strcmp(argv[index], "-b") || !strcmp(argv[index], "--build")) {
        if (argc < 3) io_errndie("build file path not provided");
        lines = io_read_lines(argv[++index], &line_cnt);
        ++index;
        if (index < argc) io_errndie("too many arguments: '%s' onwards", argv[index]);
    }

    /* if file paths are taken from argv, don't free lines */
    bool from_argv = false;

    /* if no --build set lines = &argv[index] */
    if (!lines) {
        lines = &argv[index];
        line_cnt = argc - index;
        from_argv = true;
    }

    main_parsefiles((const char**) lines, line_cnt);

    if (!from_argv && lines) {
        for (size_t i = 0; i < line_cnt; ++i)
            free(lines[i]);
        free(lines);
    }

    /* save the AST as JSON */
    if (ast_filename) AST2JSON_convert(ast_filename, ast_format);

    /* clear the entire AST */
    AST_ProcedureMap_clear();

    return 0;
}

void main_parsefiles(const char **filepaths, int file_cnt)
{
    if (file_cnt < 1) io_errndie("no file paths provided");
    for (int i = 0; i < file_cnt; ++i) {
        global_currfile = filepaths[i];
        FILE *f = (filepaths[i][0] == '-' && !filepaths[i][1]) ?
            stdin :
            fopen(filepaths[i], "rb");
        if (!f) io_errndie("couldn't read file: '%s'", filepaths[i]);
        /* auto pushes module names to a module stack */
        parse_interpret(f);
        if (f != stdin) fclose(f);
    }
}
