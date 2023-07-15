#ifndef PARSER_PARSE_STR_C_H
#define PARSER_PARSE_STR_C_H

#include "parser.h"

/** Calls strdup, remember to free */
char *parse_str(const char *str)
{
    int len = strlen(str);
    char *parsed_str = malloc(len +1);
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
            if (isdigit(str[i])) {
                char *endptr;
                int res = strtol(&str[i], &endptr, 8);
                if (!*endptr && 0 <= res && res <= 255) {
                    parsed_str[parsed_index++] = (char) res;
                    /* update the loop index */
                    i += endptr - &str[i] -1;
                } else parse_throw("invalid octal escape sequence");
            }
            /* hex escape sequence */
            else if (str[i] == 'x' && isxdigit(str[i + 1])) {
                char *endptr;
                int res = strtol(&str[i+1], &endptr, 16);
                if (!*endptr && 0 <= res && res <= 255) {
                    parsed_str[parsed_index++] = (char) res;
                    /* update the loop index */
                    i += endptr - &str[i];
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
