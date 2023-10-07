#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast/api.h"
#include "ast2json.h"
#include "globals.h"
#include "io.h"
#include "lexer.h"
#include "parser.h"
#include "runtime.h"

void main_parsefiles(const char **filepaths, int file_cnt);

int main(int argc, char **argv)
{
    if (argc < 2) io_errnexit("no args provided");

    char **lines = NULL;
    size_t line_cnt = 0;
    char* ast_filename = NULL;
    bool ast_format = false;

    /* start from 1 to skip program name */
    int index = 1;

    /* check if -v or --version is present */
    if (!strcmp(argv[index], "-v") || !strcmp(argv[index], "--version")) {
        printf("Shsc Version %s\n"
               "License: GPL 3.0\n"
               "Authors: Aviruk Basak\n", VERSION);
        exit(0);
    }

    /* check if -h or --help is present */
    if (!strcmp(argv[index], "-h") || !strcmp(argv[index], "--help")) {
        printf("USAGE:\n"
               "  shsc [FILENAMES]         execute files listed as args\n"
               "  shsc <flags> [FILENAMES] provide with additional flags\n"
               "FLAGS:\n"
               "  -r  --run  [FILENAME]    run files listed in file\n"
               "  -t  --ast  [FILENAME]    save AST as JSON to file\n"
               "  -tf --astf [FILENAME]    produce formatted JSON\n"
               "  -h  --help               view this message\n"
               "  -v  --version            version info\n"
        );
        exit(0);
    }

    /* check if -t or --ast is present */
    if (!strcmp(argv[index], "-t") || !strcmp(argv[index], "--ast")) {
        if (argc < 3) io_errnexit("no json file provided for '--ast'");
        ast_filename = argv[++index];
        ++index;
    }

    /* check if -tf or --astf is present */
    else if (!strcmp(argv[index], "-tf") || !strcmp(argv[index], "--astf")) {
        if (argc < 3) io_errnexit("no json file provided for '--astf'");
        ast_filename = argv[++index];
        ast_format = true;
        ++index;
    }

    if (index >= argc) io_errnexit("too few arguments: '%s' onwards", argv[index-1]);

    /* check if -r or --run is present */
    if (!strcmp(argv[index], "-r") || !strcmp(argv[index], "--run")) {
        if (argc < 3) {
            fprintf(stderr,
                "List File Syntax:\n"
                " - Each line of the list file has a single file path\n"
                " - Spaces in file path is valid and quotes not required\n"
                " - If shsc fails to read one file, it'll skip to next file\n"
                " - If shsc fails to parse any file, it'll report error and exit\n"
            );
            io_errnexit("no list file provided for '--run'");
        }
        lines = io_read_lines(argv[++index], &line_cnt);
        ++index;
        if (index < argc) io_errnexit("too many arguments: '%s' onwards", argv[index]);
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

#ifndef LEX_DEBUG
    if (ast_filename)
        /* save the AST as JSON */
        AST2JSON_convert(ast_filename, ast_format);
    else
        /* execute the program */
        RT_exec();
#endif

    /* clear the entire AST */
    AST_ProcedureMap_clear();

    return 0;
}

void main_parsefiles(const char **filepaths, int file_cnt)
{
    if (file_cnt < 1) io_errnexit("no file paths provided");
    for (int i = 0; i < file_cnt; ++i) {
        global_currfile = filepaths[i];
        FILE *f = (filepaths[i][0] == '-' && !filepaths[i][1]) ?
            stdin :
            fopen(filepaths[i], "r");
        if (!f) io_errnexit("couldn't read file: '%s'", filepaths[i]);
        /* auto pushes module names to a module stack */
        parse_interpret(f);
        if (f != stdin) fclose(f);
        lex_line_no = 1;
        lex_char_no = 1;
    }
}
