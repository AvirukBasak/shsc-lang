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

%token LEXTOK_BANG                     "!"
%token LEXTOK_LOGICAL_UNEQUAL          "!="
%token LEXTOK_LOGICAL_UNIDENTICAL      "!=="
%token LEXTOK_DQUOTE                   '"'
%token LEXTOK_DOLLAR                   "$"
%token LEXTOK_PERCENT                  "%"
%token LEXTOK_MODULO_ASSIGN            "%="
%token LEXTOK_AMPERSAND                "&"
%token LEXTOK_LOGICAL_AND              "&&"
%token LEXTOK_LOGICAL_AND_ASSIGN       "&&="
%token LEXTOK_BITWISE_AND_ASSIGN       "&="
%token LEXTOK_SQUOTE                   "'"
%token LEXTOK_LBRACE_PAREN             "("
%token LEXTOK_RBRACE_PAREN             ")"
%token LEXTOK_ASTERIX                  "*"
%token LEXTOK_EXPONENT                 "**"
%token LEXTOK_EXPONENT_ASSIGN          "**="
%token LEXTOK_MULTIPLY_ASSIGN          "*="
%token LEXTOK_PLUS                     "+"
%token LEXTOK_INCREMENT                "++"
%token LEXTOK_ADD_ASSIGN               "+="
%token LEXTOK_COMMA                    ","
%token LEXTOK_MINUS                    "-"
%token LEXTOK_DECREMENT                "--"
%token LEXTOK_SUBSTRACT_ASSIGN         "-="
%token LEXTOK_SARROW                   "->"
%token LEXTOK_DOT                      "."
%token LEXTOK_ELIPSIS                  "..."
%token LEXTOK_FSLASH                   "/"
%token LEXTOK_FLOOR_DIVIDE             "//"
%token LEXTOK_FLOOR_DIVIDE_ASSIGN      "//="
%token LEXTOK_DIVIDE_ASSIGN            "/="
%token LEXTOK_COLON                    ":"
%token LEXTOK_DCOLON                   "::"
%token LEXTOK_SEMICOLON                ";"
%token LEXTOK_LBRACE_ANGULAR           "<"
%token LEXTOK_BITWISE_LSHIFT           "<<"
%token LEXTOK_BITWISE_LSHIFT_ASSIGN    "<<="
%token LEXTOK_LOGICAL_LESSER_EQUAL     "<="
%token LEXTOK_ASSIGN                   "="
%token LEXTOK_LOGICAL_EQUAL            "=="
%token LEXTOK_LOGICAL_IDENTICAL        "==="
%token LEXTOK_DARROW                   "=>"
%token LEXTOK_RBRACE_ANGULAR           ">"
%token LEXTOK_LOGICAL_GREATER_EQUAL    ">="
%token LEXTOK_BITWISE_RSHIFT           ">>"
%token LEXTOK_BITWISE_RSHIFT_ASSIGN    ">>="
%token LEXTOK_ARITH_RSHIFT             ">>>"
%token LEXTOK_ARITH_RSHIFT_ASSIGN      ">>>="
%token LEXTOK_QUESTION                 "?"
%token LEXTOK_AT                       "@"
%token LEXTOK_LBRACE_SQUARE            "["
%token LEXTOK_BSLASH                   "\\"
%token LEXTOK_RBRACE_SQUARE            "]"
%token LEXTOK_CARET                    "^"
%token LEXTOK_BITWISE_XOR_ASSIGN       "^="
%token LEXTOK_BACKTICK                 "`"
%token LEXTOK_LBRACE_CURLY             "{"
%token LEXTOK_PIPE                     "|"
%token LEXTOK_BITWISE_OR_ASSIGN        "|="
%token LEXTOK_PIPEOUT                  "|>"
%token LEXTOK_LOGICAL_OR               "||"
%token LEXTOK_LOGICAL_OR_ASSIGN        "||="
%token LEXTOK_RBRACE_CURLY             "}"
%token LEXTOK_TILDE                    "~"

%token LEXTOK_NEWLINE                  "\n"

/* keywords */
%token LEXTOK_KWD_MODULE               "module"
%token LEXTOK_KWD_PROC                 "proc"
%token LEXTOK_KWD_START                "start"
%token LEXTOK_KWD_END                  "end"
%token LEXTOK_KWD_BLOCK                "block"
%token LEXTOK_KWD_IF                   "if"
%token LEXTOK_KWD_THEN                 "then"
%token LEXTOK_KWD_ELIF                 "elif"
%token LEXTOK_KWD_ELSE                 "else"
%token LEXTOK_KWD_WHILE                "while"
%token LEXTOK_KWD_BREAK                "break"
%token LEXTOK_KWD_CONTINUE             "continue"
%token LEXTOK_KWD_RETURN               "return"
%token LEXTOK_KWD_FOR                  "for"
%token LEXTOK_KWD_FROM                 "from"
%token LEXTOK_KWD_TO                   "to"
%token LEXTOK_KWD_BY                   "by"
%token LEXTOK_KWD_DO                   "do"
%token LEXTOK_KWD_VAR                  "var"
%token LEXTOK_KWD_PASS                 "pass"

/* default cases */
%token LEXTOK_EOF                      "<eof>"
%token LEXTOK_INVALID                  "<invalid>"

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

%left  LEXTOK_LOGICAL_UNEQUAL
%left  LEXTOK_LOGICAL_UNIDENTICAL
%left  LEXTOK_PERCENT
%left  LEXTOK_LOGICAL_AND
%left  LEXTOK_ASTERIX
%left  LEXTOK_PLUS
%left  LEXTOK_COMMA
%left  LEXTOK_MINUS
%left  LEXTOK_SARROW
%left  LEXTOK_DOT
%left  LEXTOK_ELIPSIS
%left  LEXTOK_FSLASH
%left  LEXTOK_FLOOR_DIVIDE
%left  LEXTOK_DCOLON
%left  LEXTOK_BITWISE_LSHIFT
%left  LEXTOK_LOGICAL_LESSER_EQUAL
%left  LEXTOK_LOGICAL_EQUAL
%left  LEXTOK_LOGICAL_IDENTICAL
%left  LEXTOK_LOGICAL_GREATER_EQUAL
%left  LEXTOK_BITWISE_RSHIFT
%left  LEXTOK_ARITH_RSHIFT
%left  LEXTOK_CARET
%left  LEXTOK_PIPE
%left  LEXTOK_PIPEOUT
%left  LEXTOK_LOGICAL_OR

%right LEXTOK_BANG
%right LEXTOK_MODULO_ASSIGN
%right LEXTOK_LOGICAL_AND_ASSIGN
%right LEXTOK_BITWISE_AND_ASSIGN
%right LEXTOK_EXPONENT
%right LEXTOK_EXPONENT_ASSIGN
%right LEXTOK_MULTIPLY_ASSIGN
%right LEXTOK_INCREMENT
%right LEXTOK_ADD_ASSIGN
%right LEXTOK_DECREMENT
%right LEXTOK_SUBSTRACT_ASSIGN
%right LEXTOK_FLOOR_DIVIDE_ASSIGN
%right LEXTOK_DIVIDE_ASSIGN
%right LEXTOK_BITWISE_LSHIFT_ASSIGN
%right LEXTOK_ASSIGN
%right LEXTOK_BITWISE_RSHIFT_ASSIGN
%right LEXTOK_ARITH_RSHIFT_ASSIGN
%right LEXTOK_BITWISE_XOR_ASSIGN
%right LEXTOK_BITWISE_OR_ASSIGN
%right LEXTOK_LOGICAL_OR_ASSIGN
%right LEXTOK_TILDE

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
    AST_Statements_t    *astnode_statements,           /* statements */
    AST_Statement_t     *astnode_statement,            /* statement */
    AST_Assignment_t    *astnode_assignment,           /* assignment */
    AST_CompoundSt_t    *astnode_compound_statement,   /* compound_statement */
    AST_IfBlock_t       *astnode_if_block,             /* if_block */
    AST_IfElseBlock_t   *astnode_if_else_block,        /* if_else_block */
    AST_IfElseIfBlock_t *astnode_if_else_if_block,     /* if_else_if_block */
    AST_ElseIfBlock_t   *astnode_else_if_block,        /* else_if_block */
    AST_WhileBlock_t    *astnode_while_block,          /* while_block */
    AST_ForBlock_t      *astnode_for_block,            /* for_block */
    AST_Block_t         *astnode_block,                /* block */
    AST_Condition_t     *astnode_condition,            /* condition */
    AST_Expression_t    *astnode_expression,           /* expression */
    AST_Operand_t       *astnode_operand,              /* operand */
    AST_Literal_t       *astnode_literal,              /* literal */
    AST_Identifier_t    *astnode_identifier            /* identifier */
}


/* semantic types of each parser rule */
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


/* parser entry point? */
%start module


%%

/* Push module name to a stack */
module:
    { AST_ModuleStack_push(AST_Identifier("main")); } program { AST_ModuleStack_pop(); }
    | "module" identifier "\n" { AST_ModuleStack_push($2); } program { AST_ModuleStack_pop(); }
    ;

/* A program is empty or a single procedure or multiple procedures */
program:
    procedure
    | program procedure
    ;

/* Map each module name to a map of procedures */
procedure:
    | "proc" identifier "start" "\n" statements "end" "\n" { AST_ProcedureMap_add(AST_ModuleStack_top(), $2, $5); }
    ;

statements:
    statement                       { $$ = AST_Statements($1, NULL);         }
    | statements statement          { $$ = AST_Statements($1, $2);           }
    ;

statement:                          { $$ = NULL;                             }
    | "pass" "\n"                   { $$ = AST_Statement_empty();            }
    | assignment "\n"               { $$ = AST_Statement_Assignment($1);     }
    | compound_statement "\n"       { $$ = AST_Statement_CompoundSt($1);     }
    ;

assignment:
    "var" identifier "=" expression { $$ = AST_Assignment_create($2, $4);    }   /* shadow or create new var */
    | expression                    { $$ = AST_Assignment_tovoid($1);        }   /* assignment to void */
    ;

compound_statement:
    if_block                        { $$ = AST_CompoundSt_IfBlock($1);       }
    | if_else_block                 { $$ = AST_CompoundSt_IfElseBlock($1);   }
    | if_else_if_block              { $$ = AST_CompoundSt_IfElseIfBlock($1); }
    | while_block                   { $$ = AST_CompoundSt_WhileBlock($1);    }
    | for_block                     { $$ = AST_CompoundSt_ForBlock($1);      }
    | block                         { $$ = AST_CompoundSt_Block($1);         }
    ;

if_block:
    "if" condition "then" "\n" statements "end" { $$ = AST_IfBlock($2, $5); }
    ;

if_else_block:
    "if" condition "then" "\n" statements "else" statements "end" { $$ = AST_IfElseBlock($2, $5, $7); }
    ;

if_else_if_block:
    "if" condition "then" "\n" statements else_if_block { $$ = AST_IfElseIfBlock($2, $5, $6); }
    ;

else_if_block:
    "else" if_else_if_block { $$ = AST_ElseIfBlock($2); }
    | "end"                 { $$ = NULL;                }
    ;

while_block:
    "while" condition "do" "\n" statements "end" { $$ = AST_WhileBlock($2, $5); }
    ;

for_block:
    "for" identifier "from" operand "to" operand "do" statements "end"                { $$ = AST_ForBlock($2, $4, $6, NULL, $8); }
    | "for" identifier "from" operand "to" operand "by" operand "do" statements "end" { $$ = AST_ForBlock($2, $4, $6, $8, $10);  }
    ;

block:
    "block" statements "end" { $$ = AST_Block($2); }
    ;

condition:
    conditional_expression { $$ = AST_Condition(NULL); }
    ;

expression:
    assignment_expression { $$ = NULL; }
    ;

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

conditional_expression:
    logical_or_expression
    | expression "if" logical_or_expression "else" conditional_expression
    ;

logical_or_expression:
    logical_and_expression
    | logical_or_expression "||" logical_and_expression
    ;

logical_and_expression:
    bitwise_or_expression
    | logical_and_expression "&&" bitwise_or_expression
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

multiplicative_expression:
    unary_expression
    | multiplicative_expression "*" unary_expression
    | multiplicative_expression "/" unary_expression
    | multiplicative_expression "%" unary_expression
    | multiplicative_expression "**" unary_expression
    | multiplicative_expression "//" unary_expression
    ;

unary_expression:
    postfix_expression
    | "-" unary_expression
    | "!" unary_expression
    | "~" unary_expression
    | "++" unary_expression
    | "--" unary_expression
    ;

postfix_expression:
    primary_expression
    | postfix_expression "(" arguments_list ")"
    | postfix_expression "[" expression "]"
    | postfix_expression "++"
    | postfix_expression "--"
    | postfix_expression "." identifier
    | postfix_expression "::" identifier
    ;

primary_expression:
    operand
    | "(" expression ")"
    ;

arguments_list:
    expression
    | arguments_list "," expression
    ;

operand:
    literal      { $$ = AST_Operand_Literal($1);    }
    | identifier { $$ = AST_Operand_Identifier($1); }
    ;

literal:
    LEXTOK_BOOL_LITERAL           { $$ = AST_Literal_bul($1); }
    | LEXTOK_CHAR_LITERAL         { $$ = AST_Literal_chr($1); }
    | LEXTOK_BINFLOAT_LITERAL     { $$ = AST_Literal_f64($1); }
    | LEXTOK_OCTFLOAT_LITERAL     { $$ = AST_Literal_f64($1); }
    | LEXTOK_DECFLOAT_LITERAL     { $$ = AST_Literal_f64($1); }
    | LEXTOK_HEXFLOAT_LITERAL     { $$ = AST_Literal_f64($1); }
    | LEXTOK_BININT_LITERAL       { $$ = AST_Literal_i64($1); }
    | LEXTOK_OCTINT_LITERAL       { $$ = AST_Literal_i64($1); }
    | LEXTOK_DECINT_LITERAL       { $$ = AST_Literal_i64($1); }
    | LEXTOK_HEXINT_LITERAL       { $$ = AST_Literal_i64($1); }
    | LEXTOK_STR_LITERAL          { $$ = AST_Literal_str($1); }
    | LEXTOK_INTERP_STR_LITERAL   { $$ = AST_Literal_interp_str($1); }
    ;

identifier:
    LEXTOK_IDENTIFIER { $$ = AST_Identifier($1); }
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
