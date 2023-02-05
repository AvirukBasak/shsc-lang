#ifndef LEX_MATCH_IDENTIFIERS_CH
#define LEX_MATCH_IDENTIFIERS_CH

LexToken lex_match_identifiers(FILE *f, char ch)
{
    if (!isalpha(ch) || c != '_') return LEX_INVALID;
    // start at 1 as ch is already in buffer
    size_t idflen = 1;
    while (true) {
        ch = lex_getc(f);
        if (!lex_isalmun_undr(ch)) {
            // unget last non identifier char
            lex_ungetc(ch, f);
            break;
        }
        idflen++;
    }
    return LEX_IDENTIFIER;
}

#endif
