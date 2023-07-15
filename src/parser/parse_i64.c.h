#ifndef PARSER_PARSE_I64_C_H
#define PARSER_PARSE_I64_C_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>

#include "parser.h"

int64_t parse_int(const char *str, int base)
{
    /* check that the base is valid */
    if (base != 2 && base != 8 && base != 10 && base != 16)
        parse_throw("unsupported base");

    char *endptr;
    int64_t result = 0;

    /* set errno to 0 before calling strtol */
    errno = 0;

    /* handle scientific notation separately */
    if (strchr(str, 'e')) {
        /* parse the integer part before the 'e' */
        result = strtol(str, &endptr, base);
        if (errno || *endptr != 'e')
            parse_throw("invalid integer format");
        /* skip over the 'e' character */
        ++endptr;
        char *exponent_endptr;
        /* parse the exponent value */
        int64_t exponent = strtol(endptr, &exponent_endptr, 10);
        if (errno || exponent_endptr == endptr || *exponent_endptr != '\0')
            parse_throw("invalid integer format");
        /* check that the resulting value is representable in int64_t */
        if (exponent >= 0) {
            if ( exponent > 18 || (result >= INT64_MAX / (int64_t) (1LL << exponent)) )
                parse_throw("integer overflow");
            /* multiply by 10^exponent */
            result *= (int64_t) (1LL << exponent);
        } else {
            if ( exponent < -18 || (result <= INT64_MIN / (int64_t) (1LL << (-exponent))) )
                parse_throw("integer underflow");
            /* divide by 10^-exponent */
            result /= (int64_t) (1LL << (-exponent));
        }
    } else {
        /* parse the integer value using strtol */
        result = strtol(str, &endptr, base);
        if (errno || *endptr != '\0')
            parse_throw("invalid integer format");
    }

    return result;
}

#else
    #warning re-inclusion of module 'parser/parse_i64.c.h'
#endif
