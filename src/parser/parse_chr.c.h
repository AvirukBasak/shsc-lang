#ifndef PARSER_PARSE_CHR_C_H
#define PARSER_PARSE_CHR_C_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "globals.h"
#include "parser.h"

char parse_char(const char *str)
{
    char c = str[0];
    const size_t len = strlen(str);

    /* if the input string has only one character, return it */
    if (len == 1) c = str[0];

    /* if the input string has two characters and the first
       character is a backslash, then the second character is an
       escape sequence */
    else if (len == 2 && str[0] == '\\') {
        switch (str[1]) {
            case 'a': c = '\a'; break;
            case 'b': c = '\b'; break;
            case 'f': c = '\f'; break;
            case 'n': c = '\n'; break;
            case 'r': c = '\r'; break;
            case 't': c = '\t'; break;
            case 'v': c = '\v'; break;
            case '0': c = '\0'; break;
            default: c = str[1]; break;
        }
    }

    /* if the input string starts with '\x', it is a hexadecimal escape sequence */
    else if (len == 4 && str[0] == '\\' && str[1] == 'x' && isxdigit(str[2])) {
        char* endptr;
        int res = strtol(&str[2], &endptr, 16);
        if (!*endptr && 0 <= res && res <= 255) c = (char) res;
        else parse_throw("invalid hex escape sequence");
    }

    /* if the input string starts with '\', it is an octal escape sequence */
    else if (len == 4 && str[0] == '\\' && isdigit(str[1])) {
        char* endptr;
        int res = strtol(&str[1], &endptr, 8);
        if (!*endptr && 0 <= res && res <= 255) c = (char) res;
        else parse_throw("invalid octal escape sequence");
    }

    /* if the input string has more than two characters, it is an error */
    else parse_throw("invalid character token");

    return c;
}

#else
    #warning re-inclusion of module 'parser/parse_chr.c.h'
#endif
