%{

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

#include "io.h"
#include "lexer.h"
#include "parser.h"
#include "ast/nodes.h"
#include "ast/util.h"

FILE *yyin = NULL;

%}

%token <tok> LEXTOK_BANG                     "!"
%token <tok> LEXTOK_LOGICAL_UNEQUAL          "!="
%token <tok> LEXTOK_LOGICAL_UNIDENTICAL      "!=="
%token <tok> LEXTOK_DQUOTE                   '"'
%token <tok> LEXTOK_DOLLAR                   "$"
%token <tok> LEXTOK_PERCENT                  "%"
%token <tok> LEXTOK_MODULO_ASSIGN            "%="
%token <tok> LEXTOK_AMPERSAND                "&"
%token <tok> LEXTOK_LOGICAL_AND              "&&"
%token <tok> LEXTOK_LOGICAL_AND_ASSIGN       "&&="
%token <tok> LEXTOK_BITWISE_AND_ASSIGN       "&="
%token <tok> LEXTOK_SQUOTE                   "'"
%token <tok> LEXTOK_LBRACE_PAREN             "("
%token <tok> LEXTOK_RBRACE_PAREN             ")"
%token <tok> LEXTOK_ASTERIX                  "*"
%token <tok> LEXTOK_EXPONENT                 "**"
%token <tok> LEXTOK_EXPONENT_ASSIGN          "**="
%token <tok> LEXTOK_MULTIPLY_ASSIGN          "*="
%token <tok> LEXTOK_PLUS                     "+"
%token <tok> LEXTOK_INCREMENT                "++"
%token <tok> LEXTOK_ADD_ASSIGN               "+="
%token <tok> LEXTOK_COMMA                    ","
%token <tok> LEXTOK_MINUS                    "-"
%token <tok> LEXTOK_DECREMENT                "--"
%token <tok> LEXTOK_SUBSTRACT_ASSIGN         "-="
%token <tok> LEXTOK_SARROW                   "->"
%token <tok> LEXTOK_DOT                      "."
%token <tok> LEXTOK_ELIPSIS                  "..."
%token <tok> LEXTOK_FSLASH                   "/"
%token <tok> LEXTOK_FLOOR_DIVIDE             "//"
%token <tok> LEXTOK_FLOOR_DIVIDE_ASSIGN      "//="
%token <tok> LEXTOK_DIVIDE_ASSIGN            "/="
%token <tok> LEXTOK_COLON                    ":"
%token <tok> LEXTOK_DCOLON                   "::"
%token <tok> LEXTOK_SEMICOLON                ";"
%token <tok> LEXTOK_LBRACE_ANGULAR           "<"
%token <tok> LEXTOK_BITWISE_LSHIFT           "<<"
%token <tok> LEXTOK_BITWISE_LSHIFT_ASSIGN    "<<="
%token <tok> LEXTOK_LOGICAL_LESSER_EQUAL     "<="
%token <tok> LEXTOK_ASSIGN                   "="
%token <tok> LEXTOK_LOGICAL_EQUAL            "=="
%token <tok> LEXTOK_LOGICAL_IDENTICAL        "==="
%token <tok> LEXTOK_DARROW                   "=>"
%token <tok> LEXTOK_RBRACE_ANGULAR           ">"
%token <tok> LEXTOK_LOGICAL_GREATER_EQUAL    ">="
%token <tok> LEXTOK_BITWISE_RSHIFT           ">>"
%token <tok> LEXTOK_BITWISE_RSHIFT_ASSIGN    ">>="
%token <tok> LEXTOK_ARITH_RSHIFT             ">>>"
%token <tok> LEXTOK_ARITH_RSHIFT_ASSIGN      ">>>="
%token <tok> LEXTOK_QUESTION                 "?"
%token <tok> LEXTOK_AT                       "@"
%token <tok> LEXTOK_LBRACE_SQUARE            "["
%token <tok> LEXTOK_BSLASH                   "\\"
%token <tok> LEXTOK_RBRACE_SQUARE            "]"
%token <tok> LEXTOK_CARET                    "^"
%token <tok> LEXTOK_BITWISE_XOR_ASSIGN       "^="
%token <tok> LEXTOK_BACKTICK                 "`"
%token <tok> LEXTOK_LBRACE_CURLY             "{"
%token <tok> LEXTOK_PIPE                     "|"
%token <tok> LEXTOK_BITWISE_OR_ASSIGN        "|="
%token <tok> LEXTOK_PIPEOUT                  "|>"
%token <tok> LEXTOK_LOGICAL_OR               "||"
%token <tok> LEXTOK_LOGICAL_OR_ASSIGN        "||="
%token <tok> LEXTOK_RBRACE_CURLY             "}"
%token <tok> LEXTOK_TILDE                    "~"

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
%token LEXTOK_KWD_IN                   "in"
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

%left  LEXTOK_KWD_MODULE
%left  LEXTOK_KWD_PROC
%left  LEXTOK_KWD_START
%left  LEXTOK_KWD_END
%left  LEXTOK_KWD_BLOCK
%left  LEXTOK_KWD_IF
%left  LEXTOK_KWD_THEN
%left  LEXTOK_KWD_ELIF
%left  LEXTOK_KWD_ELSE
%left  LEXTOK_KWD_WHILE
%left  LEXTOK_KWD_BREAK
%left  LEXTOK_KWD_CONTINUE
%left  LEXTOK_KWD_RETURN
%left  LEXTOK_KWD_FOR
%left  LEXTOK_KWD_FROM
%left  LEXTOK_KWD_TO
%left  LEXTOK_KWD_BY
%left  LEXTOK_KWD_DO
%left  LEXTOK_KWD_VAR
%left  LEXTOK_KWD_PASS

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
    /* just the token id */
    LexToken tok;

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
    AST_Statements_t        *astnode_statements;           /* statements */
    AST_Statement_t         *astnode_statement;            /* statement */
    AST_Assignment_t        *astnode_assignment;           /* assignment */
    AST_CompoundSt_t        *astnode_compound_statement;   /* compound_statement */
    AST_IfBlock_t           *astnode_if_block;             /* if_block */
    AST_ElseIfBlock_t       *astnode_else_if_block;        /* else_if_block */
    AST_ElseIfSt_t          *astnode_else_if_statement;    /* else_if_statement */
    AST_WhileBlock_t        *astnode_while_block;          /* while_block */
    AST_ForBlock_t          *astnode_for_block;            /* for_block */
    AST_Block_t             *astnode_block;                /* block */
    AST_ConditionalExpr_t   *astnode_condition;            /* condition */
    AST_Expression_t        *astnode_expression;           /* expression */
    AST_Operand_t           *astnode_operand;              /* operand */
    AST_Literal_t           *astnode_literal;              /* literal */
    AST_Identifier_t        *astnode_identifier;           /* identifier */

    /* various types of expressions */
    AST_AssignmentExpr_t    *astnode_assignment_expression;
    AST_ConditonalExpr_t    *astnode_condtional_expression;
    AST_TernaryExpr_t       *astnode_ternary_expression;
    AST_BinaryExpr_t        *astnode_binary_expression;
    AST_UnaryExpr_t         *astnode_unary_expression;
    AST_PostfixExpr_t       *astnode_postfix_expression;
    AST_PrimaryExpr_t       *astnode_primary_expression;
    AST_CommaSepList_t      *astnode_comma_list;
}


/* semantic types of each parser rule */
%type <astnode_statements>            statements
%type <astnode_statement>             statement
%type <astnode_assignment>            assignment
%type <astnode_compound_statement>    compound_statement
%type <astnode_if_block>              if_block
%type <astnode_else_if_block>         else_if_block
%type <astnode_else_if_statement>     else_if_statement
%type <astnode_while_block>           while_block
%type <astnode_for_block>             for_block
%type <astnode_block>                 block
%type <astnode_condition>             condition
%type <astnode_expression>            expression
%type <astnode_operand>               operand
%type <astnode_literal>               literal
%type <astnode_identifier>            identifier

/* various types of expressions */

/* parser entry point? */
%start module


%%

nwl: nwl "\n" | "\n";

/* Push module name to a stack */
module:
    { AST_ModuleStack_push(AST_Identifier("main")); } program { AST_ModuleStack_pop(); }
    | "module" identifier nwl { AST_ModuleStack_push($2); } program { AST_ModuleStack_pop(); }
    ;

/* A program is empty or a single procedure or multiple procedures */
program:
    %empty
    | program procedure
    ;

/* Map each module name to a map of procedures */
procedure:
    "proc" identifier "start" nwl statements "end" nwl { AST_ProcedureMap_add((AST_Identifier_t*) AST_ModuleStack_top(), $2, $5); }
    ;

statements:
    %empty                          { $$ = NULL;                             }
    | statements statement          { $$ = AST_Statements($1, $2);           }
    ;

statement:
    "pass" nwl                      { $$ = AST_Statement_empty(lex_line_no);          }
    | assignment nwl                { $$ = AST_Statement_Assignment($1, lex_line_no); }
    | compound_statement nwl        { $$ = AST_Statement_CompoundSt($1, lex_line_no); }
    ;

assignment:
    "var" identifier "=" expression { $$ = AST_Assignment_create($2, $4);    }   /* shadow or create new var */
    | expression                    { $$ = AST_Assignment_tovoid($1);        }   /* assignment to void */
    ;

compound_statement:
    if_block                        { $$ = AST_CompoundSt_IfBlock($1);       }
    | while_block                   { $$ = AST_CompoundSt_WhileBlock($1);    }
    | for_block                     { $$ = AST_CompoundSt_ForBlock($1);      }
    | block                         { $$ = AST_CompoundSt_Block($1);         }
    ;

if_block:
    "if" condition "then" nwl statements "end"                                       { $$ = AST_IfBlock($2, $5, NULL, NULL); }
    | "if" condition "then" nwl statements "else" nwl statements "end"               { $$ = AST_IfBlock($2, $5, NULL, $8);   }
    | "if" condition "then" nwl statements else_if_block "end"                       { $$ = AST_IfBlock($2, $5, $6, NULL);   }
    | "if" condition "then" nwl statements else_if_block "else" nwl statements "end" { $$ = AST_IfBlock($2, $5, $6, $9);     }
    ;

else_if_block:
    else_if_statement                            { $$ = AST_ElseIfBlock(NULL, $1); }
    | else_if_block else_if_statement            { $$ = AST_ElseIfBlock($1, $2);   }
    ;

else_if_statement:
    "else" "if" condition "then" nwl statements  { $$ = AST_ElseIfSt($3, $6);      }
    | "elif" condition "then" nwl statements     { $$ = AST_ElseIfSt($2, $5);      }
    ;

while_block:
    "while" condition "do" nwl statements "end"  { $$ = AST_WhileBlock($2, $5);    }
    ;

for_block:
    "for" identifier "from" operand "to" operand "do" nwl statements "end"                { $$ = AST_ForBlock($2, $4, $6, NULL, $9); }
    | "for" identifier "from" operand "to" operand "by" operand "do" nwl statements "end" { $$ = AST_ForBlock($2, $4, $6, $8, $11);  }
    | "for" identifier "in" operand "do" nwl statements "end"                             { $$ = AST_ForBlock_iterate($2, $4, $7);   }
    ;

block:
    "block" nwl statements "end" { $$ = AST_Block($3); }
    ;

condition:
    conditional_expression { $$ = $1; }
    ;

expression:
    assignment_expression  { $$ = $1; }
    ;

assignment_expression:
    conditional_expression                              { $$ = AST_AssignmentExpr_conditional($1); }
    | postfix_expression "=" assignment_expression      { $$ = AST_AssignmentExpr($1, $2, $3); }
    | postfix_expression "||=" assignment_expression    { $$ = AST_AssignmentExpr($1, $2, $3); }
    | postfix_expression "&&=" assignment_expression    { $$ = AST_AssignmentExpr($1, $2, $3); }
    | postfix_expression "|=" assignment_expression     { $$ = AST_AssignmentExpr($1, $2, $3); }
    | postfix_expression "^=" assignment_expression     { $$ = AST_AssignmentExpr($1, $2, $3); }
    | postfix_expression "&=" assignment_expression     { $$ = AST_AssignmentExpr($1, $2, $3); }
    | postfix_expression ">>>=" assignment_expression   { $$ = AST_AssignmentExpr($1, $2, $3); }
    | postfix_expression "<<=" assignment_expression    { $$ = AST_AssignmentExpr($1, $2, $3); }
    | postfix_expression ">>=" assignment_expression    { $$ = AST_AssignmentExpr($1, $2, $3); }
    | postfix_expression "+=" assignment_expression     { $$ = AST_AssignmentExpr($1, $2, $3); }
    | postfix_expression "-=" assignment_expression     { $$ = AST_AssignmentExpr($1, $2, $3); }
    | postfix_expression "*=" assignment_expression     { $$ = AST_AssignmentExpr($1, $2, $3); }
    | postfix_expression "/=" assignment_expression     { $$ = AST_AssignmentExpr($1, $2, $3); }
    | postfix_expression "%=" assignment_expression     { $$ = AST_AssignmentExpr($1, $2, $3); }
    | postfix_expression "**=" assignment_expression    { $$ = AST_AssignmentExpr($1, $2, $3); }
    | postfix_expression "//=" assignment_expression    { $$ = AST_AssignmentExpr($1, $2, $3); }
    ;

conditional_expression:
    logical_or_expression                               { $$ = AST_ConditionalExpr_binary($1);  }
    | ternary_expression                                { $$ = AST_ConditionalExpr_ternary($1); }
    ;

ternary_expression:
    conditional_expression "if" condition "else" conditional_expression { $$ = AST_TernaryExpr($1, $3, $5); }
    ;

logical_or_expression:
    logical_and_expression                              { $$ = $1; }
    | logical_or_expression "||" logical_and_expression { $$ = AST_BinaryExpr($1, $2, $3); }
    ;

logical_and_expression:
    bitwise_or_expression                               { $$ = $1; }
    | logical_and_expression "&&" bitwise_or_expression { $$ = AST_BinaryExpr($1, $2, $3); }
    ;

bitwise_or_expression:
    bitwise_xor_expression                              { $$ = $1; }
    | bitwise_or_expression "|" bitwise_xor_expression  { $$ = AST_BinaryExpr($1, $2, $3); }
    ;

bitwise_xor_expression:
    bitwise_and_expression                              { $$ = $1; }
    | bitwise_xor_expression "^" bitwise_and_expression { $$ = AST_BinaryExpr($1, $2, $3); }
    ;

bitwise_and_expression:
    equality_expression                                 { $$ = $1; }
    | bitwise_and_expression "&" equality_expression    { $$ = AST_BinaryExpr($1, $2, $3); }
    ;

equality_expression:
    relational_expression                               { $$ = $1; }
    | equality_expression "==" relational_expression    { $$ = AST_BinaryExpr($1, $2, $3); }
    | equality_expression "!=" relational_expression    { $$ = AST_BinaryExpr($1, $2, $3); }
    ;

relational_expression:
    shift_expression                                    { $$ = $1; }
    | relational_expression "<" shift_expression        { $$ = AST_BinaryExpr($1, $2, $3); }
    | relational_expression ">" shift_expression        { $$ = AST_BinaryExpr($1, $2, $3); }
    | relational_expression "<=" shift_expression       { $$ = AST_BinaryExpr($1, $2, $3); }
    | relational_expression ">=" shift_expression       { $$ = AST_BinaryExpr($1, $2, $3); }
    ;

shift_expression:
    additive_expression                                 { $$ = $1; }
    | shift_expression ">>>" additive_expression        { $$ = AST_BinaryExpr($1, $2, $3); }
    | shift_expression "<<" additive_expression         { $$ = AST_BinaryExpr($1, $2, $3); }
    | shift_expression ">>" additive_expression         { $$ = AST_BinaryExpr($1, $2, $3); }
    ;

additive_expression:
    multiplicative_expression                           { $$ = $1; }
    | additive_expression "+" multiplicative_expression { $$ = AST_BinaryExpr($1, $2, $3); }
    | additive_expression "-" multiplicative_expression { $$ = AST_BinaryExpr($1, $2, $3); }
    ;

multiplicative_expression:
    unary_expression                                    { $$ = AST_BinaryExpr_unary($1);            }
    | multiplicative_expression "*" unary_expression    { $$ = AST_BinaryExpr_op_unary($1, $2, $3); }
    | multiplicative_expression "/" unary_expression    { $$ = AST_BinaryExpr_op_unary($1, $2, $3); }
    | multiplicative_expression "%" unary_expression    { $$ = AST_BinaryExpr_op_unary($1, $2, $3); }
    | unary_expression "**" multiplicative_expression   { $$ = AST_BinaryExpr_unary_op($1, $2, $3); }
    | multiplicative_expression "//" unary_expression   { $$ = AST_BinaryExpr_op_unary($1, $2, $3); }
    ;

unary_expression:
    postfix_expression                                  { $$ = AST_UnaryExpr_postfix($1); }
    | "-" unary_expression                              { $$ = AST_UnaryExpr($1, $2);     }
    | "!" unary_expression                              { $$ = AST_UnaryExpr($1, $2);     }
    | "~" unary_expression                              { $$ = AST_UnaryExpr($1, $2);     }
    | "++" unary_expression                             { $$ = AST_UnaryExpr($1, $2);     }
    | "--" unary_expression                             { $$ = AST_UnaryExpr($1, $2);     }
    ;

postfix_expression:
    primary_expression                                  { $$ = AST_PostfixExpr_primary($1);      }
    | postfix_expression "(" ")"                        { $$ = AST_FunctionCallExpr($1, NULL);   }
    | postfix_expression "(" comma_list ")"             { $$ = AST_FunctionCallExpr($1, $3);     }
    | postfix_expression "[" expression "]"             { $$ = AST_IndexingExpr($1, $3);         }
    | postfix_expression "++"                           { $$ = AST_PostfixExpr($1, $2);          }
    | postfix_expression "--"                           { $$ = AST_PostfixExpr($1, $2);          }
    | postfix_expression "." identifier                 { $$ = AST_MemberAccessExpr($1, $2, $3); }
    | postfix_expression "::" identifier                { $$ = AST_MemberAccessExpr($1, $2, $3); }
    ;

primary_expression:
    operand                       { $$ = AST_PrimaryExpr_operand($1);    }
    | "(" expression ")"          { $$ = AST_PrimaryExpr_expression($1); }
    ;

comma_list:
    expression                    { $$ = AST_CommaSepList(NULL, $1); }
    | comma_list "," expression   { $$ = AST_CommaSepList($1, $2);   }
    ;

operand:
    literal                       { $$ = AST_Operand_Literal($1);    }
    | identifier                  { $$ = AST_Operand_Identifier($1); }
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
    | "[" "]"                     { $$ = AST_Literal_lst(NULL); }
    | "[" comma_list "]"          { $$ = AST_Literal_lst($2); }
    ;

identifier:
    LEXTOK_IDENTIFIER             { $$ = AST_Identifier($1); }
    ;

%%

#include "parser/parse_bool.c.h"
#include "parser/parse_chr.c.h"
#include "parser/parse_f64.c.h"
#include "parser/parse_i64.c.h"
#include "parser/parse_str.c.h"

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
