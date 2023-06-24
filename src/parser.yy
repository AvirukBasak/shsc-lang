%{

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

#include "io.h"
#include "lexer.h"
#include "parser.h"
#include "ast.h"

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
%token         LEXTOK_COMMA                    ","
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

/* keywords */
%token         LEXTOK_KWD_MODULE               "module"
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
%token         LEXTOK_KWD_BY                   "by"
%token         LEXTOK_KWD_DO                   "do"
%token         LEXTOK_KWD_VAR                  "var"
%token         LEXTOK_KWD_PASS                 "pass"


/* default cases */
%token         LEXTOK_EOF                      "<eof>"
%token         LEXTOK_INVALID                  "<invalid>"


/* literals */
%token <literal_bool>      LEXTOK_BOOL_LITERAL             "<boollit>"
%token <literal_char>      LEXTOK_CHAR_LITERAL             "<charlit>"
%token <literal_f64>       LEXTOK_BINFLOAT_LITERAL         "<binfloattlit>"
%token <literal_f64>       LEXTOK_OCTFLOAT_LITERAL         "<octfloattlit>"
%token <literal_f64>       LEXTOK_DECFLOAT_LITERAL         "<decfloattlit>"
%token <literal_f64>       LEXTOK_HEXFLOAT_LITERAL         "<hexfloattlit>"
%token <literal_i64>       LEXTOK_BININT_LITERAL           "<binintlit>"
%token <literal_i64>       LEXTOK_OCTINT_LITERAL           "<octintlit>"
%token <literal_i64>       LEXTOK_DECINT_LITERAL           "<decintlit>"
%token <literal_i64>       LEXTOK_HEXINT_LITERAL           "<hexintlit>"
%token <literal_str>       LEXTOK_STR_LITERAL              "<strlit>"
%token <literal_str>       LEXTOK_INTERP_STR_LITERAL       "<interpstrlit>"


/* identifier */
%token <identifier_name>   LEXTOK_IDENTIFIER               "<identifier>"


%union
{
    /* base literals */
    bool     literal_bool;
    char     literal_char;
    double   literal_f64;
    int64_t  literal_i64;
    char    *literal_str;
    void    *literal_any;

    /* identifier name */
    char    *identifier_name;

    /* ast nodes */
    AST_Program             *astnode_program,              /* program */
    AST_Procedure           *astnode_procedure,            /* procedure */
    AST_Statements          *astnode_statements,           /* statements */
    AST_Statement           *astnode_statement,            /* statement */
    AST_Assignment          *astnode_assignment,           /* assignment */
    AST_CompoundStatement   *astnode_compound_statement,   /* compound_statement */
    AST_IfBlock             *astnode_if_block,             /* if_block */
    AST_IfElseBlock         *astnode_if_else_block,        /* if_else_block */
    AST_IfElseIfBlock       *astnode_if_else_if_block,     /* if_else_if_block */
    AST_ElseIfBlock         *astnode_else_if_block,        /* else_if_block */
    AST_WhileBlock          *astnode_while_block,          /* while_block */
    AST_ForBlock            *astnode_for_block,            /* for_block */
    AST_Block               *astnode_block,                /* block */
    AST_Condition           *astnode_condition,            /* condition */
    AST_Expression          *astnode_expression,           /* expression */
    AST_Operand             *astnode_operand,              /* operand */
    AST_Literal             *astnode_literal,              /* literal */
    AST_Identifier          *astnode_identifier            /* identifier */
}


/* semantic types of each parser rule */
%type <astnode_program>               program
%type <astnode_procedure>             procedure
%type <astnode_statements>            statements
%type <astnode_statement>             statement
%type <astnode_assignment>            assignment
%type <astnode_compound_statement>    compound_statement
%type <astnode_if_block>              if_block
%type <astnode_if_else_block>         if_else_block
%type <astnode_if_else_if_block>      if_else_if_block
%type <astnode_else_if_block>         else_if_block
%type <astnode_while_block>           while_block
%type <astnode_for_block>             for_block
%type <astnode_block>                 block
%type <astnode_condition>             condition
%type <astnode_expression>            expression
%type <astnode_operand>               operand
%type <astnode_literal>               literal
%type <astnode_identifier>            identifier


/* associativity: logical operators */
%left LEXTOK_LOGICAL_OR
%left LEXTOK_LOGICAL_AND
%nonassoc LEXTOK_BANG
%nonassoc LEXTOK_LOGICAL_EQUAL
%nonassoc LEXTOK_LOGICAL_UNEQUAL
%nonassoc LEXTOK_LOGICAL_IDENTICAL
%nonassoc LEXTOK_LOGICAL_UNIDENTICAL


/* parser entry point? */
%start input


%%

input:
    "module" identifier "\n" program { AST_module_add($2, $4); }
    program { AST_module_add(AST_identifier("main"), $4); }
    ;

/* A program is empty or a single procedure or multiple procedures */
program:
    | procedure "\n" { $$ = AST_program($1, NULL); }
    | procedure "\n" program { $$ = AST_program($1, $2); }
    ;

procedure:
    "proc" LEXTOK_IDENTIFIER "start" "\n" statements "end" { $$ = AST_procedure($2, $5); }
    ;

statements:
    statement { $$ = AST_statements($1, NULL); }
    | statement statements { $$ = AST_statements($1, $2); }
    ;

statement:
    "\n" { $$ = AST_statement_empty(); }
    | "pass" "\n" { $$ = AST_statement_empty(); }
    | assignment "\n" { $$ = AST_statement_assignment($1); }
    | compound_statement "\n" { $$ = AST_statement_compound($1); }
    ;

assignment:
    "var" LEXTOK_IDENTIFIER "=" expression { $$ = AST_assignment_create($2, $4); }  /* shadow or create new var */
    | LEXTOK_IDENTIFIER "=" expression { $$ = AST_assignment_update($2, $4); }      /* access existing var */
    | expression { $$ = AST_assignment_tovoid($1); }                                /* assignment to void */
    ;

compound_statement:
    if_block { $$ = AST_compoundst_if_block($1); }
    | if_else_block { $$ = AST_compoundst_if_else_block($1); }
    | if_else_if_block { $$ = AST_compoundst_if_else_if_block($1); }
    | while_block { $$ = AST_compoundst_while_block($1); }
    | for_block { $$ = AST_compoundst_for_block($1); }
    | block { $$ = AST_compoundst_block($1); }
    ;

if_block:
    "if" condition "then" "\n" statements "end" { $$ = AST_if_block($2, $5); }
    ;

if_else_block:
    "if" condition "then" "\n" statements "else" statements "end" { $$ = AST_if_else_block($2, $5, $7); }
    ;

if_else_if_block:
    "if" condition "then" "\n" statements else_if_block { $$ = AST_if_else_if_block($2, $5, $6); }
    ;

else_if_block:
    "else" if_else_if_block { $$ = AST_else_if_block($2); }
    | "end" { $$ = AST_else_if_block(NULL); }
    ;

while_block:
    "while" condition "do" "\n" statements "end" { $$ = AST_while_block($2, $5); }
    ;

for_block:
    "for" identifier "from" operand "to" operand "do" statements "end" { $$ = AST_for_block($2, $4, $6, NULL, $8); }
    | "for" identifier "from" operand "to" operand "by" operand "do" statements "end" { $$ = AST_for_block($2, $4, $6, $8, $10); }
    ;

block:
    "block" statements "end" { $$ = AST_block($2); }
    ;

condition:
    expression { $$ = AST_condition($1); }
    ;

expression: operand;

operand:
    literal { $$ = AST_operand_literal($1); }
    | identifier { $$ = AST_operand_identifier($1); }
    ;

literal:
    LEXTOK_BOOL_LITERAL           { $$ = AST_literal_bul($1); }
    | LEXTOK_CHAR_LITERAL         { $$ = AST_literal_chr($1); }
    | LEXTOK_BINFLOAT_LITERAL     { $$ = AST_literal_f64($1); }
    | LEXTOK_OCTFLOAT_LITERAL     { $$ = AST_literal_f64($1); }
    | LEXTOK_DECFLOAT_LITERAL     { $$ = AST_literal_f64($1); }
    | LEXTOK_HEXFLOAT_LITERAL     { $$ = AST_literal_f64($1); }
    | LEXTOK_BININT_LITERAL       { $$ = AST_literal_i64($1); }
    | LEXTOK_OCTINT_LITERAL       { $$ = AST_literal_i64($1); }
    | LEXTOK_DECINT_LITERAL       { $$ = AST_literal_i64($1); }
    | LEXTOK_HEXINT_LITERAL       { $$ = AST_literal_i64($1); }
    | LEXTOK_STR_LITERAL          { $$ = AST_literal_str($1); }
    | LEXTOK_INTERP_STR_LITERAL   { $$ = AST_literal_interp_str($1); }
    ;

identifier:
    LEXTOK_IDENTIFIER { $$ = AST_identifier($1); }
    ;

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
