#ifndef LEX_MATCH_SYMBOLS_CH
#define LEX_MATCH_SYMBOLS_CH

#include "lexer.h"

LexToken lex_match_symbols(FILE *f, char ch)
{
    switch (ch) {
        case '!': {
            char ch = lex_getc(f);
            switch (ch) {
                case '=': {
                    char ch = lex_getc(f);
                    switch (ch) {
                        case '=': return LEXTOK_LOGICAL_UNIDENTICAL;
                        default: lex_ungetc(&ch, f);
                    }
                    return LEXTOK_LOGICAL_UNEQUAL;
                }
                default: lex_ungetc(&ch, f);
            }
            return LEXTOK_BANG;
        }
        case '"': return LEXTOK_DQUOTE;
        case '$': return LEXTOK_DOLLAR;
        case '%': {
            char ch = lex_getc(f);
            switch (ch) {
                case '=': return LEXTOK_MODULO_ASSIGN;
                default: lex_ungetc(&ch, f);
            }
            return LEXTOK_PERCENT;
        }
        case '&': {
            char ch = lex_getc(f);
            switch (ch) {
                case '&': {
                    char ch = lex_getc(f);
                    switch (ch) {
                        case '=': return LEXTOK_LOGICAL_AND_ASSIGN;
                        default: lex_ungetc(&ch, f);
                    }
                    return LEXTOK_LOGICAL_AND;
                }
                case '=': return LEXTOK_BITWISE_AND_ASSIGN;
                default: lex_ungetc(&ch, f);
            }
            return LEXTOK_AMPERSAND;
        }
        case '\'': return LEXTOK_SQUOTE;
        case '(': return LEXTOK_LBRACE_PAREN;
        case ')': return LEXTOK_RBRACE_PAREN;
        case '*': {
            char ch = lex_getc(f);
            switch (ch) {
                case '*': {
                    char ch = lex_getc(f);
                    switch (ch) {
                        case '=': return LEXTOK_EXPONENT_ASSIGN;
                        default: lex_ungetc(&ch, f);
                    }
                    return LEXTOK_EXPONENT;
                }
                case '=': return LEXTOK_MULTIPLY_ASSIGN;
                default: lex_ungetc(&ch, f);
            }
            return LEXTOK_ASTERIX;
        }
        case '+': {
            char ch = lex_getc(f);
            switch (ch) {
                case '+': return LEXTOK_INCREMENT;
                case '=': return LEXTOK_ADD_ASSIGN;
                default: lex_ungetc(&ch, f);
            }
            return LEXTOK_PLUS;
        }
        case ',': return LEXTOK_COMMA;
        case '-': {
            char ch = lex_getc(f);
            switch (ch) {
                case '-': return LEXTOK_DECREMENT;
                case '=': return LEXTOK_SUBSTRACT_ASSIGN;
                case '>': return LEXTOK_SARROW;
                default: lex_ungetc(&ch, f);
            }
            return LEXTOK_MINUS;
        }
        case '.': {
            char ch = lex_getc(f);
            switch (ch) {
                case '.': {
                    char ch = lex_getc(f);
                    switch (ch) {
                        case '.': return LEXTOK_ELIPSIS;
                        default: lex_ungetc(&ch, f);
                    }
                }
                default: lex_ungetc(&ch, f);
            }
            return LEXTOK_DOT;
        }
        case '/': {
            char ch = lex_getc(f);
            switch (ch) {
                case '/': {
                    char ch = lex_getc(f);
                    switch (ch) {
                        case '=': return LEXTOK_FLOOR_DIVIDE_ASSIGN;
                        default: lex_ungetc(&ch, f);
                    }
                    return LEXTOK_FLOOR_DIVIDE;
                }
                case '=': return LEXTOK_DIVIDE_ASSIGN;
                default: lex_ungetc(&ch, f);
            }
            return LEXTOK_FSLASH;
        }
        case ':': {
            char ch = lex_getc(f);
            switch (ch) {
                case ':': return LEXTOK_DCOLON;
                default: lex_ungetc(&ch, f);
            }
            return LEXTOK_COLON;
        }
        case ';': return LEXTOK_SEMICOLON;
        case '<': {
            char ch = lex_getc(f);
            switch (ch) {
                case '<': {
                    char ch = lex_getc(f);
                    switch (ch) {
                        case '=': return LEXTOK_BITWISE_LSHIFT_ASSIGN;
                        default: lex_ungetc(&ch, f);
                    }
                    return LEXTOK_BITWISE_LSHIFT;
                }
                case '=': return LEXTOK_LOGICAL_LESSER_EQUAL;
                default: lex_ungetc(&ch, f);
            }
            return LEXTOK_LBRACE_ANGULAR;
        }
        case '=': {
            char ch = lex_getc(f);
            switch (ch) {
                case '=': {
                    char ch = lex_getc(f);
                    switch (ch) {
                        case '=': return LEXTOK_LOGICAL_IDENTICAL;
                        default: lex_ungetc(&ch, f);
                    }
                    return LEXTOK_LOGICAL_EQUAL;
                }
                case '>': return LEXTOK_DARROW;
                default: lex_ungetc(&ch, f);
            }
            return LEXTOK_ASSIGN;
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
                                case '=': return LEXTOK_ARITH_RSHIFT_ASSIGN;
                                default: lex_ungetc(&ch, f);
                            }
                            return LEXTOK_ARITH_RSHIFT;
                        }
                        case '=': return LEXTOK_BITWISE_RSHIFT_ASSIGN;
                        default: lex_ungetc(&ch, f);
                    }
                    return LEXTOK_BITWISE_RSHIFT;
                }
                case '=': return LEXTOK_LOGICAL_GREATER_EQUAL;
                default: lex_ungetc(&ch, f);
            }
            return LEXTOK_RBRACE_ANGULAR;
        }
        case '?': return LEXTOK_QUESTION;
        case '@': return LEXTOK_AT;
        case '[': return LEXTOK_LBRACE_SQUARE;
        case '\\': return LEXTOK_BSLASH;
        case ']': return LEXTOK_RBRACE_SQUARE;
        case '^': {
            char ch = lex_getc(f);
            switch (ch) {
                case '=': return LEXTOK_BITWISE_XOR_ASSIGN;
                default: lex_ungetc(&ch, f);
            }
            return LEXTOK_CARET;
        }
        case '`': return LEXTOK_BACKTICK;
        case '{': return LEXTOK_LBRACE_CURLY;
        case '|': {
            char ch = lex_getc(f);
            switch (ch) {
                case '|': {
                    char ch = lex_getc(f);
                    switch (ch) {
                        case '=': return LEXTOK_LOGICAL_OR_ASSIGN;
                        default: lex_ungetc(&ch, f);
                    }
                    return LEXTOK_LOGICAL_OR;
                }
                case '=': return LEXTOK_BITWISE_OR_ASSIGN;
                case '>': return LEXTOK_PIPEOUT;
                default: lex_ungetc(&ch, f);
            }
            return LEXTOK_PIPE;
        }
        case '}': return LEXTOK_RBRACE_CURLY;
        case '~': return LEXTOK_TILDE;
        case (char) EOF: {
            lex_buffree();
            return LEXTOK_EOF;
        }
        default: return LEXTOK_INVALID;
    }
    return LEXTOK_INVALID;
}

#endif
