#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <inttypes.h>

/*
#include "ctl/hashmap.h"
*/
#include "parser.yac.h"

extern FILE *yyin;

int yyerror(const char* s);

void parse_interpret(FILE *f);
void parse_throw(const char *msg);

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

typedef enum {
    VARTYPE_BUL,
    VARTYPE_CHR,
    VARTYPE_I64,
    VARTYPE_F64,
    VARTYPE_STR,
    VARTYPE_ANY,
} VarType;

#endif
