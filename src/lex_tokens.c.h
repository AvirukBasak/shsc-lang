#ifndef LEX_TOKENS_CH
#define LEX_TOKENS_CH

// contributor's warning: ensure tokens are grouped and sorted in alphabetical order
char *lex_get_tokcode(LexToken code)
{
    switch (code) {
        // operators and seperators
        case LEX_BANG:                  return "LEX_BANG";
        case LEX_LOGICAL_UNEQUAL:       return "LEX_LOGICAL_UNEQUAL";
        case LEX_LOGICAL_UNIDENTICAL:   return "LEX_LOGICAL_UNIDENTICAL";
        case LEX_DQUOTE:                return "LEX_DQUOTE";
        case LEX_DOLLAR:                return "LEX_DOLLAR";
        case LEX_PERCENT:               return "LEX_PERCENT";
        case LEX_MODULO_ASSIGN:         return "LEX_MODULO_ASSIGN";
        case LEX_AMPERSAND:             return "LEX_AMPERSAND";
        case LEX_LOGICAL_AND:           return "LEX_LOGICAL_AND";
        case LEX_LOGICAL_AND_ASSIGN:    return "LEX_LOGICAL_AND_ASSIGN";
        case LEX_BITWISE_AND_ASSIGN:    return "LEX_BITWISE_AND_ASSIGN";
        case LEX_SQUOTE:                return "LEX_SQUOTE";
        case LEX_LBRACE_PAREN:          return "LEX_LBRACE_PAREN";
        case LEX_RBRACE_PAREN:          return "LEX_RBRACE_PAREN";
        case LEX_ASTERIX:               return "LEX_ASTERIX";
        case LEX_EXPONENT:              return "LEX_EXPONENT";
        case LEX_EXPONENT_ASSIGN:       return "LEX_EXPONENT_ASSIGN";
        case LEX_MULTIPLY_ASSIGN:       return "LEX_MULTIPLY_ASSIGN";
        case LEX_PLUS:                  return "LEX_PLUS";
        case LEX_INCREMENT:             return "LEX_INCREMENT";
        case LEX_ADD_ASSIGN:            return "LEX_ADD_ASSIGN";
        case LEX_COMMA:                 return "LEX_COMMA";
        case LEX_MINUS:                 return "LEX_MINUS";
        case LEX_DECREMENT:             return "LEX_DECREMENT";
        case LEX_SUBSTRACT_ASSIGN:      return "LEX_SUBSTRACT_ASSIGN";
        case LEX_SARROW:                return "LEX_SARROW";
        case LEX_DOT:                   return "LEX_DOT";
        case LEX_ELIPSIS:               return "LEX_ELIPSIS";
        case LEX_FSLASH:                return "LEX_FSLASH";
        case LEX_FLOOR_DIVIDE:          return "LEX_FLOOR_DIVIDE";
        case LEX_FLOOR_DIVIDE_ASSIGN:   return "LEX_FLOOR_DIVIDE_ASSIGN";
        case LEX_DIVIDE_ASSIGN:         return "LEX_DIVIDE_ASSIGN";
        case LEX_COLON:                 return "LEX_COLON";
        case LEX_DCOLON:                return "LEX_DCOLON";
        case LEX_SEMICOLON:             return "LEX_SEMICOLON";
        case LEX_LBRACE_ANGULAR:        return "LEX_LBRACE_ANGULAR";
        case LEX_BITWISE_LSHIFT:        return "LEX_BITWISE_LSHIFT";
        case LEX_BITWISE_LSHIFT_ASSIGN: return "LEX_BITWISE_LSHIFT_ASSIGN";
        case LEX_LOGICAL_LESSER_EQUAL:  return "LEX_LOGICAL_LESSER_EQUAL";
        case LEX_ASSIGN:                return "LEX_ASSIGN";
        case LEX_LOGICAL_EQUAL:         return "LEX_LOGICAL_EQUAL";
        case LEX_LOGICAL_IDENTICAL:     return "LEX_LOGICAL_IDENTICAL";
        case LEX_DARROW:                return "LEX_DARROW";
        case LEX_RBRACE_ANGULAR:        return "LEX_RBRACE_ANGULAR";
        case LEX_LOGICAL_GREATER_EQUAL: return "LEX_LOGICAL_GREATER_EQUAL";
        case LEX_BITWISE_RSHIFT:        return "LEX_BITWISE_RSHIFT";
        case LEX_BITWISE_RSHIFT_ASSIGN: return "LEX_BITWISE_RSHIFT_ASSIGN";
        case LEX_ARITH_RSHIFT:          return "LEX_ARITH_RSHIFT";
        case LEX_ARITH_RSHIFT_ASSIGN:   return "LEX_ARITH_RSHIFT_ASSIGN";
        case LEX_QUESTION:              return "LEX_QUESTION";
        case LEX_AT:                    return "LEX_AT";
        case LEX_LBRACE_SQUARE:         return "LEX_LBRACE_SQUARE";
        case LEX_BSLASH:                return "LEX_BSLASH";
        case LEX_RBRACE_SQUARE:         return "LEX_RBRACE_SQUARE";
        case LEX_CARET:                 return "LEX_CARET";
        case LEX_BITWISE_XOR_ASSIGN:    return "LEX_BITWISE_XOR_ASSIGN";
        case LEX_BACKTICK:              return "LEX_BACKTICK";
        case LEX_LBRACE_CURLY:          return "LEX_LBRACE_CURLY";
        case LEX_PIPE:                  return "LEX_PIPE";
        case LEX_BITWISE_OR_ASSIGN:     return "LEX_BITWISE_OR_ASSIGN";
        case LEX_PIPEOUT:               return "LEX_PIPEOUT";
        case LEX_LOGICAL_OR:            return "LEX_LOGICAL_OR";
        case LEX_LOGICAL_OR_ASSIGN:     return "LEX_LOGICAL_OR_ASSIGN";
        case LEX_RBRACE_CURLY:          return "LEX_RBRACE_CURLY";
        case LEX_TILDE:                 return "LEX_TILDE";
        // keywords
        case LEX_KWD_CALC:              return "LEX_KWD_CALC";
        case LEX_KWD_END:               return "LEX_KWD_END";
        case LEX_KWD_IF:                return "LEX_KWD_IF";
        case LEX_KWD_START:             return "LEX_KWD_START";
        case LEX_KWD_WHILE:             return "LEX_KWD_WHILE";
        // default cases
        case LEX_EOF:                   return "LEX_EOF";
        case LEX_INVALID:               return "LEX_INVALID";
        default:                        return "UNKNOWN";
    }
}

// contributor's warning: ensure tokens are grouped and sorted in alphabetical order
char *lex_get_symbol(LexToken code)
{
    switch (code) {
        // operators and seperators
        case LEX_BANG:                  return "!";
        case LEX_LOGICAL_UNEQUAL:       return "!=";
        case LEX_LOGICAL_UNIDENTICAL:   return "!==";
        case LEX_DQUOTE:                return "\"";
        case LEX_DOLLAR:                return "$";
        case LEX_PERCENT:               return "%";
        case LEX_MODULO_ASSIGN:         return "%=";
        case LEX_AMPERSAND:             return "&";
        case LEX_LOGICAL_AND:           return "&&";
        case LEX_LOGICAL_AND_ASSIGN:    return "&&=";
        case LEX_BITWISE_AND_ASSIGN:    return "&=";
        case LEX_SQUOTE:                return "'";
        case LEX_LBRACE_PAREN:          return "(";
        case LEX_RBRACE_PAREN:          return ")";
        case LEX_ASTERIX:               return "*";
        case LEX_EXPONENT:              return "**";
        case LEX_EXPONENT_ASSIGN:       return "**=";
        case LEX_MULTIPLY_ASSIGN:       return "*=";
        case LEX_PLUS:                  return "+";
        case LEX_INCREMENT:             return "++";
        case LEX_ADD_ASSIGN:            return "+=";
        case LEX_COMMA:                 return ",";
        case LEX_MINUS:                 return "-";
        case LEX_DECREMENT:             return "--";
        case LEX_SUBSTRACT_ASSIGN:      return "-=";
        case LEX_SARROW:                return "->";
        case LEX_DOT:                   return ".";
        case LEX_ELIPSIS:               return "...";
        case LEX_FSLASH:                return "/";
        case LEX_FLOOR_DIVIDE:          return "//";
        case LEX_FLOOR_DIVIDE_ASSIGN:   return "//=";
        case LEX_DIVIDE_ASSIGN:         return "/=";
        case LEX_COLON:                 return ":";
        case LEX_DCOLON:                return "::";
        case LEX_SEMICOLON:             return ";";
        case LEX_LBRACE_ANGULAR:        return "<";
        case LEX_BITWISE_LSHIFT:        return "<<";
        case LEX_BITWISE_LSHIFT_ASSIGN: return "<<=";
        case LEX_LOGICAL_LESSER_EQUAL:  return "<=";
        case LEX_ASSIGN:                return "=";
        case LEX_LOGICAL_EQUAL:         return "==";
        case LEX_LOGICAL_IDENTICAL:     return "===";
        case LEX_DARROW:                return "=>";
        case LEX_RBRACE_ANGULAR:        return ">";
        case LEX_LOGICAL_GREATER_EQUAL: return ">=";
        case LEX_BITWISE_RSHIFT:        return ">>";
        case LEX_BITWISE_RSHIFT_ASSIGN: return ">>=";
        case LEX_ARITH_RSHIFT:          return ">>>";
        case LEX_ARITH_RSHIFT_ASSIGN:   return ">>>=";
        case LEX_QUESTION:              return "?";
        case LEX_AT:                    return "@";
        case LEX_LBRACE_SQUARE:         return "[";
        case LEX_BSLASH:                return "\\";
        case LEX_RBRACE_SQUARE:         return "]";
        case LEX_CARET:                 return "^";
        case LEX_BITWISE_XOR_ASSIGN:    return "^=";
        case LEX_BACKTICK:              return "`";
        case LEX_LBRACE_CURLY:          return "{";
        case LEX_PIPE:                  return "|";
        case LEX_BITWISE_OR_ASSIGN:     return "|=";
        case LEX_PIPEOUT:               return "|>";
        case LEX_LOGICAL_OR:            return "||";
        case LEX_LOGICAL_OR_ASSIGN:     return "||=";
        case LEX_RBRACE_CURLY:          return "}";
        case LEX_TILDE:                 return "~";
        // keywords
        case LEX_KWD_CALC:              return "calc";
        case LEX_KWD_END:               return "end";
        case LEX_KWD_IF:                return "if";
        case LEX_KWD_START:             return "start";
        case LEX_KWD_WHILE:             return "while";
        // default cases
        case LEX_EOF:                   return "<eof>";
        case LEX_INVALID:               return "<invalid>";
        default:                        return "<unknown>";
    }
}

#endif
