#ifndef RUNTIME_H
#define RUNTIME_H

#include "ast.h"
#include "lexer.h"
#include "runtime/data.h"

extern const char *rt_currfile;
extern int rt_currline;

void RT_exec(void);

#endif
