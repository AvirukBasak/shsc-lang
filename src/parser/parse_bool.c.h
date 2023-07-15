#ifndef PARSER_PARSE_BOOL_C_H
#define PARSER_PARSE_BOOL_C_H

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
    parse_throw("invalid boolean literal");
    return false;
}

#else
    #warning re-inclusion of module 'parser/parse_bool.c.h'
#endif
