#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_MESSAGE_MAX_LEN 100

#define PARSE_FLOAT_ERRNDIE(msg) do { \
    char *error_message = (char*) malloc(ERROR_MESSAGE_MAX_LEN); \
    snprintf(error_message, ERROR_MESSAGE_MAX_LEN, "%s", msg); \
    parse_throw(error_message); \
    free(error_message); \
} while(1)

double parse_float(const char *str, int base) {
    const int MAX_EXP_LEN = 4;
    const int BUF_SIZE = 128;

    int len = strlen(str);
    char *buf = (char *)malloc(BUF_SIZE);
    int buf_len = 0;
    bool point_seen = false;
    bool exp_seen = false;
    int exp_sign = 1;
    int exp_val = 0;

    for (int i = 0; i < len; i++) {
        char c = str[i];

        if (c == '.') {
            if (point_seen || exp_seen) {
                PARSE_FLOAT_ERRNDIE("invalid floating point format");
            }
            point_seen = true;
            continue;
        }

        if (c == 'p' || c == 'P') {
            if (!point_seen || exp_seen) {
                PARSE_FLOAT_ERRNDIE("invalid exponent format");
            }
            exp_seen = true;
            i++;
            if (i >= len) {
                PARSE_FLOAT_ERRNDIE("invalid exponent format");
            }
            char exp_buf[MAX_EXP_LEN];
            int exp_buf_len = 0;
            if (str[i] == '+' || str[i] == '-') {
                if (str[i] == '-') {
                    exp_sign = -1;
                }
                i++;
                if (i >= len) {
                    PARSE_FLOAT_ERRNDIE("invalid exponent format");
                }
            }
            while (i < len && exp_buf_len < MAX_EXP_LEN) {
                char exp_c = str[i];
                if (!isdigit(exp_c)) {
                    PARSE_FLOAT_ERRNDIE("invalid exponent format");
                }
                exp_buf[exp_buf_len] = exp_c;
                exp_buf_len++;
                i++;
            }
            if (exp_buf_len == 0) {
                PARSE_FLOAT_ERRNDIE("invalid exponent format");
            }
            exp_val = strtol(exp_buf, NULL, 10);
            exp_val *= exp_sign;
            if (i < len) {
                PARSE_FLOAT_ERRNDIE("invalid exponent format");
            }
            break;
        }

        if (!isalnum(c)) {
            PARSE_FLOAT_ERRNDIE("invalid character in input");
        }

        if (isdigit(c) && c >= '0' + base) {
            PARSE_FLOAT_ERRNDIE("invalid character in input for given base");
        }

        if (isalpha(c) && toupper(c) >= 'A' + base - 10) {
            PARSE_FLOAT_ERRNDIE("invalid character in input for given base");
        }

        if (buf_len >= BUF_SIZE - 1) {
            PARSE_FLOAT_ERRNDIE("token too long");
        }
        buf[buf_len] = c;
        buf_len++;
    }

    if (buf_len == 0 || (!point_seen && !exp_seen)) {
        PARSE_FLOAT_ERRNDIE("invalid floating point format");
    }

    buf[buf_len] = '\0';
    double val = strtod(buf, NULL);
    if (exp_seen) {
        val *= pow(base, exp_val);
    }

    free(buf);

    return (int64_t)val;
}
