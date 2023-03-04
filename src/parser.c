#include "lexer.h"
#include "parser.h"
#include "io.h"

#include "parser/match_dollar.c.h"

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
    tok = lex_get_nexttok(f);
    while (tok != LEXTOK_EOF) {
        parse_dollar(f, tok);
        tok = lex_get_nexttok(f);
    }
}

void parse_throw(const char *msg)
{
    if (!msg) abort();
    io_print_srcerr(lex_line_no, lex_char_no, "parser error: %s", msg);
    exit(2);
}
