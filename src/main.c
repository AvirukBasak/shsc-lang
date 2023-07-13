#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "globals.h"
#include "io.h"
#include "ast/util.h"
#include "parser.h"

#include "ast/to_json.h"

int main(int argc, char **argv)
{
    if (argc < 2) io_errndie("no args provided");
    for (int i = 1; i < argc; i++) {
        global_currfile = argv[i];
        FILE *f = (argv[i][0] == '-' && !argv[i][1]) ?
            stdin :
            fopen(argv[i], "rb");
        if (!f) io_errndie("couldn't read file: '%s'", argv[i]);
        /* Auto pushes module names to a module stack */
        parse_interpret(f);
        if (f != stdin) fclose(f);
    }
    /* Save the AST as JSON */
    AST2JSON_convert("docs/SyntaxTree.json");
    /* Clear the entire AST */
    AST_ProcedureMap_clear();
    return 0;
}
