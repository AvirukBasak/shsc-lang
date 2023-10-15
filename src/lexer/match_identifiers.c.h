#ifndef LEXER_MATCH_IDENTIFIERS_C_H
#define LEXER_MATCH_IDENTIFIERS_C_H

#include <ctype.h>
#include "lexer.h"

lex_Token_t lex_match_identifiers(FILE *f, char ch)
{
    if (!isalpha(ch) && ch != '_') return TOKEN_INVALID;
    while (true) {
        ch = lex_getc(f);
        if (!lex_is_alnumundr(ch)) {
            // unget last non identifier char
            lex_ungetc(&ch, f);
            break;
        }
    }
    return TOKEN_IDENTIFIER;
}

#else
    #warning re-inclusion of module 'lexer/match_identifiers.c.h'
#endif
