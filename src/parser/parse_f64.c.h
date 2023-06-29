#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

double parse_float(const char *str, int base) {
    const int MAX_EXP_LEN = 4;
    const int BUF_SIZE = 128;
    int len = strlen(str);
    char *buf = (char*) malloc(BUF_SIZE);
    int buf_len = 0;
    bool point_seen = false;
    bool exp_seen = false;
    int exp_sign = 1;
    int exp_val = 0;

    for (int i = 0; i < len; i++) {
        char c = str[i];
        if (c == '.') {
            if (point_seen || exp_seen) {
                parse_throw("invalid floating point format");
            }
            point_seen = true;
            continue;
        }
        if (c == 'p' || c == 'P') {
            if (!point_seen || exp_seen) {
                parse_throw("invalid exponent format");
            }
            exp_seen = true;
            i++;
            if (i >= len) {
                parse_throw("invalid exponent format");
            }
            char exp_buf[MAX_EXP_LEN];
            int exp_buf_len = 0;
            if (str[i] == '+' || str[i] == '-') {
                if (str[i] == '-') {
                    exp_sign = -1;
                }
                i++;
                if (i >= len) {
                    parse_throw("invalid exponent format");
                }
            }
            while (i < len && exp_buf_len < MAX_EXP_LEN) {
                char exp_c = str[i];
                if (!isdigit(exp_c)) {
                    parse_throw("invalid exponent format");
                }
                exp_buf[exp_buf_len] = exp_c;
                exp_buf_len++;
                i++;
            }
            if (exp_buf_len == 0) {
                parse_throw("invalid exponent format");
            }
            exp_val = strtol(exp_buf, NULL, 10);
            exp_val *= exp_sign;
            if (i < len) {
                parse_throw("invalid exponent format");
            }
            break;
        }

        if (!isalnum(c)) {
            parse_throw("invalid character in input");
        }

        if (isdigit(c) && c >= '0' + base) {
            parse_throw("invalid character in input for given base");
        }

        if (isalpha(c) && toupper(c) >= 'A' + base - 10) {
            parse_throw("invalid character in input for given base");
        }

        if (buf_len >= BUF_SIZE - 1) {
            parse_throw("token too long");
        }
        buf[buf_len] = c;
        buf_len++;
    }
    if (buf_len == 0 || (!point_seen && !exp_seen)) {
        parse_throw("invalid floating point format");
    }
    buf[buf_len] = '\0';
    double val = strtod(buf, NULL);
    if (exp_seen) {
        val *= pow(base, exp_val);
    }
    free(buf);
    return (int64_t)val;
}
