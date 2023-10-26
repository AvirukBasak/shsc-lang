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

/* \n* left recursive -----------------------------------------------------------------------------
nws:
    %empty
    | nws "\n"
    ; */

/* \n* right recursive */
nws:
    %empty nws_p
    ;
nws_p:
    %empty
    | "\n" nws_p
    ;



/* \n+ left recursive -----------------------------------------------------------------------------
nwp:
    "\n"
    | nwp "\n"
    ; */

/* \n+ right recursive */
nwp:
    "\n" nwp_p
    ;
nwp_p:
    %empty
    | "\n" nwp_p
    ;



/* (\n|;)+ left recursive -------------------------------------------------------------------------
trm:
    ";"
    | "\n"
    | trm ";"
    | trm "\n"
    ; */

/* (\n|;)+ right recursive */
trm:
    | ";" trm_p
    | "\n" trm_p
    ;
trm_p:
    %empty
    | ";" trm_p
    | "\n" trm_p
    ;



/* Push module name to a stack --------------------------------------------------------------------
   non-recursive grammar */
module:
    program
    | "module" identifier trm program
    ;



/* A program is empty or a single procedure or multiple procedures --------------------------------
   left recursive grammar
program:
    %empty
    | program procedure
    ; */

/* right recursive grammar */
program:
    %empty program_p
    ;
program_p:
    %empty
    | procedure program_p
    ;



/* Map each module name to a map of procedures ----------------------------------------------------
   non-recursive grammer */
procedure:
    "proc" identifier "start" nwp statements "end" trm
    ;



/* A list of statements ---------------------------------------------------------------------------
   right recursive grammar */
statements:
    %empty
    | statement statements
    ;



/* A single statement -----------------------------------------------------------------------------
   non-recursive grammar */
statement:
    "pass" trm
    | "break" trm
    | "continue" trm
    | "return" expression trm
    | "return" trm
    | assignment trm
    | compound_statement trm
    ;



/* A single assignment ----------------------------------------------------------------------------
   non-recursive grammar */
assignment:
    "var" identifier "=" expression      /* shadow or create new var */
    | "const" identifier "=" expression  /* create new constant */
    | expression                         /* assignment to void */
    ;



/* A compound statement ---------------------------------------------------------------------------
   non-recursive grammar */
compound_statement:
    if_block
    | while_block
    | for_block
    | block
    ;



/* An if statement --------------------------------------------------------------------------------
   non-recursive grammar */
if_block:
    "if" condition "then" nwp statements "end"
    | "if" condition "then" nwp statements else_block
    ;



/* An else block ----------------------------------------------------------------------------------
   minorly right-recursive grammar */
else_block:
    "else" nwp statements "end"
    | "else" "if" condition "then" nwp statements "end"
    | "elif" condition "then" nwp statements "end"
    | "else" "if" condition "then" nwp statements else_block
    | "elif" condition "then" nwp statements else_block
    ;



/* A while block ----------------------------------------------------------------------------------
   non-recursive grammar */
while_block:
    "while" condition "do" nwp statements "end"
    ;



/* A for block ------------------------------------------------------------------------------------
   non-recursive grammar */
for_block:
    "for" identifier "from" expression "to" expression "do" nwp statements "end"
    | "for" identifier "from" expression "to" expression "by" expression "do" nwp statements "end"
    | "for" identifier "in" expression "do" nwp statements "end"
    | "for" identifier "," identifier "in" expression "do" nwp statements "end"
    ;



/* A block ----------------------------------------------------------------------------------------
   non-recursive grammar */
block:
    "block" nwp statements "end"
    ;



/* A condition ------------------------------------------------------------------------------------
   non-recursive grammar */
condition:
    conditional_expression
    ;



/* An expression ----------------------------------------------------------------------------------
   non-recursive grammar */
expression:
    assignment_expression
    ;



/* An assignment expression -----------------------------------------------------------------------
   right-recursive grammar */
assignment_expression:
    conditional_expression
    | postfix_expression "=" assignment_expression
    | postfix_expression "||=" assignment_expression
    | postfix_expression "&&=" assignment_expression
    | postfix_expression "|=" assignment_expression
    | postfix_expression "^=" assignment_expression
    | postfix_expression "&=" assignment_expression
    | postfix_expression ">>>=" assignment_expression
    | postfix_expression "<<=" assignment_expression
    | postfix_expression ">>=" assignment_expression
    | postfix_expression "+=" assignment_expression
    | postfix_expression "-=" assignment_expression
    | postfix_expression "*=" assignment_expression
    | postfix_expression "/=" assignment_expression
    | postfix_expression "%=" assignment_expression
    | postfix_expression "**=" assignment_expression
    | postfix_expression "//=" assignment_expression
    ;



/* A conditional expression -----------------------------------------------------------------------
   left-recursive grammar
conditional_expression:
    logical_or_expression
    | conditional_expression "if" condition "else" conditional_expression
    ; */

/* right-recursive grammar */
conditional_expression:
    logical_or_expression conditional_expression_p
    ;
conditional_expression_p:
    %empty
    | "if" condition "else" conditional_expression conditional_expression_p
    ;



/* A logical or expression ------------------------------------------------------------------------
   left-recursive grammar
logical_or_expression:
    logical_and_expression
    | logical_or_expression "||" logical_and_expression
    ; */

/* right-recursive grammar */
logical_or_expression:
    logical_and_expression logical_or_expression_p
    ;
logical_or_expression_p:
    %empty
    | "||" logical_and_expression logical_or_expression_p
    ;



/* A logical and expression -----------------------------------------------------------------------
   left-recursive grammar
logical_and_expression:
    bitwise_or_expression
    | logical_and_expression "&&" bitwise_or_expression
    ; */

/* right-recursive grammar */
logical_and_expression:
    bitwise_or_expression logical_and_expression_p
    ;
logical_and_expression_p:
    %empty
    | "&&" bitwise_or_expression logical_and_expression_p
    ;



bitwise_or_expression:
    bitwise_xor_expression
    | bitwise_or_expression "|" bitwise_xor_expression
    ;

bitwise_xor_expression:
    bitwise_and_expression
    | bitwise_xor_expression "^" bitwise_and_expression
    ;

bitwise_and_expression:
    equality_expression
    | bitwise_and_expression "&" equality_expression
    ;

equality_expression:
    relational_expression
    | equality_expression "==" relational_expression
    | equality_expression "!=" relational_expression
    ;

relational_expression:
    shift_expression
    | relational_expression "<" shift_expression
    | relational_expression ">" shift_expression
    | relational_expression "<=" shift_expression
    | relational_expression ">=" shift_expression
    ;

shift_expression:
    additive_expression
    | shift_expression ">>>" additive_expression
    | shift_expression "<<" additive_expression
    | shift_expression ">>" additive_expression
    ;

additive_expression:
    multiplicative_expression
    | additive_expression "+" multiplicative_expression
    | additive_expression "-" multiplicative_expression
    ;



/* A multiplicative expression --------------------------------------------------------------------
   majorly left-recursive grammar
multiplicative_expression:
    unary_expression
    | unary_expression "**" multiplicative_expression
    | multiplicative_expression "*" unary_expression
    | multiplicative_expression "/" unary_expression
    | multiplicative_expression "%" unary_expression
    | multiplicative_expression "//" unary_expression
    ; */

/* right-recursive grammar */
multiplicative_expression:
    unary_expression multiplicative_expression_p
    unary_expression "**" multiplicative_expression multiplicative_expression_p
    ;
multiplicative_expression_p:
    %empty
    | "*" unary_expression multiplicative_expression_p
    | "/" unary_expression multiplicative_expression_p
    | "%" unary_expression multiplicative_expression_p
    | "//" unary_expression multiplicative_expression_p
    ;



/* A unary expression -----------------------------------------------------------------------------
   right-recursive grammar */
unary_expression:
    postfix_expression
    | "+" unary_expression
    | "-" unary_expression
    | "!" unary_expression
    | "~" unary_expression
    | "++" unary_expression
    | "--" unary_expression
    ;



/* A postfix expression ---------------------------------------------------------------------------
   left-recursive grammar
postfix_expression:
    primary_expression
    | "$" TOKEN_DECINT_LITERAL
    | "$" "[" expression "]"
    | "$" "(" expression ")"
    | "$" identifier
    | postfix_expression "(" ")"
    | postfix_expression "(" nws comma_list ")"
    | postfix_expression "[" expression "]"
    | postfix_expression "++"
    | postfix_expression "--"
    | postfix_expression "." identifier
    | postfix_expression "::" identifier
    | postfix_expression ":" identifier
    ; */

/* right-recursive grammar */
postfix_expression:
    primary_expression postfix_expression_p
    "$" TOKEN_DECINT_LITERAL postfix_expression_p
    "$" "[" expression "]" postfix_expression_p
    "$" "(" expression ")" postfix_expression_p
    "$" identifier postfix_expression_p
    ;
postfix_expression_p:
    %empty
    | "(" ")" postfix_expression_p
    | "(" nws comma_list ")" postfix_expression_p
    | "[" expression "]" postfix_expression_p
    | "++" postfix_expression_p
    | "--" postfix_expression_p
    | "." identifier postfix_expression_p
    | "::" identifier postfix_expression_p
    | ":" identifier postfix_expression_p
    ;



/* A primary expression ---------------------------------------------------------------------------
   non-recursive grammar */
primary_expression:
    literal
    | identifier
    | "(" expression ")"
    ;



/* A comma separated list -------------------------------------------------------------------------
   right-recursive grammar */
comma_list:
    expression nws
    | expression "," nws
    | expression "," nws comma_list
    ;



/* An associative list ----------------------------------------------------------------------------
   right-recursive grammar */
assoc_list:
    string_literal ":" expression nws
    | string_literal ":" expression "," nws
    | string_literal ":" expression "," nws assoc_list
    ;



/* A literal --------------------------------------------------------------------------------------
   non-recursive grammar */
literal:
    TOKEN_BOOL_LITERAL
    | TOKEN_CHAR_LITERAL
    | TOKEN_BINFLOAT_LITERAL
    | TOKEN_OCTFLOAT_LITERAL
    | TOKEN_DECFLOAT_LITERAL
    | TOKEN_HEXFLOAT_LITERAL
    | TOKEN_BININT_LITERAL
    | TOKEN_OCTINT_LITERAL
    | TOKEN_DECINT_LITERAL
    | TOKEN_HEXINT_LITERAL
    | string_literal
    | list_literal
    | map_literal
    ;



/* A string literal -------------------------------------------------------------------------------
   non-recursive grammar */
string_literal:
    TOKEN_STR_LITERAL
    | TOKEN_INTERP_STR_LITERAL
    ;



/* A list literal ---------------------------------------------------------------------------------
   non-recursive grammar */
list_literal:
    "[" "]"
    | "[" nws comma_list "]"
    ;



/* A map literal ----------------------------------------------------------------------------------
   non-recursive grammar */
map_literal:
    "{" "}"
    | "{" nws assoc_list "}"
    ;



/* An identifier ----------------------------------------------------------------------------------
   non-recursive grammar */
identifier:
    TOKEN_IDENTIFIER
    ;

%%
