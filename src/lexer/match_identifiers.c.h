#ifndef LEXER_MATCH_IDENTIFIERS_C_H
#define LEXER_MATCH_IDENTIFIERS_C_H

#include <ctype.h>
#include "lexer.h"

lex_Token_t lex_match_identifiers(FILE *f, char ch)
{
    bool flag_colon_found = false;

    if (!isalpha(ch) && ch != '_') return TOKEN_INVALID;
    while (true) {
        ch = lex_getc(f);
        if (!lex_is_alnumundr(ch)) {
            /*
               - Lets ':' be a part of an identifier in certain conditions
               - allows using module declaration "module Mod1:SubMod1:SubMod2"
               - previously it would be "module Mod1_SubMod1_SubMod2"
               - allows calling procedure as "Mod1:SubMod1:SubMod2:procedure()"
               - previously it would be "Mod1_SubMod1_SubMod2:procedure()"
            */
            if (ch == ':') {
                flag_colon_found = true;
                continue;
            }

            // unget last non identifier char
            lex_ungetc(&ch, f);
            break;
        }
    }

    /* colon found and current line is not the first line i.e.
       this identifier is not a module declaration and is in
       form Mod1:SubMod1:SubMod2:procedure.

       we unget the procedure name so that it may be consumed
       as a seperate identifier.

       we also unget ':' as ':' is a binary operator that
       operates with LHS = module name and RHS = procedure name */
    if (flag_colon_found && lex_line_no > 1) {
        // unget procedure name till ':'
        while (ch != ':') {
            lex_ungetc(&ch, f);
        }
        // unget all consecutive ':'
        while (ch == ':') {
            lex_ungetc(&ch, f);
        }
    }

    return TOKEN_IDENTIFIER;
}

#else
    #warning re-inclusion of module 'lexer/match_identifiers.c.h'
#endif
