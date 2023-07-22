#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <inttypes.h>

extern FILE *yyin;

int yyerror(const char* s);

void parse_interpret(FILE *f);
void parse_throw(const char *msg);

#undef YY_
#define YY_(Msgid) Msgid

bool parse_bool(const char *str);
char parse_char(const char *str);
int64_t parse_int(const char *str, int base);
double parse_float(const char *str, int base);
char *parse_str(const char *str);
char *parse_interpstr(const char *str);

typedef union {
    bool bul;
    char chr;
    int64_t i64;
    double f64;
    char *str;
    void *any;
    char *idf;
} VarData;

/* based on the mapping of datatype IDs provided
   by the Scsh IR Spec
   https://github.com/AvirukBasak/scsh-runtime/docs/ScshIrSpec.md */
enum DataType_t {
    DATA_TYPE_BUL = 0,        /* boolean        : 1 B */
    DATA_TYPE_CHR = 1,        /* char           : 1 B */
    DATA_TYPE_I64 = 1,        /* int64_t        : 8 B */
    DATA_TYPE_F64 = 2,        /* double         : 8 B */
    DATA_TYPE_STR = 3,        /* char*          : variable  */
    DATA_TYPE_INTERP_STR = 4, /* parsable char* : variable  */
    DATA_TYPE_LST = 5,        /* list           : variable  */
    DATA_TYPE_ANY = 6,        /* void*          : undefined */
};

#endif
