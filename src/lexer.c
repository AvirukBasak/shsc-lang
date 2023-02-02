#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "lexer.h"

enum LexToken {
    LEX_KWD_START,
    LEX_KWD_WHILE,
    LEX_KWD_CALC,
    LEX_LOGICAL_IDENTICAL,
    LEX_LOGICAL_UNINDENTICAL,
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
    LEX_INVALID
};

struct LexBuffer {
    char *buffer;
    size_t push_i;
    size_t size;
};

char lex_getchar(FILE *f);
void lex_buffpush(char ch);
bool lex_buffmatch(const char* tok);
bool lex_is_char_literal();
bool lex_is_int_literal();
bool lex_is_float_literal();
bool lex_is_str_literal();
bool lex_is_identifier();

void lex_throw(const char *msg);

LexBuffer *lex_buffer = NULL;

char lex_getchar(FILE *f)
{
    char c = fgetc(f);
    if (!c || c == (char) EOF) return 0;
    if ((c > 0 && c <= 32 && c != '\t' && c != '\n' && c != '\r' && c != ' ') || c == 127)
        lex_throw("un-printable character found");
    if (c > 127) lex_throw("non-ascii symbol not recognized");
    // ignore single line comments and delimiters
    while ((c > 0 && c <= 32) || c == '#') {
        if (c == '#') while (c != '\n') c = fgetc(f);
        c = fgetc(f);
    }
    return c;
}

void lex_buffpush(char ch)
{
    if (!lex_buffer) lex_buffer = calloc(1, sizeof(LexBuffer));
    if (!lex_buffer) lex_throw("memory allocation failed");
    if (lex_buffer->push_i >= lex_buffer->size) {
        lex_buffer->buffer = realloc(lex_buffer->buffer, lex_buffer->size + LEX_MAX_BUFFALLOC_SZ);
        if (!lex_buffer->buffer) lex_throw("memory allocation failed");
        lex_buffer->size += LEX_MAX_BUFFALLOC_SZ;
    }
    lex_buffer->buffer[lex_buffer->push_i++] = ch;
    lex_buffer->buffer[lex_buffer->push_i] = 0;
}

bool lex_buffmatch(const char* tok)
{
    const size_t tok_len = strlen(tok);
    if (lex_buffer->push_i != tok_len)
        return false;
    if (!strncmp(lex_buffer->buffer, tok, tok_len)) {
        lex_buffer->push_i = 0;
        return true;
    }
    return false;
}

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

LexToken lex_get_nexttok(FILE *f)
{
    char curr = lex_getchar(f);
    while (curr) {
        lex_buffpush(curr);
             if (lex_buffmatch("start")) return LEX_KWD_START;
        else if (lex_buffmatch("while")) return LEX_KWD_WHILE;
        else if (lex_buffmatch("calc"))  return LEX_KWD_CALC;
        else if (lex_buffmatch("==="))   return LEX_LOGICAL_IDENTICAL;
        else if (lex_buffmatch("!=="))   return LEX_LOGICAL_UNINDENTICAL;
        else if (lex_buffmatch("if"))    return LEX_KWD_IF;
        else if (lex_buffmatch("&&"))    return LEX_LOGICAL_AND;
        else if (lex_buffmatch("||"))    return LEX_LOGICAL_OR;
        else if (lex_buffmatch("=="))    return LEX_LOGICAL_EQUALITY;
        else if (lex_buffmatch("!="))    return LEX_LOGICAL_UNEQUALITY;
        else if (lex_buffmatch(">="))    return LEX_LOGICAL_GREATER_EQUAL;
        else if (lex_buffmatch("<="))    return LEX_LOGICAL_LESSER_EQUAL;
        else if (lex_buffmatch("<<"))    return LEX_BITWISE_LSHIFT;
        else if (lex_buffmatch(">>"))    return LEX_BITWISE_RSHIFT;
        else if (lex_buffmatch("**"))    return LEX_EXPONENT;
        else if (lex_buffmatch("->"))    return LEX_SARROW;
        else if (lex_buffmatch("=>"))    return LEX_DARROW;
        else if (lex_buffmatch("|>"))    return LEX_PIPEOUT;
        else if (lex_buffmatch("!"))     return LEX_LOGICAL_NOT;
        else if (lex_buffmatch("&"))     return LEX_BITWISE_AND;
        else if (lex_buffmatch("|"))     return LEX_BITWISE_OR;
        else if (lex_buffmatch("~"))     return LEX_BITWISE_NOT;
        else if (lex_buffmatch("^"))     return LEX_BITWISE_XOR;
        else if (lex_buffmatch(">"))     return LEX_RBRACE_ANGULAR;
        else if (lex_buffmatch("<"))     return LEX_LBRACE_ANGULAR;
        else if (lex_buffmatch(")"))     return LEX_RBRACE_PAREN;
        else if (lex_buffmatch("("))     return LEX_LBRACE_PAREN;
        else if (lex_buffmatch("{"))     return LEX_RBRACE_CURLY;
        else if (lex_buffmatch("}"))     return LEX_LBRACE_CURLY;
        else if (lex_buffmatch("["))     return LEX_RBRACE_SQUARE;
        else if (lex_buffmatch("]"))     return LEX_LBRACE_SQUARE;
        else if (lex_buffmatch("="))     return LEX_ASSIGN;
        else if (lex_buffmatch("+"))     return LEX_PLUS;
        else if (lex_buffmatch("-"))     return LEX_MINUS;
        else if (lex_buffmatch("*"))     return LEX_ASTERIX;
        else if (lex_buffmatch("/"))     return LEX_FSLASH;
        else if (lex_buffmatch("\\"))    return LEX_BSLASH;
        else if (lex_buffmatch("%"))     return LEX_PERCENT;
        else if (lex_buffmatch(","))     return LEX_COMMA;
        else if (lex_buffmatch(":"))     return LEX_COLON;
        else if (lex_buffmatch(";"))     return LEX_SEMICOLON;
        else if (lex_buffmatch("."))     return LEX_DOT;
        else if (lex_buffmatch("'"))     return LEX_SQUOTE;
        else if (lex_buffmatch("\""))    return LEX_DQUOTE;
        else if (lex_buffmatch("`"))     return LEX_BACKTICK;
        else if (lex_buffmatch("?"))     return LEX_QUESTION;
        else if (lex_buffmatch("@"))     return LEX_ATRATE;
        else if (lex_buffmatch("$"))     return LEX_KWD_SET;
        else if (lex_is_char_literal())  return LEX_LITERAL_CHAR;
        else if (lex_is_int_literal())   return LEX_LITERAL_INT;
        else if (lex_is_float_literal()) return LEX_LITERAL_FLOAT;
        else if (lex_is_str_literal())   return LEX_LITERAL_STR;
        else if (lex_is_identifier())    return LEX_IDENTIFIER;
        else lex_throw("syntax error");
        curr = lex_getchar(f);
    }
    return LEX_INVALID;
}

char *lex_get_tokstr()
{
    return lex_buffer->buffer;
}

void lex_throw(const char *msg)
{
    if (msg) {
        fprintf(stderr, "scsh: lexer error: %s\n", msg);
        exit(1);
    } else abort();
}
