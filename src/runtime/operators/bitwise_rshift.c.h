#ifndef RT_OP_BITWISE_RSHIFT_C_H
#define RT_OP_BITWISE_RSHIFT_C_H

#include "runtime/data/Data.h"
#include "runtime/io.h"
#include "runtime/operators.h"

#define RT_OP_BIT_RSHIFT >>
#define RT_OP_BIT_RSHIFT_STR ">>"

void rt_op_bitwise_rshift(const rt_Data_t *lhs, const rt_Data_t *rhs) {
    RT_OP_BITWISE(RT_OP_BIT_RSHIFT, RT_OP_BIT_RSHIFT_STR, lhs, rhs);
}

#else
    #warning re-inclusion of module 'runtime/operators/bitwise_rshift.c.h'
#endif
