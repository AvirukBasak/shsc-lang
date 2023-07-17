#ifndef LEXER_IO_C_H
#define LEXER_IO_C_H

#include "lexer.h"

char lex_getc(FILE *f)
{
    char c = getc(f);
    if (!c) return 0;
    if (c == (char) EOF) return (char) EOF;
    if (!lex_is_printable(c))
        lex_throw("un-printable character found");
    if (c > 127) lex_throw("non-ascii symbol found");
    // ignore single line comments
    if (c == '#') while (c != '\n') {
        c = getc(f);
        if (!c) return 0;
        if (c == (char) EOF) return (char) EOF;
        if (!lex_is_printable(c))
            lex_throw("un-printable character found");
        if (c == '\n') { lex_line_no++; lex_char_no = 0; }
        else if (lex_is_printable(c)) lex_char_no++;
    }
    if (lex_is_printable(c)) lex_char_no++;
    if (!lex_is_delimiter(c)) lex_buffpush(c);
    if (c == '\n') { lex_line_no++; lex_char_no = 0; }
    return c;
}

char lex_ungetc(char *c, FILE *f)
{
    if (lex_is_printable(*c)) lex_char_no--;
    if (*c == '\n') { lex_line_no--; lex_char_no = -1; }
    if (*c != (char) EOF && !lex_is_delimiter(*c)) lex_buffpop();
    if (*c != (char) EOF) ungetc(*c, f);
    const char *tmp = lex_get_buffstr();
    return *c = tmp ? tmp[lex_buffer->push_i -1] : 0;
}

bool lex_is_delimiter(char c)
{
    return c == '\t' || c == '\r' || c == ' ';
}

bool lex_is_printable(char c)
{
    return (c >= 32 && c < 127) || lex_is_delimiter(c);
}

bool lex_isalmun_undr(char c)
{
    return isalnum(c) || c == '_';
}

#else
    #warning re-inclusion of module 'lexer/io.c.h'
#endif
