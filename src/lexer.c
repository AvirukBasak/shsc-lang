#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "io.h"
#include "lexer.h"
#include "stack-int.h"

struct LexBuffer {
    char *buffer;
    size_t push_i;
    size_t size;
};

LexBuffer *lex_buffer = NULL;

int lex_line_no = 1;
int lex_char_no = 0;

char lex_getc(FILE *f);
int lex_ungetc(char c, FILE *f);

bool lex_is_delimiter(char c);
bool lex_is_printable(char c);
bool lex_isalmun_undr(char c);

void lex_buffpush(char ch);
char lex_buffpop();
void lex_buffreset();

bool lex_is_char_literal();
bool lex_is_int_literal();
bool lex_is_float_literal();
bool lex_is_str_literal();
bool lex_is_identifier();

void lex_throw(const char *msg);

#include "lex_buffer.c.h"
#include "lex_io.c.h"

// the lexer state machine
#include "lex_match_symbols.c.h"
#include "lex_match_keywords.c.h"
#include "lex_match_identifiers.c.h"
#include "lex_match_literals.c.h"

LexToken lex_get_nexttok(FILE *f)
{
    lex_buffreset();
    char ch = lex_getc(f);
    while (lex_is_delimiter(ch)) ch = lex_getc(f);
    if (ch == '_') return lex_match_identifiers(f, ch);
    if (isalpha(ch)) {
        LexToken kwdtok = lex_match_keywords(f, ch);
        if (kwdtok == LEX_INVALID)
            return lex_match_identifiers(f, ch);
        return kwdtok;
    }
    if (ch == '\'' || ch == '"' || ch == '+' || ch == '-') {
        LexToken littok = lex_match_literals(f, ch);
        if (littok == LEX_INVALID && (ch == '+' || ch == '-'))
            return lex_match_symbols(f, ch);
        return littok;
    }
    if (isdigit(ch)) return lex_match_literals(f, ch);
    return lex_match_symbols(f, ch);
}

#include "lex_tokens.c.h"

void lex_throw(const char *msg)
{
    if (!msg) abort();
    io_print_srcerr(lex_line_no, lex_char_no, "lexer error: %s", msg);
    exit(1);
}
