%{

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

%token <tok> LEXTOK_BANG                              "!"
%token <tok> LEXTOK_LOGICAL_UNEQUAL                   "!="
%token <tok> LEXTOK_LOGICAL_UNIDENTICAL               "!=="
%token <tok> LEXTOK_DQUOTE                            '"'
%token <tok> LEXTOK_DOLLAR                            "$"
%token <tok> LEXTOK_PERCENT                           "%"
%token <tok> LEXTOK_MODULO_ASSIGN                     "%="
%token <tok> LEXTOK_AMPERSAND                         "&"
%token <tok> LEXTOK_LOGICAL_AND                       "&&"
%token <tok> LEXTOK_LOGICAL_AND_ASSIGN                "&&="
%token <tok> LEXTOK_BITWISE_AND_ASSIGN                "&="
%token <tok> LEXTOK_SQUOTE                            "'"
%token <tok> LEXTOK_LBRACE_PAREN                      "("
%token <tok> LEXTOK_RBRACE_PAREN                      ")"
%token <tok> LEXTOK_ASTERIX                           "*"
%token <tok> LEXTOK_EXPONENT                          "**"
%token <tok> LEXTOK_EXPONENT_ASSIGN                   "**="
%token <tok> LEXTOK_MULTIPLY_ASSIGN                   "*="
%token <tok> LEXTOK_PLUS                              "+"
%token <tok> LEXTOK_INCREMENT                         "++"
%token <tok> LEXTOK_ADD_ASSIGN                        "+="
%token <tok> LEXTOK_COMMA                             ","
%token <tok> LEXTOK_MINUS                             "-"
%token <tok> LEXTOK_DECREMENT                         "--"
%token <tok> LEXTOK_SUBSTRACT_ASSIGN                  "-="
%token <tok> LEXTOK_SARROW                            "->"
%token <tok> LEXTOK_DOT                               "."
%token <tok> LEXTOK_ELIPSIS                           "..."
%token <tok> LEXTOK_FSLASH                            "/"
%token <tok> LEXTOK_FLOOR_DIVIDE                      "//"
%token <tok> LEXTOK_FLOOR_DIVIDE_ASSIGN               "//="
%token <tok> LEXTOK_DIVIDE_ASSIGN                     "/="
%token <tok> LEXTOK_COLON                             ":"
%token <tok> LEXTOK_DCOLON                            "::"
%token <tok> LEXTOK_SEMICOLON                         ";"
%token <tok> LEXTOK_LBRACE_ANGULAR                    "<"
%token <tok> LEXTOK_BITWISE_LSHIFT                    "<<"
%token <tok> LEXTOK_BITWISE_LSHIFT_ASSIGN             "<<="
%token <tok> LEXTOK_LOGICAL_LESSER_EQUAL              "<="
%token <tok> LEXTOK_ASSIGN                            "="
%token <tok> LEXTOK_LOGICAL_EQUAL                     "=="
%token <tok> LEXTOK_LOGICAL_IDENTICAL                 "==="
%token <tok> LEXTOK_DARROW                            "=>"
%token <tok> LEXTOK_RBRACE_ANGULAR                    ">"
%token <tok> LEXTOK_LOGICAL_GREATER_EQUAL             ">="
%token <tok> LEXTOK_BITWISE_RSHIFT                    ">>"
%token <tok> LEXTOK_BITWISE_RSHIFT_ASSIGN             ">>="
%token <tok> LEXTOK_ARITH_RSHIFT                      ">>>"
%token <tok> LEXTOK_ARITH_RSHIFT_ASSIGN               ">>>="
%token <tok> LEXTOK_QUESTION                          "?"
%token <tok> LEXTOK_AT                                "@"
%token <tok> LEXTOK_LBRACE_SQUARE                     "["
%token <tok> LEXTOK_BSLASH                            "\\"
%token <tok> LEXTOK_RBRACE_SQUARE                     "]"
%token <tok> LEXTOK_CARET                             "^"
%token <tok> LEXTOK_BITWISE_XOR_ASSIGN                "^="
%token <tok> LEXTOK_BACKTICK                          "`"
%token <tok> LEXTOK_LBRACE_CURLY                      "{"
%token <tok> LEXTOK_PIPE                              "|"
%token <tok> LEXTOK_BITWISE_OR_ASSIGN                 "|="
%token <tok> LEXTOK_PIPEOUT                           "|>"
%token <tok> LEXTOK_LOGICAL_OR                        "||"
%token <tok> LEXTOK_LOGICAL_OR_ASSIGN                 "||="
%token <tok> LEXTOK_RBRACE_CURLY                      "}"
%token <tok> LEXTOK_TILDE                             "~"

/* special operation values */
%token TOKOP_NOP
%token TOKOP_FNCALL
%token TOKOP_INDEXING
%token TOKOP_TERNARY_COND
%token TOKOP_FNARGS_INDEXING

%token LEXTOK_NEWLINE                                 "\n"

/* keywords */
%token LEXTOK_KWD_MODULE                              "module"
%token LEXTOK_KWD_PROC                                "proc"
%token LEXTOK_KWD_START                               "start"
%token LEXTOK_KWD_END                                 "end"
%token LEXTOK_KWD_BLOCK                               "block"
%token LEXTOK_KWD_IF                                  "if"
%token LEXTOK_KWD_THEN                                "then"
%token LEXTOK_KWD_ELIF                                "elif"
%token LEXTOK_KWD_ELSE                                "else"
%token LEXTOK_KWD_WHILE                               "while"
%token LEXTOK_KWD_BREAK                               "break"
%token LEXTOK_KWD_CONTINUE                            "continue"
%token LEXTOK_KWD_FOR                                 "for"
%token LEXTOK_KWD_FROM                                "from"
%token LEXTOK_KWD_TO                                  "to"
%token LEXTOK_KWD_BY                                  "by"
%token LEXTOK_KWD_IN                                  "in"
%token LEXTOK_KWD_DO                                  "do"
%token LEXTOK_KWD_VAR                                 "var"
%token LEXTOK_KWD_PASS                                "pass"
%token LEXTOK_KWD_RETURN                              "return"

/* default cases */
%token LEXTOK_EOF 0                                   "<eof>"
%token LEXTOK_INVALID                                 "<invalid>"

/* literals */
%token <literal_bool> LEXTOK_BOOL_LITERAL             "<boollit>"
%token <literal_char> LEXTOK_CHAR_LITERAL             "<charlit>"
%token <literal_f64>  LEXTOK_BINFLOAT_LITERAL         "<binfloattlit>"
%token <literal_f64>  LEXTOK_OCTFLOAT_LITERAL         "<octfloattlit>"
%token <literal_f64>  LEXTOK_DECFLOAT_LITERAL         "<decfloattlit>"
%token <literal_f64>  LEXTOK_HEXFLOAT_LITERAL         "<hexfloattlit>"
%token <literal_i64>  LEXTOK_BININT_LITERAL           "<binintlit>"
%token <literal_i64>  LEXTOK_OCTINT_LITERAL           "<octintlit>"
%token <literal_i64>  LEXTOK_DECINT_LITERAL           "<decintlit>"
%token <literal_i64>  LEXTOK_HEXINT_LITERAL           "<hexintlit>"
%token <literal_str>  LEXTOK_STR_LITERAL              "<strlit>"
%token <literal_str>  LEXTOK_INTERP_STR_LITERAL       "<interpstrlit>"

/* identifier */
%token <identifier_name> LEXTOK_IDENTIFIER            "<identifier>"

%precedence LEXTOK_PERCENT
%precedence LEXTOK_ASTERIX
%precedence LEXTOK_EXPONENT
%precedence LEXTOK_FSLASH
%precedence LEXTOK_FLOOR_DIVIDE

%precedence LEXTOK_KWD_IF
%precedence LEXTOK_KWD_ELSE

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
    AST_Statements_t       *astnode_statements;           /* statements */
    AST_Statement_t        *astnode_statement;            /* statement */
    AST_Assignment_t       *astnode_assignment;           /* assignment */
    AST_CompoundSt_t       *astnode_compound_statement;   /* compound_statement */
    AST_IfBlock_t          *astnode_if_block;             /* if_block */
    AST_ElseBlock_t        *astnode_else_block;           /* else_block */
    AST_WhileBlock_t       *astnode_while_block;          /* while_block */
    AST_ForBlock_t         *astnode_for_block;            /* for_block */
    AST_Block_t            *astnode_block;                /* block */
    AST_Expression_t       *astnode_expression;           /* expression */
    AST_CommaSepList_t     *astnode_comma_list;           /* comma_list */
    AST_AssociativeList_t  *astnode_assoc_list;           /* assoc_list */
    AST_Literal_t          *astnode_literal;              /* literal */
    AST_Identifier_t       *astnode_identifier;           /* identifier */
}


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
    { AST_ModuleStack_push(AST_Identifier(strdup("main"))); } program { AST_ModuleStack_pop(); }
    | "module" identifier trm { AST_ModuleStack_push($2); } program { AST_ModuleStack_pop(); }
    ;

/* A program is empty or a single procedure or multiple procedures */
program:
    %empty
    | program procedure
    ;

/* Map each module name to a map of procedures */
procedure:
    "proc" identifier "start" nwp statements "end" trm  { AST_util_ModuleAndProcTable_add(AST_ModuleStack_top(), $2, $5);
                                                            AST_Identifier_destroy(&$2);
                                                        }
    ;

statements:
    %empty                                              { $$ = NULL; }
    | statement statements                              { $$ = AST_Statements($2, $1); }
    ;

statement:
    "pass" trm                                          { $$ = AST_Statement_empty(lex_line_no - $2); }
    | "break" trm                                       { $$ = AST_Statement_break(lex_line_no - $2); }
    | "continue" trm                                    { $$ = AST_Statement_continue(lex_line_no - $2); }
    | "return" expression trm                           { $$ = AST_Statement_return($2, lex_line_no - $3); }
    | "return" trm                                      { $$ = AST_Statement_return(NULL, lex_line_no - $2); }
    | assignment trm                                    { $$ = AST_Statement_Assignment($1, lex_line_no - $2); }
    | compound_statement trm                            { $$ = AST_Statement_CompoundSt($1, lex_line_no - $2); }
    ;

assignment:
    "var" identifier "=" expression                     { $$ = AST_Assignment_create($2, $4); } /* shadow or create new var */
    | expression                                        { $$ = AST_Assignment_tovoid($1); }     /* assignment to void */
    ;

compound_statement:
    if_block                                            { $$ = AST_CompoundSt_IfBlock($1); }
    | while_block                                       { $$ = AST_CompoundSt_WhileBlock($1); }
    | for_block                                         { $$ = AST_CompoundSt_ForBlock($1); }
    | block                                             { $$ = AST_CompoundSt_Block($1); }
    ;

if_block:
    "if" condition "then" nwp statements "end"          { $$ = AST_IfBlock($2, $5, NULL); }
    | "if" condition "then" nwp statements else_block   { $$ = AST_IfBlock($2, $5, $6); }
    ;

else_block:
    "else" nwp statements "end"                              { $$ = AST_ElseBlock(NULL, $3, NULL); }
    | "else" "if" condition "then" nwp statements "end"      { $$ = AST_ElseBlock($3, $6, NULL); }
    | "else" "if" condition "then" nwp statements else_block { $$ = AST_ElseBlock($3, $6, $7); }
    | "elif" condition "then" nwp statements "end"           { $$ = AST_ElseBlock($2, $5, NULL); }
    | "elif" condition "then" nwp statements else_block      { $$ = AST_ElseBlock($2, $5, $6); }
    ;

while_block:
    "while" condition "do" nwp statements "end"         { $$ = AST_WhileBlock($2, $5); }
    ;

for_block:
    "for" identifier "from" expression "to" expression "do" nwp statements "end"                   { $$ = AST_ForBlock($2, $4, $6, NULL, $9); }
    | "for" identifier "from" expression "to" expression "by" expression "do" nwp statements "end" { $$ = AST_ForBlock($2, $4, $6, $8, $11); }
    | "for" identifier "in" expression "do" nwp statements "end"                                   { $$ = AST_ForBlock_iterate(NULL, $2, $4, $7); }
    | "for" identifier "," identifier "in" expression "do" nwp statements "end"                    { $$ = AST_ForBlock_iterate($2, $4, $6, $9); }
    ;

block:
    "block" nwp statements "end"                        { $$ = AST_Block($3); }
    ;

condition:
    conditional_expression                              { $$ = $1; }
    ;

expression:
    assignment_expression                               { $$ = $1; }
    ;

assignment_expression:
    conditional_expression                              { $$ = $1; }
    | postfix_expression "=" assignment_expression      { $$ = AST_Expression($2, $1, $3, NULL); }
    | postfix_expression "||=" assignment_expression    { $$ = AST_Expression($2, $1, $3, NULL); }
    | postfix_expression "&&=" assignment_expression    { $$ = AST_Expression($2, $1, $3, NULL); }
    | postfix_expression "|=" assignment_expression     { $$ = AST_Expression($2, $1, $3, NULL); }
    | postfix_expression "^=" assignment_expression     { $$ = AST_Expression($2, $1, $3, NULL); }
    | postfix_expression "&=" assignment_expression     { $$ = AST_Expression($2, $1, $3, NULL); }
    | postfix_expression ">>>=" assignment_expression   { $$ = AST_Expression($2, $1, $3, NULL); }
    | postfix_expression "<<=" assignment_expression    { $$ = AST_Expression($2, $1, $3, NULL); }
    | postfix_expression ">>=" assignment_expression    { $$ = AST_Expression($2, $1, $3, NULL); }
    | postfix_expression "+=" assignment_expression     { $$ = AST_Expression($2, $1, $3, NULL); }
    | postfix_expression "-=" assignment_expression     { $$ = AST_Expression($2, $1, $3, NULL); }
    | postfix_expression "*=" assignment_expression     { $$ = AST_Expression($2, $1, $3, NULL); }
    | postfix_expression "/=" assignment_expression     { $$ = AST_Expression($2, $1, $3, NULL); }
    | postfix_expression "%=" assignment_expression     { $$ = AST_Expression($2, $1, $3, NULL); }
    | postfix_expression "**=" assignment_expression    { $$ = AST_Expression($2, $1, $3, NULL); }
    | postfix_expression "//=" assignment_expression    { $$ = AST_Expression($2, $1, $3, NULL); }
    ;

conditional_expression:
    logical_or_expression                               { $$ = $1; }
    | conditional_expression "if" condition "else" conditional_expression { $$ = AST_Expression(TOKOP_TERNARY_COND, $1, $5, $3); }
    ;

logical_or_expression:
    logical_and_expression                              { $$ = $1; }
    | logical_or_expression "||" logical_and_expression { $$ = AST_Expression($2, $1, $3, NULL); }
    ;

logical_and_expression:
    bitwise_or_expression                               { $$ = $1; }
    | logical_and_expression "&&" bitwise_or_expression { $$ = AST_Expression($2, $1, $3, NULL); }
    ;

bitwise_or_expression:
    bitwise_xor_expression                              { $$ = $1; }
    | bitwise_or_expression "|" bitwise_xor_expression  { $$ = AST_Expression($2, $1, $3, NULL); }
    ;

bitwise_xor_expression:
    bitwise_and_expression                              { $$ = $1; }
    | bitwise_xor_expression "^" bitwise_and_expression { $$ = AST_Expression($2, $1, $3, NULL); }
    ;

bitwise_and_expression:
    equality_expression                                 { $$ = $1; }
    | bitwise_and_expression "&" equality_expression    { $$ = AST_Expression($2, $1, $3, NULL); }
    ;

equality_expression:
    relational_expression                               { $$ = $1; }
    | equality_expression "==" relational_expression    { $$ = AST_Expression($2, $1, $3, NULL); }
    | equality_expression "!=" relational_expression    { $$ = AST_Expression($2, $1, $3, NULL); }
    ;

relational_expression:
    shift_expression                                    { $$ = $1; }
    | relational_expression "<" shift_expression        { $$ = AST_Expression($2, $1, $3, NULL); }
    | relational_expression ">" shift_expression        { $$ = AST_Expression($2, $1, $3, NULL); }
    | relational_expression "<=" shift_expression       { $$ = AST_Expression($2, $1, $3, NULL); }
    | relational_expression ">=" shift_expression       { $$ = AST_Expression($2, $1, $3, NULL); }
    ;

shift_expression:
    additive_expression                                 { $$ = $1; }
    | shift_expression ">>>" additive_expression        { $$ = AST_Expression($2, $1, $3, NULL); }
    | shift_expression "<<" additive_expression         { $$ = AST_Expression($2, $1, $3, NULL); }
    | shift_expression ">>" additive_expression         { $$ = AST_Expression($2, $1, $3, NULL); }
    ;

additive_expression:
    multiplicative_expression                           { $$ = $1; }
    | additive_expression "+" multiplicative_expression { $$ = AST_Expression($2, $1, $3, NULL); }
    | additive_expression "-" multiplicative_expression { $$ = AST_Expression($2, $1, $3, NULL); }
    ;

multiplicative_expression:
    unary_expression                                    { $$ = $1; }
    | multiplicative_expression "*" unary_expression    { $$ = AST_Expression($2, $1, $3, NULL); }
    | multiplicative_expression "/" unary_expression    { $$ = AST_Expression($2, $1, $3, NULL); }
    | multiplicative_expression "%" unary_expression    { $$ = AST_Expression($2, $1, $3, NULL); }
    | unary_expression "**" multiplicative_expression   { $$ = AST_Expression($2, $1, $3, NULL); }
    | multiplicative_expression "//" unary_expression   { $$ = AST_Expression($2, $1, $3, NULL); }
    ;

unary_expression:
    postfix_expression                                  { $$ = $1; }
    | "+" unary_expression                              { $$ = AST_Expression($1, NULL, $2, NULL); }
    | "-" unary_expression                              { $$ = AST_Expression($1, NULL, $2, NULL); }
    | "!" unary_expression                              { $$ = AST_Expression($1, NULL, $2, NULL); }
    | "~" unary_expression                              { $$ = AST_Expression($1, NULL, $2, NULL); }
    | "++" unary_expression                             { $$ = AST_Expression($1, NULL, $2, NULL); }
    | "--" unary_expression                             { $$ = AST_Expression($1, NULL, $2, NULL); }
    ;

postfix_expression:
    primary_expression                                  { $$ = $1; }
    | postfix_expression "(" ")"                        { $$ = AST_Expression(TOKOP_FNCALL, $1, NULL, NULL); }
    | postfix_expression "(" nws comma_list ")"         { $$ = AST_Expression(TOKOP_FNCALL, $1,
                                                            AST_Expression_CommaSepList($4), NULL);
                                                        }
    | postfix_expression "[" expression "]"             { $$ = AST_Expression(TOKOP_INDEXING, $1, $3, NULL); }
    | "$" "[" expression "]"                            { $$ = AST_Expression(TOKOP_FNARGS_INDEXING, NULL, $3, NULL); }
    | "$" "(" expression ")"                            { $$ = AST_Expression(TOKOP_FNARGS_INDEXING, NULL, $3, NULL); }
    | "$" LEXTOK_DECINT_LITERAL                         { $$ = AST_Expression(TOKOP_FNARGS_INDEXING, NULL,
                                                            AST_Expression_Literal(
                                                                AST_Literal_i64($2)), NULL);
                                                        }
    | "$" identifier                                    { $$ = AST_Expression(TOKOP_FNARGS_INDEXING, NULL,
                                                            AST_Expression_Identifier($2), NULL);
                                                        }
    | postfix_expression "++"                           { $$ = AST_Expression($2, $1, NULL, NULL); }
    | postfix_expression "--"                           { $$ = AST_Expression($2, $1, NULL, NULL); }
    | postfix_expression "." identifier                 { $$ = AST_Expression($2, $1,
                                                            AST_Expression_Identifier($3), NULL);
                                                        }
    | postfix_expression "::" identifier                { $$ = AST_Expression($2, $1,
                                                            AST_Expression_Identifier($3), NULL);
                                                        }
    | postfix_expression ":" identifier                 { $$ = AST_Expression(LEXTOK_DCOLON, $1,
                                                            AST_Expression_Identifier($3), NULL);
                                                        }
    ;

primary_expression:
    literal                                             { $$ = AST_Expression_Literal($1); }
    | identifier                                        { $$ = AST_Expression_Identifier($1); }
    | "(" expression ")"                                { $$ = $2; }
    ;

comma_list:
    expression nws                                      { $$ = AST_CommaSepList(NULL, $1); }
    | expression "," nws                                { $$ = AST_CommaSepList(NULL, $1); }
    | expression "," nws comma_list                     { $$ = AST_CommaSepList($4, $1); }
    ;

assoc_list:
    string_literal ":" expression nws                   { $$ = AST_AssociativeList(NULL, $1, $3); }
    | string_literal ":" expression "," nws             { $$ = AST_AssociativeList(NULL, $1, $3); }
    | string_literal ":" expression "," nws assoc_list  { $$ = AST_AssociativeList($6, $1, $3); }
    ;

literal:
    LEXTOK_BOOL_LITERAL                                 { $$ = AST_Literal_bul($1); }
    | LEXTOK_CHAR_LITERAL                               { $$ = AST_Literal_chr($1); }
    | LEXTOK_BINFLOAT_LITERAL                           { $$ = AST_Literal_f64($1); }
    | LEXTOK_OCTFLOAT_LITERAL                           { $$ = AST_Literal_f64($1); }
    | LEXTOK_DECFLOAT_LITERAL                           { $$ = AST_Literal_f64($1); }
    | LEXTOK_HEXFLOAT_LITERAL                           { $$ = AST_Literal_f64($1); }
    | LEXTOK_BININT_LITERAL                             { $$ = AST_Literal_i64($1); }
    | LEXTOK_OCTINT_LITERAL                             { $$ = AST_Literal_i64($1); }
    | LEXTOK_DECINT_LITERAL                             { $$ = AST_Literal_i64($1); }
    | LEXTOK_HEXINT_LITERAL                             { $$ = AST_Literal_i64($1); }
    | string_literal                                    { $$ = $1; }
    | list_literal                                      { $$ = $1; }
    | map_literal                                       { $$ = $1; }
    ;

string_literal:
    LEXTOK_STR_LITERAL                                  { $$ = AST_Literal_str($1); }
    | LEXTOK_INTERP_STR_LITERAL                         { $$ = AST_Literal_interp_str($1); }
    ;

list_literal:
    "[" "]"                                             { $$ = AST_Literal_lst(NULL); }
    | "[" nws comma_list "]"                            { $$ = AST_Literal_lst($3); }
    ;

map_literal:
    "{" "}"                                             { $$ = AST_Literal_map(NULL); }
    | "{" nws assoc_list "}"                            { $$ = AST_Literal_map($3); }
    ;

identifier:
    LEXTOK_IDENTIFIER                                   { $$ = AST_Identifier($1); }
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
    LexToken tok = lex_get_nexttok(yyin);
    while (tok != LEXTOK_EOF) {
        printf("%s: %s\n", lex_get_tokcode(tok), lex_get_symbol(tok));
        tok = lex_get_nexttok(f);
    }
    printf("%s\n", lex_get_tokcode(tok));
#else
    yyparse();
#endif
    lex_buffree();
}

void parse_throw(const char *msg, bool on)
{
    if (!msg) abort();
    int line = lex_line_no;
    if (lex_currtok == LEXTOK_NEWLINE) --line;
    if (on) io_print_srcerr(line, lex_char_no, "parsing error: %s on '%s'", msg, lex_get_symbol(lex_currtok));
    else io_print_srcerr(line, lex_char_no, "parsing error: %s", msg);
    exit(ERR_PARSER);
}
