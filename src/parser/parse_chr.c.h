#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

char parse_char(const char *str)
{
    char c = str[0];
    int len = strlen(str);
    char *err_msg = NULL;

    // If the input string has only one character, return it
    if (len == 1) c = str[0];

    // If the input string has two characters and the first character is a backslash,
    // then the second character is an escape sequence
    else if (len == 2 && str[0] == '\\') {
        switch (str[1]) {
            case 'a': c = '\a'; break;
            case 'b': c = '\b'; break;
            case 'f': c = '\f'; break;
            case 'n': c = '\n'; break;
            case 'r': c = '\r'; break;
            case 't': c = '\t'; break;
            case 'v': c = '\v'; break;
            case '\\': c = '\\'; break;
            case '\'': c = '\''; break;
            case '\"': c = '\"'; break;
            case '\?': c = '\?'; break;
            default:
                err_msg = malloc(strlen(str) + GLOBAL_BYTES_BUFFER_LEN);
                sprintf(err_msg, "invalid escape sequence: '\\%c'", str[1]);
                parse_throw(err_msg);
                free(err_msg);
        }
    }

    // If the input string starts with '\x', it is a hexadecimal escape sequence
    else if (len >= 4 && str[0] == '\\' && str[1] == 'x') {
        char hex[3];
        hex[0] = str[2];
        hex[1] = str[3];
        hex[2] = '\0';
        int num = (int) strtol(hex, NULL, 16);
        c = (char) num;
    }

    // If the input string starts with '\', it is an octal escape sequence
    else if (len > 1 && str[0] == '\\') {
        int num = 0;
        int i;
        for (i = 1; i < len && i <= 3; i++)
            if (str[i] >= '0' && str[i] <= '7')
                num = num * 8 + (str[i] - '0');
            else break;
        if (i == len) c = (char) num;
        else {
            err_msg = malloc(strlen(str) + GLOBAL_BYTES_BUFFER_LEN);
            sprintf(err_msg, "invalid escape sequence: '%s'", str);
            parse_throw(err_msg);
            free(err_msg);
        }
    }

    // If the input string has more than two characters, it is an error
    else {
        err_msg = malloc(strlen(str) + GLOBAL_BYTES_BUFFER_LEN);
        sprintf(err_msg, "invalid character token: '%s'", str);
        parse_throw(err_msg);
        free(err_msg);
    }

    return c;
}
