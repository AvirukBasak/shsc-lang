#ifndef RT_OP_ASTERIX_C_H
#define RT_OP_ASTERIX_C_H

#include "errcodes.h"
#include "io.h"
#include "runtime/data/Data.h"
#include "runtime/data/DataList.h"
#include "runtime/data/DataMap.h"
#include "runtime/data/DataStr.h"
#include "runtime/io.h"
#include "runtime/operators.h"
#include "runtime/VarTable.h"

#define RT_OP_ASTERIX *
#define RT_OP_ASTERIX_STR "*"

void rt_op_asterix(const rt_Data_t *lhs, const rt_Data_t *rhs)
{
    if (!lhs) io_errndie("rt_op_asterix:" ERR_MSG_NULLPTR " for `lhs`");
    if (!rhs) io_errndie("rt_op_asterix:" ERR_MSG_NULLPTR " for `rhs`");
    rt_Data_t ret = rt_Data_null();

    /* special cases: if one type is lst or str and other type is i64, concatenate
       i64 number of times and return */
    if (lhs->type == rt_DATA_TYPE_I64 && rhs->type == rt_DATA_TYPE_LST) {
        rt_DataList_t *lst = rt_DataList_clone(rhs->data.lst);
        for (int i = 0; i < lhs->data.i64-1; ++i) {
            rt_DataList_concat(lst, rhs->data.lst);
        }
        ret = rt_Data_list(lst);
        rt_VarTable_acc_setval(ret);
        return;
    }
    else if (lhs->type == rt_DATA_TYPE_LST && rhs->type == rt_DATA_TYPE_I64) {
        rt_DataList_t *lst = rt_DataList_clone(lhs->data.lst);
        for (int i = 0; i < rhs->data.i64-1; ++i) {
            rt_DataList_concat(lst, lhs->data.lst);
        }
        ret = rt_Data_list(lst);
        rt_VarTable_acc_setval(ret);
        return;
    }
    else if (lhs->type == rt_DATA_TYPE_I64 && rhs->type == rt_DATA_TYPE_STR) {
        rt_DataStr_t *str = rt_DataStr_clone(rhs->data.str);
        for (int i = 0; i < lhs->data.i64-1; ++i) {
            rt_DataStr_concat(str, rhs->data.str);
        }
        ret = rt_Data_str(str);
        rt_VarTable_acc_setval(ret);
        return;
    }
    else if (lhs->type == rt_DATA_TYPE_STR && rhs->type == rt_DATA_TYPE_I64) {
        rt_DataStr_t *str = rt_DataStr_clone(lhs->data.str);
        for (int i = 0; i < rhs->data.i64-1; ++i) {
            rt_DataStr_concat(str, lhs->data.str);
        }
        ret = rt_Data_str(str);
        rt_VarTable_acc_setval(ret);
        return;
    }

    enum rt_DataType_t greater_type = rt_Data_greater_type(*lhs, *rhs);
    if (greater_type != rt_DATA_TYPE_ANY) {
        rt_Data_t lhs_ = rt_Data_cast(*lhs, greater_type);
        rt_Data_t rhs_ = rt_Data_cast(*rhs, greater_type);
        switch (greater_type) {
            case rt_DATA_TYPE_BUL:
                ret = rt_Data_bul(lhs_.data.bul RT_OP_ASTERIX rhs_.data.bul);
                break;
            case rt_DATA_TYPE_CHR:
                ret = rt_Data_chr(lhs_.data.chr RT_OP_ASTERIX rhs_.data.chr);
                break;
            case rt_DATA_TYPE_I64:
                ret = rt_Data_i64(lhs_.data.i64 RT_OP_ASTERIX rhs_.data.i64);
                break;
            case rt_DATA_TYPE_F64:
                ret = rt_Data_f64(lhs_.data.f64 RT_OP_ASTERIX rhs_.data.f64);
                break;
            case rt_DATA_TYPE_STR:
            case rt_DATA_TYPE_INTERP_STR:
            case rt_DATA_TYPE_LST:
            case rt_DATA_TYPE_MAP:
            case rt_DATA_TYPE_ANY:
            case rt_DATA_TYPE_PROC:
                rt_throw("no operator '" RT_OP_ASTERIX_STR "' for types `%s` and `%s`",
                    rt_Data_typename(*lhs), rt_Data_typename(*rhs));
        }
        rt_Data_destroy(&lhs_);
        rt_Data_destroy(&rhs_);
    }
    else rt_throw("no operator '" RT_OP_ASTERIX_STR "' for types `%s` and `%s`",
        rt_Data_typename(*lhs), rt_Data_typename(*rhs));

    rt_VarTable_acc_setval(ret);

}

#else
    #warning re-inclusion of module 'runtime/operators/asterix.c.h'
#endif
