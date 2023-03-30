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

// The following form the EXTERNAL INTERFACE

typedef enum LexToken LexToken;

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

// contributor's warning: ensure tokens are grouped and sorted in alphabetical order
enum LexToken {
    // operators and seperators
    LEXTOK_BANG = 10000,           // "!"
    LEXTOK_LOGICAL_UNEQUAL,        // "!="
    LEXTOK_LOGICAL_UNIDENTICAL,    // "!=="
    LEXTOK_DQUOTE,                 // "\""
    LEXTOK_DOLLAR,                 // "$"
    LEXTOK_PERCENT,                // "%"
    LEXTOK_MODULO_ASSIGN,          // "%="
    LEXTOK_AMPERSAND,              // "&"
    LEXTOK_LOGICAL_AND,            // "&&"
    LEXTOK_LOGICAL_AND_ASSIGN,     // "&&="
    LEXTOK_BITWISE_AND_ASSIGN,     // "&="
    LEXTOK_SQUOTE,                 // "'"
    LEXTOK_LBRACE_PAREN,           // "("
    LEXTOK_RBRACE_PAREN,           // ")"
    LEXTOK_ASTERIX,                // "*"
    LEXTOK_EXPONENT,               // "**"
    LEXTOK_EXPONENT_ASSIGN,        // "**="
    LEXTOK_MULTIPLY_ASSIGN,        // "*="
    LEXTOK_PLUS,                   // "+"
    LEXTOK_INCREMENT,              // "++"
    LEXTOK_ADD_ASSIGN,             // "+="
    LEXTOK_COMMA,                  // ","
    LEXTOK_MINUS,                  // "-"
    LEXTOK_DECREMENT,              // "--"
    LEXTOK_SUBSTRACT_ASSIGN,       // "-="
    LEXTOK_SARROW,                 // "->"
    LEXTOK_DOT,                    // "."
    LEXTOK_ELIPSIS,                // "..."
    LEXTOK_FSLASH,                 // "/"
    LEXTOK_FLOOR_DIVIDE,           // "//"
    LEXTOK_FLOOR_DIVIDE_ASSIGN,    // "//="
    LEXTOK_DIVIDE_ASSIGN,          // "/="
    LEXTOK_COLON,                  // ":"
    LEXTOK_DCOLON,                 // "::"
    LEXTOK_SEMICOLON,              // ";"
    LEXTOK_LBRACE_ANGULAR,         // "<"
    LEXTOK_BITWISE_LSHIFT,         // "<<"
    LEXTOK_BITWISE_LSHIFT_ASSIGN,  // "<<="
    LEXTOK_LOGICAL_LESSER_EQUAL,   // "<="
    LEXTOK_ASSIGN,                 // "="
    LEXTOK_LOGICAL_EQUAL,          // "=="
    LEXTOK_LOGICAL_IDENTICAL,      // "==="
    LEXTOK_DARROW,                 // "=>"
    LEXTOK_RBRACE_ANGULAR,         // ">"
    LEXTOK_LOGICAL_GREATER_EQUAL,  // ">="
    LEXTOK_BITWISE_RSHIFT,         // ">>"
    LEXTOK_BITWISE_RSHIFT_ASSIGN,  // ">>="
    LEXTOK_ARITH_RSHIFT,           // ">>>"
    LEXTOK_ARITH_RSHIFT_ASSIGN,    // ">>>="
    LEXTOK_QUESTION,               // "?"
    LEXTOK_AT,                     // "@"
    LEXTOK_LBRACE_SQUARE,          // "["
    LEXTOK_BSLASH,                 // "\\"
    LEXTOK_RBRACE_SQUARE,          // "]"
    LEXTOK_CARET,                  // "^"
    LEXTOK_BITWISE_XOR_ASSIGN,     // "^="
    LEXTOK_BACKTICK,               // "`"
    LEXTOK_LBRACE_CURLY,           // "{"
    LEXTOK_PIPE,                   // "|"
    LEXTOK_BITWISE_OR_ASSIGN,      // "|="
    LEXTOK_PIPEOUT,                // "|>"
    LEXTOK_LOGICAL_OR,             // "||"
    LEXTOK_LOGICAL_OR_ASSIGN,      // "||="
    LEXTOK_RBRACE_CURLY,           // "}"
    LEXTOK_TILDE,                  // "~"
    // keywords
    LEXTOK_KWD_CALC,               // "calc"
    LEXTOK_KWD_END,                // "end"
    LEXTOK_KWD_IF,                 // "if"
    LEXTOK_KWD_START,              // "start"
    LEXTOK_KWD_WHILE,              // "while"
    // identifier
    LEXTOK_IDENTIFIER,             // "<identifier>"
    // literals
    LEXTOK_CHAR_LITERAL,           // "<charlit>"
    LEXTOK_BINFLOAT_LITERAL,       // "<binfloattlit>"
    LEXTOK_OCTFLOAT_LITERAL,       // "<octfloattlit>"
    LEXTOK_DECFLOAT_LITERAL,       // "<decfloattlit>"
    LEXTOK_HEXFLOAT_LITERAL,       // "<hexfloattlit>"
    LEXTOK_BININT_LITERAL,         // "<binintlit>"
    LEXTOK_OCTINT_LITERAL,         // "<octintlit>"
    LEXTOK_DECINT_LITERAL,         // "<decintlit>"
    LEXTOK_HEXINT_LITERAL,         // "<hexintlit>"
    LEXTOK_STR_LITERAL,            // "<strlit>"
    LEXTOK_INTERP_STR_LITERAL,     // "<interpstrlit>"
    // default cases
    LEXTOK_EOF,                    // "<eof>"
    LEXTOK_INVALID,                // "<invalid>"
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
