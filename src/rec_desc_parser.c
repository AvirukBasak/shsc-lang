/* work in progress:
   build a recursive descent parser for the following grammar */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "lexer.h"
#include "parser.h"

// /* \n* */
// nws:
//     %empty
//     | nws "\n"
//     ;
// 
// /* \n+ */
// nwp:
//     "\n"
//     | nwp "\n"
//     ;
// 
// /* (\n|;)+ */
// trm:
//     trm ";"
//     | ";"
//     | trm "\n"
//     | "\n"
//     ;
// 
// /* Push module name to a stack */
// module:
//     program
//     | "module" identifier trm program
//     ;
// 
// /* A program is empty or a single procedure or multiple procedures */
// program:
//     %empty
//     | program procedure
//     ;
// 
// /* Map each module name to a map of procedures */
// procedure:
//     "proc" identifier "start" nwp statements "end" trm
//     ;
// 
// statements:
//     %empty
//     | statement statements
//     ;
// 
// statement:
//     "pass" trm
//     | "break" trm
//     | "continue" trm
//     | "return" expression trm
//     | "return" trm
//     | assignment trm
//     | compound_statement trm
//     ;
// 
// assignment:
//     "var" identifier "=" expression      /* shadow or create new var */
//     | "const" identifier "=" expression  /* create new constant */
//     | expression                         /* assignment to void */
//     ;
// 
// compound_statement:
//     if_block
//     | while_block
//     | for_block
//     | block
//     ;
// 
// if_block:
//     "if" condition "then" nwp statements "end"
//     | "if" condition "then" nwp statements else_block
//     ;
// 
// else_block:
//     "else" nwp statements "end"
//     | "else" "if" condition "then" nwp statements "end"
//     | "else" "if" condition "then" nwp statements else_block
//     | "elif" condition "then" nwp statements "end"
//     | "elif" condition "then" nwp statements else_block
//     ;
// 
// while_block:
//     "while" condition "do" nwp statements "end"
//     ;
// 
// for_block:
//     "for" identifier "from" expression "to" expression "do" nwp statements "end"
//     | "for" identifier "from" expression "to" expression "by" expression "do" nwp statements "end"
//     | "for" identifier "in" expression "do" nwp statements "end"
//     | "for" identifier "," identifier "in" expression "do" nwp statements "end"
//     ;
// 
// block:
//     "block" nwp statements "end"
//     ;
// 
// condition:
//     conditional_expression
//     ;
// 
// expression:
//     assignment_expression
//     ;
// 
// assignment_expression:
//     conditional_expression
//     | postfix_expression "=" assignment_expression
//     | postfix_expression "||=" assignment_expression
//     | postfix_expression "&&=" assignment_expression
//     | postfix_expression "|=" assignment_expression
//     | postfix_expression "^=" assignment_expression
//     | postfix_expression "&=" assignment_expression
//     | postfix_expression ">>>=" assignment_expression
//     | postfix_expression "<<=" assignment_expression
//     | postfix_expression ">>=" assignment_expression
//     | postfix_expression "+=" assignment_expression
//     | postfix_expression "-=" assignment_expression
//     | postfix_expression "*=" assignment_expression
//     | postfix_expression "/=" assignment_expression
//     | postfix_expression "%=" assignment_expression
//     | postfix_expression "**=" assignment_expression
//     | postfix_expression "//=" assignment_expression
//     ;
// 
// conditional_expression:
//     logical_or_expression
//     | conditional_expression "if" condition "else" conditional_expression
//     ;
// 
// logical_or_expression:
//     logical_and_expression
//     | logical_or_expression "||" logical_and_expression
//     ;
// 
// logical_and_expression:
//     bitwise_or_expression
//     | logical_and_expression "&&" bitwise_or_expression
//     ;
// 
// bitwise_or_expression:
//     bitwise_xor_expression
//     | bitwise_or_expression "|" bitwise_xor_expression
//     ;
// 
// bitwise_xor_expression:
//     bitwise_and_expression
//     | bitwise_xor_expression "^" bitwise_and_expression
//     ;
// 
// bitwise_and_expression:
//     equality_expression
//     | bitwise_and_expression "&" equality_expression
//     ;
// 
// equality_expression:
//     relational_expression
//     | equality_expression "==" relational_expression
//     | equality_expression "!=" relational_expression
//     ;
// 
// relational_expression:
//     shift_expression
//     | relational_expression "<" shift_expression
//     | relational_expression ">" shift_expression
//     | relational_expression "<=" shift_expression
//     | relational_expression ">=" shift_expression
//     ;
// 
// shift_expression:
//     additive_expression
//     | shift_expression ">>>" additive_expression
//     | shift_expression "<<" additive_expression
//     | shift_expression ">>" additive_expression
//     ;
// 
// additive_expression:
//     multiplicative_expression
//     | additive_expression "+" multiplicative_expression
//     | additive_expression "-" multiplicative_expression
//     ;
// 
// multiplicative_expression:
//     unary_expression
//     | multiplicative_expression "*" unary_expression
//     | multiplicative_expression "/" unary_expression
//     | multiplicative_expression "%" unary_expression
//     | unary_expression "**" multiplicative_expression
//     | multiplicative_expression "//" unary_expression
//     ;
// 
// unary_expression:
//     postfix_expression
//     | "+" unary_expression
//     | "-" unary_expression
//     | "!" unary_expression
//     | "~" unary_expression
//     | "++" unary_expression
//     | "--" unary_expression
//     ;
// 
// postfix_expression:
//     primary_expression
//     | postfix_expression "(" ")"
//     | postfix_expression "(" nws comma_list ")"
//     | postfix_expression "[" expression "]"
//     | "$" "[" expression "]"
//     | "$" "(" expression ")"
//     | "$" TOKEN_DECINT_LITERAL
//     | "$" identifier
//     | postfix_expression "++"
//     | postfix_expression "--"
//     | postfix_expression "." identifier
//     | postfix_expression "::" identifier
//     | postfix_expression ":" identifier
//     ;
// 
// primary_expression:
//     literal
//     | identifier
//     | "(" expression ")"
//     ;
// 
// comma_list:
//     expression nws
//     | expression "," nws
//     | expression "," nws comma_list
//     ;
// 
// assoc_list:
//     string_literal ":" expression nws
//     | string_literal ":" expression "," nws
//     | string_literal ":" expression "," nws assoc_list
//     ;
// 
// literal:
//     TOKEN_BOOL_LITERAL
//     | TOKEN_CHAR_LITERAL
//     | TOKEN_BINFLOAT_LITERAL
//     | TOKEN_OCTFLOAT_LITERAL
//     | TOKEN_DECFLOAT_LITERAL
//     | TOKEN_HEXFLOAT_LITERAL
//     | TOKEN_BININT_LITERAL
//     | TOKEN_OCTINT_LITERAL
//     | TOKEN_DECINT_LITERAL
//     | TOKEN_HEXINT_LITERAL
//     | string_literal
//     | list_literal
//     | map_literal
//     ;
// 
// string_literal:
//     TOKEN_STR_LITERAL
//     | TOKEN_INTERP_STR_LITERAL
//     ;
// 
// list_literal:
//     "[" "]"
//     | "[" nws comma_list "]"
//     ;
// 
// map_literal:
//     "{" "}"
//     | "{" nws assoc_list "}"
//     ;
// 
// identifier:
//     TOKEN_IDENTIFIER
//     ;

bool parse_expect(lex_Token_t tok) {
    lex_Token_t t = lex_Token_getnext(yyin);
    if (t == tok) {
        return true;
    } else {
        lex_throw("unexpected token");
        return false;
    }
}
