#ifndef PARSE_PARSE_C_H
#define PARSE_PARSE_C_H

char parse_charlit(char *str);

int64_t parse_binintlit(char *str);
int64_t parse_octintlit(char *str);
int64_t parse_decintlit(char *str);
int64_t parse_hexintlit(char *str);

double parse_binfloatlit(char *str);
double parse_octfloatlit(char *str);
double parse_decfloatlit(char *str);
double parse_hexfloatlit(char *str);

char *parse_strlit(char *str);
char *parse_interpstrlit(char *str);

char **parse_mkarglist(FILE *f);
void parse_delarglist(char **arglist);

#endif
