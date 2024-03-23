#ifndef RT_OP_ARITH_RSHIFT_C_H
#define RT_OP_ARITH_RSHIFT_C_H

#include "runtime/data/Data.h"
#include "runtime/io.h"
#include "runtime/operators.h"

void rt_op_arith_rshift(const rt_Data_t *lhs, const rt_Data_t *rhs) {
    rt_throw("unimplemented operator: >>>");
}

#else
    #warning re-inclusion of module 'runtime/operators/arith_rshift.c.h'
#endif
