%{

#define YYMALLOC shsc_malloc
#define YYREALLOC shsc_realloc
#define YYCALLOC shsc_calloc
#define YYFREE shsc_free

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast/api.h"
#include "errcodes.h"
#include "globals.h"
#include "io.h"
#include "lexer.h"
#include "parser.h"

FILE *yyin = NULL;

%}

%union
{
    /* line count */
    int line_count;

    /* just the token id */
    enum yytokentype tok;

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
    ast_Statements_t       *astnode_statements;           /* statements */
    ast_Statement_t        *astnode_statement;            /* statement */
    ast_Assignment_t       *astnode_assignment;           /* assignment */
    ast_CompoundSt_t       *astnode_compound_statement;   /* compound_statement */
    ast_IfBlock_t          *astnode_if_block;             /* if_block */
    ast_ElseBlock_t        *astnode_else_block;           /* else_block */
    ast_WhileBlock_t       *astnode_while_block;          /* while_block */
    ast_ForBlock_t         *astnode_for_block;            /* for_block */
    ast_Block_t            *astnode_block;                /* block */
    ast_Expression_t       *astnode_expression;           /* expression */
    ast_CommaSepList_t     *astnode_comma_list;           /* comma_list */
    ast_AssociativeList_t  *astnode_assoc_list;           /* assoc_list */
    ast_Literal_t          *astnode_literal;              /* literal */
    ast_Identifier_t       *astnode_identifier;           /* identifier */
}

%token <tok> TOKEN_BANG                              "!"
%token <tok> TOKEN_LOGICAL_UNEQUAL                   "!="
%token <tok> TOKEN_LOGICAL_UNIDENTICAL               "!=="
%token <tok> TOKEN_DQUOTE                            '"'
%token <tok> TOKEN_DOLLAR                            "$"
%token <tok> TOKEN_PERCENT                           "%"
%token <tok> TOKEN_MODULO_ASSIGN                     "%="
%token <tok> TOKEN_AMPERSAND                         "&"
%token <tok> TOKEN_LOGICAL_AND                       "&&"
%token <tok> TOKEN_LOGICAL_AND_ASSIGN                "&&="
%token <tok> TOKEN_BITWISE_AND_ASSIGN                "&="
%token <tok> TOKEN_SQUOTE                            "'"
%token <tok> TOKEN_LBRACE_PAREN                      "("
%token <tok> TOKEN_RBRACE_PAREN                      ")"
%token <tok> TOKEN_ASTERIX                           "*"
%token <tok> TOKEN_EXPONENT                          "**"
%token <tok> TOKEN_EXPONENT_ASSIGN                   "**="
%token <tok> TOKEN_MULTIPLY_ASSIGN                   "*="
%token <tok> TOKEN_PLUS                              "+"
%token <tok> TOKEN_INCREMENT                         "++"
%token <tok> TOKEN_ADD_ASSIGN                        "+="
%token <tok> TOKEN_COMMA                             ","
%token <tok> TOKEN_MINUS                             "-"
%token <tok> TOKEN_DECREMENT                         "--"
%token <tok> TOKEN_SUBSTRACT_ASSIGN                  "-="
%token <tok> TOKEN_SARROW                            "->"
%token <tok> TOKEN_DOT                               "."
%token <tok> TOKEN_ELIPSIS                           "..."
%token <tok> TOKEN_FSLASH                            "/"
%token <tok> TOKEN_FLOOR_DIVIDE                      "//"
%token <tok> TOKEN_FLOOR_DIVIDE_ASSIGN               "//="
%token <tok> TOKEN_DIVIDE_ASSIGN                     "/="
%token <tok> TOKEN_COLON                             ":"
%token <tok> TOKEN_DCOLON                            "::"
%token <tok> TOKEN_SEMICOLON                         ";"
%token <tok> TOKEN_LBRACE_ANGULAR                    "<"
%token <tok> TOKEN_BITWISE_LSHIFT                    "<<"
%token <tok> TOKEN_BITWISE_LSHIFT_ASSIGN             "<<="
%token <tok> TOKEN_LOGICAL_LESSER_EQUAL              "<="
%token <tok> TOKEN_ASSIGN                            "="
%token <tok> TOKEN_LOGICAL_EQUAL                     "=="
%token <tok> TOKEN_LOGICAL_IDENTICAL                 "==="
%token <tok> TOKEN_DARROW                            "=>"
%token <tok> TOKEN_RBRACE_ANGULAR                    ">"
%token <tok> TOKEN_LOGICAL_GREATER_EQUAL             ">="
%token <tok> TOKEN_BITWISE_RSHIFT                    ">>"
%token <tok> TOKEN_BITWISE_RSHIFT_ASSIGN             ">>="
%token <tok> TOKEN_ARITH_RSHIFT                      ">>>"
%token <tok> TOKEN_ARITH_RSHIFT_ASSIGN               ">>>="
%token <tok> TOKEN_QUESTION                          "?"
%token <tok> TOKEN_AT                                "@"
%token <tok> TOKEN_LBRACE_SQUARE                     "["
%token <tok> TOKEN_BSLASH                            "\\"
%token <tok> TOKEN_RBRACE_SQUARE                     "]"
%token <tok> TOKEN_CARET                             "^"
%token <tok> TOKEN_BITWISE_XOR_ASSIGN                "^="
%token <tok> TOKEN_BACKTICK                          "`"
%token <tok> TOKEN_LBRACE_CURLY                      "{"
%token <tok> TOKEN_PIPE                              "|"
%token <tok> TOKEN_BITWISE_OR_ASSIGN                 "|="
%token <tok> TOKEN_PIPEOUT                           "|>"
%token <tok> TOKEN_LOGICAL_OR                        "||"
%token <tok> TOKEN_LOGICAL_OR_ASSIGN                 "||="
%token <tok> TOKEN_RBRACE_CURLY                      "}"
%token <tok> TOKEN_TILDE                             "~"

/* special operation values */
%token TOKOP_NOP
%token TOKOP_FNCALL
%token TOKOP_INDEXING
%token TOKOP_TERNARY_COND
%token TOKOP_FNARGS_INDEXING

%token TOKEN_NEWLINE                                 "\n"

/* keywords */
%token TOKEN_KWD_MODULE                              "module"
%token TOKEN_KWD_PROC                                "proc"
%token TOKEN_KWD_START                               "start"
%token TOKEN_KWD_END                                 "end"
%token TOKEN_KWD_BLOCK                               "block"
%token TOKEN_KWD_IF                                  "if"
%token TOKEN_KWD_THEN                                "then"
%token TOKEN_KWD_ELIF                                "elif"
%token TOKEN_KWD_ELSE                                "else"
%token TOKEN_KWD_WHILE                               "while"
%token TOKEN_KWD_BREAK                               "break"
%token TOKEN_KWD_CONTINUE                            "continue"
%token TOKEN_KWD_FOR                                 "for"
%token TOKEN_KWD_FROM                                "from"
%token TOKEN_KWD_TO                                  "to"
%token TOKEN_KWD_BY                                  "by"
%token TOKEN_KWD_IN                                  "in"
%token TOKEN_KWD_DO                                  "do"
%token TOKEN_KWD_VAR                                 "var"
%token TOKEN_KWD_CONST                               "const"
%token TOKEN_KWD_PASS                                "pass"
%token TOKEN_KWD_RETURN                              "return"

/* default cases */
%token TOKEN_EOF 0                                   "<eof>"
%token TOKEN_INVALID                                 "<invalid>"

/* literals */
%token <literal_bool> TOKEN_BOOL_LITERAL             "<boollit>"
%token <literal_char> TOKEN_CHAR_LITERAL             "<charlit>"
%token <literal_f64>  TOKEN_BINFLOAT_LITERAL         "<binfloattlit>"
%token <literal_f64>  TOKEN_OCTFLOAT_LITERAL         "<octfloattlit>"
%token <literal_f64>  TOKEN_DECFLOAT_LITERAL         "<decfloattlit>"
%token <literal_f64>  TOKEN_HEXFLOAT_LITERAL         "<hexfloattlit>"
%token <literal_i64>  TOKEN_BININT_LITERAL           "<binintlit>"
%token <literal_i64>  TOKEN_OCTINT_LITERAL           "<octintlit>"
%token <literal_i64>  TOKEN_DECINT_LITERAL           "<decintlit>"
%token <literal_i64>  TOKEN_HEXINT_LITERAL           "<hexintlit>"
%token <literal_str>  TOKEN_STR_LITERAL              "<strlit>"
%token <literal_str>  TOKEN_INTERP_STR_LITERAL       "<interpstrlit>"

/* identifier */
%token <identifier_name> TOKEN_IDENTIFIER            "<identifier>"

%precedence TOKEN_PERCENT
%precedence TOKEN_ASTERIX
%precedence TOKEN_EXPONENT
%precedence TOKEN_FSLASH
%precedence TOKEN_FLOOR_DIVIDE

%precedence TOKEN_KWD_IF
%precedence TOKEN_KWD_ELSE

%type <line_count> nws
%type <line_count> nwp
%type <line_count> trm

/* semantic types of each parser rule */
%type <astnode_statements>         statements
%type <astnode_statement>          statement
%type <astnode_assignment>         assignment
%type <astnode_compound_statement> compound_statement
%type <astnode_if_block>           if_block
%type <astnode_else_block>         else_block
%type <astnode_while_block>        while_block
%type <astnode_for_block>          for_block
%type <astnode_block>              block

%type <astnode_expression>         expression
%type <astnode_expression>         condition
%type <astnode_expression>         assignment_expression
%type <astnode_expression>         conditional_expression
%type <astnode_expression>         logical_or_expression
%type <astnode_expression>         logical_and_expression
%type <astnode_expression>         bitwise_or_expression
%type <astnode_expression>         bitwise_xor_expression
%type <astnode_expression>         bitwise_and_expression
%type <astnode_expression>         equality_expression
%type <astnode_expression>         relational_expression
%type <astnode_expression>         shift_expression
%type <astnode_expression>         additive_expression
%type <astnode_expression>         multiplicative_expression
%type <astnode_expression>         unary_expression
%type <astnode_expression>         postfix_expression
%type <astnode_expression>         primary_expression

%type <astnode_comma_list>         comma_list
%type <astnode_assoc_list>         assoc_list
%type <astnode_literal>            literal
%type <astnode_literal>            string_literal
%type <astnode_literal>            list_literal
%type <astnode_literal>            map_literal
%type <astnode_identifier>         identifier


/* parser entry point */
%start module


%%

/* \n* */
nws:
    %empty     { $$ = 0; }
    | nws "\n" { $$ = $1 + 1; }
    ;

/* \n+ */
nwp:
    "\n"       { $$ = 1; }
    | nwp "\n" { $$ = $1 + 1; }
    ;

/* (\n|;)+ */
trm:
    trm ";"    { $$ = $1; }
    | ";"      { $$ = 0; }
    | trm "\n" { $$ = $1 + 1; }
    | "\n"     { $$ = 1; }
    ;

/* Push module name to a stack */
module:
    { ast_ModuleStack_push(ast_Identifier(strdup("main"))); } program { ast_ModuleStack_pop(); }
    | "module" identifier trm { ast_ModuleStack_push($2); } program { ast_ModuleStack_pop(); }
    ;

/* A program is empty or a single procedure or multiple procedures */
program:
    %empty
    | program procedure
    ;

/* Map each module name to a map of procedures */
procedure:
    "proc" identifier "start" nwp statements "end" trm       { ast_util_ModuleAndProcTable_add(ast_ModuleStack_top(), $2, $5);
                                                                 ast_Identifier_destroy(&$2);
                                                             }
    ;

statements:
    %empty                                                   { $$ = NULL; }
    | statement statements                                   { $$ = ast_Statements($2, $1); }
    ;

statement:
    "pass" trm                                               { $$ = ast_Statement_empty(lex_line_no - $2); }
    | "break" trm                                            { $$ = ast_Statement_break(lex_line_no - $2); }
    | "continue" trm                                         { $$ = ast_Statement_continue(lex_line_no - $2); }
    | "return" expression trm                                { $$ = ast_Statement_return($2, lex_line_no - $3); }
    | "return" trm                                           { $$ = ast_Statement_return(NULL, lex_line_no - $2); }
    | assignment trm                                         { $$ = ast_Statement_Assignment($1, lex_line_no - $2); }
    | compound_statement trm                                 { $$ = ast_Statement_CompoundSt($1, lex_line_no - $2); }
    ;

assignment:
    "var" identifier "=" expression                          { $$ = ast_Assignment_create($2, $4); }   /* shadow or create new var */
    | "const" identifier "=" expression                      { $$ = ast_Assignment_mkconst($2, $4); }  /* create new constant */
    | expression                                             { $$ = ast_Assignment_tovoid($1); }       /* assignment to void */
    ;

compound_statement:
    if_block                                                 { $$ = ast_CompoundSt_IfBlock($1); }
    | while_block                                            { $$ = ast_CompoundSt_WhileBlock($1); }
    | for_block                                              { $$ = ast_CompoundSt_ForBlock($1); }
    | block                                                  { $$ = ast_CompoundSt_Block($1); }
    ;

if_block:
    "if" condition "then" nwp statements "end"               { $$ = ast_IfBlock($2, $5, NULL); }
    | "if" condition "then" nwp statements else_block        { $$ = ast_IfBlock($2, $5, $6); }
    ;

else_block:
    "else" nwp statements "end"                              { $$ = ast_ElseBlock(NULL, $3, NULL); }
    | "else" "if" condition "then" nwp statements "end"      { $$ = ast_ElseBlock($3, $6, NULL); }
    | "else" "if" condition "then" nwp statements else_block { $$ = ast_ElseBlock($3, $6, $7); }
    | "elif" condition "then" nwp statements "end"           { $$ = ast_ElseBlock($2, $5, NULL); }
    | "elif" condition "then" nwp statements else_block      { $$ = ast_ElseBlock($2, $5, $6); }
    ;

while_block:
    "while" condition "do" nwp statements "end"              { $$ = ast_WhileBlock($2, $5); }
    ;

for_block:
    "for" identifier "from" expression "to" expression "do" nwp statements "end"                   { $$ = ast_ForBlock($2, $4, $6, NULL, $9); }
    | "for" identifier "from" expression "to" expression "by" expression "do" nwp statements "end" { $$ = ast_ForBlock($2, $4, $6, $8, $11); }
    | "for" identifier "in" expression "do" nwp statements "end"                                   { $$ = ast_ForBlock_iterate(NULL, $2, $4, $7); }
    | "for" identifier "," identifier "in" expression "do" nwp statements "end"                    { $$ = ast_ForBlock_iterate($2, $4, $6, $9); }
    ;

block:
    "block" nwp statements "end"                             { $$ = ast_Block($3); }
    ;

condition:
    conditional_expression                                   { $$ = $1; }
    ;

expression:
    assignment_expression                                    { $$ = $1; }
    ;

assignment_expression:
    conditional_expression                                   { $$ = $1; }
    | postfix_expression "=" assignment_expression           { $$ = ast_Expression($2, $1, $3, NULL); }
    | postfix_expression "||=" assignment_expression         { $$ = ast_Expression($2, $1, $3, NULL); }
    | postfix_expression "&&=" assignment_expression         { $$ = ast_Expression($2, $1, $3, NULL); }
    | postfix_expression "|=" assignment_expression          { $$ = ast_Expression($2, $1, $3, NULL); }
    | postfix_expression "^=" assignment_expression          { $$ = ast_Expression($2, $1, $3, NULL); }
    | postfix_expression "&=" assignment_expression          { $$ = ast_Expression($2, $1, $3, NULL); }
    | postfix_expression ">>>=" assignment_expression        { $$ = ast_Expression($2, $1, $3, NULL); }
    | postfix_expression "<<=" assignment_expression         { $$ = ast_Expression($2, $1, $3, NULL); }
    | postfix_expression ">>=" assignment_expression         { $$ = ast_Expression($2, $1, $3, NULL); }
    | postfix_expression "+=" assignment_expression          { $$ = ast_Expression($2, $1, $3, NULL); }
    | postfix_expression "-=" assignment_expression          { $$ = ast_Expression($2, $1, $3, NULL); }
    | postfix_expression "*=" assignment_expression          { $$ = ast_Expression($2, $1, $3, NULL); }
    | postfix_expression "/=" assignment_expression          { $$ = ast_Expression($2, $1, $3, NULL); }
    | postfix_expression "%=" assignment_expression          { $$ = ast_Expression($2, $1, $3, NULL); }
    | postfix_expression "**=" assignment_expression         { $$ = ast_Expression($2, $1, $3, NULL); }
    | postfix_expression "//=" assignment_expression         { $$ = ast_Expression($2, $1, $3, NULL); }
    ;

conditional_expression:
    logical_or_expression                                    { $$ = $1; }
    | conditional_expression "if" condition "else" conditional_expression { $$ = ast_Expression(TOKOP_TERNARY_COND, $1, $5, $3); }
    ;

logical_or_expression:
    logical_and_expression                                   { $$ = $1; }
    | logical_or_expression "||" logical_and_expression      { $$ = ast_Expression($2, $1, $3, NULL); }
    ;

logical_and_expression:
    bitwise_or_expression                                    { $$ = $1; }
    | logical_and_expression "&&" bitwise_or_expression      { $$ = ast_Expression($2, $1, $3, NULL); }
    ;

bitwise_or_expression:
    bitwise_xor_expression                                   { $$ = $1; }
    | bitwise_or_expression "|" bitwise_xor_expression       { $$ = ast_Expression($2, $1, $3, NULL); }
    ;

bitwise_xor_expression:
    bitwise_and_expression                                   { $$ = $1; }
    | bitwise_xor_expression "^" bitwise_and_expression      { $$ = ast_Expression($2, $1, $3, NULL); }
    ;

bitwise_and_expression:
    equality_expression                                      { $$ = $1; }
    | bitwise_and_expression "&" equality_expression         { $$ = ast_Expression($2, $1, $3, NULL); }
    ;

equality_expression:
    relational_expression                                    { $$ = $1; }
    | equality_expression "==" relational_expression         { $$ = ast_Expression($2, $1, $3, NULL); }
    | equality_expression "!=" relational_expression         { $$ = ast_Expression($2, $1, $3, NULL); }
    ;

relational_expression:
    shift_expression                                         { $$ = $1; }
    | relational_expression "<" shift_expression             { $$ = ast_Expression($2, $1, $3, NULL); }
    | relational_expression ">" shift_expression             { $$ = ast_Expression($2, $1, $3, NULL); }
    | relational_expression "<=" shift_expression            { $$ = ast_Expression($2, $1, $3, NULL); }
    | relational_expression ">=" shift_expression            { $$ = ast_Expression($2, $1, $3, NULL); }
    ;

shift_expression:
    additive_expression                                      { $$ = $1; }
    | shift_expression ">>>" additive_expression             { $$ = ast_Expression($2, $1, $3, NULL); }
    | shift_expression "<<" additive_expression              { $$ = ast_Expression($2, $1, $3, NULL); }
    | shift_expression ">>" additive_expression              { $$ = ast_Expression($2, $1, $3, NULL); }
    ;

additive_expression:
    multiplicative_expression                                { $$ = $1; }
    | additive_expression "+" multiplicative_expression      { $$ = ast_Expression($2, $1, $3, NULL); }
    | additive_expression "-" multiplicative_expression      { $$ = ast_Expression($2, $1, $3, NULL); }
    ;

multiplicative_expression:
    unary_expression                                         { $$ = $1; }
    | multiplicative_expression "*" unary_expression         { $$ = ast_Expression($2, $1, $3, NULL); }
    | multiplicative_expression "/" unary_expression         { $$ = ast_Expression($2, $1, $3, NULL); }
    | multiplicative_expression "%" unary_expression         { $$ = ast_Expression($2, $1, $3, NULL); }
    | unary_expression "**" multiplicative_expression        { $$ = ast_Expression($2, $1, $3, NULL); }
    | multiplicative_expression "//" unary_expression        { $$ = ast_Expression($2, $1, $3, NULL); }
    ;

unary_expression:
    postfix_expression                                       { $$ = $1; }
    | "+" unary_expression                                   { $$ = ast_Expression($1, NULL, $2, NULL); }
    | "-" unary_expression                                   { $$ = ast_Expression($1, NULL, $2, NULL); }
    | "!" unary_expression                                   { $$ = ast_Expression($1, NULL, $2, NULL); }
    | "~" unary_expression                                   { $$ = ast_Expression($1, NULL, $2, NULL); }
    | "++" unary_expression                                  { $$ = ast_Expression($1, NULL, $2, NULL); }
    | "--" unary_expression                                  { $$ = ast_Expression($1, NULL, $2, NULL); }
    ;

postfix_expression:
    primary_expression                                       { $$ = $1; }
    | postfix_expression "(" ")"                             { $$ = ast_Expression(TOKOP_FNCALL, $1, NULL, NULL); }
    | postfix_expression "(" nws comma_list ")"              { $$ = ast_Expression(TOKOP_FNCALL, $1,
                                                                 ast_Expression_CommaSepList($4), NULL);
                                                             }
    | postfix_expression "[" expression "]"                  { $$ = ast_Expression(TOKOP_INDEXING, $1, $3, NULL); }
    | "$" "[" expression "]"                                 { $$ = ast_Expression(TOKOP_FNARGS_INDEXING, NULL, $3, NULL); }
    | "$" "(" expression ")"                                 { $$ = ast_Expression(TOKOP_FNARGS_INDEXING, NULL, $3, NULL); }
    | "$" TOKEN_DECINT_LITERAL                               { $$ = ast_Expression(TOKOP_FNARGS_INDEXING, NULL,
                                                                 ast_Expression_Literal(
                                                                     ast_Literal_i64($2)), NULL);
                                                             }
    | "$" identifier                                         { $$ = ast_Expression(TOKOP_FNARGS_INDEXING, NULL,
                                                                 ast_Expression_Identifier($2), NULL);
                                                             }
    | postfix_expression "++"                                { $$ = ast_Expression($2, $1, NULL, NULL); }
    | postfix_expression "--"                                { $$ = ast_Expression($2, $1, NULL, NULL); }
    | postfix_expression "." identifier                      { $$ = ast_Expression($2, $1,
                                                                 ast_Expression_Identifier($3), NULL);
                                                             }
    | postfix_expression "::" identifier                     { $$ = ast_Expression($2, $1,
                                                                 ast_Expression_Identifier($3), NULL);
                                                             }
    | postfix_expression ":" identifier                      { $$ = ast_Expression(TOKEN_DCOLON, $1,
                                                                 ast_Expression_Identifier($3), NULL);
                                                             }
    ;

primary_expression:
    literal                                                  { $$ = ast_Expression_Literal($1); }
    | identifier                                             { $$ = ast_Expression_Identifier($1); }
    | "(" expression ")"                                     { $$ = $2; }
    ;

comma_list:
    expression nws                                           { $$ = ast_CommaSepList(NULL, $1); }
    | expression "," nws                                     { $$ = ast_CommaSepList(NULL, $1); }
    | expression "," nws comma_list                          { $$ = ast_CommaSepList($4, $1); }
    ;

assoc_list:
    string_literal ":" expression nws                        { $$ = ast_AssociativeList(NULL, $1, $3); }
    | string_literal ":" expression "," nws                  { $$ = ast_AssociativeList(NULL, $1, $3); }
    | string_literal ":" expression "," nws assoc_list       { $$ = ast_AssociativeList($6, $1, $3); }
    ;

literal:
    TOKEN_BOOL_LITERAL                                       { $$ = ast_Literal_bul($1); }
    | TOKEN_CHAR_LITERAL                                     { $$ = ast_Literal_chr($1); }
    | TOKEN_BINFLOAT_LITERAL                                 { $$ = ast_Literal_f64($1); }
    | TOKEN_OCTFLOAT_LITERAL                                 { $$ = ast_Literal_f64($1); }
    | TOKEN_DECFLOAT_LITERAL                                 { $$ = ast_Literal_f64($1); }
    | TOKEN_HEXFLOAT_LITERAL                                 { $$ = ast_Literal_f64($1); }
    | TOKEN_BININT_LITERAL                                   { $$ = ast_Literal_i64($1); }
    | TOKEN_OCTINT_LITERAL                                   { $$ = ast_Literal_i64($1); }
    | TOKEN_DECINT_LITERAL                                   { $$ = ast_Literal_i64($1); }
    | TOKEN_HEXINT_LITERAL                                   { $$ = ast_Literal_i64($1); }
    | string_literal                                         { $$ = $1; }
    | list_literal                                           { $$ = $1; }
    | map_literal                                            { $$ = $1; }
    ;

string_literal:
    TOKEN_STR_LITERAL                                        { $$ = ast_Literal_str($1); }
    | TOKEN_INTERP_STR_LITERAL                               { $$ = ast_Literal_interp_str($1); }
    ;

list_literal:
    "[" "]"                                                  { $$ = ast_Literal_lst(NULL); }
    | "[" nws comma_list "]"                                 { $$ = ast_Literal_lst($3); }
    ;

map_literal:
    "{" "}"                                                  { $$ = ast_Literal_map(NULL); }
    | "{" nws assoc_list "}"                                 { $$ = ast_Literal_map($3); }
    ;

identifier:
    TOKEN_IDENTIFIER                                         { $$ = ast_Identifier($1); }
    ;

%%

#include "parser/parse_bool.c.h"
#include "parser/parse_chr.c.h"
#include "parser/parse_f64.c.h"
#include "parser/parse_i64.c.h"
#include "parser/parse_str.c.h"

int yyerror(const char* msg)
{
    parse_throw(msg, true);
    return ERR_PARSER;
}

void parse_interpret(FILE *f)
{
    yyin = f;
    if (yyin == stdin) printf(
        "Welcome to Shsc Version %s\n"
        "Enter your code and when done, press CTRL+D\n"
        "%s", VERSION, ">> "
    );
#ifdef LEX_DEBUG
    lex_Token_t tok = lex_Token_getnext(yyin);
    while (tok != TOKEN_EOF) {
        printf("%s: %s\n", lex_Token_getcode(tok), lex_Token_getsymbol(tok));
        tok = lex_Token_getnext(f);
    }
    printf("%s\n", lex_Token_getcode(tok));
#else
    yyparse();
#endif
    lex_Buffer_free();
}

void parse_throw(const char *msg, bool on)
{
    if (!msg) abort();
    int line = lex_line_no;
    if (lex_currtok == TOKEN_NEWLINE) --line;
    if (on) io_print_srcerr(line, lex_char_no, "parsing error: %s on '%s'", msg, lex_Token_getsymbol(lex_currtok));
    else io_print_srcerr(line, lex_char_no, "parsing error: %s", msg);
    exit(ERR_PARSER);
}
