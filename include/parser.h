#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <inttypes.h>

extern FILE *yyin;

int yyerror(const char* s);

void parse_interpret(FILE *f);
void parse_throw(const char *msg, bool on);

#undef YY_
#define YY_(Msgid) Msgid

bool parse_bool(const char *str);
char parse_char(const char *str);
int64_t parse_int(const char *str, int base);
double parse_float(const char *str, int base);
char *parse_str(const char *str);
char *parse_interpstr(const char *str);

#endif
