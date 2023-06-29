#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "ast.h"
#include "parser.yac.h"

#define LEX_MAX_BUFFALLOC_SZ   (64)
#define LEX_MAX_IDENTIFIER_LEN (64)

#define LEX_TOTAL_TOKENS       (128)
#define LEX_TOKEN_SIZE         (32)

// The following form the EXTERNAL INTERFACE

typedef enum yytokentype LexToken;

LexToken yylex(void);
LexToken lex_get_nexttok(FILE *f);
char *lex_get_tokcode(LexToken code);
char *lex_get_symbol(LexToken code);

char *lex_get_buffstr();

extern int lex_line_no;
extern int lex_char_no;

// The following are for INTERNAL USE

typedef struct LexBuffer LexBuffer;

extern LexBuffer *lex_buffer;

struct LexBuffer {
    char *buffer;
    size_t push_i;
    size_t size;
};

// lexer/io
char lex_getc(FILE *f);
char lex_ungetc(char *c, FILE *f);

bool lex_is_delimiter(char c);
bool lex_is_printable(char c);
bool lex_isalmun_undr(char c);

// lexer/buffer
void lex_buffpush(char ch);
char lex_buffpop();
void lex_buffreset();
void lex_buffree();

// lexer
void lex_throw(const char *msg);

#endif
