#ifndef LEX_MATCH_LITERALS_CH
#define LEX_MATCH_LITERALS_CH

LexToken lex_match_literals(FILE *f, char ch)
{
    if (ch == '\'') {
        lex_buffreset();
        do {
            ch = getc(f);
            if (ch == '\\') {
                lex_buffpush(getc(f));
                continue;
            }
            if (ch == '\'') break;
            if (ch == (char) EOF) lex_throw("unexpected end of file");
            lex_buffpush(ch);
        } while (true);
        return LEX_CHAR_LITERAL;
    } else if (ch == '"') {
        lex_buffreset();
        do {
            ch = getc(f);
            if (ch == '\\') {
                lex_buffpush(getc(f));
                continue;
            }
            if (ch == '"') break;
            if (ch == (char) EOF) lex_throw("unexpected end of file");
            lex_buffpush(ch);
        } while (true);
        return LEX_STR_LITERAL;
    } else if (isdigit(ch) || ch == '+' || ch == '-') {
        bool neg = false;
        if (ch == '+' || ch == '-') {
            if (ch == '-') neg = true;
            ch = lex_getc(f);
            if (!isdigit(ch)) {
                lex_ungetc(&ch, f);
                return LEX_INVALID;
            } else lex_ungetc(&ch, f);
        }
        bool isfloat = false;
        do {
            ch = lex_getc(f);
            if (ch == '.' && !isfloat) {
                isfloat = true;
                ch = lex_getc(f);
            } else if (ch == '.' && isfloat) {
                lex_ungetc(&ch, f);
                return LEX_FLOAT_LITERAL;
            }
        } while (isdigit(ch));
        lex_ungetc(&ch, f);
        if (isfloat) return LEX_FLOAT_LITERAL;
        else return LEX_INT_LITERAL;
    }
    return LEX_INVALID;
}

#endif
