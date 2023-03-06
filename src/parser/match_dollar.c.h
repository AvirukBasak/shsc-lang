#ifndef PARSE_DOLLAR_CH
#define PARSE_DOLLAR_CH

#include <stdio.h>
#include "lexer.h"

void parse_dollar(FILE *f, LexToken tok)
{
    switch (tok) {
        case LEXTOK_DOLLAR: {
            tok = lex_get_nexttok(f);
            switch (tok) {
                case LEXTOK_IDENTIFIER: {
                    tok = lex_get_nexttok(f);
                    const char* const idf = strdup(lex_get_buffstr());
                    switch (tok) {
                        case LEXTOK_ASSIGN: {
                            tok = lex_get_nexttok(f);
                            switch (tok) {
                                case LEXTOK_CHAR_LITERAL: {
                                    char data = parse_charlit(lex_get_buffstr());
                                    vartable_insert(idf, vartable_newdata(VarTable.CHAR, data));
                                    break;
                                }
                                case LEXTOK_BININT_LITERAL: {
                                    int64_t data = parse_binintlit(lex_get_buffstr());
                                    vartable_insert(idf, vartable_newdata(VarTable.INT64, data));
                                    break;
                                }
                                case LEXTOK_OCTINT_LITERAL: {
                                    int64_t data = parse_octintlit(lex_get_buffstr());
                                    vartable_insert(idf, vartable_newdata(VarTable.INT64, data));
                                    break;
                                }
                                case LEXTOK_DECINT_LITERAL: {
                                    int64_t data = parse_decintlit(lex_get_buffstr());
                                    vartable_insert(idf, vartable_newdata(VarTable.INT64, data));
                                    break;
                                }
                                case LEXTOK_HEXINT_LITERAL: {
                                    int64_t data = parse_hexintlit(lex_get_buffstr());
                                    vartable_insert(idf, vartable_newdata(VarTable.INT64, data));
                                    break;
                                }
                                case LEXTOK_BINFLOAT_LITERAL: {
                                    double data = parse_binfloatlit(lex_get_buffstr());
                                    vartable_insert(idf, vartable_newdata(VarTable.FLOAT64, data));
                                    break;
                                }
                                case LEXTOK_OCTFLOAT_LITERAL: {
                                    double data = parse_octfloatlit(lex_get_buffstr());
                                    vartable_insert(idf, vartable_newdata(VarTable.FLOAT64, data));
                                    break;
                                }
                                case LEXTOK_DECFLOAT_LITERAL: {
                                    double data = parse_decfloatlit(lex_get_buffstr());
                                    vartable_insert(idf, vartable_newdata(VarTable.FLOAT64, data));
                                    break;
                                }
                                case LEXTOK_HEXFLOAT_LITERAL: {
                                    double data = parse_hexfloatlit(lex_get_buffstr());
                                    vartable_insert(idf, vartable_newdata(VarTable.FLOAT64, data));
                                    break;
                                }
                                case LEXTOK_STR_LITERAL: {
                                    const char* const data = parse_strlit(lex_get_buffstr());
                                    vartable_insert(idf, vartable_newdata(VarTable.STRING, data));
                                    break;
                                }
                                case LEXTOK_INTERP_STR_LITERAL: {
                                    const char* const data = parse_interpstrlit(lex_get_buffstr());
                                    vartable_insert(idf, vartable_newdata(VarTable.STRING, data));
                                    break;
                                }
                                case LEXTOK_IDENTIFIER: {
                                    const char* const idf2 = lex_get_buffstr();
                                    /* Copies idf2 over to idf, frees all recourse held by idf
                                     * this means, even if idf2 holds a seperate object, it'll be cloned
                                     * and idf gets its own copy
                                     * Changes to idf will not be reflected in idf2 and vice-versa
                                     * regardless of datatype
                                     */
                                    if (vartable_clone(idf, idf2)) break;
                                    char* err_ = "no such identifier: '";
                                    char* errmsg = malloc(strlen(err_) + strlen(idf2) + 2);
                                    strcat(errmsg, err_);
                                    strcat(errmsg, idf2);
                                    strcat(errmsg, "'");
                                    parse_throw(errmsg);
                                    free(errmsg);
                                    break;
                                }
                                case LEXTOK_KWD_CALC: {
                                    const char** const arglist = parse_mkarglist(f);
                                    CalcResult res = func_calc(arglist);
                                    switch (res.type) {
                                        case CHAR:
                                            vartable_insert(idf, vartable_newdata(VarTable.CHAR, (char) res.data));
                                            break;
                                        case INT64:
                                            vartable_insert(idf, vartable_newdata(VarTable.INT64, (int64_t) res.data));
                                            break;
                                        case FLOAT64:
                                            vartable_insert(idf, vartable_newdata(VarTable.FLOAT64, (double) res.data));
                                            break;
                                        case STRING:
                                            vartable_insert(idf, vartable_newdata(VarTable.STRING, (char*) res.data));
                                            break;
                                        default: parse_throw("calc returned unexpected result type");
                                    }
                                    break;
                                }
                                default: parse_throw("unexpected symbol, expected literal or identifier");
                            }
                        }
                        default: parse_throw("unexpected symbol, expected '='");
                    }
                }
                default: parse_throw("unexpected symbol, expected identifier");
            }
        }
        default: parse_throw("unexpected symbol, expected '$'");
    }
}

#endif
