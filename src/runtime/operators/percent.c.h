#ifndef RT_OP_PERCENT_C_H
#define RT_OP_PERCENT_C_H

#include "errcodes.h"
#include "io.h"
#include "runtime/data/Data.h"
#include "runtime/data/DataList.h"
#include "runtime/data/DataMap.h"
#include "runtime/data/DataStr.h"
#include "runtime/io.h"
#include "runtime/operators.h"
#include "runtime/VarTable.h"

#define RT_OP_PERCENT %
#define RT_OP_PERCENT_STR "%%"

void rt_op_percent(const rt_Data_t *lhs, const rt_Data_t *rhs)
{
    if (!lhs) io_errndie("rt_op_percent:" ERR_MSG_NULLPTR " for `lhs`");
    if (!rhs) io_errndie("rt_op_percent:" ERR_MSG_NULLPTR " for `rhs`");
    rt_Data_t ret = rt_Data_null();

    enum rt_DataType_t greater_type = rt_Data_greater_type(*lhs, *rhs);
    if (greater_type != rt_DATA_TYPE_ANY) {
        rt_Data_t lhs_ = rt_Data_cast(*lhs, greater_type);
        rt_Data_t rhs_ = rt_Data_cast(*rhs, greater_type);
        switch (greater_type) {
            case rt_DATA_TYPE_BUL:
                if (rhs_.data.bul == 0) rt_throw("cannot divide by zero");
                ret = rt_Data_bul(lhs_.data.bul RT_OP_PERCENT rhs_.data.bul);
                break;
            case rt_DATA_TYPE_CHR:
                if (rhs_.data.bul == 0) rt_throw("cannot divide by zero");
                ret = rt_Data_chr(lhs_.data.chr RT_OP_PERCENT rhs_.data.chr);
                break;
            case rt_DATA_TYPE_I64:
                if (rhs_.data.bul == 0) rt_throw("cannot divide by zero");
                ret = rt_Data_i64(lhs_.data.i64 RT_OP_PERCENT rhs_.data.i64);
                break;
            case rt_DATA_TYPE_F64:
            case rt_DATA_TYPE_STR:
            case rt_DATA_TYPE_INTERP_STR:
            case rt_DATA_TYPE_LST:
            case rt_DATA_TYPE_MAP:
            case rt_DATA_TYPE_PROC:
            case rt_DATA_TYPE_LAMBDA:
            case rt_DATA_TYPE_LIBHANDLE:
            case rt_DATA_TYPE_ANY:
                rt_throw("no operator '" RT_OP_PERCENT_STR "' for types `%s` and `%s`",
                    rt_Data_typename(*lhs), rt_Data_typename(*rhs));
        }
        rt_Data_destroy(&lhs_);
        rt_Data_destroy(&rhs_);
    }
    else rt_throw("no operator '" RT_OP_PERCENT_STR "' for types `%s` and `%s`",
        rt_Data_typename(*lhs), rt_Data_typename(*rhs));

    rt_VarTable_acc_setval(ret);
}

#else
    #warning re-inclusion of module 'runtime/operators/percent.c.h'
#endif
