/* work in progress:
   build a recursive descent parser for the following grammar */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "lexer.h"
#include "parser.h"

bool parse_expect(lex_Token_t tok) {
    lex_Token_t t = lex_Token_getnext(yyin);
    if (t == tok) {
        return true;
    } else {
        lex_throw("unexpected token");
        return false;
    }
}
