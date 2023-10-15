#ifndef PARSER_PARSE_BOOL_C_H
#define PARSER_PARSE_BOOL_C_H

#include <string.h>
#include <stdbool.h>

#include "lexer.h"
#include "parser.h"

bool parse_bool(const char *str)
{
    if (!strcmp(lex_Buffer_getstr(), "true"))  return true;
    if (!strcmp(lex_Buffer_getstr(), "false")) return false;
    parse_throw("invalid boolean literal", true);
    return false;
}

#else
    #warning re-inclusion of module 'parser/parse_bool.c.h'
#endif
