#ifndef PARSER_PARSE_F64_C_H
#define PARSER_PARSE_F64_C_H

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

double parse_float(const char *str, int base)
{
    int sign = 1;
    double result = 0.0;
    char *endptr = NULL;

    /* check for sign */
    if (str[0] == '-') {
        sign = -1;
        ++str;
    } else if (str[0] == '+') {
        ++str;
    }

    /* parse the integer */
    result = strtol(str, &endptr, base);
    const char *dot_index = endptr;
    if (*endptr == '\0') return sign * result;
    if (*endptr != '.') parse_throw("invalid float format 1; wtf was the lexer designer doing?");

    /* parse the fraction if available */ 
    const int64_t fraction = strtol(dot_index +1, &endptr, base);
    const char *exp_index = endptr;
    result += (double) fraction / pow(base, exp_index - dot_index -1);
    if (*endptr == '\0') return sign * result;
    if (*endptr != 'p') parse_throw("invalid float format 2; wtf was the lexer designer doing?");

    /* parse the exponent if available */
    const int64_t exponent = strtol(exp_index +1, &endptr, base);
    result *= pow(base, exponent);
    if (*endptr != '\0') parse_throw("invalid float format 3; wtf was the lexer designer doing?");

    return sign * result;
}

#else
    #warning re-inclusion of module 'parser/parse_f64.c.h'
#endif
