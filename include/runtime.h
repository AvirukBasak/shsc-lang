#ifndef RUNTIME_H
#define RUNTIME_H

#include "ast.h"
#include "lexer.h"
#include "runtime/data/Data.h"

extern const char *rt_currfile;
extern int rt_currline;

const ast_Identifier_t *rt_modulename_get(void);
const ast_Identifier_t *rt_procname_get(void);

void rt_exec(int argc, char **argv);

#endif
