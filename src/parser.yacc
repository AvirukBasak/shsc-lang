%{

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "io.h"
#include "lexer.h"

void parse_interpret(FILE *f);
void parse_throw(const char *msg);

int yyerror(const char* s);
int yylex(void);

%}

%token YYTOK_BANG                         LEXTOK_BANG                       "!"
%token YYTOK_LOGICAL_UNEQUAL              LEXTOK_LOGICAL_UNEQUAL            "!="
%token YYTOK_LOGICAL_UNIDENTICAL          LEXTOK_LOGICAL_UNIDENTICAL        "!=="
%token YYTOK_DQUOTE                       LEXTOK_DQUOTE                     "\""
%token YYTOK_DOLLAR                       LEXTOK_DOLLAR                     "$"
%token YYTOK_PERCENT                      LEXTOK_PERCENT                    "%"
%token YYTOK_MODULO_ASSIGN                LEXTOK_MODULO_ASSIGN              "%="
%token YYTOK_AMPERSAND                    LEXTOK_AMPERSAND                  "&"
%token YYTOK_LOGICAL_AND                  LEXTOK_LOGICAL_AND                "&&"
%token YYTOK_LOGICAL_AND_ASSIGN           LEXTOK_LOGICAL_AND_ASSIGN         "&&="
%token YYTOK_BITWISE_AND_ASSIGN           LEXTOK_BITWISE_AND_ASSIGN         "&="
%token YYTOK_SQUOTE                       LEXTOK_SQUOTE                     "'"
%token YYTOK_LBRACE_PAREN                 LEXTOK_LBRACE_PAREN               "("
%token YYTOK_RBRACE_PAREN                 LEXTOK_RBRACE_PAREN               ")"
%token YYTOK_ASTERIX                      LEXTOK_ASTERIX                    "*"
%token YYTOK_EXPONENT                     LEXTOK_EXPONENT                   "**"
%token YYTOK_EXPONENT_ASSIGN              LEXTOK_EXPONENT_ASSIGN            "**="
%token YYTOK_MULTIPLY_ASSIGN              LEXTOK_MULTIPLY_ASSIGN            "*="
%token YYTOK_PLUS                         LEXTOK_PLUS                       "+"
%token YYTOK_INCREMENT                    LEXTOK_INCREMENT                  "++"
%token YYTOK_ADD_ASSIGN                   LEXTOK_ADD_ASSIGN                 "+="
%token YYTOK_COMMA                        LEXTOK_COMMA                      ""
%token YYTOK_MINUS                        LEXTOK_MINUS                      "-"
%token YYTOK_DECREMENT                    LEXTOK_DECREMENT                  "--"
%token YYTOK_SUBSTRACT_ASSIGN             LEXTOK_SUBSTRACT_ASSIGN           "-="
%token YYTOK_SARROW                       LEXTOK_SARROW                     "->"
%token YYTOK_DOT                          LEXTOK_DOT                        "."
%token YYTOK_ELIPSIS                      LEXTOK_ELIPSIS                    "..."
%token YYTOK_FSLASH                       LEXTOK_FSLASH                     "/"
%token YYTOK_FLOOR_DIVIDE                 LEXTOK_FLOOR_DIVIDE               "//"
%token YYTOK_FLOOR_DIVIDE_ASSIGN          LEXTOK_FLOOR_DIVIDE_ASSIGN        "//="
%token YYTOK_DIVIDE_ASSIGN                LEXTOK_DIVIDE_ASSIGN              "/="
%token YYTOK_COLON                        LEXTOK_COLON                      ":"
%token YYTOK_DCOLON                       LEXTOK_DCOLON                     "::"
%token YYTOK_SEMICOLON                    LEXTOK_SEMICOLON                  ";"
%token YYTOK_LBRACE_ANGULAR               LEXTOK_LBRACE_ANGULAR             "<"
%token YYTOK_BITWISE_LSHIFT               LEXTOK_BITWISE_LSHIFT             "<<"
%token YYTOK_BITWISE_LSHIFT_ASSIGN        LEXTOK_BITWISE_LSHIFT_ASSIGN      "<<="
%token YYTOK_LOGICAL_LESSER_EQUAL         LEXTOK_LOGICAL_LESSER_EQUAL       "<="
%token YYTOK_ASSIGN                       LEXTOK_ASSIGN                     "="
%token YYTOK_LOGICAL_EQUAL                LEXTOK_LOGICAL_EQUAL              "=="
%token YYTOK_LOGICAL_IDENTICAL            LEXTOK_LOGICAL_IDENTICAL          "==="
%token YYTOK_DARROW                       LEXTOK_DARROW                     "=>"
%token YYTOK_RBRACE_ANGULAR               LEXTOK_RBRACE_ANGULAR             ">"
%token YYTOK_LOGICAL_GREATER_EQUAL        LEXTOK_LOGICAL_GREATER_EQUAL      ">="
%token YYTOK_BITWISE_RSHIFT               LEXTOK_BITWISE_RSHIFT             ">>"
%token YYTOK_BITWISE_RSHIFT_ASSIGN        LEXTOK_BITWISE_RSHIFT_ASSIGN      ">>="
%token YYTOK_ARITH_RSHIFT                 LEXTOK_ARITH_RSHIFT               ">>>"
%token YYTOK_ARITH_RSHIFT_ASSIGN          LEXTOK_ARITH_RSHIFT_ASSIGN        ">>>="
%token YYTOK_QUESTION                     LEXTOK_QUESTION                   "?"
%token YYTOK_AT                           LEXTOK_AT                         "@"
%token YYTOK_LBRACE_SQUARE                LEXTOK_LBRACE_SQUARE              "["
%token YYTOK_BSLASH                       LEXTOK_BSLASH                     "\\"
%token YYTOK_RBRACE_SQUARE                LEXTOK_RBRACE_SQUARE              "]"
%token YYTOK_CARET                        LEXTOK_CARET                      "^"
%token YYTOK_BITWISE_XOR_ASSIGN           LEXTOK_BITWISE_XOR_ASSIGN         "^="
%token YYTOK_BACKTICK                     LEXTOK_BACKTICK                   "`"
%token YYTOK_LBRACE_CURLY                 LEXTOK_LBRACE_CURLY               "{"
%token YYTOK_PIPE                         LEXTOK_PIPE                       "|"
%token YYTOK_BITWISE_OR_ASSIGN            LEXTOK_BITWISE_OR_ASSIGN          "|="
%token YYTOK_PIPEOUT                      LEXTOK_PIPEOUT                    "|>"
%token YYTOK_LOGICAL_OR                   LEXTOK_LOGICAL_OR                 "||"
%token YYTOK_LOGICAL_OR_ASSIGN            LEXTOK_LOGICAL_OR_ASSIGN          "||="
%token YYTOK_RBRACE_CURLY                 LEXTOK_RBRACE_CURLY               "}"
%token YYTOK_TILDE                        LEXTOK_TILDE                      "~"

// keywords
%token YYTOK_KWD_CALC                     LEXTOK_KWD_CALC                   "calc"
%token YYTOK_KWD_END                      LEXTOK_KWD_END                    "end"
%token YYTOK_KWD_IF                       LEXTOK_KWD_IF                     "if"
%token YYTOK_KWD_START                    LEXTOK_KWD_START                  "start"
%token YYTOK_KWD_WHILE                    LEXTOK_KWD_WHILE                  "while"

// identifier
%token <idf> YYTOK_IDENTIFIER             LEXTOK_IDENTIFIER                 "<identifier>"

// literals
%token <chr> YYTOK_CHAR_LITERAL           LEXTOK_CHAR_LITERAL               "<charlit>"
%token <f64> YYTOK_BINFLOAT_LITERAL       LEXTOK_BINFLOAT_LITERAL           "<binfloattlit>"
%token <f64> YYTOK_OCTFLOAT_LITERAL       LEXTOK_OCTFLOAT_LITERAL           "<octfloattlit>"
%token <f64> YYTOK_DECFLOAT_LITERAL       LEXTOK_DECFLOAT_LITERAL           "<decfloattlit>"
%token <f64> YYTOK_HEXFLOAT_LITERAL       LEXTOK_HEXFLOAT_LITERAL           "<hexfloattlit>"
%token <i64> YYTOK_BININT_LITERAL         LEXTOK_BININT_LITERAL             "<binintlit>"
%token <i64> YYTOK_OCTINT_LITERAL         LEXTOK_OCTINT_LITERAL             "<octintlit>"
%token <i64> YYTOK_DECINT_LITERAL         LEXTOK_DECINT_LITERAL             "<decintlit>"
%token <i64> YYTOK_HEXINT_LITERAL         LEXTOK_HEXINT_LITERAL             "<hexintlit>"
%token <str> YYTOK_STR_LITERAL            LEXTOK_STR_LITERAL                "<strlit>"
%token <str> YYTOK_INTERP_STR_LITERAL     LEXTOK_INTERP_STR_LITERAL         "<interpstrlit>"

// default cases
%token YYTOK_EOF                          LEXTOK_EOF                        "<eof>"
%token YYTOK_INVALID                      LEXTOK_INVALID                    "<invalid>"


%union {
    char chr;
    int64_t i64;
    double f64;
    char *str;
    void *any;
    char *idf;
}

%start program

%%

program: /* Add rules here */ ;

%%

void parse_interpret(FILE *f)
{
    yyin = f;
    yyparse();
}

void parse_throw(const char *msg)
{
    if (!msg) abort();
    io_print_srcerr(lex_line_no, lex_char_no, "parser error: %s", msg);
    exit(2);
}

int yylex(void)
{
    int token = lex_get_nexttok(yyin);
    switch (token) {
        case YYTOK_IDENTIFIER:
            yylval.idf = strdup(lex_get_buffstr());
            break;
        case YYTOK_CHAR_LITERAL:
            yylval.chr = parse_char(lex_get_buffstr());
            break;
        case YYTOK_STR_LITERAL:
            yylval.str = parse_str(lex_get_buffstr());
            break;
        case YYTOK_INTERP_STR_LITERAL:
            yylval.str = parse_interpstr(lex_get_buffstr());
            break;
        case YYTOK_BINFLOAT_LITERAL:
            yylval.f64 = parse_float(lex_get_buffstr(), 2);
            break;
        case YYTOK_OCTFLOAT_LITERAL:
            yylval.f64 = parse_float(lex_get_buffstr(), 8);
            break;
        case YYTOK_DECFLOAT_LITERAL:
            yylval.f64 = parse_float(lex_get_buffstr(), 10);
            break;
        case YYTOK_HEXFLOAT_LITERAL:
            yylval.f64 = parse_float(lex_get_buffstr(), 16);
            break;
        case YYTOK_BININT_LITERAL:
            yylval.i64 = parse_int(lex_get_buffstr(), 2);
            break;
        case YYTOK_OCTINT_LITERAL:
            yylval.i64 = parse_int(lex_get_buffstr(), 8);
            break;
        case YYTOK_DECINT_LITERAL:
            yylval.i64 = parse_int(lex_get_buffstr(), 10);
            break;
        case YYTOK_HEXINT_LITERAL:
            yylval.i64 = parse_int(lex_get_buffstr(), 16);
            break;
        default: break;
    }
    return token;
}
