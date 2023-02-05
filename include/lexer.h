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

// contributor's warning: ensure tokens are grouped and sorted in alphabetical order
enum LexToken {
    // operators and seperators
    LEX_BANG,                   // "!"
    LEX_LOGICAL_UNEQUAL,        // "!="
    LEX_LOGICAL_UNIDENTICAL,    // "!=="
    LEX_DQUOTE,                 // "\""
    LEX_DOLLAR,                 // "$"
    LEX_PERCENT,                // "%"
    LEX_MODULO_ASSIGN,          // "%="
    LEX_AMPERSAND,              // "&"
    LEX_LOGICAL_AND,            // "&&"
    LEX_LOGICAL_AND_ASSIGN,     // "&&="
    LEX_BITWISE_AND_ASSIGN,     // "&="
    LEX_SQUOTE,                 // "'"
    LEX_LBRACE_PAREN,           // "("
    LEX_RBRACE_PAREN,           // ")"
    LEX_ASTERIX,                // "*"
    LEX_EXPONENT,               // "**"
    LEX_EXPONENT_ASSIGN,        // "**="
    LEX_MULTIPLY_ASSIGN,        // "*="
    LEX_PLUS,                   // "+"
    LEX_INCREMENT,              // "++"
    LEX_ADD_ASSIGN,             // "+="
    LEX_COMMA,                  // ","
    LEX_MINUS,                  // "-"
    LEX_DECREMENT,              // "--"
    LEX_SUBSTRACT_ASSIGN,       // "-="
    LEX_SARROW,                 // "->"
    LEX_DOT,                    // "."
    LEX_ELIPSIS,                // "..."
    LEX_FSLASH,                 // "/"
    LEX_FLOOR_DIVIDE,           // "//"
    LEX_FLOOR_DIVIDE_ASSIGN,    // "//="
    LEX_DIVIDE_ASSIGN,          // "/="
    LEX_COLON,                  // ":"
    LEX_DCOLON,                 // "::"
    LEX_SEMICOLON,              // ";"
    LEX_LBRACE_ANGULAR,         // "<"
    LEX_BITWISE_LSHIFT,         // "<<"
    LEX_BITWISE_LSHIFT_ASSIGN,  // "<<="
    LEX_LOGICAL_LESSER_EQUAL,   // "<="
    LEX_ASSIGN,                 // "="
    LEX_LOGICAL_EQUAL,          // "=="
    LEX_LOGICAL_IDENTICAL,      // "==="
    LEX_DARROW,                 // "=>"
    LEX_RBRACE_ANGULAR,         // ">"
    LEX_LOGICAL_GREATER_EQUAL,  // ">="
    LEX_BITWISE_RSHIFT,         // ">>"
    LEX_BITWISE_RSHIFT_ASSIGN,  // ">>="
    LEX_ARITH_RSHIFT,           // ">>>"
    LEX_ARITH_RSHIFT_ASSIGN,    // ">>>="
    LEX_QUESTION,               // "?"
    LEX_AT,                     // "@"
    LEX_LBRACE_SQUARE,          // "["
    LEX_BSLASH,                 // "\\"
    LEX_RBRACE_SQUARE,          // "]"
    LEX_CARET,                  // "^"
    LEX_BITWISE_XOR_ASSIGN,     // "^="
    LEX_BACKTICK,               // "`"
    LEX_LBRACE_CURLY,           // "{"
    LEX_PIPE,                   // "|"
    LEX_BITWISE_OR_ASSIGN,      // "|="
    LEX_PIPEOUT,                // "|>"
    LEX_LOGICAL_OR,             // "||"
    LEX_LOGICAL_OR_ASSIGN,      // "||="
    LEX_RBRACE_CURLY,           // "}"
    LEX_TILDE,                  // "~"
    // keywords
    LEX_KWD_CALC,               // "calc"
    LEX_KWD_END,                // "end"
    LEX_KWD_IF,                 // "if"
    LEX_KWD_START,              // "start"
    LEX_KWD_WHILE,              // "while"
    // identifier
    LEX_IDENTIFIER,             // "<identifier>"
    // literals
    LEX_CHAR_LITERAL,           // "<charlit>"
    LEX_FLOAT_LITERAL,          // "<floattlit>"
    LEX_INT_LITERAL,            // "<intlit>"
    LEX_STR_LITERAL,            // "<strlit>"
    // default cases
    LEX_EOF,                    // "<eof>"
    LEX_INVALID,                // "<invalid>"
};

extern int lex_line_no;
extern int lex_char_no;

char *lex_get_buffstr();

LexToken lex_get_nexttok(FILE *f);
char *lex_get_tokcode(LexToken code);
char *lex_get_symbol(LexToken code);

#endif
