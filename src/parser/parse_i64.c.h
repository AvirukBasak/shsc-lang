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
    // Check that the base is valid
    if (base != 2 && base != 8 && base != 10 && base != 16) {
        parse_throw("unsupported base");
    }

    char *endptr;    // Pointer to the first invalid character in the input string
    int64_t result;  // The parsed integer value
    errno = 0;       // Set errno to 0 before calling strtol

    // Handle scientific notation separately
    if (strchr(str, 'e')) {
        result = strtol(str, &endptr, base);  // Parse the integer part before the 'e'
        if (errno || *endptr != 'e') {
            parse_throw("invalid integer format");
        }
        endptr++;  // Skip over the 'e' character

        char *exponent_endptr;
        int64_t exponent = strtol(endptr, &exponent_endptr, 10);  // Parse the exponent value
        if (errno || exponent_endptr == endptr || *exponent_endptr != '\0') {
            parse_throw("invalid integer format");
        }

        // Check that the resulting value is representable in int64_t
        if (exponent >= 0) {
            if (exponent > 18 || (result >= INT64_MAX / (int64_t)(1LL << exponent))) {
                parse_throw("integer overflow");
            }
            result *= (int64_t)(1LL << exponent);  // Multiply by 10^exponent
        } else {
            if (exponent < -18 || (result <= INT64_MIN / (int64_t)(1LL << (-exponent)))) {
                parse_throw("integer underflow");
            }
            result /= (int64_t)(1LL << (-exponent));  // Divide by 10^-exponent
        }
    } else {
        // Parse the integer value using strtol
        result = strtol(str, &endptr, base);
        if (errno || *endptr != '\0') {
            parse_throw("invalid integer format");
        }
    }

    return result;
}

#else
    #warning re-inclusion of module 'parser/parse_i64.c.h'
#endif
