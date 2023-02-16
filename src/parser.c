#include "lexer.h"
#include "parser.h"

void parser_interpret(FILE *f)
{
    LexToken tok = lex_get_nexttok(f);
    while (tok != LEXTOK_EOF) {
        printf("%s: %s\n", lex_get_tokcode(tok), lex_get_buffstr());
        tok = lex_get_nexttok(f);
    }
    printf("%s\n", lex_get_tokcode(tok));
}
