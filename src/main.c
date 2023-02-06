#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "globals.h"
#include "io.h"
#include "lexer.h"

int main(int argc, char **argv)
{
    if (argc < 2) io_errndie("no args provided");
    for (int i = 1; i < argc; i++) {
        global_currfile = argv[i];
        FILE *f = (argv[i][0] == '-' && !argv[i][1]) ?
            stdin :
            fopen(argv[i], "r");
        if (!f) io_errndie("couldn't read file: '%s'", argv[i]);
        LexToken tok = lex_get_nexttok(f);
        while (tok != LEXTOK_EOF) {
            printf("%s: %s\n", lex_get_tokcode(tok), lex_get_buffstr());
            tok = lex_get_nexttok(f);
        }
        printf("%s\n", lex_get_tokcode(tok));
        if (f != stdin) fclose(f);
    }
    return 0;
}
