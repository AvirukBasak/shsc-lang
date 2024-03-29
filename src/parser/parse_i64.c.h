#ifndef PARSER_PARSE_I64_C_H
#define PARSER_PARSE_I64_C_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "parser.h"

int64_t parse_int(const char *str, int base)
{
    /* check that the base is valid */
    if (base != 2 && base != 8 && base != 10 && base != 16)
        parse_throw("unsupported base", true);

    char *endptr;
    char *exp_loc = NULL;
    int64_t result = 0;

    /* set errno to 0 before calling strtol */
    errno = 0;

    /* handle scientific notation separately */
    if ( (exp_loc = strchr(str, 'p')) ) {
        /* parse the integer part before the 'p' */
        result = strtol(str, &endptr, base);
        if (errno || *endptr != 'p')
            parse_throw("invalid integer format 1; wtf was the lexer designer doing?", true);
        /* skip over the 'p' character */
        ++endptr;
        char *exponent_endptr;
        /* parse the exponent value */
        int64_t exponent = strtol(endptr, &exponent_endptr, 10);
        if (errno || exponent_endptr == endptr || *exponent_endptr != '\0')
            parse_throw("invalid integer format 2; wtf was the lexer designer doing?", true);
        /* check that the resulting value is representable in int64_t */
        if (exponent >= 0) {
            if ( exponent > 18 || result >= INT64_MAX / (int64_t) (1LL * pow(base, exponent)) )
                parse_throw("integer overflow", true);
            /* multiply by base ^ exponent */
            result *= (int64_t) (1LL * pow(base, exponent));
        } else {
            if ( exponent < -18 || result <= INT64_MIN / (int64_t) (1LL * pow(base, -exponent)) )
                parse_throw("integer underflow", true);
            /* divide by base ^ exponent */
            result *= (int64_t) (1LL * pow(base, exponent));
        }
    } else {
        /* parse the integer value using strtol */
        result = strtol(str, &endptr, base);
        if (errno || *endptr != '\0')
            parse_throw("invalid integer format 3; wtf was the lexer designer doing?", true);
    }

    return result;
}

#else
    #warning re-inclusion of module 'parser/parse_i64.c.h'
#endif
