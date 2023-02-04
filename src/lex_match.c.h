#ifndef LEX_MATCH_CH
#define LEX_MATCH_CH

LexToken lex_match(FILE *f)
{
    lex_buffreset();
    char ch = lex_getc(f);
    while (lex_is_delimiter(ch)) ch = lex_getc(f);
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
        case '%': return LEX_PERCENT;
        case '&': {
            char ch = lex_getc(f);
            switch (ch) {
                case '&': return LEX_LOGICAL_AND;
                case '=': return LEX_INVALID;
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
                    switch (ch) {
                        case '=': return LEX_INVALID;
                        default: lex_ungetc(ch, f);
                    }
                    return LEX_EXPONENT;
                }
                case '=': return LEX_INVALID;
                default: lex_ungetc(ch, f);
            }
            return LEX_ASTERIX;
        }
        case '+': {
            char ch = lex_getc(f);
            switch (ch) {
                case '+': return LEX_INCREMENT;
                case '=': return LEX_INVALID;
                default: lex_ungetc(ch, f);
            }
            return LEX_PLUS;
        }
        case ',': return LEX_COMMA;
        case '-': {
            char ch = lex_getc(f);
            switch (ch) {
                case '-': return LEX_DECREMENT;
                case '=': return LEX_INVALID;
                default: lex_ungetc(ch, f);
            }
            return LEX_MINUS;
        }
        case '.': return LEX_DOT;
        case '/': {
            char ch = lex_getc(f);
            switch (ch) {
                case '/': return LEX_INVALID;
                case '=': return LEX_INVALID;
                default: lex_ungetc(ch, f);
            }
            return LEX_FSLASH;
        }
        case ':': {
            return LEX_INVALID;
        }
        case ';': return LEX_SEMICOLON;
        case '<': {
            char ch = lex_getc(f);
            switch (ch) {
                case '<': return LEX_BITWISE_LSHIFT;
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
                case '>': return LEX_BITWISE_RSHIFT;
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
                case '=': return LEX_INVALID;
                default: lex_ungetc(ch, f);
            }
            return LEX_CARET;
        }
        case '`': return LEX_BACKTICK;
        case '{': return LEX_LBRACE_CURLY;
        case '|': {
            char ch = lex_getc(f);
            switch (ch) {
                case '|': return LEX_LOGICAL_OR;
                case '>': return LEX_PIPEOUT;
                case '=': return LEX_INVALID;
                default: lex_ungetc(ch, f);
            }
            return LEX_PIPE;
        }
        case '}': return LEX_INVALID;
        case '~': return LEX_TILDE;
        case (char) EOF: return LEX_EOF;
        default: return LEX_INVALID;
    }
    return LEX_INVALID;
}

#endif
