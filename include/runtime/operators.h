#ifndef RT_OPERATORS_H
#define RT_OPERATORS_H

#include "runtime/data/Data.h"

void rt_op_ampersand            (const rt_Data_t *lhs, const rt_Data_t *rhs);
void rt_op_arith_rshift         (const rt_Data_t *lhs, const rt_Data_t *rhs);
void rt_op_assign               (rt_Data_t *lhs, const rt_Data_t *rhs);
void rt_op_weak_assign          (rt_Data_t *lhs, const rt_Data_t *rhs)
void rt_op_asterix              (const rt_Data_t *lhs, const rt_Data_t *rhs);
void rt_op_bang                 (const rt_Data_t *lhs, const rt_Data_t *rhs);
void rt_op_bitwise_lshift       (const rt_Data_t *lhs, const rt_Data_t *rhs);
void rt_op_bitwise_rshift       (const rt_Data_t *lhs, const rt_Data_t *rhs);
void rt_op_caret                (const rt_Data_t *lhs, const rt_Data_t *rhs);
void rt_op_dcolon               (const ast_Expression_t *expr);
void rt_op_decrement            (rt_Data_t *lhs, rt_Data_t *rhs);
void rt_op_dot                  (const rt_Data_t *lhs, const rt_Data_t *rhs);
void rt_op_exponent             (const rt_Data_t *lhs, const rt_Data_t *rhs);
void rt_op_floor_divide         (const rt_Data_t *lhs, const rt_Data_t *rhs);
void rt_op_fslash               (const rt_Data_t *lhs, const rt_Data_t *rhs);
void rt_op_increment            (rt_Data_t *lhs, rt_Data_t *rhs);
void rt_op_lbrace_angular       (const rt_Data_t *lhs, const rt_Data_t *rhs);
void rt_op_logical_and          (const rt_Data_t *lhs, const rt_Data_t *rhs);
void rt_op_logical_equal        (const rt_Data_t *lhs, const rt_Data_t *rhs);
void rt_op_logical_greater_equal(const rt_Data_t *lhs, const rt_Data_t *rhs);
void rt_op_logical_lesser_equal (const rt_Data_t *lhs, const rt_Data_t *rhs);
void rt_op_logical_or           (const rt_Data_t *lhs, const rt_Data_t *rhs);
void rt_op_logical_unequal      (const rt_Data_t *lhs, const rt_Data_t *rhs);
void rt_op_minus                (const rt_Data_t *lhs, const rt_Data_t *rhs);
void rt_op_percent              (const rt_Data_t *lhs, const rt_Data_t *rhs);
void rt_op_pipe                 (const rt_Data_t *lhs, const rt_Data_t *rhs);
void rt_op_plus                 (const rt_Data_t *lhs, const rt_Data_t *rhs);
void rt_op_rbrace_angular       (const rt_Data_t *lhs, const rt_Data_t *rhs);
void rt_op_tilde                (const rt_Data_t *lhs, const rt_Data_t *rhs);
void rt_op_fnargs_indexing      (const rt_Data_t *lhs, const rt_Data_t *rhs);
void rt_op_fncall               (const rt_Data_t *lhs, const rt_Data_t *rhs);
void rt_op_indexing             (const rt_Data_t *lhs, const rt_Data_t *rhs);
void rt_op_nop                  (const rt_Data_t *lhs);
void rt_op_ternary_cond         (const rt_Data_t *lhs, const rt_Data_t *rhs, const rt_Data_t *condition);

#endif
