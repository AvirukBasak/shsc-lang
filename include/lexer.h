#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define LEX_MAX_BUFFALLOC_SZ   (64)
#define LEX_MAX_IDENTIFIER_LEN (64)

typedef enum LexToken LexToken;
typedef struct LexBuffer LexBuffer;

LexToken lex_get_nexttok(FILE *f);
char *lex_get_tokstr();

#endif
