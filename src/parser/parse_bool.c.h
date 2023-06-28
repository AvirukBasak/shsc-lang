#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "parser.h"

bool parse_bool(const char *str)
{
    if (!strcmp(lex_get_buffstr(), "true"))  return true;
    if (!strcmp(lex_get_buffstr(), "false")) return false;
    err_msg = malloc(strlen(str) + 22);
    sprintf(err_msg, "invalid boolean literal: '%s'", str);
    parse_throw(err_msg);
    free(err_msg);
    return false;
}
