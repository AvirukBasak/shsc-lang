#ifndef PARSE_DOLLAR_CH
#define PARSE_DOLLAR_CH

void parse_dollar(FILE *f, LexToken tok)
{
    switch (tok) {
        case LEXTOK_DOLLAR: {
            tok = lex_get_nexttok(f);
            switch (tok) {
                case LEXTOK_IDENTIFIER: {
                    tok = lex_get_nexttok(f);
                    switch (tok) {
                        case LEXTOK_ASSIGN: {
                            tok = lex_get_nexttok(f);
                            switch (tok) {
                                case LEXTOK_CHAR_LITERAL: {
                                    break;
                                }
                                case LEXTOK_BINFLOAT_LITERAL: {
                                    break;
                                }
                                case LEXTOK_OCTFLOAT_LITERAL: {
                                    break;
                                }
                                case LEXTOK_DECFLOAT_LITERAL: {
                                    break;
                                }
                                case LEXTOK_HEXFLOAT_LITERAL: {
                                    break;
                                }
                                case LEXTOK_BININT_LITERAL: {
                                    break;
                                }
                                case LEXTOK_OCTINT_LITERAL: {
                                    break;
                                }
                                case LEXTOK_DECINT_LITERAL: {
                                    break;
                                }
                                case LEXTOK_HEXINT_LITERAL: {
                                    break;
                                }
                                case LEXTOK_STR_LITERAL: {
                                    break;
                                }
                                case LEXTOK_INTERP_STR_LITERAL: {
                                    break;
                                }
                                case LEXTOK_IDENTIFIER: {
                                    break;
                                }
                                case LEXTOK_KWD_CALC: {
                                    break;
                                }
                                default: parser_throw("unexpected symbol, expected literal or identifier");
                            }
                        }
                        default: parser_throw("unexpected symbol, expected '='");
                    }
                }
                default: parser_throw("unexpected symbol, expected identifier");
            }
        }
        default: parser_throw("unexpected symbol, expected '$'");
    }
}

#endif
