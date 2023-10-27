/* work in progress:
   build a recursive descent parser for the following grammar */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "lexer.h"
#include "parser.h"

bool parse_expect(lex_Token_t tok, bool recover) {
    lex_Token_t t = lex_Token_getnext(yyin);
    if (t == tok) {
        return true;
    } else {
        if (!recover) parse_throw("syntax error", true);
        return false;
    }
}
