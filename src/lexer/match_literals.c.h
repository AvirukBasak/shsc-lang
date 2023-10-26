#ifndef LEXER_MATCH_LITERALS_C_H
#define LEXER_MATCH_LITERALS_C_H

#include <ctype.h>
#include <string.h>

#include "lexer.h"

lex_Token_t lex_match_bool(FILE *f, char ch)
{
    if (!isalpha(ch)) return TOKEN_INVALID;
    /* start at 1 as ch is already in buffer */
    size_t currlen = 1;
    while (true) {
        ch = lex_getc(f);
        if (!isalpha(ch)) {
            /* unget last non alpha char */
            lex_ungetc(&ch, f);
            break;
        }
        currlen++;
    }
    if (lex_Buffer_getstr()[0] == 't' && !strcmp(lex_Buffer_getstr(), "true"))  return TOKEN_BOOL_LITERAL;
    if (lex_Buffer_getstr()[0] == 'f' && !strcmp(lex_Buffer_getstr(), "false")) return TOKEN_BOOL_LITERAL;
    /* unget all characters except the first if all matches failed */
    while (currlen > 1) {
        lex_ungetc(&ch, f);
        currlen--;
    }
    return TOKEN_INVALID;
}

lex_Token_t lex_match_char(FILE *f, char ch)
{
    if (ch != '\'') return TOKEN_INVALID;
    /* pop out quote symbol */
    lex_Buffer_pop();
    char prev2 = 0, prev = 0;
    while (true) {
        /* can't use lex_getc as it doesn't buffer delimiters */
        prev2 = prev;
        prev = ch;
        ch = getc(f);
        if (prev2 != '\\' && prev == '\\' && ch == '\'') {
            lex_Buffer_push(ch);
            continue;
        }
        if (ch == '\'') break;
        if (ch == '\n') lex_throw("character literal cannot have un-escaped newline");
        if (ch == (char) EOF) lex_throw("unexpected end of file");
        lex_Buffer_push(ch);
    }
    return TOKEN_CHAR_LITERAL;
}

lex_Token_t lex_match_string(FILE *f, char ch)
{
    if (ch != '"') {
        if (ch != 'f') return TOKEN_INVALID;
        char ch = getc(f);
        if (ch != '"') {
            ungetc(ch, f);
            ungetc('f', f);
            return TOKEN_INVALID;
        }
    }
    /* after the above checks, ch is now either " or f */
    lex_Token_t tok = ch == '"' ? TOKEN_STR_LITERAL : TOKEN_INTERP_STR_LITERAL;
    /* pop out " or f symbol */
    lex_Buffer_pop();
    char prev2 = 0, prev = 0;
    while (true) {
        /* can't use lex_getc as it doesn't buffer delimiters */
        prev2 = prev;
        prev = ch;
        ch = getc(f);
        if (prev2 != '\\' && prev == '\\' && ch == '"') {
            lex_Buffer_push(ch);
            continue;
        }
        if (ch == '"') break;
        if (ch == (char) EOF) lex_throw("unexpected end of file");
        lex_Buffer_push(ch);
    }
    return tok;
}

enum LexBase {
    LEXBASE_2  =  2,
    LEXBASE_8  =  8,
    LEXBASE_10 = 10,
    LEXBASE_16 = 16,
};

bool lex_isbindigit(char c) {
    return c >= '0' && c <= '1';
}

bool lex_isoctdigit(char c) {
    return c >= '0' && c <= '7';
}

bool lex_isdecdigit(char c) {
    return c >= '0' && c <= '9';
}

bool lex_ishexdigit(char c) {
    return (c >= '0' && c <= '9')
        || (c >= 'a' && c <= 'f')
        || (c >= 'A' && c <= 'F');
}

typedef bool (*lex_digitchecker_ft)(char);
lex_digitchecker_ft lex_get_dgitchecker(enum LexBase base)
{
    switch (base) {
        case LEXBASE_2: return lex_isbindigit;
        case LEXBASE_8: return lex_isoctdigit;
        case LEXBASE_16: return lex_ishexdigit;
        default: return lex_isdecdigit;
    }
}

char lex_match_digits(FILE* f, char ch, enum LexBase base)
{
    /* get digit checker based on base */
    lex_digitchecker_ft lex_isdigit = lex_get_dgitchecker(base);
    /* convert lower case hex digits to uppercase */
    if (lex_isdigit(ch) && ch >= 'a' && ch <= 'f') {
        lex_Buffer_push(lex_Buffer_pop() - ('a' - 'A'));
    }
    /* match [a-fA-F0-9_]+ */
    while (lex_isdigit(ch)) {
        ch = lex_getc(f);
        /* convert lower case hex digits to uppercase */
        if (lex_isdigit(ch) && ch >= 'a' && ch <= 'f') {
            lex_Buffer_push(lex_Buffer_pop() - ('a' - 'A'));
        }
        /* if _ consume it but don't buffer it */
        if (ch == '_') {
            lex_Buffer_pop();
            ch = lex_getc(f);
        }
    }
    return ch;
}

/* this function accepts numeric strings that start with any digit or '.'
   and have the form (\d*)(\.\d+)?([ep][+-]?\d+)? */
lex_Token_t lex_match_unum(FILE *f, char ch, enum LexBase base)
{
    /* get digit checker based on base */
    lex_digitchecker_ft lex_isdigit = lex_get_dgitchecker(base);
    /* get token type based on base */
    lex_Token_t inttok, floattok;
    switch (base) {
        case LEXBASE_2:
            inttok = TOKEN_BININT_LITERAL;
            floattok = TOKEN_BINFLOAT_LITERAL;
            break;
        case LEXBASE_8:
            inttok = TOKEN_OCTINT_LITERAL;
            floattok = TOKEN_OCTFLOAT_LITERAL;
            break;
        case LEXBASE_16:
            inttok = TOKEN_HEXINT_LITERAL;
            floattok = TOKEN_HEXFLOAT_LITERAL;
            break;
        default:
            inttok = TOKEN_DECINT_LITERAL;
            floattok = TOKEN_DECFLOAT_LITERAL;
            break;
    }
    lex_Token_t retok = TOKEN_INVALID;
    /* match \d* */
    if (!lex_isdigit(ch) && ch != '.') return TOKEN_INVALID;
    if (ch != '.') {
        ch = lex_match_digits(f, ch, base);
        /* integer or integer part matched */
        retok = inttok;
    }
    /* match (\.\d+){0:1} */
    if (ch == '.') {
        ch = lex_getc(f);
        if (!lex_isdigit(ch)) {
            lex_ungetc(&ch, f);    /* unget ch */
            return retok;
        }
        ch = lex_match_digits(f, ch, base);
        /* float matched */
        retok = floattok;
    }
    /* match ([ep][+-]?\d+){0:1} */
    if ((base != LEXBASE_16 && ch == 'e') || ch == 'p') {
        /* pop 'e' and push 'p', convert e to p */
        char backup_expchar = ch;
        lex_Buffer_pop();
        lex_Buffer_push('p');
        /* next char */
        ch = lex_getc(f);
        /* consume + or - symbol */
        if (ch == '+' || ch == '-') {
            ch = lex_getc(f);
            if (!lex_isdigit(ch)) {
                lex_ungetc(&ch, f);    /* unget ch */
                lex_ungetc(&ch, f);    /* unget '+' or '-' */
                /* unget 'e' or 'p' */
                ch = lex_ungetc(&backup_expchar, f);
                return retok;
            }
        }
        if (!lex_isdigit(ch)) {
            lex_ungetc(&ch, f);    /* unget ch */
            /* unget 'e' or 'p' */
            ch = lex_ungetc(&backup_expchar, f);
            return retok;
        }
        ch = lex_match_digits(f, ch, base);
    }
    /* if last matches failed unget last char */
    lex_ungetc(&ch, f);
    return retok;
}

/* may accept only if the string starts w/ '+', '-', '.', digit or '0' */
lex_Token_t lex_match_numeric(FILE *f, char ch)
{
    /* if starts with a 0 */
    if (ch == '0') {
        ch = lex_getc(f);
        switch (ch) {
            case 'b': {
                /* pop "0b" */
                lex_Buffer_pop();
                lex_Buffer_pop();
                ch = lex_getc(f);
                return lex_match_unum(f, ch, LEXBASE_2);
            }
            case 'x': {
                /* pop "0x" */
                lex_Buffer_pop();
                lex_Buffer_pop();
                ch = lex_getc(f);
                return lex_match_unum(f, ch, LEXBASE_16);
            }
            default: {
                /* for values like 023... and 00.12... and many others */
                if (isdigit(ch)) {
                    lex_ungetc(&ch, f);  /* unget curr char */
                    lex_Buffer_pop();       /* pop leading '0' from buffer */
                    ch = lex_getc(f);    /* get back the unget char after '0' */
                    return lex_match_unum(f, ch, LEXBASE_8);
                }
                /* for numbers like 0.12... or 0_34, or just 0 */
                else if (ch == '.' || ch == '_') {
                    /* unget leading 0 and start matching using unum */
                    lex_ungetc(&ch, f);
                    return lex_match_unum(f, ch, LEXBASE_10);
                }
                else {
                    /* unget ch and return int literal for '0' */
                    lex_ungetc(&ch, f);
                    return TOKEN_DECINT_LITERAL;
                }
            }
        }
    }
    /* starts with any other number or '.' */
    else if (isdigit(ch) || ch == '.')
        return lex_match_unum(f, ch, LEXBASE_10);
    else return TOKEN_INVALID;
}

#else
    #warning re-inclusion of module 'lexer/match_literals.c.h'
#endif
