#ifndef RT_OP_TILDE_C_H
#define RT_OP_TILDE_C_H

#include "runtime/data/Data.h"
#include "runtime/io.h"
#include "runtime/operators.h"

#define RT_OP_BIT_COMPLEMENT ~
#define RT_OP_BIT_COMPLEMENT_STR "~"

void rt_op_tilde(const rt_Data_t *lhs, const rt_Data_t *rhs) {
    if (lhs) io_errndie("RT_OP_BITWISE: " RT_OP_BIT_COMPLEMENT_STR ": " "non-null value for `lhs`");
    if (!rhs) io_errndie("RT_OP_BITWISE: " RT_OP_BIT_COMPLEMENT_STR ": " ERR_MSG_NULLPTR " for `rhs`");
    rt_Data_t ret = rt_Data_null();

    rt_Data_t rhs_ = rt_Data_cast(*rhs, rt_DATA_TYPE_ANY);
    switch (rhs->type) {
        case rt_DATA_TYPE_BUL:
            ret = rt_Data_bul(RT_OP_BIT_COMPLEMENT rhs_.data.i64);
            break;
        case rt_DATA_TYPE_CHR:
            ret = rt_Data_chr(RT_OP_BIT_COMPLEMENT rhs_.data.i64);
            break;
        case rt_DATA_TYPE_I64:
            ret = rt_Data_i64(RT_OP_BIT_COMPLEMENT rhs_.data.i64);
            break;
        case rt_DATA_TYPE_F64:
            ret = rt_Data_f64(RT_OP_BIT_COMPLEMENT rhs_.data.i64);
            break;
        case rt_DATA_TYPE_STR:
        case rt_DATA_TYPE_INTERP_STR:
        case rt_DATA_TYPE_LST:
        case rt_DATA_TYPE_MAP:
        case rt_DATA_TYPE_ANY:
        case rt_DATA_TYPE_PROC:
            rt_throw("no operator '" RT_OP_BIT_COMPLEMENT_STR "' for type `%s`", rt_Data_typename(*rhs));
    }

    rt_VarTable_acc_setval(ret);
}

#else
    #warning re-inclusion of module 'runtime/operators/tilde.c.h'
#endif
