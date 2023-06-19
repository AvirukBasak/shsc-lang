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

typedef const char *str_t;

typedef enum {
    VT_BUL,
    VT_CHR,
    VT_I64,
    VT_F64,
    VT_STR,
    VT_ANY,
} VarType;

typedef struct {
    YYSTYPE var;
    VarType type;
} VarData;

/*
HASHMAP_DECLARE(str_t, VarData);

HashMap(str_t, VarData) var_table;
*/

#endif
