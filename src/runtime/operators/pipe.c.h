#ifndef RT_OP_PIPE_C_H
#define RT_OP_PIPE_C_H

#include "runtime/data/Data.h"
#include "runtime/io.h"
#include "runtime/operators.h"

void rt_op_pipe(const rt_Data_t *lhs, const rt_Data_t *rhs) {
    rt_throw("unimplemented operator: |");
}

#else
    #warning re-inclusion of module 'runtime/operators/pipe.c.h'
#endif
