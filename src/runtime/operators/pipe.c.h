#ifndef RT_OP_PIPE_C_H
#define RT_OP_PIPE_C_H

#include "runtime/data/Data.h"
#include "runtime/io.h"
#include "runtime/operators.h"

#define RT_OP_BIT_OR |
#define RT_OP_BIT_OR_STR "|"

void rt_op_pipe(const rt_Data_t *lhs, const rt_Data_t *rhs) {
    RT_OP_BITWISE(RT_OP_BIT_OR, RT_OP_BIT_OR_STR, lhs, rhs);
}

#else
    #warning re-inclusion of module 'runtime/operators/pipe.c.h'
#endif
