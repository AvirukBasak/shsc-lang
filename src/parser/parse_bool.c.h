#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "globals.h"
#include "parser.h"

bool parse_bool(const char *str)
{
    if (!strcmp(lex_get_buffstr(), "true"))  return true;
    if (!strcmp(lex_get_buffstr(), "false")) return false;
    char *err_msg = malloc(strlen(str) + GLOBAL_BYTES_BUFFER_LEN);
    sprintf(err_msg, "invalid boolean literal: '%s'", str);
    parse_throw(err_msg);
    free(err_msg);
    return false;
}
