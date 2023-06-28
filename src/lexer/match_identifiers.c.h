#ifndef LEX_MATCH_IDENTIFIERS_CH
#define LEX_MATCH_IDENTIFIERS_CH

#include "lexer.h"

LexToken lex_match_identifiers(FILE *f, char ch)
{
    if (!isalpha(ch) && ch != '_') return LEXTOK_INVALID;
    while (true) {
        ch = lex_getc(f);
        if (!lex_isalmun_undr(ch)) {
            // unget last non identifier char
            lex_ungetc(&ch, f);
            break;
        }
    }
    // a boolean literal is just a special identifier lol
    if (!strcmp(lex_get_buffstr(), "true"))  return LEXTOK_BOOL_LITERAL;
    if (!strcmp(lex_get_buffstr(), "false")) return LEXTOK_BOOL_LITERAL;
    return LEXTOK_IDENTIFIER;
}

#endif
