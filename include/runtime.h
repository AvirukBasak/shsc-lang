#ifndef RUNTIME_H
#define RUNTIME_H

#include "ast.h"
#include "lexer.h"
#include "runtime/data/Data.h"
    
int rt_exec(int argc, char **argv);

#endif
