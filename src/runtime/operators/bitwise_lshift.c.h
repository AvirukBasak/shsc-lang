#ifndef RT_OP_BITWISE_LSHIFT_C_H
#define RT_OP_BITWISE_LSHIFT_C_H

#include "runtime/data/Data.h"
#include "runtime/io.h"
#include "runtime/operators.h"

#define RT_OP_BIT_LSHIFT <<
#define RT_OP_BIT_LSHIFT_STR "<<"

void rt_op_bitwise_lshift(const rt_Data_t *lhs, const rt_Data_t *rhs) {
    RT_OP_BITWISE(RT_OP_BIT_LSHIFT, RT_OP_BIT_LSHIFT_STR, lhs, rhs);
}

#else
    #warning re-inclusion of module 'runtime/operators/bitwise_lshift.c.h'
#endif
