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
#include "util.h"

/**
 * Parses the files given and generates the AST. AST can be obtained
 * from the ast_util_ModuleAndProcTable.
 */
void main_parsefiles(const char **filepaths, size_t file_cnt);

int main(int argc, char **argv)
{
    /* global variables */
    global_rng_state_seed = (int) util_gettime_ms();

    /* list of shsc scripts */
    char **filepaths = NULL;
    size_t file_cnt = 0;

    /* cli args to shsc program */
    const char **rt_argv = NULL;
    int rt_argc = 0;

    /* outfile and flags for ast2json module */
    const char *ast_filename = NULL;
    bool ast_format = false;

    /* if true, filepaths will be deallocated */
    bool from_listfile = false;

    /* if argc is 1, i.e. no args have been passed */
    if (argc < 2) io_errnexit("no args provided");

    /* start from 1 to skip program name */
    int argv_index = 1;

    /* check if -v or --version is present */
    if (!strcmp(argv[argv_index], "-v") || !strcmp(argv[argv_index], "--version")) {
        printf(""
                "Shsc Version %s\n"
                "License: GPL 3.0\n"
                "Authors: %s\n", VERSION, AUTHORS);
        exit(0);
    }

    /* check if -h or --help is present */
    if (!strcmp(argv[argv_index], "-h") || !strcmp(argv[argv_index], "--help")) {
        printf(""
                "Usage:\n"
                "  shsc [options] [files...] -args [args...]\n"
                "\nOptions:\n"
                "  -v,    --version                        Show version\n"
                "  -h,    --help                           Show this help message\n"
                "  -r,    --run       [listfile]           Run scripts listed in the listfile\n"
                "  -t,    --ast       [outfile] [files...] Parse file and save AST as JSON in outfile\n"
                "  -tf,   --astf      [outfile] [files...] Parse file and save formatted AST as JSON in outfile\n"
                "  -ldbg, --lex-debug [files...]           Scan file and print lexer debug output\n"
                "\nNotes:\n"
                "  [files...] - One or more shsc code files\n"
                "  [args...]  - Arguments passed to the main:main shsc method (optional)\n"
                "  Flag -args can be added after [files...] or after [listfile] in case of --run\n"
                "  Passing a dash (-) anywhere as filename will read from stdin or write to stdout\n"
        );
        exit(0);
    }

    /* check if -ldbg or --lex-debug is present */
    if (!strcmp(argv[argv_index], "-ldbg") || !strcmp(argv[argv_index], "--lex-debug")) {
        /* enable lexer debug */
        global_lex_dbg = true;
        /* go to next argument */
        ++argv_index;
        /* as --lex-debug doesn't work alone, make sure there are other arguments */
        if (argv_index >= argc) io_errnexit("too few arguments: '%s' onwards", argv[argv_index-1]);
    }

    /* check if -t or --ast is present */
    if (!strcmp(argv[argv_index], "-t") || !strcmp(argv[argv_index], "--ast")) {
        /* check if there is a json file to save the AST */
        if (argv_index +1 >= argc) io_errnexit("no json file provided for '--ast'");
        ast_filename = argv[++argv_index];
        ast_format = false;
        /* go to next argument */
        ++argv_index;
        /* as --ast doesn't work alone, make sure there are other arguments */
        if (argv_index >= argc) io_errnexit("too few arguments: '%s' onwards", argv[argv_index-1]);
    }
    /* check if -tf or --astf is present */
    else if (!strcmp(argv[argv_index], "-tf") || !strcmp(argv[argv_index], "--astf")) {
        /* check if there is a json file to save the AST */
        if (argv_index +1 >= argc) io_errnexit("no json file provided for '--astf'");
        ast_filename = argv[++argv_index];
        ast_format = true;
        /* go to next argument */
        ++argv_index;
        /* as --ast doesn't work alone, make sure there are other arguments */
        if (argv_index >= argc) io_errnexit("too few arguments: '%s' onwards", argv[argv_index-1]);
    }

    /* check if -r or --run is present */
    if (!strcmp(argv[argv_index], "-r") || !strcmp(argv[argv_index], "--run")) {
        /* check if there is a list file to load the scripts */
        if (argv_index +1 >= argc) io_errnexit("no list file provided for '--run'");
        /* get lisfile path */
        const char *listfilepah = argv[++argv_index];
        /* get listfile dirname */
        char *listfiledir = util_dirname(listfilepah);
        /* read the list file */
        filepaths = io_read_lines(listfilepah, &file_cnt);
        /* to each line read, prepend listfiledir
           this makes all files relative to listfiledir */
        for (size_t i = 0; i < file_cnt; ++i) {
            char *newpath = util_sjoin("%s/%s", listfiledir, filepaths[i]);
            free(filepaths[i]);
            filepaths[i] = newpath;
        }
        /* free listfiledir */
        free(listfiledir);
        /* set flag to deallocate filepaths */
        from_listfile = true;
        /* go to next argument; --run can work alone */
        ++argv_index;
    }

    /* if not loaded from listfile, then filepaths come from argv, so load them */
    if (!from_listfile) {
        /* check if there are any file paths */
        if (argv_index >= argc) io_errnexit("no shsc scripts provided");
        /* make sure the script file name is not -args */
        if (!strcmp(argv[argv_index], "-args")) io_errnexit("no shsc scripts provided");
        /* set the filepaths */
        filepaths = &argv[argv_index];
        file_cnt = argc - argv_index;
        /* go to next argument i.e. we expect at least one shsc script */
        ++argv_index;
    }

    /* if more arguments are present, there is a chance that -args is present */
    if (argv_index < argc) {
        /* find index of -args */
        int index = -1;
        /* find the index of -args */
        for (int i = argv_index; i < argc; ++i) {
            if (!strcmp(argv[i], "-args")) {
                index = i;
                break;
            }
        }
        /* if -args is present, set rt_argv and rt_argc */
        if (index != -1) {
            rt_argc = argc - (index + 1);
            rt_argv = (const char **) &argv[index + 1];
            /* set new file_cnt only if not loaded from listfile */
            if (!from_listfile) {
                file_cnt = argc - (argv_index -1) - (rt_argc + 1);
            }
        }
    }

#ifdef ARGS_DEBUG
    /* print arguments */
    for (int i = 0; i < argc; ++i)
        printf("argv[%d]: %s\n", i, argv[i]);
    printf("argc: %d\n\n", argc);

    /* print filepaths */
    for (size_t i = 0; i < file_cnt; ++i)
        printf("filepaths[%zu]: %s\n", i, filepaths[i]);
    printf("file_cnt: %zu\n\n", file_cnt);

    /* print rt_argv */
    for (int i = 0; i < rt_argc; ++i)
        printf("rt_argv[%d]: %s\n", i, rt_argv[i]);
    printf("rt_argc: %d\n\n", rt_argc);
#endif

    /* parse the files and generate the AST */
    main_parsefiles((const char **) filepaths, file_cnt);

    /* deallocate filepaths if loaded from listfile */
    if (from_listfile && filepaths) {
        for (size_t i = 0; i < file_cnt; ++i)
            free(filepaths[i]);
        free(filepaths);
    }

    int exit_code = 0;

    /* if global_lex_dbg is true, then lexer debug output is printed
     * but shsc code is neither parsed nor executed */
    if (!global_lex_dbg) {
        if (ast_filename)
            /* save the AST as JSON */
            ast2json_convert(ast_filename, ast_format);
        else
            /* execute the program */
            exit_code = rt_exec(rt_argc, rt_argv);
        /* clear the entire AST */
        ast_util_ModuleAndProcTable_clear();
    }

    return exit_code;
}

void main_parsefiles(const char **filepaths, size_t file_cnt)
{
    if (file_cnt < 1) io_errnexit("no file paths provided");
    for (size_t i = 0; i < file_cnt; ++i) {
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
