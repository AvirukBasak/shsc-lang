#ifndef RT_OP_AMPERSAND_C_H
#define RT_OP_AMPERSAND_C_H

#include "runtime/data/Data.h"
#include "runtime/io.h"
#include "runtime/operators.h"

#define RT_OP_BIT_AND &
#define RT_OP_BIT_AND_STR "&"

void rt_op_ampersand(const rt_Data_t *lhs, const rt_Data_t *rhs) {
    RT_OP_BITWISE(RT_OP_BIT_AND, RT_OP_BIT_AND_STR, lhs, rhs);
}

#else
    #warning re-inclusion of module 'runtime/operators/ampersand.c.h'
#endif
