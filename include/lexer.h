#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define LEX_MAX_BUFFALLOC_SZ   (64)
#define LEX_MAX_IDENTIFIER_LEN (64)

#define LEX_TOTAL_TOKENS       (46)
#define LEX_TOKEN_SIZE         (32)

typedef enum LexToken LexToken;
typedef struct LexBuffer LexBuffer;

enum LexToken {
    LEX_KWD_START,
    LEX_KWD_WHILE,
    LEX_KWD_CALC,
    LEX_LOGICAL_IDENTICAL,
    LEX_LOGICAL_UNIDENTICAL,
    LEX_KWD_IF,
    LEX_LOGICAL_AND,
    LEX_LOGICAL_OR,
    LEX_LOGICAL_EQUALITY,
    LEX_LOGICAL_UNEQUALITY,
    LEX_LOGICAL_GREATER_EQUAL,
    LEX_LOGICAL_LESSER_EQUAL,
    LEX_BITWISE_LSHIFT,
    LEX_BITWISE_RSHIFT,
    LEX_EXPONENT,
    LEX_SARROW,
    LEX_DARROW,
    LEX_DCOLON,
    LEX_PIPEOUT,
    LEX_LOGICAL_NOT,
    LEX_BITWISE_AND,
    LEX_BITWISE_OR,
    LEX_BITWISE_NOT,
    LEX_BITWISE_XOR,
    LEX_RBRACE_ANGULAR,
    LEX_LBRACE_ANGULAR,
    LEX_RBRACE_PAREN,
    LEX_LBRACE_PAREN,
    LEX_RBRACE_CURLY,
    LEX_LBRACE_CURLY,
    LEX_RBRACE_SQUARE,
    LEX_LBRACE_SQUARE,
    LEX_ASSIGN,
    LEX_PLUS,
    LEX_MINUS,
    LEX_ASTERIX,
    LEX_FSLASH,
    LEX_BSLASH,
    LEX_PERCENT,
    LEX_COMMA,
    LEX_COLON,
    LEX_SEMICOLON,
    LEX_DOT,
    LEX_SQUOTE,
    LEX_DQUOTE,
    LEX_BACKTICK,
    LEX_QUESTION,
    LEX_ATRATE,
    LEX_KWD_SET,
    LEX_LITERAL_CHAR,
    LEX_LITERAL_INT,
    LEX_LITERAL_FLOAT,
    LEX_LITERAL_STR,
    LEX_IDENTIFIER,
    LEX_INVALID,
    LEX_EOF
};

extern int lex_line_no;
extern int lex_char_no;

LexToken lex_get_nexttok(FILE *f);
char *lex_get_tokcode(LexToken code);
char *lex_get_tokstr();

#endif
