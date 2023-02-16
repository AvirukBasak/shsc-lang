#ifndef LEX_MATCH_LITERALS_CH
#define LEX_MATCH_LITERALS_CH

LexToken lex_match_char(FILE *f, char ch)
{
    if (ch == '\'') {
        // pop out quote symbol
        lex_buffpop();
        do {
            // can't use lex_getc as it doesn't buffer delimiters
            ch = getc(f);
            if (ch == '\\') {
                lex_buffpush(getc(f));
                continue;
            }
            if (ch == '\'') break;
            if (ch == (char) EOF) lex_throw("unexpected end of file");
            lex_buffpush(ch);
        } while (true);
        return LEXTOK_CHAR_LITERAL;
    }
    return LEXTOK_INVALID;
}

LexToken lex_match_string(FILE *f, char ch)
{
    if (ch == '"') {
        // pop out quote symbol
        lex_buffpop();
        do {
            // can't use lex_getc as it doesn't buffer delimiters
            ch = getc(f);
            if (ch == '\\') {
                lex_buffpush(getc(f));
                continue;
            }
            if (ch == '"') break;
            if (ch == (char) EOF) lex_throw("unexpected end of file");
            lex_buffpush(ch);
        } while (true);
        return LEXTOK_STR_LITERAL;
    }
    else if (ch == '`') {
        // pop out backtick symbol
        lex_buffpop();
        do {
            // can't use lex_getc as it doesn't buffer delimiters
            ch = getc(f);
            if (ch == '\\') {
                lex_buffpush(getc(f));
                continue;
            }
            if (ch == '`') break;
            if (ch == (char) EOF) lex_throw("unexpected end of file");
            lex_buffpush(ch);
        } while (true);
        return LEXTOK_INTERP_STR_LITERAL;
    }
    return LEXTOK_INVALID;
}

typedef enum {
    LEXBASE_2  =  2,
    LEXBASE_8  =  8,
    LEXBASE_10 = 10,
    LEXBASE_16 = 16,
} LexBase;

bool lex_isbindigit(char c) {
    return c >= '0' && c <= '1';
}

bool lex_isoctdigit(char c) {
    return c >= '0' && c <= '7';
}

bool lex_isdecdigit(char c) {
    return c >= '0' && c <= '9';
}

bool lex_ishexdigit(char c) {
    return (c >= '0' && c <= '9')
        || (c >= 'a' && c <= 'f')
        || (c >= 'A' && c <= 'F');
}

typedef bool (*lex_digitchecker_ft)(char);
lex_digitchecker_ft lex_get_dgitchecker(LexBase base)
{
    switch (base) {
        case LEXBASE_2: return lex_isbindigit;
        case LEXBASE_8: return lex_isoctdigit;
        case LEXBASE_16: return lex_ishexdigit;
        default: return lex_isdecdigit;
    }
}

char lex_match_digits(FILE* f, char ch, LexBase base)
{
    // get digit checker based on base
    lex_digitchecker_ft lex_isdigit = lex_get_dgitchecker(base);
    // convert lower case hex digits to uppercase
    if (lex_isdigit(ch) && ch >= 'a' && ch <= 'f') {
        lex_buffpush(lex_buffpop() - ('a' - 'A'));
    }
    // match [a-fA-F0-9_]+
    while (lex_isdigit(ch)) {
        ch = lex_getc(f);
        // convert lower case hex digits to uppercase
        if (lex_isdigit(ch) && ch >= 'a' && ch <= 'f') {
            lex_buffpush(lex_buffpop() - ('a' - 'A'));
        }
        // if _ consume it but don't buffer it
        if (ch == '_') {
            lex_buffpop();
            ch = lex_getc(f);
        }
    }
    return ch;
}

LexToken lex_match_unum(FILE *f, char ch, LexBase base)
{
    // get digit checker based on base
    lex_digitchecker_ft lex_isdigit = lex_get_dgitchecker(base);
    // get token type based on base
    LexToken inttok, floattok;
    switch (base) {
        case LEXBASE_2:
            inttok = LEXTOK_BININT_LITERAL;
            floattok = LEXTOK_BINFLOAT_LITERAL;
            break;
        case LEXBASE_8:
            inttok = LEXTOK_OCTINT_LITERAL;
            floattok = LEXTOK_OCTFLOAT_LITERAL;
            break;
        case LEXBASE_16:
            inttok = LEXTOK_HEXINT_LITERAL;
            floattok = LEXTOK_HEXFLOAT_LITERAL;
            break;
        default:
            inttok = LEXTOK_DECINT_LITERAL;
            floattok = LEXTOK_DECFLOAT_LITERAL;
            break;
    }
    LexToken retok = LEXTOK_INVALID;
    // match \d+
    if (!lex_isdigit(ch)) return LEXTOK_INVALID;
    ch = lex_match_digits(f, ch, base);
    // integer matched
    retok = inttok;
    // match (\.\d+){0:1}
    if (ch == '.') {
        ch = lex_getc(f);
        if (!lex_isdigit(ch)) {
            lex_ungetc(&ch, f);    // unget ch
            lex_ungetc(&ch, f);    // unget '.'
            return retok;
        }
        ch = lex_match_digits(f, ch, base);
        // float matched
        retok = floattok;
    }
    // match ([ep][+-]\d+){0:1}
    if ((base != LEXBASE_16 && ch == 'e') || ch == 'p') {
        // pop 'p' and push 'e', convert p to e
        lex_buffpop();
        lex_buffpush('e');
        // next char
        ch = lex_getc(f);
        // consume + or - symbol
        if (ch == '+' || ch == '-') {
            ch = lex_getc(f);
            if (!lex_isdigit(ch)) {
                lex_ungetc(&ch, f);    // unget ch
                lex_ungetc(&ch, f);    // unget '+' or '-'
                lex_ungetc(&ch, f);    // unget 'e' or 'p'
                return retok;
            }
        }
        if (!lex_isdigit(ch)) {
            lex_ungetc(&ch, f);    // unget ch
            lex_ungetc(&ch, f);    // unget 'e' or 'p'
            return retok;
        }
        ch = lex_match_digits(f, ch, base);
    }
    // if last matches failed unget last char
    lex_ungetc(&ch, f);
    return retok;
}

LexToken lex_match_numeric(FILE *f, char ch)
{
    // if starts with a 0
    if (ch == '0') {
        ch = lex_getc(f);
        switch (ch) {
            case 'b': {
                // pop "0b"
                lex_buffpop();
                lex_buffpop();
                ch = lex_getc(f);
                return lex_match_unum(f, ch, LEXBASE_2);
            }
            case 'x': {
                // pop "0x"
                lex_buffpop();
                lex_buffpop();
                ch = lex_getc(f);
                return lex_match_unum(f, ch, LEXBASE_16);
            }
            default: {
                // for values like 023... and 00.12... and many others
                if (isdigit(ch)) {
                    lex_ungetc(&ch, f);  // unget curr char
                    lex_buffpop();       // pop leading '0' from buffer
                    ch = lex_getc(f);    // after '0'
                    return lex_match_unum(f, ch, LEXBASE_8);
                }
                // for numbers like 0.12... or 0_34, or just 0
                else if (ch == '.' || ch == '_') {
                    // unget leading 0
                    lex_ungetc(&ch, f);
                    return lex_match_unum(f, ch, LEXBASE_10);
                }
                else {
                    // unget ch and return int literal for '0'
                    lex_ungetc(&ch, f);
                    return LEXTOK_DECINT_LITERAL;
                }
            }
        }
    }
    // starts with any other number
    else if (isdigit(ch))
        return lex_match_unum(f, ch, LEXBASE_10);
    // starts with '.'
    else if (ch == '.') {
        lex_ungetc(&ch, f);      // unget '.'
        lex_buffpush(ch = '0');  // push a '0'
        return lex_match_unum(f, ch, LEXBASE_10);
    }
    else return LEXTOK_INVALID;
}

#endif
