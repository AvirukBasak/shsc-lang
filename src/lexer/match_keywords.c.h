#ifndef LEXER_MATCH_KEYWORDS_C_H
#define LEXER_MATCH_KEYWORDS_C_H

#include "lexer.h"

LexToken lex_match_keywords(FILE *f, char ch)
{
    if (!isalpha(ch)) return LEXTOK_INVALID;
    // start at 1 as ch is already in buffer
    size_t kwdlen = 1;
    while (true) {
        ch = lex_getc(f);
        if (!isalpha(ch)) {
            // unget last non alpha char
            lex_ungetc(&ch, f);
            break;
        }
        kwdlen++;
    }
    if (!strcmp(lex_get_buffstr(), "module"))    return LEXTOK_KWD_MODULE;
    if (!strcmp(lex_get_buffstr(), "proc"))      return LEXTOK_KWD_PROC;
    if (!strcmp(lex_get_buffstr(), "start"))     return LEXTOK_KWD_START;
    if (!strcmp(lex_get_buffstr(), "end"))       return LEXTOK_KWD_END;
    if (!strcmp(lex_get_buffstr(), "block"))     return LEXTOK_KWD_BLOCK;
    if (!strcmp(lex_get_buffstr(), "if"))        return LEXTOK_KWD_IF;
    if (!strcmp(lex_get_buffstr(), "then"))      return LEXTOK_KWD_THEN;
    if (!strcmp(lex_get_buffstr(), "elif"))      return LEXTOK_KWD_ELIF;
    if (!strcmp(lex_get_buffstr(), "else"))      return LEXTOK_KWD_ELSE;
    if (!strcmp(lex_get_buffstr(), "while"))     return LEXTOK_KWD_WHILE;
    if (!strcmp(lex_get_buffstr(), "break"))     return LEXTOK_KWD_BREAK;
    if (!strcmp(lex_get_buffstr(), "continue"))  return LEXTOK_KWD_CONTINUE;
    if (!strcmp(lex_get_buffstr(), "return"))    return LEXTOK_KWD_RETURN;
    if (!strcmp(lex_get_buffstr(), "for"))       return LEXTOK_KWD_FOR;
    if (!strcmp(lex_get_buffstr(), "from"))      return LEXTOK_KWD_FROM;
    if (!strcmp(lex_get_buffstr(), "to"))        return LEXTOK_KWD_TO;
    if (!strcmp(lex_get_buffstr(), "by"))        return LEXTOK_KWD_BY;
    if (!strcmp(lex_get_buffstr(), "do"))        return LEXTOK_KWD_DO;
    if (!strcmp(lex_get_buffstr(), "var"))       return LEXTOK_KWD_VAR;
    if (!strcmp(lex_get_buffstr(), "pass"))      return LEXTOK_KWD_PASS;
    // unget all characters except the first if all matches failed
    while (kwdlen > 1) {
        lex_ungetc(&ch, f);
        kwdlen--;
    }
    return LEXTOK_INVALID;
}

#else
    #warning re-inclusion of module 'lexer/match_keywords.c.h'
#endif
