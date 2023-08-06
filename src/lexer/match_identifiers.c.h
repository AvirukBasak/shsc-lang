#ifndef LEXER_MATCH_IDENTIFIERS_C_H
#define LEXER_MATCH_IDENTIFIERS_C_H

#include <ctype.h>
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
    return LEXTOK_IDENTIFIER;
}

#else
    #warning re-inclusion of module 'lexer/match_identifiers.c.h'
#endif
