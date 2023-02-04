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

bool lex_is_char_literal()
{ return false; }

bool lex_is_int_literal()
{ return false; }

bool lex_is_float_literal()
{ return false; }

bool lex_is_str_literal()
{ return false; }

bool lex_is_identifier()
{
    if (lex_buffer->push_i > LEX_MAX_IDENTIFIER_LEN) return false;
    if (!isalpha(lex_buffer->buffer[0]) && lex_buffer->buffer[0] != '_')
        return false;
    for (int i = 0; i < lex_buffer->push_i; i++)
        if (!isalnum(lex_buffer->buffer[i]) && lex_buffer->buffer[i] != '_')
            return false;
    return true;
}

// the lexer state machine
#include "lex_match.c.h"

LexToken lex_get_nexttok(FILE *f)
{
    return lex_match(f);
}

#include "lex_tokens.c.h"

void lex_throw(const char *msg)
{
    if (!msg) abort();
    io_print_srcerr(lex_line_no, lex_char_no, "lexer error: %s", msg);
    exit(1);
}
