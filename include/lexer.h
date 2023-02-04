#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define LEX_MAX_BUFFALLOC_SZ   (64)
#define LEX_MAX_IDENTIFIER_LEN (64)

#define LEX_TOTAL_TOKENS       (128)
#define LEX_TOKEN_SIZE         (32)

typedef enum LexToken LexToken;
typedef struct LexBuffer LexBuffer;

// contributor's warning: ensure tokens are sorted according to the order in lex_init()
enum LexToken {
    LEX_BANG,                  // "!"
    LEX_LOGICAL_UNEQUAL,       // "!="
    LEX_LOGICAL_UNIDENTICAL,   // "!=="
    LEX_DQUOTE,                // "\""
    LEX_DOLLAR,                // "$"
    LEX_PERCENT,               // "%"
    LEX_AMPERSAND,             // "&"
    LEX_LOGICAL_AND,           // "&&"
    LEX_SQUOTE,                // "'"
    LEX_LBRACE_PAREN,          // "("
    LEX_RBRACE_PAREN,          // ")"
    LEX_ASTERIX,               // "*"
    LEX_EXPONENT,              // "**"
    LEX_PLUS,                  // "+"
    LEX_INCREMENT,             // "++"
    LEX_COMMA,                 // ","
    LEX_MINUS,                 // "-"
    LEX_DECREMENT,             // "--"
    LEX_SARROW,                // "->"
    LEX_DOT,                   // "."
    LEX_FSLASH,                // "/"
    LEX_COLON,                 // ":"
    LEX_DCOLON,                // "::"
    LEX_SEMICOLON,             // ";"
    LEX_LBRACE_ANGULAR,        // "<"
    LEX_BITWISE_LSHIFT,        // "<<"
    LEX_LOGICAL_LESSER_EQUAL,  // "<="
    LEX_ASSIGN,                // "="
    LEX_LOGICAL_EQUAL,         // "=="
    LEX_LOGICAL_IDENTICAL,     // "==="
    LEX_DARROW,                // "=>"
    LEX_RBRACE_ANGULAR,        // ">"
    LEX_LOGICAL_GREATER_EQUAL, // ">="
    LEX_BITWISE_RSHIFT,        // ">>"
    LEX_QUESTION,              // "?"
    LEX_AT,                    // "@"
    LEX_LBRACE_SQUARE,         // "["
    LEX_BSLASH,                // "\\"
    LEX_RBRACE_SQUARE,         // "]"
    LEX_CARET,                 // "^"
    LEX_BACKTICK,              // "`"
    LEX_LBRACE_CURLY,          // "{"
    LEX_PIPE,                  // "|"
    LEX_PIPEOUT,               // "|>"
    LEX_LOGICAL_OR,            // "||"
    LEX_RBRACE_CURLY,          // "}"
    LEX_BITWISE_NOT,           // "~"
    LEX_EOF,                   // "<eof>"
    LEX_INVALID                // "<invalid>"
};

extern int lex_line_no;
extern int lex_char_no;

LexToken lex_get_nexttok(FILE *f);
char *lex_get_tokcode(LexToken code);
char *lex_get_symbol(LexToken code);
char *lex_get_tokstr();

#endif
