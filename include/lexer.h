#ifndef LEXER_H
#define LEXER_H

/* the following includes are absolutely needed as this
   file acts as an all-in-one header for all ast functions
   - #include <stdbool.h>
   - #include <stdint.h>
   - #include "ast.h"
   - #include "parser.yy.h"
   even if your IDE screams of unused-includes, DO NOT remove them */

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "ast.h"
#include "parser.yy.h"

#define LEX_MAX_BUFFALLOC_SZ   (64)
#define LEX_MAX_IDENTIFIER_LEN (64)

#define LEX_TOTAL_TOKENS       (128)
#define LEX_TOKEN_SIZE         (32)

// The following form the EXTERNAL INTERFACE

typedef enum yytokentype lex_Token_t;

lex_Token_t yylex(void);
lex_Token_t lex_Token_getnext(FILE *f);
const char *lex_Token_getcode(lex_Token_t code);
const char *lex_Token_getsymbol(lex_Token_t code);

const char *lex_Buffer_getstr();

extern int lex_line_no;
extern int lex_char_no;

// The following are for INTERNAL USE

typedef struct lex_Buffer_t lex_Buffer_t;

extern lex_Buffer_t *lex_buffer;
extern lex_Token_t lex_currtok;

struct lex_Buffer_t {
    char *buffer;
    size_t push_i;
    size_t size;
};

// lexer/io
char lex_getc(FILE *f);
char lex_ungetc(char *c, FILE *f);

bool lex_is_delimiter(char c);
bool lex_is_printable(char c);
bool lex_is_alnumundr(char c);

// lexer/buffer
void lex_Buffer_push(char ch);
char lex_Buffer_pop();
void lex_Buffer_reset();
void lex_Buffer_free();

// lexer
void lex_throw(const char *msg);

#endif
