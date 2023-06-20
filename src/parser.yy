%{

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

#include "io.h"
#include "lexer.h"
#include "parser.h"

#include "parser/parse_chr.c.h"
#include "parser/parse_i64.c.h"
#include "parser/parse_f64.c.h"
#include "parser/parse_str.c.h"

FILE *yyin = NULL;

%}

%token         LEXTOK_BANG                     "!"
%token         LEXTOK_LOGICAL_UNEQUAL          "!="
%token         LEXTOK_LOGICAL_UNIDENTICAL      "!=="
%token         LEXTOK_DQUOTE                   '"'
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
%token         LEXTOK_KWD_PROC                 "proc"
%token         LEXTOK_KWD_START                "start"
%token         LEXTOK_KWD_END                  "end"
%token         LEXTOK_KWD_BLOCK                "block"
%token         LEXTOK_KWD_IF                   "if"
%token         LEXTOK_KWD_THEN                 "then"
%token         LEXTOK_KWD_ELIF                 "elif"
%token         LEXTOK_KWD_ELSE                 "else"
%token         LEXTOK_KWD_WHILE                "while"
%token         LEXTOK_KWD_FOR                  "for"
%token         LEXTOK_KWD_FROM                 "from"
%token         LEXTOK_KWD_TO                   "to"
%token         LEXTOK_KWD_DO                   "do"
%token         LEXTOK_KWD_VAR                  "var"
%token         LEXTOK_KWD_PASS                 "pass"

// identifier
%token <idf>   LEXTOK_IDENTIFIER               "<identifier>"

// literals
%token <bul>   LEXTOK_BOOL_LITERAL             "<boollit>"
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
    bool bul;
    char chr;
    int64_t i64;
    double f64;
    char *str;
    void *any;
    char *idf;
    VarData var_data;
}

%type <any>      procedure
%type <any>      statements
%type <any>      statement
%type <any>      if_block
%type <any>      else_if_ladder
%type <any>      loop_block
%type <any>      block

%type <bul>      condition
%type <var_data> expression
%type <var_data> expression_endpt

%start program

%%

/* A program is a single procedure or multiple procedures */
program:
    procedure "\n"
|   procedure "\n" program
;

procedure:
    "proc" LEXTOK_IDENTIFIER "start" "\n" statements "end" {
        scoping_pushscope($2);
        { $$ = $5; }
        scoping_popscope();
    }
;

statements:
    statement
|   statement statements
;

statement:
    "\n"
|   "pass" "\n"
|   "var" LEXTOK_IDENTIFIER "=" expression "\n" { vartable_setvar($2, $4, true); } /* shadow or create new var */
|   LEXTOK_IDENTIFIER "=" expression "\n" { vartable_setvar($1, $3, false); }      /* access existing var */
|   compound_statement "\n"
|   expression "\n"
;

compound_statement:
    if_block
|   loop_block
|   block
;

if_block:
    "if" condition "then" "\n" statements "end" {
        scoping_pushscope(itoa(lex_line_no));
        if ($2) { $$ = $5; }
        scoping_popscope();
    }
|   "if" condition "then" "\n" statements "else" statements "end" {
        scoping_pushscope(itoa(lex_line_no));
        if ($2) { $5; } else { $$ = $7; }
        scoping_popscope();
    }
|   "if" condition "then" "\n" statements else_if_ladder {
        scoping_pushscope(itoa(lex_line_no));
        if ($2) { $5; } else { $$ = $6; }
        scoping_popscope();
    }
;

else_if_ladder:
    "else" if_block
;

loop_block:
    "while" condition "do" "\n" statements "end" {
        scoping_pushscope(itoa(lex_line_no));
        while ($2) { $$ = $5; }
        scoping_popscope();
    }
|   "for" LEXTOK_IDENTIFIER "from" LEXTOK_DECINT_LITERAL "to" LEXTOK_DECINT_LITERAL "do" statements "end" {
        scoping_pushscope(itoa(lex_line_no));
        for (int64_t i = $4; i < $6; ($4 <= $6) ? ++i : --i) {
            vartable_setvar($2, (VarData) { .var.i64 = i, .type = VT_I64 }, true);
            $$ = $8;
        }
        scoping_popscope();
    }
;

block:
    "block" statements "end" {
        scoping_pushscope(itoa(lex_line_no));
        { $$ = $2; }
        scoping_popscope();
    }
;

condition: expression {
    switch ($1.type) {
        case VT_BUL: $$ = $1.var.bul; break;
        case VT_CHR: $$ = (bool) $1.var.chr; break;
        case VT_I64: $$ = (bool) $1.var.i64; break;
        case VT_F64: $$ = (bool) $1.var.f64; break;
        case VT_STR: $$ = (bool) ($1.var.str ? strlen($1.var.str) : $1.var.str); break;
        case VT_ANY: $$ = (bool) $1.var.any; break;
        default: $$ = false;
    }
};

expression: expression_endpt { $$ = $1; }
;

expression_endpt:
    LEXTOK_BOOL_LITERAL         { $$ = (VarData) { .var.bul = $1.bul, .type = VT_BUL }; }
|   LEXTOK_CHAR_LITERAL         { $$ = (VarData) { .var.chr = $1.chr, .type = VT_CHR }; }
|   LEXTOK_BINFLOAT_LITERAL     { $$ = (VarData) { .var.f64 = $1.bul, .type = VT_BUL }; }
|   LEXTOK_OCTFLOAT_LITERAL     { $$ = (VarData) { .var.f64 = $1.f64, .type = VT_F64 }; }
|   LEXTOK_DECFLOAT_LITERAL     { $$ = (VarData) { .var.f64 = $1.f64, .type = VT_F64 }; }
|   LEXTOK_HEXFLOAT_LITERAL     { $$ = (VarData) { .var.f64 = $1.f64, .type = VT_F64 }; }
|   LEXTOK_BININT_LITERAL       { $$ = (VarData) { .var.i64 = $1.i64, .type = VT_I64 }; }
|   LEXTOK_OCTINT_LITERAL       { $$ = (VarData) { .var.i64 = $1.i64, .type = VT_I64 }; }
|   LEXTOK_DECINT_LITERAL       { $$ = (VarData) { .var.i64 = $1.i64, .type = VT_I64 }; }
|   LEXTOK_HEXINT_LITERAL       { $$ = (VarData) { .var.i64 = $1.i64, .type = VT_I64 }; }
|   LEXTOK_STR_LITERAL          { $$ = (VarData) { .var.str = $1.str, .type = VT_STR }; }
|   LEXTOK_INTERP_STR_LITERAL   { $$ = (VarData) { .var.str = $1.str, .type = VT_STR }; }
|   LEXTOK_IDENTIFIER           { $$ = (VarData) { .var.idf = $1.idf, .type = VT_ANY }; };

%%

int yyerror(const char* s)
{
    parse_throw(s);
    return 1;
}

void parse_interpret(FILE *f)
{
    yyin = f;
    LexToken tok = lex_get_nexttok(yyin);
    while (tok != LEXTOK_EOF) {
        printf("%s: %s\n", lex_get_tokcode(tok), lex_get_buffstr());
        tok = lex_get_nexttok(f);
    }
    printf("%s\n", lex_get_tokcode(tok));
    return;
    yyparse();
}

void parse_throw(const char *msg)
{
    if (!msg) abort();
    io_print_srcerr(lex_line_no, lex_char_no, "parser error: %s", msg);
    exit(2);
}
