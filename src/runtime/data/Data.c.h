#ifndef RT_DATA_C_H
#define RT_DATA_C_H

#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast/api.h"
#include "errcodes.h"
#include "io.h"
#include "runtime/data/Data.h"
#include "runtime/data/DataStr.h"
#include "runtime/data/DataList.h"
#include "runtime/data/DataMap.h"
#include "runtime/io.h"
#include "runtime/VarTable.h"

bool rt_Data_Identifier_isvalid(const char *idf);

rt_Data_t rt_Data_bul(bool val)
{
    rt_Data_t var;
    var.is_const = false;
    var.is_weak = false;
    var.lvalue = false;
    var.type = rt_DATA_TYPE_BUL;
    var.data.bul = !!val;
    return var;
}

rt_Data_t rt_Data_chr(char val)
{
    rt_Data_t var;
    var.is_const = false;
    var.is_weak = false;
    var.lvalue = false;
    var.type = rt_DATA_TYPE_CHR;
    var.data.chr = val;
    return var;
}

rt_Data_t rt_Data_i64(int64_t val)
{
    rt_Data_t var;
    var.is_const = false;
    var.is_weak = false;
    var.lvalue = false;
    var.type = rt_DATA_TYPE_I64;
    var.data.i64 = val;
    return var;
}

rt_Data_t rt_Data_f64(double val)
{
    rt_Data_t var;
    var.is_const = false;
    var.is_weak = false;
    var.lvalue = false;
    var.type = rt_DATA_TYPE_F64;
    var.data.f64 = val;
    return var;
}

#include "runtime/data/DataList.c.h"
#include "runtime/data/DataStr.c.h"
#include "runtime/data/DataMap.c.h"
#include "runtime/data/GarbageColl.c.h"

rt_Data_t rt_Data_str(rt_DataStr_t *str)
{
    rt_Data_t var;
    var.is_const = false;
    var.is_weak = false;
    var.lvalue = false;
    var.type = rt_DATA_TYPE_STR;
    var.data.str = str;
    return var;
}

rt_Data_t rt_Data_interp_str(const char *str)
{
    char *parsed_str = rt_Data_interp_str_parse(str);
    rt_Data_t var = rt_Data_str(
        rt_DataStr_init(parsed_str));
    free(parsed_str);
    return var;
}

rt_Data_t rt_Data_list(rt_DataList_t *lst)
{
    rt_Data_t var;
    var.is_const = false;
    var.is_weak = false;
    var.lvalue = false;
    var.type = rt_DATA_TYPE_LST;
    var.data.lst = lst;
    return var;
}

rt_Data_t rt_Data_map(rt_DataMap_t *mp)
{
    rt_Data_t var;
    var.is_const = false;
    var.is_weak = false;
    var.lvalue = false;
    var.type = rt_DATA_TYPE_MAP;
    var.data.mp = mp;
    return var;
}

rt_Data_t rt_Data_proc(
    const ast_Identifier_t *module_name,
    const ast_Identifier_t *proc_name
) {
    rt_Data_t var;
    var.is_const = false;
    var.is_weak = false;
    var.lvalue = false;
    var.type = rt_DATA_TYPE_PROC;
    var.data.proc.module_name = module_name;
    var.data.proc.proc_name = proc_name;
    var.data.proc.context = NULL;
    return var;
}

rt_Data_t rt_Data_lambda_nonnative(const ast_LambdaLiteral_t *lambda)
{
    rt_Data_t var;
    var.is_const = false;
    var.is_weak = false;
    var.lvalue = false;
    var.type = rt_DATA_TYPE_LAMBDA;
    var.data.lambda.type = rt_DATA_LAMBDA_TYPE_NONNATIVE;
    var.data.lambda.module_name = lambda->module_name;
    var.data.lambda.file_name = lambda->file_name;
    var.data.lambda.context = NULL;
    var.data.lambda.fnptr.nonnative = lambda;
    return var;
}

rt_Data_t rt_Data_lambda_native(const rt_fn_NativeFunction_t fnptr)
{
    rt_Data_t var;
    var.is_const = false;
    var.is_weak = false;
    var.lvalue = false;
    var.type = rt_DATA_TYPE_LAMBDA;
    var.data.lambda.type = rt_DATA_LAMBDA_TYPE_NATIVE;
    var.data.lambda.module_name = NULL;
    var.data.lambda.file_name = NULL;
    var.data.lambda.context = NULL;
    var.data.lambda.fnptr.native = fnptr;
    return var;
}

rt_Data_t rt_Data_lambda(const ast_LambdaLiteral_t *lambda)
{
    return rt_Data_lambda_nonnative(lambda);
}

rt_Data_t rt_Data_any(void *ptr)
{
    rt_Data_t var;
    var.is_const = false;
    var.is_weak = false;
    var.lvalue = false;
    var.type = rt_DATA_TYPE_ANY;
    var.data.any = ptr;
    return var;
}

rt_Data_t rt_Data_null(void)
{
    return rt_Data_any(NULL);
}

void rt_Data_increfc(rt_Data_t *var)
{
    switch (var->type) {
        case rt_DATA_TYPE_STR:
        case rt_DATA_TYPE_INTERP_STR:
            rt_DataStr_increfc(var->data.str);
            break;
        case rt_DATA_TYPE_LST:
            rt_DataList_increfc(var->data.lst);
            break;
        case rt_DATA_TYPE_MAP:
            rt_DataMap_increfc(var->data.mp);
            break;
        case rt_DATA_TYPE_BUL:
        case rt_DATA_TYPE_CHR:
        case rt_DATA_TYPE_I64:
        case rt_DATA_TYPE_F64:
        case rt_DATA_TYPE_ANY:
        case rt_DATA_TYPE_PROC:
        case rt_DATA_TYPE_LAMBDA:
            break;
    }
}

void rt_Data_decrefc(rt_Data_t *var)
{
    switch (var->type) {
        case rt_DATA_TYPE_STR:
        case rt_DATA_TYPE_INTERP_STR:
            rt_DataStr_decrefc(var->data.str);
            break;
        case rt_DATA_TYPE_LST:
            rt_DataList_decrefc(var->data.lst);
            break;
        case rt_DATA_TYPE_MAP:
            rt_DataMap_decrefc(var->data.mp);
            break;
        case rt_DATA_TYPE_BUL:
        case rt_DATA_TYPE_CHR:
        case rt_DATA_TYPE_I64:
        case rt_DATA_TYPE_F64:
        case rt_DATA_TYPE_ANY:
        case rt_DATA_TYPE_PROC:
        case rt_DATA_TYPE_LAMBDA:
            break;
    }
}

rt_Data_t rt_Data_clone(const rt_Data_t var)
{
    switch (var.type) {
        case rt_DATA_TYPE_BUL:
            return rt_Data_bul(var.data.bul);
        case rt_DATA_TYPE_CHR:
            return rt_Data_chr(var.data.chr);
        case rt_DATA_TYPE_I64:
            return rt_Data_i64(var.data.i64);
        case rt_DATA_TYPE_F64:
            return rt_Data_f64(var.data.f64);
        case rt_DATA_TYPE_STR:
        case rt_DATA_TYPE_INTERP_STR:
            return rt_Data_str(rt_DataStr_clone(var.data.str));
        case rt_DATA_TYPE_LST:
            return rt_Data_list(rt_DataList_clone(var.data.lst));
        case rt_DATA_TYPE_MAP:
            return rt_Data_map(rt_DataMap_clone(var.data.mp));
        case rt_DATA_TYPE_ANY:
            return rt_Data_any(var.data.any);
        case rt_DATA_TYPE_PROC:
            return rt_Data_proc(
                var.data.proc.module_name,
                var.data.proc.proc_name
            );
        case rt_DATA_TYPE_LAMBDA:
            if (var.data.lambda.type == rt_DATA_LAMBDA_TYPE_NONNATIVE)
                return rt_Data_lambda(var.data.lambda.fnptr.nonnative);
            else if (var.data.lambda.type == rt_DATA_LAMBDA_TYPE_NATIVE)
                return rt_Data_lambda_native(var.data.lambda.fnptr.native);

    }
    return rt_Data_null();
}

void rt_Data_destroy_circular(rt_Data_t *var, bool flag)
{
    /* if ref is weak, don't free it */
    if (var->is_weak) return;
    switch (var->type) {
        case rt_DATA_TYPE_STR:
        case rt_DATA_TYPE_INTERP_STR:
            rt_DataStr_destroy_circular(&var->data.str, flag);
            if (!var->data.str) *var = rt_Data_null();
            break;
        case rt_DATA_TYPE_LST:
            rt_DataList_destroy_circular(&var->data.lst, flag);
            if (!var->data.lst) *var = rt_Data_null();
            break;
        case rt_DATA_TYPE_MAP:
            rt_DataMap_destroy_circular(&var->data.mp, flag);
            if (!var->data.mp) *var = rt_Data_null();
            break;
        case rt_DATA_TYPE_ANY:
            if (var->data.any) free(var->data.any);
            var->data.any = NULL;
            *var = rt_Data_null();
        case rt_DATA_TYPE_BUL:
        case rt_DATA_TYPE_CHR:
        case rt_DATA_TYPE_I64:
        case rt_DATA_TYPE_F64:
        case rt_DATA_TYPE_PROC:
        case rt_DATA_TYPE_LAMBDA:
            /* assigning non-composite data to rt_VarTable_null on destroy
               corrupts data in case *var points to a rt_ global var */
            break;
    }
}

void rt_Data_destroy(rt_Data_t *var)
{
    rt_Data_destroy_circular(var, false);
}

bool rt_Data_isnull(const rt_Data_t var)
{
    return var.type == rt_DATA_TYPE_ANY && !var.data.any;
}

bool rt_Data_isnumeric(const rt_Data_t var)
{
    switch (var.type) {
        case rt_DATA_TYPE_BUL:
        case rt_DATA_TYPE_CHR:
        case rt_DATA_TYPE_I64:
        case rt_DATA_TYPE_F64:
            return true;
        case rt_DATA_TYPE_STR:
        case rt_DATA_TYPE_INTERP_STR:
        case rt_DATA_TYPE_LST:
        case rt_DATA_TYPE_MAP:
        case rt_DATA_TYPE_ANY:
        case rt_DATA_TYPE_PROC:
        case rt_DATA_TYPE_LAMBDA:
            return false;
    }
    return false;
}

bool rt_Data_isequal(const rt_Data_t var1, const rt_Data_t var2)
{
    /* if var1.type != var2.type, and either of them is numeric
       but the other is not, return false */
    if (var1.type != var2.type) {
        if ( (rt_Data_isnumeric(var1) && !rt_Data_isnumeric(var2))
          || (rt_Data_isnumeric(var2) && !rt_Data_isnumeric(var1)))
            return false;
    }
    return rt_Data_compare(var1, var2) == 0;
}

int64_t rt_Data_compare(const rt_Data_t var1, const rt_Data_t var2)
{
    double diff = 0;
    enum rt_DataType_t greater_type = rt_Data_greater_type(var1, var2);
    if (greater_type != rt_DATA_TYPE_ANY) {
        rt_Data_t var1_ = rt_Data_cast(var1, greater_type);
        rt_Data_t var2_ = rt_Data_cast(var2, greater_type);
        switch (greater_type) {
            case rt_DATA_TYPE_BUL:
                diff = (double) (var1_.data.bul - var2_.data.bul);
                break;
            case rt_DATA_TYPE_CHR:
                diff = (double) (var1_.data.chr - var2_.data.chr);
                break;
            case rt_DATA_TYPE_I64:
                diff = (double) (var1_.data.i64 - var2_.data.i64);
                break;
            case rt_DATA_TYPE_F64:
                diff = var1_.data.f64 - var2_.data.f64;
                break;
            case rt_DATA_TYPE_STR:
            case rt_DATA_TYPE_INTERP_STR:
                diff = (double) rt_DataStr_compare(var1_.data.str, var2_.data.str);
                break;
            case rt_DATA_TYPE_LST:
                diff = (double) rt_DataList_compare(var1_.data.lst, var2_.data.lst);
                break;
            case rt_DATA_TYPE_MAP:
            case rt_DATA_TYPE_ANY:
            case rt_DATA_TYPE_PROC:
            case rt_DATA_TYPE_LAMBDA:
                rt_throw("cannot compare type '%s' with type '%s'",
                    rt_Data_typename(var2), rt_Data_typename(var1));
        }
        rt_Data_destroy(&var1_);
        rt_Data_destroy(&var2_);
    }
    else rt_throw("cannot compare type '%s' with type '%s'",
        rt_Data_typename(var2), rt_Data_typename(var1));
    if (0 < diff && diff < 1) diff = +1;
    else if (-1 < diff && diff < 0) diff = -1;
    return (int64_t) diff;
}

bool rt_Data_Identifier_isvalid(const char *idf)
{
    if (!idf) return false;
    if (idf[0] != '_' && !isalpha(idf[0])) return false;
    int64_t i = 1;
    while (idf[i] != '\0') {
        if (!isalnum(idf[i]) && idf[i] != '_') return false;
        ++i;
    }
    return idf[i] == '\0';
}

char *rt_Data_interp_str_parse(const char *str_)
{
    char *str = strdup(str_),
         *ret = NULL;
    int p = 0;
    size_t ret_sz = 0;
    size_t str_sz = strlen(str);
    for (int64_t i = 0; i < str_sz; ++i) {
        if (p >= ret_sz) {
            ret = (char*) realloc(ret, (ret_sz += ret_sz * 2 +1) * sizeof(char));
            if (!ret) io_errndie("rt_Data_interp_str_parse:" ERR_MSG_REALLOCFAIL);
        }
        if (str[i] != '{') {
            *(ret + p++) = str[i];
            continue;
        }
        char *closing = strchr(&str[i] +1, '}');
        if (!closing) rt_throw("unterminated string interpolation: '%s'", str_);
        size_t idflen = closing - &str[i] -1;
        *(closing++) = '\0';
        if (!rt_Data_Identifier_isvalid(&str[i] +1))
            rt_throw("invalid interpolation identifier: '%s'", &str[i] +1);
        rt_Data_t var = *rt_VarTable_getref(&str[i] +1);
        if (rt_Data_isnull(var))
            rt_throw("undeclared identifier: '%s'", &str[i] +1);
        char *val = rt_Data_tostr(var);
        size_t sz = strlen(val) +1;
        ret = (char*) realloc(ret, (ret_sz += sz) * sizeof(char));
        if (!ret) io_errndie("rt_Data_interp_str_parse:" ERR_MSG_REALLOCFAIL);
        sprintf(ret +p, "%s", val);
        free(val);
        val = NULL;
        p += sz -1;
        i += idflen +1;
    }
    free(str);
    str = NULL;
    ret[p] = 0;
    return ret;
}

/** convert any data to truthy or falsy value */
bool rt_Data_tobool(const rt_Data_t var)
{
    switch (var.type) {
        case rt_DATA_TYPE_BUL:
            return var.data.bul;
        case rt_DATA_TYPE_CHR:
            return !!var.data.chr;
        case rt_DATA_TYPE_I64:
            return !!var.data.i64;
        case rt_DATA_TYPE_F64:
            return !!var.data.f64;
        case rt_DATA_TYPE_STR:
        case rt_DATA_TYPE_INTERP_STR:
            return !!var.data.str->var && !!rt_DataStr_length(var.data.str);
        case rt_DATA_TYPE_LST:
            return !!var.data.lst->var && !!rt_DataList_length(var.data.lst);
        case rt_DATA_TYPE_MAP:
            return !!var.data.mp->data_map && !!rt_DataMap_length(var.data.mp);
        case rt_DATA_TYPE_ANY:
            return !!var.data.any;
        case rt_DATA_TYPE_PROC:
            return !!var.data.proc.proc_name && !!var.data.proc.module_name;
        case rt_DATA_TYPE_LAMBDA:
            return !!var.data.lambda.fnptr.nonnative || !!var.data.lambda.fnptr.native;
    }
    return false;
}

/** used to convert a Data object to a printable char* */
char *rt_Data_tostr(const rt_Data_t var)
{
    switch (var.type) {
        case rt_DATA_TYPE_BUL: {
            char *str = (char*) malloc(5 +1 * sizeof(char));
            if (!str) io_errndie("rt_Data_tostr:" ERR_MSG_MALLOCFAIL);
            sprintf(str, "%s", var.data.bul ? "true" : "false");
            return str;
        }
        case rt_DATA_TYPE_CHR: {
            char *str = (char*) malloc(1 +1 * sizeof(char));
            if (!str) io_errndie("rt_Data_tostr:" ERR_MSG_MALLOCFAIL);
            sprintf(str, "%c", var.data.chr);
            return str;
        }
        case rt_DATA_TYPE_I64: {
            char *str = (char*) malloc(20 +1 * sizeof(char));
            if (!str) io_errndie("rt_Data_tostr:" ERR_MSG_MALLOCFAIL);
            sprintf(str, "%" PRId64, var.data.i64);
            return str;
        }
        case rt_DATA_TYPE_F64: {
            size_t sz = snprintf(NULL, 0, "%lf", var.data.f64);
            char *str = (char*) malloc((sz +1) * sizeof(char));
            if (!str) io_errndie("rt_Data_tostr:" ERR_MSG_MALLOCFAIL);
            sprintf(str, "%lf", var.data.f64);
            return str;
        }
        case rt_DATA_TYPE_STR: {
            return rt_DataStr_tostr(var.data.str);
        }
        case rt_DATA_TYPE_INTERP_STR: {
            char *istr = rt_DataStr_tostr(var.data.str);
            char *res_str = rt_Data_interp_str_parse(istr);
            free(istr);
            istr = NULL;
            return res_str;
        }
        case rt_DATA_TYPE_LST: {
            return rt_DataList_tostr(var.data.lst);
        }
        case rt_DATA_TYPE_MAP: {
            return rt_DataMap_tostr(var.data.mp);
        }
        case rt_DATA_TYPE_ANY: {
            if (!var.data.any) return strdup("null");
            char *str = (char*) malloc(16 +1 * sizeof(char));
            if (!str) io_errndie("rt_Data_tostr:" ERR_MSG_MALLOCFAIL);
            sprintf(str, "%p", var.data.any);
            return str;
        }
        case rt_DATA_TYPE_PROC: {
            size_t sz = snprintf(NULL, 0, "%s:%s",
                var.data.proc.proc_name,
                var.data.proc.module_name
            );
            char *str = (char*) malloc((sz +1) * sizeof(char));
            if (!str) io_errndie("rt_Data_tostr:" ERR_MSG_MALLOCFAIL);
            sprintf(str, "%s:%s",
                var.data.proc.module_name,
                var.data.proc.proc_name
            );
            return str;
        }
        case rt_DATA_TYPE_LAMBDA: {
            size_t sz = snprintf(NULL, 0, "%s:%s",
                rt_DATA_LAMBDA_DEFAULT_NAME,
                var.data.lambda.module_name
            );
            char *str = (char*) malloc((sz +1) * sizeof(char));
            if (!str) io_errndie("rt_Data_tostr:" ERR_MSG_MALLOCFAIL);
            sprintf(str, "%s:%s",
                var.data.lambda.module_name,
                rt_DATA_LAMBDA_DEFAULT_NAME
            );
            return str;
        }
    }
    return NULL;
}

rt_Data_t rt_Data_cast(const rt_Data_t data, enum rt_DataType_t type)
{
    if (data.type == type)
        return rt_Data_clone(data);
    switch (type) {
        case rt_DATA_TYPE_BUL:
            return rt_Data_bul(rt_Data_tobool(data));
        case rt_DATA_TYPE_CHR: {
            switch (data.type) {
                case rt_DATA_TYPE_BUL:
                    return rt_Data_chr((char) data.data.bul);
                case rt_DATA_TYPE_CHR:
                    return rt_Data_chr((char) data.data.chr);
                case rt_DATA_TYPE_I64:
                    return rt_Data_chr((char) data.data.i64);
                case rt_DATA_TYPE_F64:
                    return rt_Data_chr((char) data.data.f64);
                case rt_DATA_TYPE_ANY:
                    if (rt_Data_isnull(data))
                        return rt_Data_chr('\0');
                case rt_DATA_TYPE_STR:
                case rt_DATA_TYPE_LST:
                case rt_DATA_TYPE_MAP:
                case rt_DATA_TYPE_INTERP_STR:
                case rt_DATA_TYPE_PROC:
                case rt_DATA_TYPE_LAMBDA:
                    rt_throw("cannot cast '%s' to '%s'", rt_Data_typename(data),
                        rt_Data_typename((rt_Data_t) { .type = type }));
            }
        }
        case rt_DATA_TYPE_I64: {
            switch (data.type) {
                case rt_DATA_TYPE_BUL:
                    return rt_Data_i64((int64_t) data.data.bul);
                case rt_DATA_TYPE_CHR:
                    return rt_Data_i64((int64_t) data.data.chr);
                case rt_DATA_TYPE_I64:
                    return rt_Data_i64((int64_t) data.data.i64);
                case rt_DATA_TYPE_F64:
                    return rt_Data_i64((int64_t) data.data.f64);
                case rt_DATA_TYPE_ANY:
                    if (rt_Data_isnull(data))
                        return rt_Data_i64(0);
                case rt_DATA_TYPE_STR:
                case rt_DATA_TYPE_LST:
                case rt_DATA_TYPE_MAP:
                case rt_DATA_TYPE_INTERP_STR:
                case rt_DATA_TYPE_PROC:
                case rt_DATA_TYPE_LAMBDA:
                    rt_throw("cannot cast '%s' to '%s'", rt_Data_typename(data),
                        rt_Data_typename((rt_Data_t) { .type = type }));
            }
        }
        case rt_DATA_TYPE_F64: {
            switch (data.type) {
                case rt_DATA_TYPE_BUL:
                    return rt_Data_f64((double) data.data.bul);
                case rt_DATA_TYPE_CHR:
                    return rt_Data_f64((double) data.data.chr);
                case rt_DATA_TYPE_I64:
                    return rt_Data_f64((double) data.data.i64);
                case rt_DATA_TYPE_F64:
                    return rt_Data_f64((double) data.data.f64);
                case rt_DATA_TYPE_ANY:
                    if (rt_Data_isnull(data))
                        return rt_Data_f64(0);
                case rt_DATA_TYPE_STR:
                case rt_DATA_TYPE_LST:
                case rt_DATA_TYPE_MAP:
                case rt_DATA_TYPE_INTERP_STR:
                case rt_DATA_TYPE_PROC:
                case rt_DATA_TYPE_LAMBDA:
                    rt_throw("cannot cast '%s' to '%s'", rt_Data_typename(data),
                        rt_Data_typename((rt_Data_t) { .type = type }));
            }
        }
        case rt_DATA_TYPE_STR:
        case rt_DATA_TYPE_INTERP_STR: {
            if (rt_Data_isnull(data))
                return rt_Data_str(rt_DataStr_init(""));
            char *strdata = rt_Data_tostr(data);
            rt_Data_t retstr = rt_Data_str(rt_DataStr_init(strdata));
            free(strdata);
            return retstr;
        }
        case rt_DATA_TYPE_LST:
            if (rt_Data_isnull(data))
                return rt_Data_list(rt_DataList_init());
        case rt_DATA_TYPE_MAP:
            if (rt_Data_isnull(data))
                return rt_Data_map(rt_DataMap_init());
        case rt_DATA_TYPE_PROC:
        case rt_DATA_TYPE_LAMBDA:
            rt_throw("cannot cast '%s' to '%s'", rt_Data_typename(data),
                rt_Data_typename((rt_Data_t) { .type = type }));
        case rt_DATA_TYPE_ANY: {
            switch (data.type) {
                case rt_DATA_TYPE_BUL:
                    return rt_Data_any((void*) *(long long *) &data.data.bul);
                case rt_DATA_TYPE_CHR:
                    return rt_Data_any((void*) *(long long *) &data.data.chr);
                case rt_DATA_TYPE_I64:
                    return rt_Data_any((void*) *(long long *) &data.data.i64);
                case rt_DATA_TYPE_F64:
                    return rt_Data_any((void*) *(long long *) &data.data.f64);
                case rt_DATA_TYPE_ANY:
                    return data;
                case rt_DATA_TYPE_STR:
                case rt_DATA_TYPE_LST:
                case rt_DATA_TYPE_MAP:
                case rt_DATA_TYPE_INTERP_STR:
                case rt_DATA_TYPE_PROC:
                case rt_DATA_TYPE_LAMBDA:
                    rt_throw("cannot cast '%s' to '%s'", rt_Data_typename(data),
                        rt_Data_typename((rt_Data_t) { .type = type }));
            }
        }
    }
    return rt_Data_null();
}

const char *rt_Data_typename(const rt_Data_t var)
{
    switch (var.type) {
        case rt_DATA_TYPE_BUL:        return "bul";
        case rt_DATA_TYPE_CHR:        return "chr";
        case rt_DATA_TYPE_I64:        return "i64";
        case rt_DATA_TYPE_F64:        return "f64";
        case rt_DATA_TYPE_STR:        return "str";
        case rt_DATA_TYPE_INTERP_STR: return "interp_str";
        case rt_DATA_TYPE_LST:        return "lst";
        case rt_DATA_TYPE_MAP:        return "map";
        case rt_DATA_TYPE_ANY:        return var.data.any ? "any" : "null";
        case rt_DATA_TYPE_PROC:       return "proc";
        case rt_DATA_TYPE_LAMBDA:     return "lambda";
    }
    return NULL;
}

bool rt_Data_assert_type(
    const rt_Data_t var,
    enum rt_DataType_t expected_type,
    const char *for_varname
) {
    if (var.type != expected_type) {
        rt_throw("invalid type for %s: '%s', expected '%s'",
            for_varname, rt_Data_typename(var), rt_Data_typename((rt_Data_t) {
                .type = expected_type
            }));
        return false;
    }
    return true;
}

enum rt_DataType_t rt_Data_greater_type(const rt_Data_t var1, const rt_Data_t var2)
{
    if (var1.type == var2.type)
        return var1.type;
    if (rt_Data_isnumeric(var1) && rt_Data_isnumeric(var2)) {
        if (var1.type == rt_DATA_TYPE_F64 || var2.type == rt_DATA_TYPE_F64)
            return rt_DATA_TYPE_F64;
        if (var1.type == rt_DATA_TYPE_I64 || var2.type == rt_DATA_TYPE_I64)
            return rt_DATA_TYPE_I64;
        if (var1.type == rt_DATA_TYPE_CHR || var2.type == rt_DATA_TYPE_CHR)
            return rt_DATA_TYPE_CHR;
        return rt_DATA_TYPE_BUL;
    }
    if (var1.type == rt_DATA_TYPE_STR || var2.type == rt_DATA_TYPE_STR
     || var1.type == rt_DATA_TYPE_INTERP_STR || var2.type == rt_DATA_TYPE_INTERP_STR)
        return rt_DATA_TYPE_STR;
    return rt_DATA_TYPE_ANY;
}

int rt_Data_print(rt_Data_t var)
{
    char *str = rt_Data_tostr(var);
    int bytes = printf("%s", str);
    free(str);
    return bytes;
}

#else
    #warning re-inclusion of module 'runtime/data/Data.c.h'
#endif
