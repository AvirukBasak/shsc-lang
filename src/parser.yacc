%{

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "io.h"
#include "lexer.h"
#include "parser.h"

FILE *yyin = NULL;

%}

%token         LEXTOK_BANG                     "!"
%token         LEXTOK_LOGICAL_UNEQUAL          "!="
%token         LEXTOK_LOGICAL_UNIDENTICAL      "!=="
%token         LEXTOK_DQUOTE                   "\""
%token         LEXTOK_DOLLAR                   "$"
%token         LEXTOK_PERCENT                  "%"
%token         LEXTOK_MODULO_ASSIGN            "%="
%token         LEXTOK_AMPERSAND                "&"
%token         LEXTOK_LOGICAL_AND              "&&"
%token         LEXTOK_LOGICAL_AND_ASSIGN       "&&="
%token         LEXTOK_BITWISE_AND_ASSIGN       "&="
%token         LEXTOK_SQUOTE                   "'"
%token         LEXTOK_LBRACE_PAREN             "("
%token         LEXTOK_RBRACE_PAREN             ")"
%token         LEXTOK_ASTERIX                  "*"
%token         LEXTOK_EXPONENT                 "**"
%token         LEXTOK_EXPONENT_ASSIGN          "**="
%token         LEXTOK_MULTIPLY_ASSIGN          "*="
%token         LEXTOK_PLUS                     "+"
%token         LEXTOK_INCREMENT                "++"
%token         LEXTOK_ADD_ASSIGN               "+="
%token         LEXTOK_COMMA                    ""
%token         LEXTOK_MINUS                    "-"
%token         LEXTOK_DECREMENT                "--"
%token         LEXTOK_SUBSTRACT_ASSIGN         "-="
%token         LEXTOK_SARROW                   "->"
%token         LEXTOK_DOT                      "."
%token         LEXTOK_ELIPSIS                  "..."
%token         LEXTOK_FSLASH                   "/"
%token         LEXTOK_FLOOR_DIVIDE             "//"
%token         LEXTOK_FLOOR_DIVIDE_ASSIGN      "//="
%token         LEXTOK_DIVIDE_ASSIGN            "/="
%token         LEXTOK_COLON                    ":"
%token         LEXTOK_DCOLON                   "::"
%token         LEXTOK_SEMICOLON                ";"
%token         LEXTOK_LBRACE_ANGULAR           "<"
%token         LEXTOK_BITWISE_LSHIFT           "<<"
%token         LEXTOK_BITWISE_LSHIFT_ASSIGN    "<<="
%token         LEXTOK_LOGICAL_LESSER_EQUAL     "<="
%token         LEXTOK_ASSIGN                   "="
%token         LEXTOK_LOGICAL_EQUAL            "=="
%token         LEXTOK_LOGICAL_IDENTICAL        "==="
%token         LEXTOK_DARROW                   "=>"
%token         LEXTOK_RBRACE_ANGULAR           ">"
%token         LEXTOK_LOGICAL_GREATER_EQUAL    ">="
%token         LEXTOK_BITWISE_RSHIFT           ">>"
%token         LEXTOK_BITWISE_RSHIFT_ASSIGN    ">>="
%token         LEXTOK_ARITH_RSHIFT             ">>>"
%token         LEXTOK_ARITH_RSHIFT_ASSIGN      ">>>="
%token         LEXTOK_QUESTION                 "?"
%token         LEXTOK_AT                       "@"
%token         LEXTOK_LBRACE_SQUARE            "["
%token         LEXTOK_BSLASH                   "\\"
%token         LEXTOK_RBRACE_SQUARE            "]"
%token         LEXTOK_CARET                    "^"
%token         LEXTOK_BITWISE_XOR_ASSIGN       "^="
%token         LEXTOK_BACKTICK                 "`"
%token         LEXTOK_LBRACE_CURLY             "{"
%token         LEXTOK_PIPE                     "|"
%token         LEXTOK_BITWISE_OR_ASSIGN        "|="
%token         LEXTOK_PIPEOUT                  "|>"
%token         LEXTOK_LOGICAL_OR               "||"
%token         LEXTOK_LOGICAL_OR_ASSIGN        "||="
%token         LEXTOK_RBRACE_CURLY             "}"
%token         LEXTOK_TILDE                    "~"

%token         LEXTOK_NEWLINE                  "\n"

// keywords
%token         LEXTOK_KWD_CALC                 "calc"
%token         LEXTOK_KWD_END                  "end"
%token         LEXTOK_KWD_IF                   "if"
%token         LEXTOK_KWD_START                "start"
%token         LEXTOK_KWD_WHILE                "while"

// identifier
%token <idf>   LEXTOK_IDENTIFIER               "<identifier>"

// literals
%token <chr>   LEXTOK_CHAR_LITERAL             "<charlit>"
%token <f64>   LEXTOK_BINFLOAT_LITERAL         "<binfloattlit>"
%token <f64>   LEXTOK_OCTFLOAT_LITERAL         "<octfloattlit>"
%token <f64>   LEXTOK_DECFLOAT_LITERAL         "<decfloattlit>"
%token <f64>   LEXTOK_HEXFLOAT_LITERAL         "<hexfloattlit>"
%token <i64>   LEXTOK_BININT_LITERAL           "<binintlit>"
%token <i64>   LEXTOK_OCTINT_LITERAL           "<octintlit>"
%token <i64>   LEXTOK_DECINT_LITERAL           "<decintlit>"
%token <i64>   LEXTOK_HEXINT_LITERAL           "<hexintlit>"
%token <str>   LEXTOK_STR_LITERAL              "<strlit>"
%token <str>   LEXTOK_INTERP_STR_LITERAL       "<interpstrlit>"

// default cases
%token         LEXTOK_EOF                      "<eof>"
%token         LEXTOK_INVALID                  "<invalid>"

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

int yyerror(const char* s)
{
    parse_throw(s);
    return 1;
}

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
