#ifndef RT_VARIABLE_C_H
#define RT_VARIABLE_C_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "errcodes.h"
#include "runtime/variable.h"
#include "runtime/vartable.h"

RT_Variable_t rt_variable_bul(bool val)
{
    RT_Variable_t var;
    var.type = RT_DATA_TYPE_BUL;
    var.data.bul = val;
    return var;
}

RT_Variable_t rt_variable_chr(char val)
{
    RT_Variable_t var;
    var.type = RT_DATA_TYPE_CHR;
    var.data.chr = val;
    return var;
}

RT_Variable_t rt_variable_i64(int64_t val)
{
    RT_Variable_t var;
    var.type = RT_DATA_TYPE_I64;
    var.data.i64 = val;
    return var;
}

RT_Variable_t rt_variable_f64(double val)
{
    RT_Variable_t var;
    var.type = RT_DATA_TYPE_F64;
    var.data.f64 = val;
    return var;
}

RT_Variable_t rt_variable_str(char *str)
{
    RT_Variable_t var;
    var.type = RT_DATA_TYPE_STR;
    var.data.str = str;
    return var;
}

RT_Variable_t rt_variable_interp_str(char *str)
{
    RT_Variable_t var;
    var.type = RT_DATA_TYPE_INTERP_STR;
    var.data.str = str;
    return var;
}

RT_Variable_t rt_variable_list(RT_VarList_t *lst)
{
    RT_Variable_t var;
    var.type = RT_DATA_TYPE_LST;
    var.data.lst = lst;
    return var;
}

RT_Variable_t rt_variable_any(void *ptr)
{
    RT_Variable_t var;
    var.type = RT_DATA_TYPE_ANY;
    var.data.any = ptr;
    return var;
}

RT_Variable_t rt_variable_null(void)
{
    return rt_variable_any(NULL);
}

void rt_variable_destroy(RT_Variable_t *var)
{
    switch (var->type) {
        case RT_DATA_TYPE_STR:
        case RT_DATA_TYPE_INTERP_STR:
            if (var->data.str) free(var->data.str);
            var->data.str = NULL;
            break;
        case RT_DATA_TYPE_LST:
            rt_varlist_destroy(&var->data.lst);
            break;
        case RT_DATA_TYPE_ANY:
            if (var->data.any) free(var->data.any);
            var->data.any = NULL;
            break;
        default:
            break;
    }
}

bool rt_variable_isnull(const RT_Variable_t var)
{
    return var.type == RT_DATA_TYPE_ANY && !var.data.any;
}

bool rt_variable_valid_idf(const char *idf)
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

char *rt_varable_parse_interp_str(const char *str_)
{
    char *str = strdup(str_),
         *ret = NULL;
    int p = 0;
    size_t ret_sz = 0;
    size_t str_sz = strlen(str);
    for (int64_t i = 0; i < str_sz; ++i) {
        if (p >= ret_sz) {
            ret = (char*) realloc(ret, (ret_sz += ret_sz * 2 +1) * sizeof(char));
            if (!ret) rt_throw("rt_varable_parse_interp_str:" ERR_MSG_REALLOCFAIL);
        }
        if (str[i] != '{') {
            *(ret + p++) = str[i];
            continue;
        }
        char *closing = strchr(&str[i] +1, '}');
        if (!closing) rt_throw("unterminated string interpolation: '%s'", str_);
        size_t idflen = closing - &str[i] -1;
        *(closing++) = '\0';
        if (!rt_variable_valid_idf(&str[i] +1))
            rt_throw("invalid interpolation identifier: '%s'", &str[i] +1);
        RT_Variable_t var = vartable_get(&str[i] +1);
        if (rt_variable_isnull(var))
            rt_throw("undeclared identifier: '%s'", &str[i] +1);
        char *val = rt_variable_tostr(var);
        size_t sz = strlen(val) +1;
        ret = (char*) realloc(ret, (ret_sz += sz) * sizeof(char));
        if (!ret) rt_throw("rt_varable_parse_interp_str:" ERR_MSG_REALLOCFAIL);
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

char *rt_variable_tostr(const RT_Variable_t var)
{
    switch (var.type) {
        case RT_DATA_TYPE_BUL: {
            char *str = (char*) malloc(5 +1 * sizeof(char));
            if (!str) rt_throw("rt_variable_tostr:" ERR_MSG_MALLOCFAIL);
            sprintf(str, "%s", var.data.bul ? "true" : "false");
            return str;
        }
        case RT_DATA_TYPE_CHR: {
            char *str = (char*) malloc(1 +1 * sizeof(char));
            if (!str) rt_throw("rt_variable_tostr:" ERR_MSG_MALLOCFAIL);
            sprintf(str, "%c", var.data.chr);
            return str;
        }
        case RT_DATA_TYPE_I64: {
            char *str = (char*) malloc(20 +1 * sizeof(char));
            if (!str) rt_throw("rt_variable_tostr:" ERR_MSG_MALLOCFAIL);
            sprintf(str, "%" PRId64, var.data.i64);
            return str;
        }
        case RT_DATA_TYPE_F64: {
            size_t sz = sprintf(NULL, "%lf", var.data.f64);
            char *str = (char*) malloc(sz +1 * sizeof(char));
            if (!str) rt_throw("rt_variable_tostr:" ERR_MSG_MALLOCFAIL);
            sprintf(str, "%lf", var.data.f64);
            return str;
        }
        case RT_DATA_TYPE_STR: {
            return strdup(var.data.str);
        }
        case RT_DATA_TYPE_INTERP_STR: {
            return rt_varable_parse_interp_str(var.data.str);
        }
        case RT_DATA_TYPE_LST: {
            return rt_varlist_tostr(var.data.lst);
        }
        case RT_DATA_TYPE_ANY: {
            if (!var.data.any) return strdup("null");
            char *str = (char*) malloc(16 +1 * sizeof(char));
            if (!str) rt_throw("rt_variable_tostr:" ERR_MSG_MALLOCFAIL);
            sprintf(str, "0x%p", var.data.any);
            return str;
        }
        default:
            return strdup("undefined");
    }
}

void rt_variable_print(RT_Variable_t var)
{
    char *str = rt_variable_tostr(var);
    printf("%s", str);
    free(str);
}

RT_VarList_t *rt_varlist_init()
{
    RT_VarList_t *lst = (RT_VarList_t*) malloc(sizeof(RT_VarList_t));
    if (!lst) rt_throw("rt_varlist_init:" ERR_MSG_MALLOCFAIL);
    lst->var = NULL;
    lst->length = 0;
    lst->capacity = 0;
    return lst;
}

int64_t rt_varlist_length(const RT_VarList_t *lst)
{
    return lst->length;
}

void rt_varlist_destroy(RT_VarList_t **ptr)
{
    if (!ptr || !*ptr) return;
    RT_VarList_t *lst = *ptr;
    for (int64_t i = 0; i < lst->length; i++) {
        RT_Variable_t var = lst->var[i];
        if (var.type == RT_DATA_TYPE_STR || var.type == RT_DATA_TYPE_INTERP_STR) {
            free(var.data.str);
            var.data.str = NULL;
            var.type = RT_DATA_TYPE_ANY;
        } else if (var.type == RT_DATA_TYPE_LST)
            rt_varlist_destroy(&var.data.lst);
    }
    free(lst->var);
    free(lst);
    *ptr = NULL;
}

void rt_varlist_append(RT_VarList_t *lst, RT_Variable_t var)
{
    if (lst->length >= lst->capacity) {
        lst->capacity = lst->capacity == 0 ? 4 : lst->capacity * 2;
        lst->var = (RT_Variable_t*) realloc(lst->var, lst->capacity * sizeof(RT_Variable_t));
        if (!lst->var) rt_throw("rt_varlist_append:" ERR_MSG_REALLOCFAIL);
    }
    lst->var[lst->length++] = var;
}

void rt_varlist_set(RT_VarList_t *lst, int64_t idx, RT_Variable_t var)
{
    if (idx >= 0 && idx < lst->length) {
        RT_Variable_t old_var = lst->var[idx];
        if (old_var.type == RT_DATA_TYPE_STR || old_var.type == RT_DATA_TYPE_INTERP_STR) {
            free(old_var.data.str);
            var.data.str = NULL;
        } else if (old_var.type == RT_DATA_TYPE_LST)
            rt_varlist_destroy(&old_var.data.lst);
        lst->var[idx] = var;
    }
}

RT_Variable_t rt_varlist_get(const RT_VarList_t *lst, int64_t idx)
{
    RT_Variable_t var;
    if (idx >= 0 && idx < lst->length)
        var = lst->var[idx];
    else var = rt_variable_any(NULL);
    return var;
}

void rt_varlist_del_index(RT_VarList_t *lst, int64_t idx)
{
    if (idx >= 0 && idx < lst->length) {
        RT_Variable_t var = lst->var[idx];
        if (var.type == RT_DATA_TYPE_STR || var.type == RT_DATA_TYPE_INTERP_STR)
            free(var.data.str);
        for (int64_t i = idx + 1; i < lst->length; i++)
            lst->var[i-1] = lst->var[i];
        --lst->length;
    }
}

void rt_varlist_del_val(RT_VarList_t *lst, RT_Variable_t var)
{
    for (int64_t i = 0; i < lst->length; i++) {
        if (memcmp(&lst->var[i], &var, sizeof(RT_Variable_t)) == 0) {
            rt_varlist_del_index(lst, i);
            return;
        }
    }
}

char *rt_varlist_tostr(const RT_VarList_t *lst)
{
    char *str = (char*) malloc(3 * sizeof(char));
    if (!str) rt_throw("rt_varlist_tostr:" ERR_MSG_MALLOCFAIL);
    int p = 0;
    size_t size = 3;
    sprintf(str + p++, "[");
    for (int64_t i = 0; i < lst->length; ++i) {
        char *lst_el = rt_variable_tostr(lst->var[i]);
        const size_t sz = strlen(lst_el) +1;
        str = (char*) realloc(str, (size += sz) * sizeof(char));
        if (!str) rt_throw("rt_varlist_tostr:" ERR_MSG_REALLOCFAIL);
        sprintf(str + p, "%s", lst_el);
        free(lst_el);
        lst_el = NULL;
        p += sz;
        if (i != lst->length - 1) {
            str = (char*) realloc(str, (size += 2) * sizeof(char));
            if (!str) rt_throw("rt_varlist_tostr:" ERR_MSG_REALLOCFAIL);
            sprintf(str + p, ", ");
            p += 2;
        }
    }
    sprintf(str + p++, "]");
    return str;
}

#else
    #warning re-inclusion of module 'runtime/variable.c.h'
#endif
