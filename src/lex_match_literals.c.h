#ifndef LEX_MATCH_LITERALS_CH
#define LEX_MATCH_LITERALS_CH

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

LexToken lex_match_number(FILE *f, char ch, LexBase base)
{
    bool (*lex_isdigit)(char) = lex_get_dgitchecker(base);
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
    bool found_point = (ch == '.');
    bool found_exp = false;
    while (true) {
        ch = lex_getc(f);
        if (ch == '.') {
            if (!found_point) {
                found_point = true;
                continue;
            } else {
                lex_ungetc(&ch, f);
                return floattok;
            }
        } else if (ch == 'e') {
            if (!found_exp) {
                found_exp = true;
                continue;
            } else {
                lex_ungetc(&ch, f);
                if (found_point) return floattok;
                else return inttok;
            }
        }
        else if (lex_isdigit(ch)) continue;
        else {
            lex_ungetc(&ch, f);
            if (found_point) return floattok;
            else return inttok;
        }
    }
    return LEXTOK_INVALID;
}

LexToken lex_match_literals(FILE *f, char ch)
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
    if (ch != '+' && ch != '-' && ch != '.' && !isdigit(ch))
        return LEXTOK_INVALID;
    if (ch == '+' || ch == '-') {
        ch = lex_getc(f);
        if (ch != '.' && !isdigit(ch)) {
            lex_ungetc(&ch, f);
            return LEXTOK_INVALID;
        }
    }
    if (ch == '0') {
        ch = lex_getc(f);
        switch (ch) {
            case 'b': return lex_match_number(f, ch, LEXBASE_2);
            case 'x': return lex_match_number(f, ch, LEXBASE_16);
            default: {
                if (isdigit(ch)) return lex_match_number(f, ch, LEXBASE_8);
                else {
                    lex_ungetc(&ch, f);
                    return LEXTOK_DECINT_LITERAL;
                }
            }
        }
    }
    return lex_match_number(f, ch, LEXBASE_10);
}

#endif
