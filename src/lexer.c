
typedef enum {
    LEX_KWD_START,
    LEX_KWD_WHILE,
    LEX_KWD_CALC,
    LEX_LOGICAL_IDENTICAL,
    LEX_LOGICAL_UNINDENTICAL,
    LEX_KWD_IF,
    LEX_LOGICAL_AND,
    LEX_LOGICAL_OR,
    LEX_LOGICAL_EQUALITY,
    LEX_LOGICAL_GREATER_EQUAL,
    LEX_LOGICAL_LESSER_EQUAL,
    LEX_LOGICAL_UNEQUALITY,
    LEX_BITWISE_LSHIFT,
    LEX_BITWISE_RSHIFT,
    LEX_EXPONENT,
    LEX_SARROW,
    LEX_DARROW,
    LEX_PIPEOUT,
    LEX_LOGICAL_NOT,
    LEX_BITWISE_AND,
    LEX_BITWISE_OR,
    LEX_BITWISE_NOT,
    LEX_BITWISE_XOR,
    LEX_RBRACE_ANGULAR,
    LEX_LBRACE_ANGULAR,
    LEX_RBRACE_PAREN,
    LEX_LBRACE_PAREN,
    LEX_RBRACE_CURLY,
    LEX_LBRACE_CURLY,
    LEX_RBRACE_SQUARE,
    LEX_LBRACE_SQUARE,
    LEX_ASSIGN,
    LEX_PLUS,
    LEX_MINUS,
    LEX_ASTERIX,
    LEX_FSLASH,
    LEX_BSLASH,
    LEX_PERCENT,
    LEX_COMMA,
    LEX_COLON,
    LEX_SEMICOLON,
    LEX_DOT,
    LEX_SQUOTE,
    LEX_DQUOTE,
    LEX_BACKTICK,
    LEX_QUESTION,
    LEX_ATRATE,
    LEX_KWD_SET,
    LEX_IDENTIFIER
} LexToken;

char const *lexer_buffer = NULL;

void lexer_init(size_t sz) {
    if (lexer_buffer) return;
    lexer_buffer = calloc(1, sz);
}

LexToken lexer_nexttoken()
{
    char curr = lexer_getchar();
    while (curr != EOF) {
        lexer_buffpush(curr);
             if (lexer_buffmatch("start")) return LEX_KWD_START;
        else if (lexer_buffmatch("while")) return LEX_KWD_WHILE;
        else if (lexer_buffmatch("calc"))  return LEX_KWD_CALC;
        else if (lexer_buffmatch("==="))   return LEX_LOGICAL_IDENTICAL;
        else if (lexer_buffmatch("!=="))   return LEX_LOGICAL_UNINDENTICAL;
        else if (lexer_buffmatch("if"))    return LEX_KWD_IF;
        else if (lexer_buffmatch("&&"))    return LEX_LOGICAL_AND;
        else if (lexer_buffmatch("||"))    return LEX_LOGICAL_OR;
        else if (lexer_buffmatch("=="))    return LEX_LOGICAL_EQUALITY;
        else if (lexer_buffmatch(">="))    return LEX_LOGICAL_GREATER_EQUAL;
        else if (lexer_buffmatch("<="))    return LEX_LOGICAL_LESSER_EQUAL;
        else if (lexer_buffmatch("!="))    return LEX_LOGICAL_UNEQUALITY;
        else if (lexer_buffmatch("<<"))    return LEX_BITWISE_LSHIFT;
        else if (lexer_buffmatch(">>"))    return LEX_BITWISE_RSHIFT;
        else if (lexer_buffmatch("**"))    return LEX_EXPONENT;
        else if (lexer_buffmatch("->"))    return LEX_SARROW;
        else if (lexer_buffmatch("=>"))    return LEX_DARROW;
        else if (lexer_buffmatch("|>"))    return LEX_PIPEOUT;
        else if (lexer_buffmatch("!"))     return LEX_LOGICAL_NOT;
        else if (lexer_buffmatch("&"))     return LEX_BITWISE_AND;
        else if (lexer_buffmatch("|"))     return LEX_BITWISE_OR;
        else if (lexer_buffmatch("~"))     return LEX_BITWISE_NOT;
        else if (lexer_buffmatch("^"))     return LEX_BITWISE_XOR;
        else if (lexer_buffmatch(">"))     return LEX_RBRACE_ANGULAR;
        else if (lexer_buffmatch("<"))     return LEX_LBRACE_ANGULAR;
        else if (lexer_buffmatch(")"))     return LEX_RBRACE_PAREN;
        else if (lexer_buffmatch("("))     return LEX_LBRACE_PAREN;
        else if (lexer_buffmatch("{"))     return LEX_RBRACE_CURLY;
        else if (lexer_buffmatch("}"))     return LEX_LBRACE_CURLY;
        else if (lexer_buffmatch("["))     return LEX_RBRACE_SQUARE;
        else if (lexer_buffmatch("]"))     return LEX_LBRACE_SQUARE;
        else if (lexer_buffmatch("="))     return LEX_ASSIGN;
        else if (lexer_buffmatch("+"))     return LEX_PLUS;
        else if (lexer_buffmatch("-"))     return LEX_MINUS;
        else if (lexer_buffmatch("*"))     return LEX_ASTERIX;
        else if (lexer_buffmatch("/"))     return LEX_FSLASH;
        else if (lexer_buffmatch("\\"))    return LEX_BSLASH;
        else if (lexer_buffmatch("%"))     return LEX_PERCENT;
        else if (lexer_buffmatch(","))     return LEX_COMMA;
        else if (lexer_buffmatch(":"))     return LEX_COLON;
        else if (lexer_buffmatch(";"))     return LEX_SEMICOLON;
        else if (lexer_buffmatch("."))     return LEX_DOT;
        else if (lexer_buffmatch("'"))     return LEX_SQUOTE;
        else if (lexer_buffmatch("\""))    return LEX_DQUOTE;
        else if (lexer_buffmatch("`"))     return LEX_BACKTICK;
        else if (lexer_buffmatch("?"))     return LEX_QUESTION;
        else if (lexer_buffmatch("@"))     return LEX_ATRATE;
        else if (lexer_buffmatch("$"))     return LEX_KWD_SET;
        else if (lexer_isidentifier())     return LEX_IDENTIFIER;
        else lexer_throw("syntax error");
        curr = lexer_getchar();
    }
}
