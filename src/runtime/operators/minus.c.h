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

    if (   (lhs->type == rt_DATA_TYPE_INTERP_STR || lhs->type == rt_DATA_TYPE_ANY || lhs->type == rt_DATA_TYPE_PROC)
        || (rhs->type == rt_DATA_TYPE_INTERP_STR || rhs->type == rt_DATA_TYPE_ANY || rhs->type == rt_DATA_TYPE_PROC) )
          rt_throw("no operator '" RT_OP_MINUS_STR "' for types `%s` and `%s`",
            rt_Data_typename(*lhs), rt_Data_typename(*rhs));

    switch (lhs->type) {
        case rt_DATA_TYPE_BUL:
            switch (rhs->type) {
                case rt_DATA_TYPE_BUL:
                    ret = rt_Data_bul(lhs->data.bul  RT_OP_MINUS  rhs->data.bul);
                    break;
                case rt_DATA_TYPE_CHR:
                    ret = rt_Data_chr(lhs->data.bul  RT_OP_MINUS  rhs->data.chr);
                    break;
                case rt_DATA_TYPE_I64:
                    ret = rt_Data_i64(lhs->data.bul  RT_OP_MINUS  rhs->data.i64);
                    break;
                case rt_DATA_TYPE_F64:
                    ret = rt_Data_f64(lhs->data.bul  RT_OP_MINUS  rhs->data.f64);
                    break;
                case rt_DATA_TYPE_STR:
                    break;
                case rt_DATA_TYPE_LST:
                    break;
                case rt_DATA_TYPE_MAP:
                    break;
                case rt_DATA_TYPE_INTERP_STR:
                case rt_DATA_TYPE_ANY:
                case rt_DATA_TYPE_PROC:
                    break;
            }
            break;
        case rt_DATA_TYPE_CHR:
            switch (rhs->type) {
                case rt_DATA_TYPE_BUL:
                    ret = rt_Data_chr(lhs->data.chr  RT_OP_MINUS  rhs->data.bul);
                    break;
                case rt_DATA_TYPE_CHR:
                    ret = rt_Data_chr(lhs->data.chr  RT_OP_MINUS  rhs->data.chr);
                    break;
                case rt_DATA_TYPE_I64:
                    ret = rt_Data_i64(lhs->data.chr  RT_OP_MINUS  rhs->data.i64);
                    break;
                case rt_DATA_TYPE_F64:
                    ret = rt_Data_f64(lhs->data.chr  RT_OP_MINUS  rhs->data.f64);
                    break;
                case rt_DATA_TYPE_STR:
                    break;
                case rt_DATA_TYPE_LST:
                    break;
                case rt_DATA_TYPE_MAP:
                    break;
                case rt_DATA_TYPE_INTERP_STR:
                case rt_DATA_TYPE_ANY:
                case rt_DATA_TYPE_PROC:
                    break;
            }
            break;
        case rt_DATA_TYPE_I64:
            switch (rhs->type) {
                case rt_DATA_TYPE_BUL:
                    ret = rt_Data_i64(lhs->data.i64  RT_OP_MINUS  rhs->data.bul);
                    break;
                case rt_DATA_TYPE_CHR:
                    ret = rt_Data_i64(lhs->data.i64  RT_OP_MINUS  rhs->data.chr);
                    break;
                case rt_DATA_TYPE_I64:
                    ret = rt_Data_i64(lhs->data.i64  RT_OP_MINUS  rhs->data.i64);
                    break;
                case rt_DATA_TYPE_F64:
                    ret = rt_Data_f64(lhs->data.i64  RT_OP_MINUS  rhs->data.f64);
                    break;
                case rt_DATA_TYPE_STR:
                    break;
                case rt_DATA_TYPE_LST:
                    break;
                case rt_DATA_TYPE_MAP:
                    break;
                case rt_DATA_TYPE_INTERP_STR:
                case rt_DATA_TYPE_ANY:
                case rt_DATA_TYPE_PROC:
                    break;
            }
            break;
        case rt_DATA_TYPE_F64:
            switch (rhs->type) {
                case rt_DATA_TYPE_BUL:
                    ret = rt_Data_f64(lhs->data.f64  RT_OP_MINUS  rhs->data.bul);
                    break;
                case rt_DATA_TYPE_CHR:
                    ret = rt_Data_f64(lhs->data.f64  RT_OP_MINUS  rhs->data.chr);
                    break;
                case rt_DATA_TYPE_I64:
                    ret = rt_Data_f64(lhs->data.f64  RT_OP_MINUS  rhs->data.i64);
                    break;
                case rt_DATA_TYPE_F64:
                    ret = rt_Data_f64(lhs->data.f64  RT_OP_MINUS  rhs->data.f64);
                    break;
                case rt_DATA_TYPE_STR:
                    break;
                case rt_DATA_TYPE_LST:
                    break;
                case rt_DATA_TYPE_MAP:
                    break;
                case rt_DATA_TYPE_INTERP_STR:
                case rt_DATA_TYPE_ANY:
                case rt_DATA_TYPE_PROC:
                    break;
            }
            break;
        case rt_DATA_TYPE_STR:
            switch (rhs->type) {
                case rt_DATA_TYPE_BUL:
                    break;
                case rt_DATA_TYPE_CHR:
                    break;
                case rt_DATA_TYPE_I64:
                    break;
                case rt_DATA_TYPE_F64:
                    break;
                case rt_DATA_TYPE_STR:
                    break;
                case rt_DATA_TYPE_LST:
                    break;
                case rt_DATA_TYPE_MAP:
                    break;
                case rt_DATA_TYPE_INTERP_STR:
                case rt_DATA_TYPE_ANY:
                case rt_DATA_TYPE_PROC:
                    break;
            }
            break;
        case rt_DATA_TYPE_LST:
            switch (rhs->type) {
                case rt_DATA_TYPE_BUL:
                    break;
                case rt_DATA_TYPE_CHR:
                    break;
                case rt_DATA_TYPE_I64:
                    break;
                case rt_DATA_TYPE_F64:
                    break;
                case rt_DATA_TYPE_STR:
                    break;
                case rt_DATA_TYPE_LST:
                    break;
                case rt_DATA_TYPE_MAP:
                    break;
                case rt_DATA_TYPE_INTERP_STR:
                case rt_DATA_TYPE_ANY:
                case rt_DATA_TYPE_PROC:
                    break;
            }
            break;
        case rt_DATA_TYPE_MAP:
            switch (rhs->type) {
                case rt_DATA_TYPE_BUL:
                    break;
                case rt_DATA_TYPE_CHR:
                    break;
                case rt_DATA_TYPE_I64:
                    break;
                case rt_DATA_TYPE_F64:
                    break;
                case rt_DATA_TYPE_STR:
                    break;
                case rt_DATA_TYPE_LST:
                    break;
                case rt_DATA_TYPE_MAP:
                    break;
                case rt_DATA_TYPE_INTERP_STR:
                case rt_DATA_TYPE_ANY:
                case rt_DATA_TYPE_PROC:
                    break;
            }
            break;
        case rt_DATA_TYPE_INTERP_STR:
        case rt_DATA_TYPE_ANY:
        case rt_DATA_TYPE_PROC:
            break;
    }
    rt_VarTable_acc_setval(ret);
}

#else
    #warning re-inclusion of module 'runtime/operators/minus.c.h'
#endif
