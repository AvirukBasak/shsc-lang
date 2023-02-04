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

char *lex_tokens[LEX_TOTAL_TOKENS];

void lex_init();

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

// contributor's warning: ensure tokens are alphabetically sorted
void lex_init()
{
    lex_tokens[LEX_BANG]                  = "!";
    lex_tokens[LEX_LOGICAL_UNEQUAL]       = "!=";
    lex_tokens[LEX_LOGICAL_UNIDENTICAL]   = "!==";
    lex_tokens[LEX_DQUOTE]                = "\"";
    lex_tokens[LEX_DOLLAR]                = "$";
    lex_tokens[LEX_PERCENT]               = "%";
    lex_tokens[LEX_AMPERSAND]             = "&";
    lex_tokens[LEX_LOGICAL_AND]           = "&&";
    lex_tokens[LEX_SQUOTE]                = "'";
    lex_tokens[LEX_LBRACE_PAREN]          = "(";
    lex_tokens[LEX_RBRACE_PAREN]          = ")";
    lex_tokens[LEX_ASTERIX]               = "*";
    lex_tokens[LEX_EXPONENT]              = "**";
    lex_tokens[LEX_PLUS]                  = "+";
    lex_tokens[LEX_INCREMENT]             = "++";
    lex_tokens[LEX_COMMA]                 = ",";
    lex_tokens[LEX_MINUS]                 = "-";
    lex_tokens[LEX_DECREMENT]             = "--";
    lex_tokens[LEX_SARROW]                = "->";
    lex_tokens[LEX_DOT]                   = ".";
    lex_tokens[LEX_FSLASH]                = "/";
    lex_tokens[LEX_COLON]                 = ":";
    lex_tokens[LEX_DCOLON]                = "::";
    lex_tokens[LEX_SEMICOLON]             = ";";
    lex_tokens[LEX_LBRACE_ANGULAR]        = "<";
    lex_tokens[LEX_BITWISE_LSHIFT]        = "<<";
    lex_tokens[LEX_LOGICAL_LESSER_EQUAL]  = "<=";
    lex_tokens[LEX_ASSIGN]                = "=";
    lex_tokens[LEX_LOGICAL_EQUAL]         = "==";
    lex_tokens[LEX_LOGICAL_IDENTICAL]     = "===";
    lex_tokens[LEX_DARROW]                = "=>";
    lex_tokens[LEX_RBRACE_ANGULAR]        = ">";
    lex_tokens[LEX_LOGICAL_GREATER_EQUAL] = ">=";
    lex_tokens[LEX_BITWISE_RSHIFT]        = ">>";
    lex_tokens[LEX_QUESTION]              = "?";
    lex_tokens[LEX_AT]                    = "@";
    lex_tokens[LEX_LBRACE_SQUARE]         = "[";
    lex_tokens[LEX_BSLASH]                = "\\";
    lex_tokens[LEX_RBRACE_SQUARE]         = "]";
    lex_tokens[LEX_CARET]                 = "^";
    lex_tokens[LEX_BACKTICK]              = "`";
    lex_tokens[LEX_LBRACE_CURLY]          = "{";
    lex_tokens[LEX_PIPE]                  = "|";
    lex_tokens[LEX_PIPEOUT]               = "|>";
    lex_tokens[LEX_LOGICAL_OR]            = "||";
    lex_tokens[LEX_RBRACE_CURLY]          = "}";
    lex_tokens[LEX_BITWISE_NOT]           = "~";
    lex_tokens[LEX_EOF]                   = "<eof>";
    lex_tokens[LEX_INVALID]               = "<invalid>";
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

char lex_buffpop()
{
    if (!lex_buffer) abort();
    char tmp = 0;
    if (lex_buffer->push_i > 0) {
        tmp = lex_buffer->buffer[lex_buffer->push_i -1];
        lex_buffer->buffer[--lex_buffer->push_i] = 0;
    }
    return tmp;
}

void lex_buffreset()
{
    if (!lex_buffer) return;
    lex_buffer->buffer[lex_buffer->push_i = 0] = 0;
}

char lex_getc(FILE *f)
{
    char c = getc(f);
    if (!c) return 0;
    if (c == (char) EOF) return (char) EOF;
    if (!lex_is_printable(c))
        lex_throw("un-printable character found");
    if (c > 127) lex_throw("non-ascii symbol found");
    // ignore single line comments
    if (c == '#') while (c != '\n') {
        c = getc(f);
        if (!c) return 0;
        if (c == (char) EOF) return (char) EOF;
        if (!lex_is_printable(c))
            lex_throw("un-printable character found");
        if (c == '\n') { lex_line_no++; lex_char_no = 0; }
        else if (lex_is_printable(c)) lex_char_no++;
    }
    else if (c == '\n') { lex_line_no++; lex_char_no = 0; }
    else if (lex_is_printable(c)) lex_char_no++;
    if (!lex_is_delimiter(c)) lex_buffpush(c);
    return c;
}

int lex_ungetc(char c, FILE *f)
{
    if (c == '\n') { lex_line_no--; lex_char_no = -1; }
    else if (lex_is_printable(c)) lex_char_no--;
    if (!lex_is_delimiter(c)) lex_buffpop();
    return ungetc(c, f);
}

bool lex_is_delimiter(char c)
{
    return c == '\t' || c == '\n' || c == '\r' || c == ' ';
}

bool lex_is_printable(char c)
{
    return (c >= 32 && c < 127) || lex_is_delimiter(c);
}

bool lex_isalmun_undr(char c)
{
    return isalnum(c) || c == '_';
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

// the lexer state machine
LexToken lex_get_nexttok(FILE *f)
{
    lex_buffreset();
    char c0 = lex_getc(f);
    while (lex_is_delimiter(c0)) c0 = lex_getc(f);
    switch (c0) {
        case '!': {
            char c1 = lex_getc(f);
            switch (c1) {
                case '=': {
                    char c2 = lex_getc(f);
                    switch (c2) {
                        case '=': return LEX_LOGICAL_UNIDENTICAL;
                        default: lex_ungetc(c2, f);
                    }
                    return LEX_LOGICAL_UNEQUAL;
                }
                default: lex_ungetc(c1, f);
            }
            return LEX_BANG;
        }
        case '"':         return LEX_DQUOTE;
        case '$':         return LEX_DOLLAR;
        case '%':         return LEX_PERCENT;
        case '&': {
            return LEX_INVALID;
        }
        case '\'':        return LEX_SQUOTE;
        case '(':         return LEX_LBRACE_PAREN;
        case ')':         return LEX_RBRACE_PAREN;
        case '*': {
            return LEX_INVALID;
        }
        case '+': {
            return LEX_INVALID;
        }
        case ',':         return LEX_COMMA;
        case '-': {
            return LEX_INVALID;
        }
        case '.':         return LEX_DOT;
        case '/':         return LEX_FSLASH;
        case ':': {
            return LEX_INVALID;
        }
        case ';':         return LEX_SEMICOLON;
        case '<': {
            return LEX_INVALID;
        }
        case '=': {
            char c1 = lex_getc(f);
            switch (c1) {
                case '=': {
                    char c2 = lex_getc(f);
                    switch (c2) {
                        case '=': return LEX_LOGICAL_IDENTICAL;
                        default: lex_ungetc(c2, f);
                    }
                    return LEX_LOGICAL_EQUAL;
                }
                case '>': return LEX_DARROW;
                default: lex_ungetc(c1, f);
            }
            return LEX_ASSIGN;
        }
        case '>': {
            return LEX_INVALID;
        }
        case '?':         return LEX_QUESTION;
        case '@':         return LEX_AT;
        case '[':         return LEX_LBRACE_SQUARE;
        case '\\':        return LEX_BSLASH;
        case ']':         return LEX_RBRACE_SQUARE;
        case '^':         return LEX_CARET;
        case '`':         return LEX_BACKTICK;
        case '{':         return LEX_LBRACE_CURLY;
        case '|': {
            return LEX_INVALID;
        }
        case '}':         return LEX_INVALID;
        case '~':         return LEX_BITWISE_NOT;
        case (char) EOF:  return LEX_EOF;
        default:          return LEX_INVALID;
    }
    return LEX_INVALID;
}

char *lex_get_tokcode(LexToken code)
{
    // contributor's warning: ensure tokens are sorted according to the order in lex_init()
    switch(code) {
        case LEX_BANG:                  return "LEX_BANG";
        case LEX_LOGICAL_UNEQUAL:       return "LEX_LOGICAL_UNEQUAL";
        case LEX_LOGICAL_UNIDENTICAL:   return "LEX_LOGICAL_UNIDENTICAL";
        case LEX_DQUOTE:                return "LEX_DQUOTE";
        case LEX_DOLLAR:                return "LEX_DOLLAR";
        case LEX_PERCENT:               return "LEX_PERCENT";
        case LEX_AMPERSAND:             return "LEX_AMPERSAND";
        case LEX_LOGICAL_AND:           return "LEX_LOGICAL_AND";
        case LEX_SQUOTE:                return "LEX_SQUOTE";
        case LEX_LBRACE_PAREN:          return "LEX_LBRACE_PAREN";
        case LEX_RBRACE_PAREN:          return "LEX_RBRACE_PAREN";
        case LEX_ASTERIX:               return "LEX_ASTERIX";
        case LEX_EXPONENT:              return "LEX_EXPONENT";
        case LEX_PLUS:                  return "LEX_PLUS";
        case LEX_INCREMENT:             return "LEX_INCREMENT";
        case LEX_COMMA:                 return "LEX_COMMA";
        case LEX_MINUS:                 return "LEX_MINUS";
        case LEX_DECREMENT:             return "LEX_DECREMENT";
        case LEX_SARROW:                return "LEX_SARROW";
        case LEX_DOT:                   return "LEX_DOT";
        case LEX_FSLASH:                return "LEX_FSLASH";
        case LEX_COLON:                 return "LEX_COLON";
        case LEX_DCOLON:                return "LEX_DCOLON";
        case LEX_SEMICOLON:             return "LEX_SEMICOLON";
        case LEX_LBRACE_ANGULAR:        return "LEX_LBRACE_ANGULAR";
        case LEX_BITWISE_LSHIFT:        return "LEX_BITWISE_LSHIFT";
        case LEX_LOGICAL_LESSER_EQUAL:  return "LEX_LOGICAL_LESSER_EQUAL";
        case LEX_ASSIGN:                return "LEX_ASSIGN";
        case LEX_LOGICAL_EQUAL:         return "LEX_LOGICAL_EQUAL";
        case LEX_LOGICAL_IDENTICAL:     return "LEX_LOGICAL_IDENTICAL";
        case LEX_DARROW:                return "LEX_DARROW";
        case LEX_RBRACE_ANGULAR:        return "LEX_RBRACE_ANGULAR";
        case LEX_LOGICAL_GREATER_EQUAL: return "LEX_LOGICAL_GREATER_EQUAL";
        case LEX_BITWISE_RSHIFT:        return "LEX_BITWISE_RSHIFT";
        case LEX_QUESTION:              return "LEX_QUESTION";
        case LEX_AT:                    return "LEX_AT";
        case LEX_LBRACE_SQUARE:         return "LEX_LBRACE_SQUARE";
        case LEX_BSLASH:                return "LEX_BSLASH";
        case LEX_RBRACE_SQUARE:         return "LEX_RBRACE_SQUARE";
        case LEX_CARET:                 return "LEX_CARET";
        case LEX_BACKTICK:              return "LEX_BACKTICK";
        case LEX_LBRACE_CURLY:          return "LEX_LBRACE_CURLY";
        case LEX_PIPE:                  return "LEX_PIPE";
        case LEX_PIPEOUT:               return "LEX_PIPEOUT";
        case LEX_LOGICAL_OR:            return "LEX_LOGICAL_OR";
        case LEX_RBRACE_CURLY:          return "LEX_RBRACE_CURLY";
        case LEX_BITWISE_NOT:           return "LEX_BITWISE_NOT";
        case LEX_EOF:                   return "LEX_EOF";
        case LEX_INVALID:               return "LEX_INVALID";
        default:                        return "UNKNOWN";
    }
}

char *lex_get_tokstr()
{
    if (!lex_buffer->push_i) return "NULL";
    return lex_buffer->buffer;
}

void lex_throw(const char *msg)
{
    if (!msg) abort();
    io_print_srcerr(lex_line_no, lex_char_no, "lexer error: %s", msg);
    exit(1);
}
