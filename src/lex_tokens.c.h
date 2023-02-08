#ifndef LEX_TOKENS_CH
#define LEX_TOKENS_CH

// contributor's warning: ensure tokens are grouped and sorted in alphabetical order
char *lex_get_tokcode(LexToken code)
{
    switch (code) {
        // operators and seperators
        case LEXTOK_BANG:                  return "LEXTOK_BANG";
        case LEXTOK_LOGICAL_UNEQUAL:       return "LEXTOK_LOGICAL_UNEQUAL";
        case LEXTOK_LOGICAL_UNIDENTICAL:   return "LEXTOK_LOGICAL_UNIDENTICAL";
        case LEXTOK_DQUOTE:                return "LEXTOK_DQUOTE";
        case LEXTOK_DOLLAR:                return "LEXTOK_DOLLAR";
        case LEXTOK_PERCENT:               return "LEXTOK_PERCENT";
        case LEXTOK_MODULO_ASSIGN:         return "LEXTOK_MODULO_ASSIGN";
        case LEXTOK_AMPERSAND:             return "LEXTOK_AMPERSAND";
        case LEXTOK_LOGICAL_AND:           return "LEXTOK_LOGICAL_AND";
        case LEXTOK_LOGICAL_AND_ASSIGN:    return "LEXTOK_LOGICAL_AND_ASSIGN";
        case LEXTOK_BITWISE_AND_ASSIGN:    return "LEXTOK_BITWISE_AND_ASSIGN";
        case LEXTOK_SQUOTE:                return "LEXTOK_SQUOTE";
        case LEXTOK_LBRACE_PAREN:          return "LEXTOK_LBRACE_PAREN";
        case LEXTOK_RBRACE_PAREN:          return "LEXTOK_RBRACE_PAREN";
        case LEXTOK_ASTERIX:               return "LEXTOK_ASTERIX";
        case LEXTOK_EXPONENT:              return "LEXTOK_EXPONENT";
        case LEXTOK_EXPONENT_ASSIGN:       return "LEXTOK_EXPONENT_ASSIGN";
        case LEXTOK_MULTIPLY_ASSIGN:       return "LEXTOK_MULTIPLY_ASSIGN";
        case LEXTOK_PLUS:                  return "LEXTOK_PLUS";
        case LEXTOK_INCREMENT:             return "LEXTOK_INCREMENT";
        case LEXTOK_ADD_ASSIGN:            return "LEXTOK_ADD_ASSIGN";
        case LEXTOK_COMMA:                 return "LEXTOK_COMMA";
        case LEXTOK_MINUS:                 return "LEXTOK_MINUS";
        case LEXTOK_DECREMENT:             return "LEXTOK_DECREMENT";
        case LEXTOK_SUBSTRACT_ASSIGN:      return "LEXTOK_SUBSTRACT_ASSIGN";
        case LEXTOK_SARROW:                return "LEXTOK_SARROW";
        case LEXTOK_DOT:                   return "LEXTOK_DOT";
        case LEXTOK_ELIPSIS:               return "LEXTOK_ELIPSIS";
        case LEXTOK_FSLASH:                return "LEXTOK_FSLASH";
        case LEXTOK_FLOOR_DIVIDE:          return "LEXTOK_FLOOR_DIVIDE";
        case LEXTOK_FLOOR_DIVIDE_ASSIGN:   return "LEXTOK_FLOOR_DIVIDE_ASSIGN";
        case LEXTOK_DIVIDE_ASSIGN:         return "LEXTOK_DIVIDE_ASSIGN";
        case LEXTOK_COLON:                 return "LEXTOK_COLON";
        case LEXTOK_DCOLON:                return "LEXTOK_DCOLON";
        case LEXTOK_SEMICOLON:             return "LEXTOK_SEMICOLON";
        case LEXTOK_LBRACE_ANGULAR:        return "LEXTOK_LBRACE_ANGULAR";
        case LEXTOK_BITWISE_LSHIFT:        return "LEXTOK_BITWISE_LSHIFT";
        case LEXTOK_BITWISE_LSHIFT_ASSIGN: return "LEXTOK_BITWISE_LSHIFT_ASSIGN";
        case LEXTOK_LOGICAL_LESSER_EQUAL:  return "LEXTOK_LOGICAL_LESSER_EQUAL";
        case LEXTOK_ASSIGN:                return "LEXTOK_ASSIGN";
        case LEXTOK_LOGICAL_EQUAL:         return "LEXTOK_LOGICAL_EQUAL";
        case LEXTOK_LOGICAL_IDENTICAL:     return "LEXTOK_LOGICAL_IDENTICAL";
        case LEXTOK_DARROW:                return "LEXTOK_DARROW";
        case LEXTOK_RBRACE_ANGULAR:        return "LEXTOK_RBRACE_ANGULAR";
        case LEXTOK_LOGICAL_GREATER_EQUAL: return "LEXTOK_LOGICAL_GREATER_EQUAL";
        case LEXTOK_BITWISE_RSHIFT:        return "LEXTOK_BITWISE_RSHIFT";
        case LEXTOK_BITWISE_RSHIFT_ASSIGN: return "LEXTOK_BITWISE_RSHIFT_ASSIGN";
        case LEXTOK_ARITH_RSHIFT:          return "LEXTOK_ARITH_RSHIFT";
        case LEXTOK_ARITH_RSHIFT_ASSIGN:   return "LEXTOK_ARITH_RSHIFT_ASSIGN";
        case LEXTOK_QUESTION:              return "LEXTOK_QUESTION";
        case LEXTOK_AT:                    return "LEXTOK_AT";
        case LEXTOK_LBRACE_SQUARE:         return "LEXTOK_LBRACE_SQUARE";
        case LEXTOK_BSLASH:                return "LEXTOK_BSLASH";
        case LEXTOK_RBRACE_SQUARE:         return "LEXTOK_RBRACE_SQUARE";
        case LEXTOK_CARET:                 return "LEXTOK_CARET";
        case LEXTOK_BITWISE_XOR_ASSIGN:    return "LEXTOK_BITWISE_XOR_ASSIGN";
        case LEXTOK_BACKTICK:              return "LEXTOK_BACKTICK";
        case LEXTOK_LBRACE_CURLY:          return "LEXTOK_LBRACE_CURLY";
        case LEXTOK_PIPE:                  return "LEXTOK_PIPE";
        case LEXTOK_BITWISE_OR_ASSIGN:     return "LEXTOK_BITWISE_OR_ASSIGN";
        case LEXTOK_PIPEOUT:               return "LEXTOK_PIPEOUT";
        case LEXTOK_LOGICAL_OR:            return "LEXTOK_LOGICAL_OR";
        case LEXTOK_LOGICAL_OR_ASSIGN:     return "LEXTOK_LOGICAL_OR_ASSIGN";
        case LEXTOK_RBRACE_CURLY:          return "LEXTOK_RBRACE_CURLY";
        case LEXTOK_TILDE:                 return "LEXTOK_TILDE";
        // keywords
        case LEXTOK_KWD_CALC:              return "LEXTOK_KWD_CALC";
        case LEXTOK_KWD_END:               return "LEXTOK_KWD_END";
        case LEXTOK_KWD_IF:                return "LEXTOK_KWD_IF";
        case LEXTOK_KWD_START:             return "LEXTOK_KWD_START";
        case LEXTOK_KWD_WHILE:             return "LEXTOK_KWD_WHILE";
        // identifier
        case LEXTOK_IDENTIFIER:            return "LEXTOK_IDENTIFIER";
        // literals
        case LEXTOK_CHAR_LITERAL:          return "LEXTOK_CHAR_LITERAL";
        case LEXTOK_CHAR_LITERAL:          return "<charlit>";
        case LEXTOK_BINFLOAT_LITERAL:      return "LEXTOK_BINFLOAT_LITERAL";
        case LEXTOK_OCTFLOAT_LITERAL:      return "LEXTOK_OCTFLOAT_LITERAL";
        case LEXTOK_DECFLOAT_LITERAL:      return "LEXTOK_DECFLOAT_LITERAL";
        case LEXTOK_HEXFLOAT_LITERAL:      return "LEXTOK_HEXFLOAT_LITERAL";
        case LEXTOK_BININT_LITERAL:        return "LEXTOK_BININT_LITERAL";
        case LEXTOK_OCTINT_LITERAL:        return "LEXTOK_OCTINT_LITERAL";
        case LEXTOK_DECINT_LITERAL:        return "LEXTOK_DECINT_LITERAL";
        case LEXTOK_HEXINT_LITERAL:        return "LEXTOK_HEXINT_LITERAL";
        case LEXTOK_STR_LITERAL:           return "LEXTOK_STR_LITERAL";
        // default cases
        case LEXTOK_EOF:                   return "LEXTOK_EOF";
        case LEXTOK_INVALID:               return "LEXTOK_INVALID";
        default:                           return "UNKNOWN";
    }
}

// contributor's warning: ensure tokens are grouped and sorted in alphabetical order
char *lex_get_symbol(LexToken code)
{
    switch (code) {
        // operators and seperators
        case LEXTOK_BANG:                  return "!";
        case LEXTOK_LOGICAL_UNEQUAL:       return "!=";
        case LEXTOK_LOGICAL_UNIDENTICAL:   return "!==";
        case LEXTOK_DQUOTE:                return "\"";
        case LEXTOK_DOLLAR:                return "$";
        case LEXTOK_PERCENT:               return "%";
        case LEXTOK_MODULO_ASSIGN:         return "%=";
        case LEXTOK_AMPERSAND:             return "&";
        case LEXTOK_LOGICAL_AND:           return "&&";
        case LEXTOK_LOGICAL_AND_ASSIGN:    return "&&=";
        case LEXTOK_BITWISE_AND_ASSIGN:    return "&=";
        case LEXTOK_SQUOTE:                return "'";
        case LEXTOK_LBRACE_PAREN:          return "(";
        case LEXTOK_RBRACE_PAREN:          return ")";
        case LEXTOK_ASTERIX:               return "*";
        case LEXTOK_EXPONENT:              return "**";
        case LEXTOK_EXPONENT_ASSIGN:       return "**=";
        case LEXTOK_MULTIPLY_ASSIGN:       return "*=";
        case LEXTOK_PLUS:                  return "+";
        case LEXTOK_INCREMENT:             return "++";
        case LEXTOK_ADD_ASSIGN:            return "+=";
        case LEXTOK_COMMA:                 return ",";
        case LEXTOK_MINUS:                 return "-";
        case LEXTOK_DECREMENT:             return "--";
        case LEXTOK_SUBSTRACT_ASSIGN:      return "-=";
        case LEXTOK_SARROW:                return "->";
        case LEXTOK_DOT:                   return ".";
        case LEXTOK_ELIPSIS:               return "...";
        case LEXTOK_FSLASH:                return "/";
        case LEXTOK_FLOOR_DIVIDE:          return "//";
        case LEXTOK_FLOOR_DIVIDE_ASSIGN:   return "//=";
        case LEXTOK_DIVIDE_ASSIGN:         return "/=";
        case LEXTOK_COLON:                 return ":";
        case LEXTOK_DCOLON:                return "::";
        case LEXTOK_SEMICOLON:             return ";";
        case LEXTOK_LBRACE_ANGULAR:        return "<";
        case LEXTOK_BITWISE_LSHIFT:        return "<<";
        case LEXTOK_BITWISE_LSHIFT_ASSIGN: return "<<=";
        case LEXTOK_LOGICAL_LESSER_EQUAL:  return "<=";
        case LEXTOK_ASSIGN:                return "=";
        case LEXTOK_LOGICAL_EQUAL:         return "==";
        case LEXTOK_LOGICAL_IDENTICAL:     return "===";
        case LEXTOK_DARROW:                return "=>";
        case LEXTOK_RBRACE_ANGULAR:        return ">";
        case LEXTOK_LOGICAL_GREATER_EQUAL: return ">=";
        case LEXTOK_BITWISE_RSHIFT:        return ">>";
        case LEXTOK_BITWISE_RSHIFT_ASSIGN: return ">>=";
        case LEXTOK_ARITH_RSHIFT:          return ">>>";
        case LEXTOK_ARITH_RSHIFT_ASSIGN:   return ">>>=";
        case LEXTOK_QUESTION:              return "?";
        case LEXTOK_AT:                    return "@";
        case LEXTOK_LBRACE_SQUARE:         return "[";
        case LEXTOK_BSLASH:                return "\\";
        case LEXTOK_RBRACE_SQUARE:         return "]";
        case LEXTOK_CARET:                 return "^";
        case LEXTOK_BITWISE_XOR_ASSIGN:    return "^=";
        case LEXTOK_BACKTICK:              return "`";
        case LEXTOK_LBRACE_CURLY:          return "{";
        case LEXTOK_PIPE:                  return "|";
        case LEXTOK_BITWISE_OR_ASSIGN:     return "|=";
        case LEXTOK_PIPEOUT:               return "|>";
        case LEXTOK_LOGICAL_OR:            return "||";
        case LEXTOK_LOGICAL_OR_ASSIGN:     return "||=";
        case LEXTOK_RBRACE_CURLY:          return "}";
        case LEXTOK_TILDE:                 return "~";
        // keywords
        case LEXTOK_KWD_CALC:              return "calc";
        case LEXTOK_KWD_END:               return "end";
        case LEXTOK_KWD_IF:                return "if";
        case LEXTOK_KWD_START:             return "start";
        case LEXTOK_KWD_WHILE:             return "while";
        // identifier
        case LEXTOK_IDENTIFIER:            return "<identifier>";
        // literals
        case LEXTOK_CHAR_LITERAL:          return "<charlit>";
        case LEXTOK_BINFLOAT_LITERAL:      return "<binfloattlit>";
        case LEXTOK_OCTFLOAT_LITERAL:      return "<octfloattlit>";
        case LEXTOK_DECFLOAT_LITERAL:      return "<decfloattlit>";
        case LEXTOK_HEXFLOAT_LITERAL:      return "<hexfloattlit>";
        case LEXTOK_BININT_LITERAL:        return "<binintlit>";
        case LEXTOK_OCTINT_LITERAL:        return "<octintlit>";
        case LEXTOK_DECINT_LITERAL:        return "<decintlit>";
        case LEXTOK_HEXINT_LITERAL:        return "<hexintlit>";
        case LEXTOK_STR_LITERAL:           return "<strlit>";
        // default cases
        case LEXTOK_EOF:                   return "<eof>";
        case LEXTOK_INVALID:               return "<invalid>";
        default:                           return "<unknown>";
    }
}

#endif
