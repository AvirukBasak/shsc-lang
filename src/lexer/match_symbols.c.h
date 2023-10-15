#ifndef LEXER_MATCH_SYMBOLS_C_H
#define LEXER_MATCH_SYMBOLS_C_H

#include "lexer.h"

lex_Token_t lex_match_symbols(FILE *f, char ch)
{
    switch (ch) {
        case '!': {
            char ch = lex_getc(f);
            switch (ch) {
                case '=': {
                    char ch = lex_getc(f);
                    switch (ch) {
                        case '=': return TOKEN_LOGICAL_UNIDENTICAL;
                        default: lex_ungetc(&ch, f);
                    }
                    return TOKEN_LOGICAL_UNEQUAL;
                }
                default: lex_ungetc(&ch, f);
            }
            return TOKEN_BANG;
        }
        case '"': return TOKEN_DQUOTE;
        case '$': return TOKEN_DOLLAR;
        case '%': {
            char ch = lex_getc(f);
            switch (ch) {
                case '=': return TOKEN_MODULO_ASSIGN;
                default: lex_ungetc(&ch, f);
            }
            return TOKEN_PERCENT;
        }
        case '&': {
            char ch = lex_getc(f);
            switch (ch) {
                case '&': {
                    char ch = lex_getc(f);
                    switch (ch) {
                        case '=': return TOKEN_LOGICAL_AND_ASSIGN;
                        default: lex_ungetc(&ch, f);
                    }
                    return TOKEN_LOGICAL_AND;
                }
                case '=': return TOKEN_BITWISE_AND_ASSIGN;
                default: lex_ungetc(&ch, f);
            }
            return TOKEN_AMPERSAND;
        }
        case '\'': return TOKEN_SQUOTE;
        case '(': return TOKEN_LBRACE_PAREN;
        case ')': return TOKEN_RBRACE_PAREN;
        case '*': {
            char ch = lex_getc(f);
            switch (ch) {
                case '*': {
                    char ch = lex_getc(f);
                    switch (ch) {
                        case '=': return TOKEN_EXPONENT_ASSIGN;
                        default: lex_ungetc(&ch, f);
                    }
                    return TOKEN_EXPONENT;
                }
                case '=': return TOKEN_MULTIPLY_ASSIGN;
                default: lex_ungetc(&ch, f);
            }
            return TOKEN_ASTERIX;
        }
        case '+': {
            char ch = lex_getc(f);
            switch (ch) {
                case '+': return TOKEN_INCREMENT;
                case '=': return TOKEN_ADD_ASSIGN;
                default: lex_ungetc(&ch, f);
            }
            return TOKEN_PLUS;
        }
        case ',': return TOKEN_COMMA;
        case '-': {
            char ch = lex_getc(f);
            switch (ch) {
                case '-': return TOKEN_DECREMENT;
                case '=': return TOKEN_SUBSTRACT_ASSIGN;
                case '>': return TOKEN_SARROW;
                default: lex_ungetc(&ch, f);
            }
            return TOKEN_MINUS;
        }
        case '.': {
            char ch = lex_getc(f);
            switch (ch) {
                case '.': {
                    char ch = lex_getc(f);
                    switch (ch) {
                        case '.': return TOKEN_ELIPSIS;
                        default: lex_ungetc(&ch, f);
                    }
                }
                default: lex_ungetc(&ch, f);
            }
            return TOKEN_DOT;
        }
        case '/': {
            char ch = lex_getc(f);
            switch (ch) {
                case '/': {
                    char ch = lex_getc(f);
                    switch (ch) {
                        case '=': return TOKEN_FLOOR_DIVIDE_ASSIGN;
                        default: lex_ungetc(&ch, f);
                    }
                    return TOKEN_FLOOR_DIVIDE;
                }
                case '=': return TOKEN_DIVIDE_ASSIGN;
                default: lex_ungetc(&ch, f);
            }
            return TOKEN_FSLASH;
        }
        case ':': {
            char ch = lex_getc(f);
            switch (ch) {
                case ':': return TOKEN_DCOLON;
                default: lex_ungetc(&ch, f);
            }
            return TOKEN_COLON;
        }
        case ';': return TOKEN_SEMICOLON;
        case '<': {
            char ch = lex_getc(f);
            switch (ch) {
                case '<': {
                    char ch = lex_getc(f);
                    switch (ch) {
                        case '=': return TOKEN_BITWISE_LSHIFT_ASSIGN;
                        default: lex_ungetc(&ch, f);
                    }
                    return TOKEN_BITWISE_LSHIFT;
                }
                case '=': return TOKEN_LOGICAL_LESSER_EQUAL;
                default: lex_ungetc(&ch, f);
            }
            return TOKEN_LBRACE_ANGULAR;
        }
        case '=': {
            char ch = lex_getc(f);
            switch (ch) {
                case '=': {
                    char ch = lex_getc(f);
                    switch (ch) {
                        case '=': return TOKEN_LOGICAL_IDENTICAL;
                        default: lex_ungetc(&ch, f);
                    }
                    return TOKEN_LOGICAL_EQUAL;
                }
                case '>': return TOKEN_DARROW;
                default: lex_ungetc(&ch, f);
            }
            return TOKEN_ASSIGN;
        }
        case '>': {
            char ch = lex_getc(f);
            switch (ch) {
                case '>': {
                    char ch = lex_getc(f);
                    switch (ch) {
                        case '>': {
                            char ch = lex_getc(f);
                            switch (ch) {
                                case '=': return TOKEN_ARITH_RSHIFT_ASSIGN;
                                default: lex_ungetc(&ch, f);
                            }
                            return TOKEN_ARITH_RSHIFT;
                        }
                        case '=': return TOKEN_BITWISE_RSHIFT_ASSIGN;
                        default: lex_ungetc(&ch, f);
                    }
                    return TOKEN_BITWISE_RSHIFT;
                }
                case '=': return TOKEN_LOGICAL_GREATER_EQUAL;
                default: lex_ungetc(&ch, f);
            }
            return TOKEN_RBRACE_ANGULAR;
        }
        case '?': return TOKEN_QUESTION;
        case '@': return TOKEN_AT;
        case '[': return TOKEN_LBRACE_SQUARE;
        case '\\': return TOKEN_BSLASH;
        case ']': return TOKEN_RBRACE_SQUARE;
        case '^': {
            char ch = lex_getc(f);
            switch (ch) {
                case '=': return TOKEN_BITWISE_XOR_ASSIGN;
                default: lex_ungetc(&ch, f);
            }
            return TOKEN_CARET;
        }
        case '`': return TOKEN_BACKTICK;
        case '{': return TOKEN_LBRACE_CURLY;
        case '|': {
            char ch = lex_getc(f);
            switch (ch) {
                case '|': {
                    char ch = lex_getc(f);
                    switch (ch) {
                        case '=': return TOKEN_LOGICAL_OR_ASSIGN;
                        default: lex_ungetc(&ch, f);
                    }
                    return TOKEN_LOGICAL_OR;
                }
                case '=': return TOKEN_BITWISE_OR_ASSIGN;
                case '>': return TOKEN_PIPEOUT;
                default: lex_ungetc(&ch, f);
            }
            return TOKEN_PIPE;
        }
        case '}': return TOKEN_RBRACE_CURLY;
        case '~': return TOKEN_TILDE;
        case (char) EOF: {
            lex_Buffer_free();
            return TOKEN_EOF;
        }
        case '\n': return TOKEN_NEWLINE;
        default: return TOKEN_INVALID;
    }
    return TOKEN_INVALID;
}

#else
    #warning re-inclusion of module 'lexer/match_symbols.c.h'
#endif
