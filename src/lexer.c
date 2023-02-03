#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "io.h"
#include "lexer.h"

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
char lex_getchar(FILE *f);
bool lex_is_printable(char c);
bool lex_isalmun_undr(char c);
void lex_buffpush(char ch);
bool lex_buffmatch(const char* tok);
bool lex_is_char_literal();
bool lex_is_int_literal();
bool lex_is_float_literal();
bool lex_is_str_literal();
bool lex_is_identifier();

void lex_throw(const char *msg);

char lex_getc(FILE *f)
{
    char c = getc(f);
    if (c == '\n') { lex_line_no++; lex_char_no = 0; }
    else if (lex_is_printable(c)) lex_char_no++;
    return c;
}

int lex_ungetc(char c, FILE *f)
{
    if (c == '\n') { lex_line_no--; lex_char_no = -1; }
    else if (lex_is_printable(c)) lex_char_no--;
    return ungetc(c, f);
}

char lex_getchar(FILE *f)
{
    char c = lex_getc(f);
    if (!c || c == (char) EOF) return 0;
    if (!lex_is_printable(c))
        lex_throw("un-printable character found");
    if (c > 127) lex_throw("non-ascii symbol not recognized");
    // ignore single line comments and delimiters
    while ((c > 0 && c <= 32) || c == '#') {
        if (c == '#') while (c != '\n') c = lex_getc(f);
        c = lex_getc(f);
    }
    return c;
}

bool lex_is_printable(char c)
{
    return (c >= 32 && c < 127) || c != '\t' || c != '\n' || c != '\r';
}

bool lex_isalmun_undr(char c)
{
    return isalnum(c) || c == '_';
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
        if (lex_buffmatch("==="))   return LEX_LOGICAL_IDENTICAL;
        if (lex_buffmatch("!=="))   return LEX_LOGICAL_UNINDENTICAL;
        if (lex_buffmatch("if"))    return LEX_KWD_IF;
        if (lex_buffmatch("&&"))    return LEX_LOGICAL_AND;
        if (lex_buffmatch("||"))    return LEX_LOGICAL_OR;
        if (lex_buffmatch("=="))    return LEX_LOGICAL_EQUALITY;
        if (lex_buffmatch("!="))    return LEX_LOGICAL_UNEQUALITY;
        if (lex_buffmatch(">="))    return LEX_LOGICAL_GREATER_EQUAL;
        if (lex_buffmatch("<="))    return LEX_LOGICAL_LESSER_EQUAL;
        if (lex_buffmatch("<<"))    return LEX_BITWISE_LSHIFT;
        if (lex_buffmatch(">>"))    return LEX_BITWISE_RSHIFT;
        if (lex_buffmatch("**"))    return LEX_EXPONENT;
        if (lex_buffmatch("->"))    return LEX_SARROW;
        if (lex_buffmatch("=>"))    return LEX_DARROW;
        if (lex_buffmatch("::"))    return LEX_DCOLON;
        if (lex_buffmatch("|>"))    return LEX_PIPEOUT;
        if (lex_buffmatch("!"))     return LEX_LOGICAL_NOT;
        if (lex_buffmatch("&"))     return LEX_BITWISE_AND;
        if (lex_buffmatch("|"))     return LEX_BITWISE_OR;
        if (lex_buffmatch("~"))     return LEX_BITWISE_NOT;
        if (lex_buffmatch("^"))     return LEX_BITWISE_XOR;
        if (lex_buffmatch(">"))     return LEX_RBRACE_ANGULAR;
        if (lex_buffmatch("<"))     return LEX_LBRACE_ANGULAR;
        if (lex_buffmatch(")"))     return LEX_RBRACE_PAREN;
        if (lex_buffmatch("("))     return LEX_LBRACE_PAREN;
        if (lex_buffmatch("{"))     return LEX_RBRACE_CURLY;
        if (lex_buffmatch("}"))     return LEX_LBRACE_CURLY;
        if (lex_buffmatch("["))     return LEX_RBRACE_SQUARE;
        if (lex_buffmatch("]"))     return LEX_LBRACE_SQUARE;
        if (lex_buffmatch("="))     return LEX_ASSIGN;
        if (lex_buffmatch("+"))     return LEX_PLUS;
        if (lex_buffmatch("-"))     return LEX_MINUS;
        if (lex_buffmatch("*"))     return LEX_ASTERIX;
        if (lex_buffmatch("/"))     return LEX_FSLASH;
        if (lex_buffmatch("\\"))    return LEX_BSLASH;
        if (lex_buffmatch("%"))     return LEX_PERCENT;
        if (lex_buffmatch(","))     return LEX_COMMA;
        if (lex_buffmatch(":"))     return LEX_COLON;
        if (lex_buffmatch(";"))     return LEX_SEMICOLON;
        if (lex_buffmatch("."))     return LEX_DOT;
        if (lex_buffmatch("'"))     return LEX_SQUOTE;
        if (lex_buffmatch("\""))    return LEX_DQUOTE;
        if (lex_buffmatch("`"))     return LEX_BACKTICK;
        if (lex_buffmatch("?"))     return LEX_QUESTION;
        if (lex_buffmatch("@"))     return LEX_ATRATE;
        if (lex_buffmatch("$"))     return LEX_KWD_SET;
        else lex_throw("syntax error");
        curr = lex_getchar(f);
    }
    return LEX_INVALID;
}

char *lex_get_tokcode(LexToken code)
{
    switch(code) {
        case LEX_KWD_START:              return "LEX_KWD_START";
        case LEX_KWD_WHILE:              return "LEX_KWD_WHILE";
        case LEX_KWD_CALC:               return "LEX_KWD_CALC";
        case LEX_LOGICAL_IDENTICAL:      return "LEX_LOGICAL_IDENTICAL";
        case LEX_LOGICAL_UNINDENTICAL:   return "LEX_LOGICAL_UNINDENTICAL";
        case LEX_KWD_IF:                 return "LEX_KWD_IF";
        case LEX_LOGICAL_AND:            return "LEX_LOGICAL_AND";
        case LEX_LOGICAL_OR:             return "LEX_LOGICAL_OR";
        case LEX_LOGICAL_EQUALITY:       return "LEX_LOGICAL_EQUALITY";
        case LEX_LOGICAL_UNEQUALITY:     return "LEX_LOGICAL_UNEQUALITY";
        case LEX_LOGICAL_GREATER_EQUAL:  return "LEX_LOGICAL_GREATER_EQUAL";
        case LEX_LOGICAL_LESSER_EQUAL:   return "LEX_LOGICAL_LESSER_EQUAL";
        case LEX_BITWISE_LSHIFT:         return "LEX_BITWISE_LSHIFT";
        case LEX_BITWISE_RSHIFT:         return "LEX_BITWISE_RSHIFT";
        case LEX_EXPONENT:               return "LEX_EXPONENT";
        case LEX_SARROW:                 return "LEX_SARROW";
        case LEX_DARROW:                 return "LEX_DARROW";
        case LEX_DCOLON:                 return "LEX_DCOLON";
        case LEX_PIPEOUT:                return "LEX_PIPEOUT";
        case LEX_LOGICAL_NOT:            return "LEX_LOGICAL_NOT";
        case LEX_BITWISE_AND:            return "LEX_BITWISE_AND";
        case LEX_BITWISE_OR:             return "LEX_BITWISE_OR";
        case LEX_BITWISE_NOT:            return "LEX_BITWISE_NOT";
        case LEX_BITWISE_XOR:            return "LEX_BITWISE_XOR";
        case LEX_RBRACE_ANGULAR:         return "LEX_RBRACE_ANGULAR";
        case LEX_LBRACE_ANGULAR:         return "LEX_LBRACE_ANGULAR";
        case LEX_RBRACE_PAREN:           return "LEX_RBRACE_PAREN";
        case LEX_LBRACE_PAREN:           return "LEX_LBRACE_PAREN";
        case LEX_RBRACE_CURLY:           return "LEX_RBRACE_CURLY";
        case LEX_LBRACE_CURLY:           return "LEX_LBRACE_CURLY";
        case LEX_RBRACE_SQUARE:          return "LEX_RBRACE_SQUARE";
        case LEX_LBRACE_SQUARE:          return "LEX_LBRACE_SQUARE";
        case LEX_ASSIGN:                 return "LEX_ASSIGN";
        case LEX_PLUS:                   return "LEX_PLUS";
        case LEX_MINUS:                  return "LEX_MINUS";
        case LEX_ASTERIX:                return "LEX_ASTERIX";
        case LEX_FSLASH:                 return "LEX_FSLASH";
        case LEX_BSLASH:                 return "LEX_BSLASH";
        case LEX_PERCENT:                return "LEX_PERCENT";
        case LEX_COMMA:                  return "LEX_COMMA";
        case LEX_COLON:                  return "LEX_COLON";
        case LEX_SEMICOLON:              return "LEX_SEMICOLON";
        case LEX_DOT:                    return "LEX_DOT";
        case LEX_SQUOTE:                 return "LEX_SQUOTE";
        case LEX_DQUOTE:                 return "LEX_DQUOTE";
        case LEX_BACKTICK:               return "LEX_BACKTICK";
        case LEX_QUESTION:               return "LEX_QUESTION";
        case LEX_ATRATE:                 return "LEX_ATRATE";
        case LEX_KWD_SET:                return "LEX_KWD_SET";
        case LEX_LITERAL_CHAR:           return "LEX_LITERAL_CHAR";
        case LEX_LITERAL_INT:            return "LEX_LITERAL_INT";
        case LEX_LITERAL_FLOAT:          return "LEX_LITERAL_FLOAT";
        case LEX_LITERAL_STR:            return "LEX_LITERAL_STR";
        case LEX_IDENTIFIER:             return "LEX_IDENTIFIER";
        case LEX_INVALID:                return "LEX_INVALID";
        case LEX_EOF:                    return "LEX_EOF";
        default:                         return "UNKNOWN";
    }
}

char *lex_get_tokstr()
{
    return lex_buffer->buffer;
}

void lex_throw(const char *msg)
{
    if (msg) {
        io_print_srcerr(lex_line_no, lex_char_no, "lexer error: %s", msg);
        exit(1);
    } else abort();
}
