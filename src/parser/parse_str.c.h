#ifndef PARSER_PARSE_STR_C_H
#define PARSER_PARSE_STR_C_H

#include "parser.h"

/** Calls strdup, remember to free */
char *parse_str(const char *str)
{
    fprintf(stderr, "scsh: warning: parser/parse_str.c.h: 'parse_str' is unimplemented\n");
    return strdup(str);
}

/** Calls strdup, remember to free */
char *parse_interpstr(const char *str)
{
    fprintf(stderr, "scsh: warning: parser/parse_str.c.h: 'parse_interpstr' is unimplemented\n");
    return strdup(str);
}

#else
    #warning re-inclusion of module 'parser/parse_str.c.h'
#endif
