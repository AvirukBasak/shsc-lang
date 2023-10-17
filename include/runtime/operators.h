#ifndef RT_OPERATORS_H
#define RT_OPERATORS_H

#include "runtime/data/Data.h"

void rt_op_ampersand            (rt_Data_t *lhs, rt_Data_t *rhs);
void rt_op_arith_rshift         (rt_Data_t *lhs, rt_Data_t *rhs);
void rt_op_assign               (rt_Data_t *lhs, rt_Data_t *rhs);
void rt_op_asterix              (rt_Data_t *lhs, rt_Data_t *rhs);
void rt_op_bang                 (rt_Data_t *lhs, rt_Data_t *rhs);
void rt_op_bitwise_lshift       (rt_Data_t *lhs, rt_Data_t *rhs);
void rt_op_bitwise_rshift       (rt_Data_t *lhs, rt_Data_t *rhs);
void rt_op_caret                (rt_Data_t *lhs, rt_Data_t *rhs);
void rt_op_dcolon               (rt_Data_t *lhs, rt_Data_t *rhs);
void rt_op_decrement            (rt_Data_t *lhs, rt_Data_t *rhs);
void rt_op_dot                  (rt_Data_t *lhs, rt_Data_t *rhs);
void rt_op_exponent             (rt_Data_t *lhs, rt_Data_t *rhs);
void rt_op_floor_divide         (rt_Data_t *lhs, rt_Data_t *rhs);
void rt_op_fncall               (rt_Data_t *lhs, rt_Data_t *rhs);
void rt_op_fslash               (rt_Data_t *lhs, rt_Data_t *rhs);
void rt_op_increment            (rt_Data_t *lhs, rt_Data_t *rhs);
void rt_op_lbrace_angular       (rt_Data_t *lhs, rt_Data_t *rhs);
void rt_op_logical_and          (rt_Data_t *lhs, rt_Data_t *rhs);
void rt_op_logical_equal        (rt_Data_t *lhs, rt_Data_t *rhs);
void rt_op_logical_greater_equal(rt_Data_t *lhs, rt_Data_t *rhs);
void rt_op_logical_lesser_equal (rt_Data_t *lhs, rt_Data_t *rhs);
void rt_op_logical_or           (rt_Data_t *lhs, rt_Data_t *rhs);
void rt_op_logical_unequal      (rt_Data_t *lhs, rt_Data_t *rhs);
void rt_op_minus                (rt_Data_t *lhs, rt_Data_t *rhs);
void rt_op_percent              (rt_Data_t *lhs, rt_Data_t *rhs);
void rt_op_pipe                 (rt_Data_t *lhs, rt_Data_t *rhs);
void rt_op_plus                 (rt_Data_t *lhs, rt_Data_t *rhs);
void rt_op_rbrace_angular       (rt_Data_t *lhs, rt_Data_t *rhs);
void rt_op_tilde                (rt_Data_t *lhs, rt_Data_t *rhs);
void rt_op_fnargs_indexing      (rt_Data_t *lhs, rt_Data_t *rhs);
void rt_op_fncall               (rt_Data_t *lhs, rt_Data_t *rhs);
void rt_op_indexing             (rt_Data_t *lhs, rt_Data_t *rhs);
void rt_op_nop                  (rt_Data_t *lhs, rt_Data_t *rhs);
void rt_op_ternary_cond         (rt_Data_t *lhs, rt_Data_t *rhs, rt_Data_t *cond);

#endif
