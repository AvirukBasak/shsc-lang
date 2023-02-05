#ifndef LEX_MATCH_KEYWORDS_CH
#define LEX_MATCH_KEYWORDS_CH

LexToken lex_match_keywords(FILE *f, char ch)
{
    if (!isalpha(ch)) return LEX_INVALID;
    // start at 1 as ch is already in buffer
    size_t kwdlen = 1;
    while (true) {
        ch = lex_getc(f);
        if (!isalpha(ch)) {
            // unget last non alpha char
            lex_ungetc(ch, f);
            break;
        }
        kwdlen++;
    }
    if (!strcmp(lex_get_buffstr(), "calc"))  return LEX_KWD_CALC;
    if (!strcmp(lex_get_buffstr(), "end"))   return LEX_KWD_END;
    if (!strcmp(lex_get_buffstr(), "if"))    return LEX_KWD_IF;
    if (!strcmp(lex_get_buffstr(), "start")) return LEX_KWD_START;
    if (!strcmp(lex_get_buffstr(), "while")) return LEX_KWD_WHILE;
    // unget all characters except the first if all matches failed
    while (kwdlen > 1) {
        ch = lex_ungetc(ch, f);
        kwdlen--;
    }
    return LEX_INVALID;
}

#endif
