#ifndef RT_EVAL_LITERAL_C_H
#define RT_EVAL_LITERAL_C_H

#include "ast.h"
#include "ast/api.h"
#include "runtime/data/Data.h"
#include "runtime/data/DataStr.h"
#include "runtime/eval.h"
#include "runtime/io.h"
#include "runtime/VarTable.h"

void rt_eval_Literal(const ast_Literal_t *literal)
{
    if (!literal) {
        rt_VarTable_acc_setval(rt_Data_null());
        return;
    }
    switch (literal->type) {
        case DATA_TYPE_BUL:
            rt_VarTable_acc_setval(
                rt_Data_bul(literal->data.bul));
            break;
        case DATA_TYPE_CHR:
            rt_VarTable_acc_setval(
                rt_Data_chr(literal->data.chr));
            break;
        case DATA_TYPE_I64:
            rt_VarTable_acc_setval(
                rt_Data_i64(literal->data.i64));
            break;
        case DATA_TYPE_F64:
            rt_VarTable_acc_setval(
                rt_Data_f64(literal->data.f64));
            break;
        case DATA_TYPE_STR:
            rt_VarTable_acc_setval(
                rt_Data_str(
                    rt_DataStr_init(literal->data.str)));
            break;
        case DATA_TYPE_INTERP_STR:
            rt_VarTable_acc_setval(
                rt_Data_interp_str(literal->data.str));
            break;
        case DATA_TYPE_LST:
            rt_eval_CommaSepList(literal->data.lst);
            break;
        case DATA_TYPE_MAP:
            rt_eval_AssociativeList(literal->data.mp);
            break;
        case DATA_TYPE_LAMBDA:
            rt_VarTable_acc_setval(
                rt_Data_lambda_nonnative(literal->data.lambda));
            break;
        case DATA_TYPE_ANY:
            /* void* must be explicitly casted */
            rt_VarTable_acc_setval(
                rt_Data_any((void*) literal->data.any));
            break;
    }
}

#else
    #warning re-inclusion of module 'runtime/eval/literal.c.h'
#endif
