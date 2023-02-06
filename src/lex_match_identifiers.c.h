#ifndef LEX_MATCH_IDENTIFIERS_CH
#define LEX_MATCH_IDENTIFIERS_CH

LexToken lex_match_identifiers(FILE *f, char ch)
{
    if (!isalpha(ch) && ch != '_') return LEXTOK_INVALID;
    while (true) {
        ch = lex_getc(f);
        if (!lex_isalmun_undr(ch)) {
            // unget last non identifier char
            lex_ungetc(&ch, f);
            break;
        }
    }
    return LEXTOK_IDENTIFIER;
}

#endif
