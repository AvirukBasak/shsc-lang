#ifndef RT_OP_MINUS_C_H
#define RT_OP_MINUS_C_H

#include "errcodes.h"
#include "io.h"
#include "runtime/data/Data.h"
#include "runtime/io.h"
#include "runtime/operators.h"
#include "runtime/VarTable.h"

#define RT_OP_MINUS -
#define RT_OP_MINUS_STR "-"

void rt_op_minus(const rt_Data_t *lhs, const rt_Data_t *rhs)
{
    /* this takes care of unary ops by considering lhs = 0 */
    rt_Data_t lhs_ = rt_Data_i64(0);
    if (!lhs) lhs = &lhs_;

    if (!rhs) io_errndie("rt_op_minus:" ERR_MSG_NULLPTR " for `rhs`");
    rt_Data_t ret = rt_Data_null();

    enum rt_DataType_t greater_type = rt_Data_greater_type(*lhs, *rhs);
    if (greater_type != rt_DATA_TYPE_ANY) {
        rt_Data_t lhs_ = rt_Data_cast(*lhs, greater_type);
        rt_Data_t rhs_ = rt_Data_cast(*rhs, greater_type);
        switch (greater_type) {
            case rt_DATA_TYPE_BUL:
                ret = rt_Data_bul(lhs_.data.bul RT_OP_MINUS rhs_.data.bul);
                break;
            case rt_DATA_TYPE_CHR:
                ret = rt_Data_chr(lhs_.data.chr RT_OP_MINUS rhs_.data.chr);
                break;
            case rt_DATA_TYPE_I64:
                ret = rt_Data_i64(lhs_.data.i64 RT_OP_MINUS rhs_.data.i64);
                break;
            case rt_DATA_TYPE_F64:
                ret = rt_Data_f64(lhs_.data.f64 RT_OP_MINUS rhs_.data.f64);
                break;
            case rt_DATA_TYPE_STR:
            case rt_DATA_TYPE_INTERP_STR:
            case rt_DATA_TYPE_LST:
            case rt_DATA_TYPE_MAP:
            case rt_DATA_TYPE_PROC:
            case rt_DATA_TYPE_LAMBDA:
            case rt_DATA_TYPE_LIBHANDLE:
            case rt_DATA_TYPE_ANY:
                rt_throw("no operator '" RT_OP_MINUS_STR "' for types `%s` and `%s`",
                    rt_Data_typename(*lhs), rt_Data_typename(*rhs));
        }
        rt_Data_destroy(&lhs_);
        rt_Data_destroy(&rhs_);
    }
    else rt_throw("no operator '" RT_OP_MINUS_STR "' for types `%s` and `%s`",
        rt_Data_typename(*lhs), rt_Data_typename(*rhs));

    rt_VarTable_acc_setval(ret);
}

#else
    #warning re-inclusion of module 'runtime/operators/minus.c.h'
#endif
