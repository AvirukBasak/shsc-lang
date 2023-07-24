#ifndef PARSER_PARSE_STR_C_H
#define PARSER_PARSE_STR_C_H

#include "errcodes.h"
#include "parser.h"

/** Calls strdup, remember to free */
char *parse_str(const char *str)
{
    if (!str || !strcmp(str, "NULL")) str = "\0";
    const size_t len = strlen(str);
    char *parsed_str = (char*) malloc(len +1);
    if (!parsed_str) parse_throw("parse_str:" ERR_MSG_MALLOCFAIL);
    int parsed_index = 0;
    for (int i = 0; i < len; ++i) {
        /* if the current character is a backslash, it might be an escape sequence */
        if (str[i] == '\\') {
            /* move to the next character after the backslash */
            ++i;
            if (i >= len) {
                parse_throw("incomplete escape sequence");
                free(parsed_str);
            }
            /* octal escape sequence */
            if ( isdigit(str[i]) && len - (i+1) >= 2 && isdigit(str[i+1]) && isdigit(str[i+2]) ) {
                char *endptr;
                char oct[4] = { str[i], str[i+1], str[i+2], '\0' };
                int res = strtol(oct, &endptr, 8);
                if (!*endptr && 0 <= res && res <= 255) {
                    parsed_str[parsed_index++] = (char) res;
                    /* update the loop index */
                    i += 2;
                } else parse_throw("invalid octal escape sequence");
            }
            /* hex escape sequence */
            else if ( str[i] == 'x' && len - (i+1) >= 2 && isxdigit(str[i+1]) && isxdigit(str[i+2]) ) {
                char *endptr;
                char hex[3] = { str[i+1], str[i+2], '\0' };
                int res = strtol(hex, &endptr, 16);
                if (!*endptr && 0 <= res && res <= 255) {
                    parsed_str[parsed_index++] = (char) res;
                    /* update the loop index */
                    i += 2;
                } else parse_throw("invalid hex escape sequence");
            }
            /* other escape sequences */
            else switch (str[i]) {
                case 'a': parsed_str[parsed_index++] = '\a'; break;
                case 'b': parsed_str[parsed_index++] = '\b'; break;
                case 'f': parsed_str[parsed_index++] = '\f'; break;
                case 'n': parsed_str[parsed_index++] = '\n'; break;
                case 'r': parsed_str[parsed_index++] = '\r'; break;
                case 't': parsed_str[parsed_index++] = '\t'; break;
                case 'v': parsed_str[parsed_index++] = '\v'; break;
                case '0': parsed_str[parsed_index++] = '\0'; break;
                default:
                    parsed_str[parsed_index++] = str[i];
                    break;
            }
        } else
            parsed_str[parsed_index++] = str[i];
    }
    /* null-terminate the parsed string */
    parsed_str[parsed_index] = '\0';
    return parsed_str;
}

/** Calls strdup, remember to free */
char *parse_interpstr(const char *str)
{
    return parse_str(str);
}

#else
    #warning re-inclusion of module 'parser/parse_str.c.h'
#endif
