#ifndef RT_OP_CARET_C_H
#define RT_OP_CARET_C_H

#include "runtime/data/Data.h"
#include "runtime/io.h"
#include "runtime/operators.h"

#define RT_OP_BIT_XOR ^
#define RT_OP_BIT_XOR_STR "^"

void rt_op_caret(const rt_Data_t *lhs, const rt_Data_t *rhs) {
    RT_OP_BITWISE(RT_OP_BIT_XOR, RT_OP_BIT_XOR_STR, lhs, rhs);
}

#else
    #warning re-inclusion of module 'runtime/operators/caret.c.h'
#endif
