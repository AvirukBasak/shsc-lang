#ifndef PARSE_DOLLAR_CH
#define PARSE_DOLLAR_CH

#include <stdio.h>

#include "lexer.h"
#include "parser.h"

#include "functions/calc.c.h"

#include "parse.c.h"
#include "vartable.c.h"

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
                                    VarData data; data.chr = (char) parse_charlit(lex_get_buffstr());
                                    vartable_insert(idf, vartable_newdata(VT_CHR, data));
                                    break;
                                }
                                case LEXTOK_BININT_LITERAL: {
                                    VarData data; data.i64 = (int64_t) parse_binintlit(lex_get_buffstr());
                                    vartable_insert(idf, vartable_newdata(VT_I64, data));
                                    break;
                                }
                                case LEXTOK_OCTINT_LITERAL: {
                                    VarData data; data.i64 = (int64_t) parse_octintlit(lex_get_buffstr());
                                    vartable_insert(idf, vartable_newdata(VT_I64, data));
                                    break;
                                }
                                case LEXTOK_DECINT_LITERAL: {
                                    VarData data; data.i64 = (int64_t) parse_decintlit(lex_get_buffstr());
                                    vartable_insert(idf, vartable_newdata(VT_I64, data));
                                    break;
                                }
                                case LEXTOK_HEXINT_LITERAL: {
                                    VarData data; data.i64 = (int64_t) parse_hexintlit(lex_get_buffstr());
                                    vartable_insert(idf, vartable_newdata(VT_I64, data));
                                    break;
                                }
                                case LEXTOK_BINFLOAT_LITERAL: {
                                    VarData data; data.f64 = (double) parse_binfloatlit(lex_get_buffstr());
                                    vartable_insert(idf, vartable_newdata(VT_F64, data));
                                    break;
                                }
                                case LEXTOK_OCTFLOAT_LITERAL: {
                                    VarData data; data.f64 = (double) parse_octfloatlit(lex_get_buffstr());
                                    vartable_insert(idf, vartable_newdata(VT_F64, data));
                                    break;
                                }
                                case LEXTOK_DECFLOAT_LITERAL: {
                                    VarData data; data.f64 = (double) parse_decfloatlit(lex_get_buffstr());
                                    vartable_insert(idf, vartable_newdata(VT_F64, data));
                                    break;
                                }
                                case LEXTOK_HEXFLOAT_LITERAL: {
                                    VarData data; data.f64 = (double) parse_hexfloatlit(lex_get_buffstr());
                                    vartable_insert(idf, vartable_newdata(VT_F64, data));
                                    break;
                                }
                                case LEXTOK_STR_LITERAL: {
                                    VarData data; data.str = (char*) parse_strlit(lex_get_buffstr());
                                    vartable_insert(idf, vartable_newdata(VT_STR, data));
                                    break;
                                }
                                case LEXTOK_INTERP_STR_LITERAL: {
                                    VarData data; data.str = (char*) parse_interpstrlit(lex_get_buffstr());
                                    vartable_insert(idf, vartable_newdata(VT_STR, data));
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
                                    char** arglist = parse_mkarglist(f);
                                    VarEntry res = func_calc(arglist);
                                    switch (res.type) {
                                        case VT_CHR:
                                            vartable_insert(idf, vartable_newdata(VT_CHR, res.data));
                                            break;
                                        case VT_I64:
                                            vartable_insert(idf, vartable_newdata(VT_I64, res.data));
                                            break;
                                        case VT_F64:
                                            vartable_insert(idf, vartable_newdata(VT_F64, res.data));
                                            break;
                                        case VT_STR:
                                            vartable_insert(idf, vartable_newdata(VT_STR, res.data));
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
