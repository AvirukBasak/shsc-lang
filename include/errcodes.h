#ifndef ERRCODES_H
#define ERRCODES_H

#define ERR_MSG_MALLOCFAIL  " memory allocation failed"
#define ERR_MSG_REALLOCFAIL " memory reallocation failed"
#define ERR_MSG_NULLPTR     " null pointer error"

enum ErrCodes {
    ERR_LEXER = 1,
    ERR_PARSER,
    ERR_RUNTIME,
    ERR_MEMORY,
    ERR_DIE,
};

#endif
