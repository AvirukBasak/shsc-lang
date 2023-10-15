#ifndef LEXER_MATCH_KEYWORDS_C_H
#define LEXER_MATCH_KEYWORDS_C_H

#include <ctype.h>
#include <string.h>

#include "lexer.h"

lex_Token_t lex_match_keywords(FILE *f, char ch)
{
    if (!isalpha(ch)) return TOKEN_INVALID;
    /* start at 1 as ch is already in buffer */
    size_t kwdlen = 1;
    while (true) {
        ch = lex_getc(f);
        if (!isalpha(ch)) {
            /* unget last non alpha char */
            lex_ungetc(&ch, f);
            break;
        }
        kwdlen++;
    }
    if (!strcmp(lex_Buffer_getstr(), "module"))    return TOKEN_KWD_MODULE;
    if (!strcmp(lex_Buffer_getstr(), "proc"))      return TOKEN_KWD_PROC;
    if (!strcmp(lex_Buffer_getstr(), "start"))     return TOKEN_KWD_START;
    if (!strcmp(lex_Buffer_getstr(), "end"))       return TOKEN_KWD_END;
    if (!strcmp(lex_Buffer_getstr(), "block"))     return TOKEN_KWD_BLOCK;
    if (!strcmp(lex_Buffer_getstr(), "if"))        return TOKEN_KWD_IF;
    if (!strcmp(lex_Buffer_getstr(), "then"))      return TOKEN_KWD_THEN;
    if (!strcmp(lex_Buffer_getstr(), "elif"))      return TOKEN_KWD_ELIF;
    if (!strcmp(lex_Buffer_getstr(), "else"))      return TOKEN_KWD_ELSE;
    if (!strcmp(lex_Buffer_getstr(), "while"))     return TOKEN_KWD_WHILE;
    if (!strcmp(lex_Buffer_getstr(), "break"))     return TOKEN_KWD_BREAK;
    if (!strcmp(lex_Buffer_getstr(), "continue"))  return TOKEN_KWD_CONTINUE;
    if (!strcmp(lex_Buffer_getstr(), "for"))       return TOKEN_KWD_FOR;
    if (!strcmp(lex_Buffer_getstr(), "from"))      return TOKEN_KWD_FROM;
    if (!strcmp(lex_Buffer_getstr(), "in"))        return TOKEN_KWD_IN;
    if (!strcmp(lex_Buffer_getstr(), "to"))        return TOKEN_KWD_TO;
    if (!strcmp(lex_Buffer_getstr(), "by"))        return TOKEN_KWD_BY;
    if (!strcmp(lex_Buffer_getstr(), "do"))        return TOKEN_KWD_DO;
    if (!strcmp(lex_Buffer_getstr(), "var"))       return TOKEN_KWD_VAR;
    if (!strcmp(lex_Buffer_getstr(), "pass"))      return TOKEN_KWD_PASS;
    if (!strcmp(lex_Buffer_getstr(), "return"))    return TOKEN_KWD_RETURN;
    /* unget all characters except the first if all matches failed */
    while (kwdlen > 1) {
        lex_ungetc(&ch, f);
        kwdlen--;
    }
    return TOKEN_INVALID;
}

#else
    #warning re-inclusion of module 'lexer/match_keywords.c.h'
#endif
