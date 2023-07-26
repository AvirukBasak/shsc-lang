#ifndef RT_DATA_C_H
#define RT_DATA_C_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "errcodes.h"
#include "runtime/data.h"
#include "runtime/data/string.h"
#include "runtime/data/list.h"
#include "runtime/vartable.h"
#include "io.h"

RT_Data_t RT_Data_bul(bool val)
{
    RT_Data_t var;
    var.type = RT_DATA_TYPE_BUL;
    var.data.bul = val;
    return var;
}

RT_Data_t RT_Data_chr(char val)
{
    RT_Data_t var;
    var.type = RT_DATA_TYPE_CHR;
    var.data.chr = val;
    return var;
}

RT_Data_t RT_Data_i64(int64_t val)
{
    RT_Data_t var;
    var.type = RT_DATA_TYPE_I64;
    var.data.i64 = val;
    return var;
}

RT_Data_t RT_Data_f64(double val)
{
    RT_Data_t var;
    var.type = RT_DATA_TYPE_F64;
    var.data.f64 = val;
    return var;
}

RT_Data_t RT_Data_str(RT_DataStr_t *str)
{
    RT_Data_t var;
    var.type = RT_DATA_TYPE_STR;
    var.data.str = str;
    return var;
}

RT_Data_t RT_Data_interp_str(RT_DataStr_t *str)
{
    RT_Data_t var;
    var.type = RT_DATA_TYPE_INTERP_STR;
    var.data.str = str;
    return var;
}

RT_Data_t RT_Data_list(RT_DataList_t *lst)
{
    RT_Data_t var;
    var.type = RT_DATA_TYPE_LST;
    var.data.lst = lst;
    return var;
}

RT_Data_t RT_Data_any(void *ptr)
{
    RT_Data_t var;
    var.type = RT_DATA_TYPE_ANY;
    var.data.any = ptr;
    return var;
}

RT_Data_t RT_Data_null(void)
{
    return RT_Data_any(NULL);
}

void RT_Data_destroy(RT_Data_t *var)
{
    switch (var->type) {
        case RT_DATA_TYPE_STR:
        case RT_DATA_TYPE_INTERP_STR:
            RT_DataStr_destroy(&var->data.str);
            break;
        case RT_DATA_TYPE_LST:
            RT_DataList_destroy(&var->data.lst);
            break;
        case RT_DATA_TYPE_ANY:
            if (var->data.any) free(var->data.any);
            var->data.any = NULL;
            break;
        default:
            break;
    }
}

bool RT_Data_isnull(const RT_Data_t var)
{
    return var.type == RT_DATA_TYPE_ANY && !var.data.any;
}

bool RT_Data_Identifier_isvalid(const char *idf)
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

char *RT_Data_interp_str_parse(const char *str_)
{
    char *str = strdup(str_),
         *ret = NULL;
    int p = 0;
    size_t ret_sz = 0;
    size_t str_sz = strlen(str);
    for (int64_t i = 0; i < str_sz; ++i) {
        if (p >= ret_sz) {
            ret = (char*) realloc(ret, (ret_sz += ret_sz * 2 +1) * sizeof(char));
            if (!ret) io_errndie("RT_Data_interp_str_parse:" ERR_MSG_REALLOCFAIL);
        }
        if (str[i] != '{') {
            *(ret + p++) = str[i];
            continue;
        }
        char *closing = strchr(&str[i] +1, '}');
        if (!closing) rt_throw("unterminated string interpolation: '%s'", str_);
        size_t idflen = closing - &str[i] -1;
        *(closing++) = '\0';
        if (!RT_Data_Identifier_isvalid(&str[i] +1))
            rt_throw("invalid interpolation identifier: '%s'", &str[i] +1);
        RT_Data_t var = RT_VarTable_get(&str[i] +1);
        if (RT_Data_isnull(var))
            rt_throw("undeclared identifier: '%s'", &str[i] +1);
        char *val = RT_Data_tostr(var);
        size_t sz = strlen(val) +1;
        ret = (char*) realloc(ret, (ret_sz += sz) * sizeof(char));
        if (!ret) io_errndie("RT_Data_interp_str_parse:" ERR_MSG_REALLOCFAIL);
        sprintf(ret +p, "%s", val);
        free(val);
        val = NULL;
        p += sz;
        i += idflen -1;
    }
    free(str);
    str = NULL;
    return ret;
}

/** Used to convert a Data object to a printable char* */
char *RT_Data_tostr(const RT_Data_t var)
{
    switch (var.type) {
        case RT_DATA_TYPE_BUL: {
            char *str = (char*) malloc(5 +1 * sizeof(char));
            if (!str) io_errndie("RT_Data_tostr:" ERR_MSG_MALLOCFAIL);
            sprintf(str, "%s", var.data.bul ? "true" : "false");
            return str;
        }
        case RT_DATA_TYPE_CHR: {
            char *str = (char*) malloc(1 +1 * sizeof(char));
            if (!str) io_errndie("RT_Data_tostr:" ERR_MSG_MALLOCFAIL);
            sprintf(str, "%c", var.data.chr);
            return str;
        }
        case RT_DATA_TYPE_I64: {
            char *str = (char*) malloc(20 +1 * sizeof(char));
            if (!str) io_errndie("RT_Data_tostr:" ERR_MSG_MALLOCFAIL);
            sprintf(str, "%" PRId64, var.data.i64);
            return str;
        }
        case RT_DATA_TYPE_F64: {
            size_t sz = snprintf(NULL, 0, "%lf", var.data.f64);
            char *str = (char*) malloc((sz +1) * sizeof(char));
            if (!str) io_errndie("RT_Data_tostr:" ERR_MSG_MALLOCFAIL);
            sprintf(str, "%lf", var.data.f64);
            return str;
        }
        case RT_DATA_TYPE_STR: {
            return strdup(var.data.str->var);
        }
        case RT_DATA_TYPE_INTERP_STR: {
            return RT_Data_interp_str_parse(var.data.str->var);
        }
        case RT_DATA_TYPE_LST: {
            return RT_DataList_tostr(var.data.lst);
        }
        case RT_DATA_TYPE_ANY: {
            if (!var.data.any) return strdup("null");
            char *str = (char*) malloc(16 +1 * sizeof(char));
            if (!str) io_errndie("RT_Data_tostr:" ERR_MSG_MALLOCFAIL);
            sprintf(str, "0x%p", var.data.any);
            return str;
        }
        default:
            return strdup("undefined");
    }
}

void RT_Data_print(RT_Data_t var)
{
    char *str = RT_Data_tostr(var);
    printf("%s", str);
    free(str);
}

#include "data/string.c.h"
#include "data/list.c.h"

#else
    #warning re-inclusion of module 'runtime/data.c.h'
#endif
