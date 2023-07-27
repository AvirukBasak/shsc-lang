#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errcodes.h"
#include "io.h"
#include "lexer.h"
#include "parser.h"

LexBuffer *lex_buffer = NULL;
LexToken lex_currtok = LEXTOK_INVALID;

int lex_line_no = 1;
int lex_char_no = 1;

LexToken yylex(void)
{
    int token = lex_currtok = lex_get_nexttok(yyin);
    switch (token) {
        case LEXTOK_IDENTIFIER:
            yylval.identifier_name = strdup(lex_get_buffstr());
            break;
        case LEXTOK_BOOL_LITERAL:
            yylval.literal_bool = parse_bool(lex_get_buffstr());
            break;
        case LEXTOK_CHAR_LITERAL:
            yylval.literal_char = parse_char(lex_get_buffstr());
            break;
        case LEXTOK_STR_LITERAL:
            yylval.literal_str = parse_str(lex_get_buffstr());
            break;
        case LEXTOK_INTERP_STR_LITERAL:
            yylval.literal_str = parse_interpstr(lex_get_buffstr());
            break;
        case LEXTOK_BINFLOAT_LITERAL:
            yylval.literal_f64 = parse_float(lex_get_buffstr(), 2);
            break;
        case LEXTOK_OCTFLOAT_LITERAL:
            yylval.literal_f64 = parse_float(lex_get_buffstr(), 8);
            break;
        case LEXTOK_DECFLOAT_LITERAL:
            yylval.literal_f64 = parse_float(lex_get_buffstr(), 10);
            break;
        case LEXTOK_HEXFLOAT_LITERAL:
            yylval.literal_f64 = parse_float(lex_get_buffstr(), 16);
            break;
        case LEXTOK_BININT_LITERAL:
            yylval.literal_i64 = parse_int(lex_get_buffstr(), 2);
            break;
        case LEXTOK_OCTINT_LITERAL:
            yylval.literal_i64 = parse_int(lex_get_buffstr(), 8);
            break;
        case LEXTOK_DECINT_LITERAL:
            yylval.literal_i64 = parse_int(lex_get_buffstr(), 10);
            break;
        case LEXTOK_HEXINT_LITERAL:
            yylval.literal_i64 = parse_int(lex_get_buffstr(), 16);
            break;
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

LexToken lex_get_nexttok(FILE *f)
{
    lex_buffreset();
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
            LexToken currtok = lex_match_bool(f, ch);
            if (currtok == LEXTOK_INVALID) {
                currtok = lex_match_keywords(f, ch);
                if (currtok == LEXTOK_INVALID)
                    return lex_match_identifiers(f, ch);
                return currtok;
            }
            return currtok;
        }
    }
    /* can be boolean `true` literal */
    else if (ch == 't') {
        LexToken currtok = lex_match_bool(f, ch);
        /* can be keyword or identifier */
        if (currtok == LEXTOK_INVALID) {
            currtok = lex_match_keywords(f, ch);
            if (currtok == LEXTOK_INVALID)
                return lex_match_identifiers(f, ch);
            return currtok;
        }
        return currtok;
    }
    /* any other alphanumeric combo is either a
       keyword or identifier */
    else if (isalpha(ch)) {
        LexToken currtok = lex_match_keywords(f, ch);
        if (currtok == LEXTOK_INVALID)
            return lex_match_identifiers(f, ch);
        return currtok;
    }
    else if (ch == '\'') return lex_match_char(f, ch);
    else if (ch == '"') return lex_match_string(f, ch);
    else if (isdigit(ch)) return lex_match_numeric(f, ch);
    else if (ch == '.') {
        LexToken currtok = lex_match_numeric(f, ch);
        if (currtok == LEXTOK_INVALID)
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
    /* if (lex_currtok == LEXTOK_NEWLINE) --line; */
    io_print_srcerr(line, lex_char_no, "lexing error: after token '%s': %s", lex_get_symbol(lex_currtok), msg);
    exit(ERR_LEXER);
}
