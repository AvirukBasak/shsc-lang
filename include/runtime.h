#ifndef RUNTIME_H
#define RUNTIME_H

#include "ast.h"
#include "lexer.h"
#include "runtime/data.h"

extern const char *rt_currfile;
extern int rt_currline;

const AST_Identifier_t *RT_modulename_get(void);
const AST_Identifier_t *RT_procname_get(void);

void RT_exec(void);

#endif
