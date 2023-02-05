#ifndef LEX_MATCH_SYMBOLS_CH
#define LEX_MATCH_SYMBOLS_CH

LexToken lex_match_symbols(FILE *f, char ch)
{
    switch (ch) {
        case '!': {
            char ch = lex_getc(f);
            switch (ch) {
                case '=': {
                    char ch = lex_getc(f);
                    switch (ch) {
                        case '=': return LEX_LOGICAL_UNIDENTICAL;
                        default: lex_ungetc(ch, f);
                    }
                    return LEX_LOGICAL_UNEQUAL;
                }
                default: lex_ungetc(ch, f);
            }
            return LEX_BANG;
        }
        case '"': return LEX_DQUOTE;
        case '$': return LEX_DOLLAR;
        case '%': {
            char ch = lex_getc(f);
            switch (ch) {
                case '=': return LEX_MODULO_ASSIGN;
                default: lex_ungetc(ch, f);
            }
            return LEX_PERCENT;
        }
        case '&': {
            char ch = lex_getc(f);
            switch (ch) {
                case '&': {
                    char ch = lex_getc(f);
                    switch (ch) {
                        case '=': return LEX_LOGICAL_AND_ASSIGN;
                        default: lex_ungetc(ch, f);
                    }
                    return LEX_LOGICAL_AND;
                }
                case '=': return LEX_BITWISE_AND_ASSIGN;
                default: lex_ungetc(ch, f);
            }
            return LEX_AMPERSAND;
        }
        case '\'': return LEX_SQUOTE;
        case '(': return LEX_LBRACE_PAREN;
        case ')': return LEX_RBRACE_PAREN;
        case '*': {
            char ch = lex_getc(f);
            switch (ch) {
                case '*': {
                    char ch = lex_getc(f);
                    switch (ch) {
                        case '=': return LEX_EXPONENT_ASSIGN;
                        default: lex_ungetc(ch, f);
                    }
                    return LEX_EXPONENT;
                }
                case '=': return LEX_MULTIPLY_ASSIGN;
                default: lex_ungetc(ch, f);
            }
            return LEX_ASTERIX;
        }
        case '+': {
            char ch = lex_getc(f);
            switch (ch) {
                case '+': return LEX_INCREMENT;
                case '=': return LEX_ADD_ASSIGN;
                default: lex_ungetc(ch, f);
            }
            return LEX_PLUS;
        }
        case ',': return LEX_COMMA;
        case '-': {
            char ch = lex_getc(f);
            switch (ch) {
                case '-': return LEX_DECREMENT;
                case '=': return LEX_SUBSTRACT_ASSIGN;
                case '>': return LEX_SARROW;
                default: lex_ungetc(ch, f);
            }
            return LEX_MINUS;
        }
        case '.': {
            char ch = lex_getc(f);
            switch (ch) {
                case '.': {
                    char ch = lex_getc(f);
                    switch (ch) {
                        case '.': return LEX_ELIPSIS;
                        default: lex_ungetc(ch, f);
                    }
                }
                default: lex_ungetc(ch, f);
            }
            return LEX_DOT;
        }
        case '/': {
            char ch = lex_getc(f);
            switch (ch) {
                case '/': {
                    char ch = lex_getc(f);
                    switch (ch) {
                        case '=': return LEX_FLOOR_DIVIDE_ASSIGN;
                        default: lex_ungetc(ch, f);
                    }
                    return LEX_FLOOR_DIVIDE;
                }
                case '=': return LEX_DIVIDE_ASSIGN;
                default: lex_ungetc(ch, f);
            }
            return LEX_FSLASH;
        }
        case ':': {
            char ch = lex_getc(f);
            switch (ch) {
                case ':': return LEX_DCOLON;
                default: lex_ungetc(ch, f);
            }
            return LEX_COLON;
        }
        case ';': return LEX_SEMICOLON;
        case '<': {
            char ch = lex_getc(f);
            switch (ch) {
                case '<': {
                    char ch = lex_getc(f);
                    switch (ch) {
                        case '=': return LEX_BITWISE_LSHIFT_ASSIGN;
                        default: lex_ungetc(ch, f);
                    }
                    return LEX_BITWISE_LSHIFT;
                }
                case '=': return LEX_LOGICAL_LESSER_EQUAL;
                default: lex_ungetc(ch, f);
            }
            return LEX_LBRACE_ANGULAR;
        }
        case '=': {
            char ch = lex_getc(f);
            switch (ch) {
                case '=': {
                    char ch = lex_getc(f);
                    switch (ch) {
                        case '=': return LEX_LOGICAL_IDENTICAL;
                        default: lex_ungetc(ch, f);
                    }
                    return LEX_LOGICAL_EQUAL;
                }
                case '>': return LEX_DARROW;
                default: lex_ungetc(ch, f);
            }
            return LEX_ASSIGN;
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
                                case '=': return LEX_ARITH_RSHIFT_ASSIGN;
                                default: lex_ungetc(ch, f);
                            }
                            return LEX_ARITH_RSHIFT;
                        }
                        case '=': return LEX_BITWISE_RSHIFT_ASSIGN;
                        default: lex_ungetc(ch, f);
                    }
                    return LEX_BITWISE_RSHIFT;
                }
                case '=': return LEX_LOGICAL_GREATER_EQUAL;
                default: lex_ungetc(ch, f);
            }
            return LEX_RBRACE_ANGULAR;
        }
        case '?': return LEX_QUESTION;
        case '@': return LEX_AT;
        case '[': return LEX_LBRACE_SQUARE;
        case '\\': return LEX_BSLASH;
        case ']': return LEX_RBRACE_SQUARE;
        case '^': {
            char ch = lex_getc(f);
            switch (ch) {
                case '=': return LEX_BITWISE_XOR_ASSIGN;
                default: lex_ungetc(ch, f);
            }
            return LEX_CARET;
        }
        case '`': return LEX_BACKTICK;
        case '{': return LEX_LBRACE_CURLY;
        case '|': {
            char ch = lex_getc(f);
            switch (ch) {
                case '|': {
                    char ch = lex_getc(f);
                    switch (ch) {
                        case '=': return LEX_LOGICAL_OR_ASSIGN;
                        default: lex_ungetc(ch, f);
                    }
                    return LEX_LOGICAL_OR;
                }
                case '=': return LEX_BITWISE_OR_ASSIGN;
                case '>': return LEX_PIPEOUT;
                default: lex_ungetc(ch, f);
            }
            return LEX_PIPE;
        }
        case '}': return LEX_RBRACE_CURLY;
        case '~': return LEX_TILDE;
        case (char) EOF: return LEX_EOF;
        default: return LEX_INVALID;
    }
    return LEX_INVALID;
}

#endif
