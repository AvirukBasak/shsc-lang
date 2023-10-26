#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errcodes.h"
#include "io.h"
#include "lexer.h"
#include "parser.h"

lex_Buffer_t *lex_buffer = NULL;
lex_Token_t lex_currtok = TOKEN_INVALID;

int lex_line_no = 1;
int lex_char_no = 1;

lex_Token_t yylex(void)
{
    if (lex_currtok == TOKEN_NEWLINE)
        if (yyin == stdin) printf("%s", ">> ");

    int token = lex_currtok = lex_Token_getnext(yyin);
    switch (token) {
        case TOKEN_IDENTIFIER:
            yylval.identifier_name = strdup(lex_Buffer_getstr());
            break;
        case TOKEN_BOOL_LITERAL:
            yylval.literal_bool = parse_bool(lex_Buffer_getstr());
            break;
        case TOKEN_CHAR_LITERAL:
            yylval.literal_char = parse_char(lex_Buffer_getstr());
            break;
        case TOKEN_STR_LITERAL:
            yylval.literal_str = parse_str(lex_Buffer_getstr());
            break;
        case TOKEN_INTERP_STR_LITERAL:
            yylval.literal_str = parse_interpstr(lex_Buffer_getstr());
            break;
        case TOKEN_BINFLOAT_LITERAL:
            yylval.literal_f64 = parse_float(lex_Buffer_getstr(), 2);
            break;
        case TOKEN_OCTFLOAT_LITERAL:
            yylval.literal_f64 = parse_float(lex_Buffer_getstr(), 8);
            break;
        case TOKEN_DECFLOAT_LITERAL:
            yylval.literal_f64 = parse_float(lex_Buffer_getstr(), 10);
            break;
        case TOKEN_HEXFLOAT_LITERAL:
            yylval.literal_f64 = parse_float(lex_Buffer_getstr(), 16);
            break;
        case TOKEN_BININT_LITERAL:
            yylval.literal_i64 = parse_int(lex_Buffer_getstr(), 2);
            break;
        case TOKEN_OCTINT_LITERAL:
            yylval.literal_i64 = parse_int(lex_Buffer_getstr(), 8);
            break;
        case TOKEN_DECINT_LITERAL:
            yylval.literal_i64 = parse_int(lex_Buffer_getstr(), 10);
            break;
        case TOKEN_HEXINT_LITERAL:
            yylval.literal_i64 = parse_int(lex_Buffer_getstr(), 16);
            break;
        /* using default here coz there's a lot of cases */
        default:
            yylval.tok = token;
            break;
    }
    return token;
}

#include "lexer/buffer.c.h"
#include "lexer/io.c.h"

// the lexer state machine
#include "lexer/match_identifiers.c.h"
#include "lexer/match_keywords.c.h"
#include "lexer/match_literals.c.h"
#include "lexer/match_symbols.c.h"

lex_Token_t lex_Token_getnext(FILE *f)
{
    lex_Buffer_reset();
    char ch = lex_getc(f);
    while (lex_is_delimiter(ch)) ch = lex_getc(f);
    if (ch == '_') return lex_match_identifiers(f, ch);
    if (ch == 'f') {
        char ch = lex_getc(f);
        /* can be a format string literal */
        if (ch == '"') {
            lex_ungetc(&ch, f);
            return lex_match_string(f, ch);
        } else {
            /* can be boolean `false` literal or keyword
               or identifier */
            lex_ungetc(&ch, f);
            lex_Token_t currtok = lex_match_bool(f, ch);
            if (currtok == TOKEN_INVALID) {
                currtok = lex_match_keywords(f, ch);
                if (currtok == TOKEN_INVALID)
                    return lex_match_identifiers(f, ch);
                return currtok;
            }
            return currtok;
        }
    }
    /* can be boolean `true` literal */
    else if (ch == 't') {
        lex_Token_t currtok = lex_match_bool(f, ch);
        /* can be keyword or identifier */
        if (currtok == TOKEN_INVALID) {
            currtok = lex_match_keywords(f, ch);
            if (currtok == TOKEN_INVALID)
                return lex_match_identifiers(f, ch);
            return currtok;
        }
        return currtok;
    }
    /* any other alphanumeric combo is either a
       keyword or identifier */
    else if (isalpha(ch)) {
        lex_Token_t currtok = lex_match_keywords(f, ch);
        if (currtok == TOKEN_INVALID)
            return lex_match_identifiers(f, ch);
        return currtok;
    }
    else if (ch == '\'') return lex_match_char(f, ch);
    else if (ch == '"') return lex_match_string(f, ch);
    else if (isdigit(ch)) return lex_match_numeric(f, ch);
    else if (ch == '.') {
        lex_Token_t currtok = lex_match_numeric(f, ch);
        if (currtok == TOKEN_INVALID)
            return lex_match_symbols(f, ch);
        return currtok;
    }
    else return lex_match_symbols(f, ch);
}

#include "lexer/tokens.c.h"

void lex_throw(const char *msg)
{
    if (!msg) abort();
    int line = lex_line_no;
    /* if (lex_currtok == TOKEN_NEWLINE) --line; */
    io_print_srcerr(line, lex_char_no, "lexing error: after token '%s': %s", lex_Token_getsymbol(lex_currtok), msg);
    exit(ERR_LEXER);
}
