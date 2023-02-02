#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lexer.h"

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "scsh: no args provided\n");
        exit(2);
    }
    for (int i = 1; i < argc; i++) {
        FILE *f = fopen(argv[i], "r");
        if (!f) fprintf(stderr, "scsh: couldn't read file: '%s'\n", argv[i]);
        LexToken tok = lex_get_nexttok(f);
        do {
            printf("%s: %s\n", lex_get_tokcode(tok), lex_get_tokstr());
            tok = lex_get_nexttok(f);
        } while (tok != LEX_INVALID);
        fclose(f);
    }
    return 0;
}
