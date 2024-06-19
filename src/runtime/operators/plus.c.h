#ifndef RT_OP_PLUS_C_H
#define RT_OP_PLUS_C_H

#include "errcodes.h"
#include "io.h"
#include "runtime/data/Data.h"
#include "runtime/data/DataList.h"
#include "runtime/data/DataMap.h"
#include "runtime/data/DataStr.h"
#include "runtime/io.h"
#include "runtime/operators.h"
#include "runtime/VarTable.h"

#define RT_OP_PLUS +
#define RT_OP_PLUS_STR "+"

void rt_op_plus(const rt_Data_t *lhs, const rt_Data_t *rhs)
{
    /* this takes care of unary ops by considering lhs = 0 */
    rt_Data_t lhs_ = rt_Data_i64(0);
    if (!lhs) lhs = &lhs_;

    if (!rhs) io_errndie("rt_op_plus:" ERR_MSG_NULLPTR " for `rhs`");
    rt_Data_t ret = rt_Data_null();

    enum rt_DataType_t greater_type = rt_Data_greater_type(*lhs, *rhs);
    if (greater_type != rt_DATA_TYPE_ANY) {
        rt_Data_t lhs_ = rt_Data_cast(*lhs, greater_type);
        rt_Data_t rhs_ = rt_Data_cast(*rhs, greater_type);
        switch (greater_type) {
            case rt_DATA_TYPE_BUL:
                ret = rt_Data_bul(lhs_.data.bul RT_OP_PLUS rhs_.data.bul);
                break;
            case rt_DATA_TYPE_CHR:
                ret = rt_Data_chr(lhs_.data.chr RT_OP_PLUS rhs_.data.chr);
                break;
            case rt_DATA_TYPE_I64:
                ret = rt_Data_i64(lhs_.data.i64 RT_OP_PLUS rhs_.data.i64);
                break;
            case rt_DATA_TYPE_F64:
                ret = rt_Data_f64(lhs_.data.f64 RT_OP_PLUS rhs_.data.f64);
                break;
            case rt_DATA_TYPE_STR:
            case rt_DATA_TYPE_INTERP_STR: {
                rt_DataStr_t *lhs_str = rt_DataStr_clone(lhs_.data.str);
                rt_DataStr_concat(lhs_str, rhs_.data.str);
                ret = rt_Data_str(lhs_str);
                break;
            }
            case rt_DATA_TYPE_LST: {
                rt_DataList_t *lhs_lst = rt_DataList_clone(lhs_.data.lst);
                rt_DataList_concat(lhs_lst, rhs_.data.lst);
                ret = rt_Data_list(lhs_lst);
                break;
            }
            case rt_DATA_TYPE_MAP: {
                rt_DataMap_t *lhs_map = rt_DataMap_clone(lhs_.data.mp);
                rt_DataMap_concat(lhs_map, rhs_.data.mp);
                ret = rt_Data_map(lhs_map);
                break;
            }
            case rt_DATA_TYPE_ANY:
            case rt_DATA_TYPE_PROC:
            case rt_DATA_TYPE_LAMBDA:
            case rt_DATA_TYPE_LIBHANDLE:
                rt_throw("no operator '" RT_OP_PLUS_STR "' for types `%s` and `%s`",
                    rt_Data_typename(*lhs), rt_Data_typename(*rhs));
        }
        rt_Data_destroy(&lhs_);
        rt_Data_destroy(&rhs_);
    }
    else rt_throw("no operator '" RT_OP_PLUS_STR "' for types `%s` and `%s`",
        rt_Data_typename(*lhs), rt_Data_typename(*rhs));

    rt_VarTable_acc_setval(ret);
}

#else
    #warning re-inclusion of module 'runtime/operators/plus.c.h'
#endif
