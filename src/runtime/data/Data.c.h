#ifndef RT_DATA_C_H
#define RT_DATA_C_H

#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
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

rt_Data_t rt_Data_bul(bool val)
{
    rt_Data_t var;
    var.type = rt_DATA_TYPE_BUL;
    var.data.bul = !!val;
    return var;
}

rt_Data_t rt_Data_chr(char val)
{
    rt_Data_t var;
    var.type = rt_DATA_TYPE_CHR;
    var.data.chr = val;
    return var;
}

rt_Data_t rt_Data_i64(int64_t val)
{
    rt_Data_t var;
    var.type = rt_DATA_TYPE_I64;
    var.data.i64 = val;
    return var;
}

rt_Data_t rt_Data_f64(double val)
{
    rt_Data_t var;
    var.type = rt_DATA_TYPE_F64;
    var.data.f64 = val;
    return var;
}

#include "runtime/data/DataList.c.h"
#include "runtime/data/DataStr.c.h"
#include "runtime/data/DataMap.c.h"

rt_Data_t rt_Data_str(rt_DataStr_t *str)
{
    rt_Data_t var;
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
    var.type = rt_DATA_TYPE_LST;
    var.data.lst = lst;
    return var;
}

rt_Data_t rt_Data_map(rt_DataMap_t *mp)
{
    rt_Data_t var;
    var.type = rt_DATA_TYPE_MAP;
    var.data.mp = mp;
    return var;
}

rt_Data_t rt_Data_any(void *ptr)
{
    rt_Data_t var;
    var.type = rt_DATA_TYPE_ANY;
    var.data.any = ptr;
    return var;
}

rt_Data_t rt_Data_null(void)
{
    return rt_VarTable_rsv_null;
}

void rt_Data_copy(rt_Data_t *var)
{
    switch (var->type) {
        case rt_DATA_TYPE_STR:
        case rt_DATA_TYPE_INTERP_STR:
            rt_DataStr_copy(var->data.str);
            break;
        case rt_DATA_TYPE_LST:
            rt_DataList_copy(var->data.lst);
            break;
        case rt_DATA_TYPE_MAP:
            rt_DataMap_copy(var->data.mp);
            break;
        default:
            break;
    }
}

void rt_Data_destroy(rt_Data_t *var)
{
    switch (var->type) {
        case rt_DATA_TYPE_STR:
        case rt_DATA_TYPE_INTERP_STR:
            rt_DataStr_destroy(&var->data.str);
            if (!var->data.str) *var = rt_Data_null();
            break;
        case rt_DATA_TYPE_LST:
            rt_DataList_destroy(&var->data.lst);
            if (!var->data.lst) *var = rt_Data_null();
            break;
        case rt_DATA_TYPE_MAP:
            rt_DataMap_destroy(&var->data.mp);
            if (!var->data.mp) *var = rt_Data_null();
            break;
        case rt_DATA_TYPE_ANY:
            if (var->data.any) free(var->data.any);
            var->data.any = NULL;
            *var = rt_Data_null();
            break;
        default:
            /* assigning non-composite data to rt_VarTable_null
               corrupts data in case *var points to a rt_ global var */
            break;
    }
}

bool rt_Data_isnull(const rt_Data_t var)
{
    return var.type == rt_DATA_TYPE_ANY && !var.data.any;
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
        default:
            return false;
    }
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
        default:
            return strdup("undefined");
    }
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
    }
    return NULL;
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
