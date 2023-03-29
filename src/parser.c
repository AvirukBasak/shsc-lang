#include "lexer.h"
#include "parser.h"
#include "io.h"

void parse_interpret(FILE *f)
{
    LexToken tok = lex_get_nexttok(f);
    while (tok != LEXTOK_EOF) {
        printf("%s: %s\n", lex_get_tokcode(tok), lex_get_buffstr());
        tok = lex_get_nexttok(f);
    }
    printf("%s\n", lex_get_tokcode(tok));
    return;
    // new code
}

void parse_throw(const char *msg)
{
    if (!msg) abort();
    io_print_srcerr(lex_line_no, lex_char_no, "parser error: %s", msg);
    exit(2);
}
