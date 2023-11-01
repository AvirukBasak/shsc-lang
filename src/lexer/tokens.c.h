#ifndef LEXER_TOKENS_C_H
#define LEXER_TOKENS_C_H

#include "lexer.h"
#include "parser.yy.h"

/* contributor's warning: ensure tokens are grouped and sorted in alphabetical order */
const char *lex_Token_getcode(lex_Token_t code)
{
    switch (code) {
        /* operators and seperators */
        case TOKEN_BANG:                  return "TOKEN_BANG";
        case TOKEN_LOGICAL_UNEQUAL:       return "TOKEN_LOGICAL_UNEQUAL";
        case TOKEN_LOGICAL_UNIDENTICAL:   return "TOKEN_LOGICAL_UNIDENTICAL";
        case TOKEN_DQUOTE:                return "TOKEN_DQUOTE";
        case TOKEN_DOLLAR:                return "TOKEN_DOLLAR";
        case TOKEN_PERCENT:               return "TOKEN_PERCENT";
        case TOKEN_MODULO_ASSIGN:         return "TOKEN_MODULO_ASSIGN";
        case TOKEN_AMPERSAND:             return "TOKEN_AMPERSAND";
        case TOKEN_LOGICAL_AND:           return "TOKEN_LOGICAL_AND";
        case TOKEN_LOGICAL_AND_ASSIGN:    return "TOKEN_LOGICAL_AND_ASSIGN";
        case TOKEN_BITWISE_AND_ASSIGN:    return "TOKEN_BITWISE_AND_ASSIGN";
        case TOKEN_SQUOTE:                return "TOKEN_SQUOTE";
        case TOKEN_LBRACE_PAREN:          return "TOKEN_LBRACE_PAREN";
        case TOKEN_RBRACE_PAREN:          return "TOKEN_RBRACE_PAREN";
        case TOKEN_ASTERIX:               return "TOKEN_ASTERIX";
        case TOKEN_EXPONENT:              return "TOKEN_EXPONENT";
        case TOKEN_EXPONENT_ASSIGN:       return "TOKEN_EXPONENT_ASSIGN";
        case TOKEN_MULTIPLY_ASSIGN:       return "TOKEN_MULTIPLY_ASSIGN";
        case TOKEN_PLUS:                  return "TOKEN_PLUS";
        case TOKEN_INCREMENT:             return "TOKEN_INCREMENT";
        case TOKEN_ADD_ASSIGN:            return "TOKEN_ADD_ASSIGN";
        case TOKEN_COMMA:                 return "TOKEN_COMMA";
        case TOKEN_MINUS:                 return "TOKEN_MINUS";
        case TOKEN_DECREMENT:             return "TOKEN_DECREMENT";
        case TOKEN_SUBSTRACT_ASSIGN:      return "TOKEN_SUBSTRACT_ASSIGN";
        case TOKEN_SARROW:                return "TOKEN_SARROW";
        case TOKEN_DOT:                   return "TOKEN_DOT";
        case TOKEN_ELIPSIS:               return "TOKEN_ELIPSIS";
        case TOKEN_FSLASH:                return "TOKEN_FSLASH";
        case TOKEN_FLOOR_DIVIDE:          return "TOKEN_FLOOR_DIVIDE";
        case TOKEN_FLOOR_DIVIDE_ASSIGN:   return "TOKEN_FLOOR_DIVIDE_ASSIGN";
        case TOKEN_DIVIDE_ASSIGN:         return "TOKEN_DIVIDE_ASSIGN";
        case TOKEN_COLON:                 return "TOKEN_COLON";
        case TOKEN_DCOLON:                return "TOKEN_DCOLON";
        case TOKEN_SEMICOLON:             return "TOKEN_SEMICOLON";
        case TOKEN_LBRACE_ANGULAR:        return "TOKEN_LBRACE_ANGULAR";
        case TOKEN_BITWISE_LSHIFT:        return "TOKEN_BITWISE_LSHIFT";
        case TOKEN_BITWISE_LSHIFT_ASSIGN: return "TOKEN_BITWISE_LSHIFT_ASSIGN";
        case TOKEN_LOGICAL_LESSER_EQUAL:  return "TOKEN_LOGICAL_LESSER_EQUAL";
        case TOKEN_ASSIGN:                return "TOKEN_ASSIGN";
        case TOKEN_LOGICAL_EQUAL:         return "TOKEN_LOGICAL_EQUAL";
        case TOKEN_LOGICAL_IDENTICAL:     return "TOKEN_LOGICAL_IDENTICAL";
        case TOKEN_DARROW:                return "TOKEN_DARROW";
        case TOKEN_RBRACE_ANGULAR:        return "TOKEN_RBRACE_ANGULAR";
        case TOKEN_LOGICAL_GREATER_EQUAL: return "TOKEN_LOGICAL_GREATER_EQUAL";
        case TOKEN_BITWISE_RSHIFT:        return "TOKEN_BITWISE_RSHIFT";
        case TOKEN_BITWISE_RSHIFT_ASSIGN: return "TOKEN_BITWISE_RSHIFT_ASSIGN";
        case TOKEN_ARITH_RSHIFT:          return "TOKEN_ARITH_RSHIFT";
        case TOKEN_ARITH_RSHIFT_ASSIGN:   return "TOKEN_ARITH_RSHIFT_ASSIGN";
        case TOKEN_QUESTION:              return "TOKEN_QUESTION";
        case TOKEN_AT:                    return "TOKEN_AT";
        case TOKEN_LBRACE_SQUARE:         return "TOKEN_LBRACE_SQUARE";
        case TOKEN_BSLASH:                return "TOKEN_BSLASH";
        case TOKEN_RBRACE_SQUARE:         return "TOKEN_RBRACE_SQUARE";
        case TOKEN_CARET:                 return "TOKEN_CARET";
        case TOKEN_BITWISE_XOR_ASSIGN:    return "TOKEN_BITWISE_XOR_ASSIGN";
        case TOKEN_BACKTICK:              return "TOKEN_BACKTICK";
        case TOKEN_LBRACE_CURLY:          return "TOKEN_LBRACE_CURLY";
        case TOKEN_PIPE:                  return "TOKEN_PIPE";
        case TOKEN_BITWISE_OR_ASSIGN:     return "TOKEN_BITWISE_OR_ASSIGN";
        case TOKEN_PIPEOUT:               return "TOKEN_PIPEOUT";
        case TOKEN_LOGICAL_OR:            return "TOKEN_LOGICAL_OR";
        case TOKEN_LOGICAL_OR_ASSIGN:     return "TOKEN_LOGICAL_OR_ASSIGN";
        case TOKEN_RBRACE_CURLY:          return "TOKEN_RBRACE_CURLY";
        case TOKEN_TILDE:                 return "TOKEN_TILDE";
        case TOKEN_NEWLINE:               return "TOKEN_NEWLINE";
        /* special operations */
        case TOKOP_NOP:                   return "TOKOP_NOP";
        case TOKOP_FNCALL:                return "TOKOP_FNCALL";
        case TOKOP_INDEXING:              return "TOKOP_INDEXING";
        case TOKOP_WEAK_ASSIGN:           return "TOKOP_WEAK_ASSIGN";
        case TOKOP_TERNARY_COND:          return "TOKOP_TERNARY_COND";
        case TOKOP_FNARGS_INDEXING:       return "TOKOP_FNARGS_INDEXING";
        /* keywords */
        case TOKEN_KWD_MODULE:            return "TOKEN_KWD_MODULE";
        case TOKEN_KWD_PROC:              return "TOKEN_KWD_PROC";
        case TOKEN_KWD_START:             return "TOKEN_KWD_START";
        case TOKEN_KWD_END:               return "TOKEN_KWD_END";
        case TOKEN_KWD_BLOCK:             return "TOKEN_KWD_BLOCK";
        case TOKEN_KWD_IF:                return "TOKEN_KWD_IF";
        case TOKEN_KWD_THEN:              return "TOKEN_KWD_THEN";
        case TOKEN_KWD_ELIF:              return "TOKEN_KWD_ELIF";
        case TOKEN_KWD_ELSE:              return "TOKEN_KWD_ELSE";
        case TOKEN_KWD_WHILE:             return "TOKEN_KWD_WHILE";
        case TOKEN_KWD_BREAK:             return "TOKEN_KWD_BREAK";
        case TOKEN_KWD_CONTINUE:          return "TOKEN_KWD_CONTINUE";
        case TOKEN_KWD_FOR:               return "TOKEN_KWD_FOR";
        case TOKEN_KWD_FROM:              return "TOKEN_KWD_FROM";
        case TOKEN_KWD_IN:                return "TOKEN_KWD_IN";
        case TOKEN_KWD_TO:                return "TOKEN_KWD_TO";
        case TOKEN_KWD_BY:                return "TOKEN_KWD_BY";
        case TOKEN_KWD_DO:                return "TOKEN_KWD_DO";
        case TOKEN_KWD_VAR:               return "TOKEN_KWD_VAR";
        case TOKEN_KWD_CONST:             return "TOKEN_KWD_CONST";
        case TOKEN_KWD_PASS:              return "TOKEN_KWD_PASS";
        case TOKEN_KWD_RETURN:            return "TOKEN_KWD_RETURN";
        case TOKEN_KWD_WEAK:              return "TOKEN_KWD_WEAK";
        /* identifier */
        case TOKEN_IDENTIFIER:            return "TOKEN_IDENTIFIER";
        /* literals */
        case TOKEN_BOOL_LITERAL:          return "TOKEN_BOOL_LITERAL";
        case TOKEN_CHAR_LITERAL:          return "TOKEN_CHAR_LITERAL";
        case TOKEN_BINFLOAT_LITERAL:      return "TOKEN_BINFLOAT_LITERAL";
        case TOKEN_OCTFLOAT_LITERAL:      return "TOKEN_OCTFLOAT_LITERAL";
        case TOKEN_DECFLOAT_LITERAL:      return "TOKEN_DECFLOAT_LITERAL";
        case TOKEN_HEXFLOAT_LITERAL:      return "TOKEN_HEXFLOAT_LITERAL";
        case TOKEN_BININT_LITERAL:        return "TOKEN_BININT_LITERAL";
        case TOKEN_OCTINT_LITERAL:        return "TOKEN_OCTINT_LITERAL";
        case TOKEN_DECINT_LITERAL:        return "TOKEN_DECINT_LITERAL";
        case TOKEN_HEXINT_LITERAL:        return "TOKEN_HEXINT_LITERAL";
        case TOKEN_STR_LITERAL:           return "TOKEN_STR_LITERAL";
        case TOKEN_INTERP_STR_LITERAL:    return "TOKEN_INTERP_STR_LITERAL";
        /* default cases */
        case TOKEN_EOF:                   return "TOKEN_EOF";
        case TOKEN_INVALID:               return "TOKEN_INVALID";
        case YYEMPTY:                     return "YYEMPTY";
        case YYerror:                     return "YYerror";
        case YYUNDEF:                     return "YYUNDEF";
    }
    return "INTERNAL";
}

/* contributor's warning: ensure tokens are grouped and sorted in alphabetical order */
const char *lex_Token_getsymbol(lex_Token_t code)
{
    switch (code) {
        /* operators and seperators */
        case TOKEN_BANG:                  return "!";
        case TOKEN_LOGICAL_UNEQUAL:       return "!=";
        case TOKEN_LOGICAL_UNIDENTICAL:   return "!==";
        case TOKEN_DQUOTE:                return "\"";
        case TOKEN_DOLLAR:                return "$";
        case TOKEN_PERCENT:               return "%";
        case TOKEN_MODULO_ASSIGN:         return "%=";
        case TOKEN_AMPERSAND:             return "&";
        case TOKEN_LOGICAL_AND:           return "&&";
        case TOKEN_LOGICAL_AND_ASSIGN:    return "&&=";
        case TOKEN_BITWISE_AND_ASSIGN:    return "&=";
        case TOKEN_SQUOTE:                return "'";
        case TOKEN_LBRACE_PAREN:          return "(";
        case TOKEN_RBRACE_PAREN:          return ")";
        case TOKEN_ASTERIX:               return "*";
        case TOKEN_EXPONENT:              return "**";
        case TOKEN_EXPONENT_ASSIGN:       return "**=";
        case TOKEN_MULTIPLY_ASSIGN:       return "*=";
        case TOKEN_PLUS:                  return "+";
        case TOKEN_INCREMENT:             return "++";
        case TOKEN_ADD_ASSIGN:            return "+=";
        case TOKEN_COMMA:                 return ",";
        case TOKEN_MINUS:                 return "-";
        case TOKEN_DECREMENT:             return "--";
        case TOKEN_SUBSTRACT_ASSIGN:      return "-=";
        case TOKEN_SARROW:                return "->";
        case TOKEN_DOT:                   return ".";
        case TOKEN_ELIPSIS:               return "...";
        case TOKEN_FSLASH:                return "/";
        case TOKEN_FLOOR_DIVIDE:          return "//";
        case TOKEN_FLOOR_DIVIDE_ASSIGN:   return "//=";
        case TOKEN_DIVIDE_ASSIGN:         return "/=";
        case TOKEN_COLON:                 return ":";
        case TOKEN_DCOLON:                return "::";
        case TOKEN_SEMICOLON:             return ";";
        case TOKEN_LBRACE_ANGULAR:        return "<";
        case TOKEN_BITWISE_LSHIFT:        return "<<";
        case TOKEN_BITWISE_LSHIFT_ASSIGN: return "<<=";
        case TOKEN_LOGICAL_LESSER_EQUAL:  return "<=";
        case TOKEN_ASSIGN:                return "=";
        case TOKEN_LOGICAL_EQUAL:         return "==";
        case TOKEN_LOGICAL_IDENTICAL:     return "===";
        case TOKEN_DARROW:                return "=>";
        case TOKEN_RBRACE_ANGULAR:        return ">";
        case TOKEN_LOGICAL_GREATER_EQUAL: return ">=";
        case TOKEN_BITWISE_RSHIFT:        return ">>";
        case TOKEN_BITWISE_RSHIFT_ASSIGN: return ">>=";
        case TOKEN_ARITH_RSHIFT:          return ">>>";
        case TOKEN_ARITH_RSHIFT_ASSIGN:   return ">>>=";
        case TOKEN_QUESTION:              return "?";
        case TOKEN_AT:                    return "@";
        case TOKEN_LBRACE_SQUARE:         return "[";
        case TOKEN_BSLASH:                return "\\";
        case TOKEN_RBRACE_SQUARE:         return "]";
        case TOKEN_CARET:                 return "^";
        case TOKEN_BITWISE_XOR_ASSIGN:    return "^=";
        case TOKEN_BACKTICK:              return "`";
        case TOKEN_LBRACE_CURLY:          return "{";
        case TOKEN_PIPE:                  return "|";
        case TOKEN_BITWISE_OR_ASSIGN:     return "|=";
        case TOKEN_PIPEOUT:               return "|>";
        case TOKEN_LOGICAL_OR:            return "||";
        case TOKEN_LOGICAL_OR_ASSIGN:     return "||=";
        case TOKEN_RBRACE_CURLY:          return "}";
        case TOKEN_TILDE:                 return "~";
        case TOKEN_NEWLINE:               return "\\n";
        /* special operations */
        case TOKOP_NOP:                   return "NOP";
        case TOKOP_FNCALL:                return "()";
        case TOKOP_INDEXING:              return "[]";
        case TOKOP_WEAK_ASSIGN:           return "weak =";
        case TOKOP_TERNARY_COND:          return "?:";
        case TOKOP_FNARGS_INDEXING:       return "$[]";
        /* keywords */
        case TOKEN_KWD_MODULE:            return "module";
        case TOKEN_KWD_PROC:              return "proc";
        case TOKEN_KWD_START:             return "start";
        case TOKEN_KWD_END:               return "end";
        case TOKEN_KWD_BLOCK:             return "block";
        case TOKEN_KWD_IF:                return "if";
        case TOKEN_KWD_THEN:              return "then";
        case TOKEN_KWD_ELIF:              return "elif";
        case TOKEN_KWD_ELSE:              return "else";
        case TOKEN_KWD_WHILE:             return "while";
        case TOKEN_KWD_BREAK:             return "break";
        case TOKEN_KWD_CONTINUE:          return "continue";
        case TOKEN_KWD_FOR:               return "for";
        case TOKEN_KWD_FROM:              return "from";
        case TOKEN_KWD_IN:                return "in";
        case TOKEN_KWD_TO:                return "to";
        case TOKEN_KWD_BY:                return "by";
        case TOKEN_KWD_DO:                return "do";
        case TOKEN_KWD_VAR:               return "var";
        case TOKEN_KWD_CONST:             return "const";
        case TOKEN_KWD_PASS:              return "pass";
        case TOKEN_KWD_RETURN:            return "return";
        case TOKEN_KWD_WEAK:              return "weak";
        /* identifier */
        case TOKEN_IDENTIFIER:            return lex_Buffer_getstr() ? lex_Buffer_getstr() : "NULL";
        /* literals */
        case TOKEN_BOOL_LITERAL:          return lex_Buffer_getstr() ? lex_Buffer_getstr() : "NULL";
        case TOKEN_CHAR_LITERAL:          return lex_Buffer_getstr() ? lex_Buffer_getstr() : "NULL";
        case TOKEN_BINFLOAT_LITERAL:      return lex_Buffer_getstr() ? lex_Buffer_getstr() : "NULL";
        case TOKEN_OCTFLOAT_LITERAL:      return lex_Buffer_getstr() ? lex_Buffer_getstr() : "NULL";
        case TOKEN_DECFLOAT_LITERAL:      return lex_Buffer_getstr() ? lex_Buffer_getstr() : "NULL";
        case TOKEN_HEXFLOAT_LITERAL:      return lex_Buffer_getstr() ? lex_Buffer_getstr() : "NULL";
        case TOKEN_BININT_LITERAL:        return lex_Buffer_getstr() ? lex_Buffer_getstr() : "NULL";
        case TOKEN_OCTINT_LITERAL:        return lex_Buffer_getstr() ? lex_Buffer_getstr() : "NULL";
        case TOKEN_DECINT_LITERAL:        return lex_Buffer_getstr() ? lex_Buffer_getstr() : "NULL";
        case TOKEN_HEXINT_LITERAL:        return lex_Buffer_getstr() ? lex_Buffer_getstr() : "NULL";
        case TOKEN_STR_LITERAL:           return lex_Buffer_getstr() ? lex_Buffer_getstr() : "NULL";
        case TOKEN_INTERP_STR_LITERAL:    return lex_Buffer_getstr() ? lex_Buffer_getstr() : "NULL";
        /* default cases */
        case TOKEN_EOF:                   return "end-of-file";
        case TOKEN_INVALID:               return "invalid token";
        case YYEMPTY:                     return "<YYEMPTY>";
        case YYerror:                     return "<YYerror>";
        case YYUNDEF:                     return "<YYUNDEF>";
    }
    return "<internal>";
}

#else
    #warning re-inclusion of module 'lexer/tokens.c.h'
#endif
