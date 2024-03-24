#ifndef RT_OP_ARITH_RSHIFT_C_H
#define RT_OP_ARITH_RSHIFT_C_H

#include "runtime/data/Data.h"
#include "runtime/io.h"
#include "runtime/operators.h"

#define RT_OP_BIT_ARSHIFT >>
#define RT_OP_BIT_ARSHIFT_STR ">>>"

void rt_op_arith_rshift(const rt_Data_t *lhs, const rt_Data_t *rhs) {
    RT_OP_BITWISE(RT_OP_BIT_ARSHIFT, RT_OP_BIT_ARSHIFT_STR, lhs, rhs);
}

#else
    #warning re-inclusion of module 'runtime/operators/arith_rshift.c.h'
#endif
