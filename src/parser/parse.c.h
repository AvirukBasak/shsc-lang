#ifndef PARSE_PARSE_C_H
#define PARSE_PARSE_C_H

#include "lexer.h"

typedef struct ParserArg ParserArg;
typedef struct ParserArgList ParserArgList;

struct ParserArg {
    LexToken type;
    char *tokstr;
};

struct ParserArgList {
    ParserArg *argv;
    size_t length;
};

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

ParserArgList parse_mkarglist(FILE *f, LexToken endtok);
void parse_delarglist(ParserArgList *arglist);

ParserArgList parse_mkarglist(FILE *f, LexToken endtok)
{
    ParserArgList arglist = { NULL, 0 };
    LexToken tok = lex_get_nexttok(f);
    while (tok != endtok) {
        if (tok == LEXTOK_EOF) parse_throw("unexpected end of file");
        arglist.argv = realloc(arglist.argv, ++arglist.length);
        arglist.argv[arglist.length -1].type = tok;
        arglist.argv[arglist.length -1].tokstr = strdup(lex_get_buffstr());
        tok = lex_get_nexttok(f);
    }
    return arglist;
}

void parse_delarglist(ParserArgList *arglist)
{
    if (!arglist->argv) return;
    for (int i = 0; i < arglist->length; i++) {
        if (!arglist->argv[i].tokstr) continue;
        free(arglist->argv[i].tokstr);
    }
    free(arglist->argv);
    arglist->argv = NULL;
    arglist->length = 0;
}

#endif
