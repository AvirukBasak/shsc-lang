#ifndef RT_DATA_STRING_C_H
#define RT_DATA_STRING_C_H

#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "errcodes.h"
#include "runtime/data/Data.h"
#include "runtime/data/DataList.h"
#include "runtime/data/DataStr.h"
#include "runtime/io.h"

rt_DataStr_t *rt_DataStr_init(const char *s)
{
    rt_DataStr_t *str = (rt_DataStr_t*) malloc(sizeof(rt_DataStr_t));
    if (!str) io_errndie("rt_DataStr_init:" ERR_MSG_MALLOCFAIL);
    str->var = rt_DataList_init();
    int64_t length = strlen(s);
    for (int64_t i = 0; i < length; i++)
        rt_DataList_append(str->var, rt_Data_chr(s[i]));
    return str;
}

rt_DataStr_t *rt_DataStr_clone(const rt_DataStr_t *str)
{
    rt_DataStr_t *str2 = (rt_DataStr_t*) malloc(sizeof(rt_DataStr_t));
    if (!str2) io_errndie("rt_DataStr_clone:" ERR_MSG_MALLOCFAIL);
    for (int64_t i = 0; i < rt_DataStr_length(str); i++) {
        char ch = rt_DataList_getref(str->var, i)->data.chr;
        rt_DataList_append(str2->var, rt_Data_chr(ch));
    }
    return str2;
}

int64_t rt_DataStr_length(const rt_DataStr_t *str)
{
    return rt_DataList_length(str->var);
}

void rt_DataStr_increfc(rt_DataStr_t *str)
{
    rt_DataList_increfc(str->var);
}

void rt_DataStr_decrefc(rt_DataStr_t *str)
{
    rt_DataList_decrefc(str->var);
}

void rt_DataStr_destroy_circular(rt_DataStr_t **ptr, bool flag)
{
    if (!ptr || !*ptr) return;
    rt_DataList_destroy_circular(&(*ptr)->var, flag);
    /* free wrapper only if the list inside was freed and nulled */
    if ((*ptr)->var) return;
    free(*ptr);
    *ptr = NULL;
}

void rt_DataStr_destroy(rt_DataStr_t **ptr)
{
    rt_DataStr_destroy_circular(ptr, false);
}

void rt_DataStr_append(rt_DataStr_t *str, char var)
{
    rt_DataList_append(str->var, rt_Data_chr(var));
}

void rt_DataStr_concat(rt_DataStr_t *str, const rt_DataStr_t *str2)
{
    int64_t length = rt_DataStr_length(str2);
    for (int64_t i = 0; i < length; i++) {
        char ch = rt_DataList_getref(str2->var, i)->data.chr;
        rt_DataList_append(str->var, rt_Data_chr(ch));
    }
}

void rt_DataStr_insert(rt_DataStr_t *str, int64_t idx, char var)
{
    if (idx >= 0 && idx < rt_DataStr_length(str))
        rt_DataList_insert(str->var, idx, rt_Data_chr(var));
    else rt_throw("string out of bounds for index '%" PRId64 "'", idx);
}

void rt_DataStr_insert_str(rt_DataStr_t *str, int64_t idx, const rt_DataStr_t *str2)
{
    if (idx >= 0 && idx < rt_DataStr_length(str)) {
        int64_t length = rt_DataStr_length(str2);
        for (int64_t i = 0; i < length; i++) {
            char ch = rt_DataList_getref(str2->var, i)->data.chr;
            rt_DataList_insert(str->var, idx + i, rt_Data_chr(ch));
        }
    }
    else rt_throw("string out of bounds for index '%" PRId64 "'", idx);
}

void rt_DataStr_erase(rt_DataStr_t *str, int64_t idx, int64_t len)
{
    if (idx >= 0 && idx < rt_DataStr_length(str)) {
        if (len < 0) rt_throw("negative length '%" PRId64 "'", len);
        if (idx + len > rt_DataStr_length(str))
            rt_throw("string out of bounds for index '%" PRId64 "'", idx + len);
        for (int64_t i = 0; i < len; i++)
            rt_DataList_del_index(str->var, idx);
    }
    else rt_throw("string out of bounds for index '%" PRId64 "'", idx);
}

void rt_DataStr_reverse(rt_DataStr_t *str)
{
    rt_DataList_reverse(str->var);
}

bool rt_DataStr_isequal(const rt_DataStr_t *str, const rt_DataStr_t *str2)
{
    int64_t length = rt_DataStr_length(str);
    int64_t length2 = rt_DataStr_length(str2);
    if (length != length2) return false;
    for (int64_t i = 0; i < length; i++) {
        char ch = rt_DataList_getref(str->var, i)->data.chr;
        char ch2 = rt_DataList_getref(str2->var, i)->data.chr;
        if (ch != ch2) return false;
    }
    return true;
}

int64_t rt_DataStr_compare(const rt_DataStr_t *str, const rt_DataStr_t *str2)
{
    int64_t length = rt_DataStr_length(str);
    int64_t length2 = rt_DataStr_length(str2);
    int64_t minlen = length < length2 ? length : length2;
    for (int64_t i = 0; i < minlen; i++) {
        char ch = rt_DataList_getref(str->var, i)->data.chr;
        char ch2 = rt_DataList_getref(str2->var, i)->data.chr;
        if (ch != ch2) return ch - ch2;
    }
    return length - length2;
}

int64_t rt_DataStr_find(const rt_DataStr_t *str, char var)
{
    return rt_DataList_find(str->var, rt_Data_chr(var));
}

int64_t rt_DataStr_find_str(const rt_DataStr_t *str, const rt_DataStr_t *str2)
{
    int64_t length = rt_DataStr_length(str);
    int64_t length2 = rt_DataStr_length(str2);
    for (int64_t i = 0; i < length; i++) {
        bool found = true;
        for (int64_t j = 0; j < length2; j++) {
            if (i + j >= length) {
                found = false;
                break;
            }
            char ch = rt_DataList_getref(str->var, i + j)->data.chr;
            char ch2 = rt_DataList_getref(str2->var, j)->data.chr;
            if (ch != ch2) {
                found = false;
                break;
            }
        }
        if (found) return i;
    }
    return -1;
}

rt_DataStr_t *rt_DataStr_substr(const rt_DataStr_t *str, int64_t idx, int64_t len)
{
    rt_DataStr_t *str2 = rt_DataStr_init("");
    str2->var = rt_DataList_sublist(str->var, idx, len);
    return str2;
}

rt_DataList_t *rt_DataStr_split(const rt_DataStr_t *str, char var)
{
    rt_DataList_t *lst = rt_DataList_init();
    int64_t length = rt_DataStr_length(str);
    int64_t start = 0;
    for (int64_t i = 0; i < length; i++) {
        char ch = rt_DataList_getref(str->var, i)->data.chr;
        if (ch == var) {
            rt_DataStr_t *str2 = rt_DataStr_init("");
            str2->var = rt_DataList_sublist(str->var, start, i - start);
            rt_DataList_append(lst, rt_Data_str(str2));
            start = i + 1;
        }
    }
    rt_DataStr_t *str2 = rt_DataStr_init("");
    str2->var = rt_DataList_sublist(str->var, start, length - start);
    rt_DataList_append(lst, rt_Data_str(str2));
    return lst;
}

rt_DataList_t *rt_DataStr_split_str(const rt_DataStr_t *str, const rt_DataStr_t *str2)
{
    rt_DataList_t *lst = rt_DataList_init();
    int64_t length = rt_DataStr_length(str);
    int64_t length2 = rt_DataStr_length(str2);
    int64_t start = 0;
    for (int64_t i = 0; i < length; i++) {
        bool found = true;
        for (int64_t j = 0; j < length2; j++) {
            if (i + j >= length) {
                found = false;
                break;
            }
            char ch = rt_DataList_getref(str->var, i + j)->data.chr;
            char ch2 = rt_DataList_getref(str2->var, j)->data.chr;
            if (ch != ch2) {
                found = false;
                break;
            }
        }
        if (found) {
            rt_DataStr_t *str3 = rt_DataStr_init("");
            str3->var = rt_DataList_sublist(str->var, start, i - start);
            rt_DataList_append(lst, rt_Data_str(str3));
            start = i + length2;
        }
    }
    rt_DataStr_t *str3 = rt_DataStr_init("");
    str3->var = rt_DataList_sublist(str->var, start, length - start);
    rt_DataList_append(lst, rt_Data_str(str3));
    return lst;
}

rt_DataStr_t *rt_DataStr_sort(rt_DataStr_t *str)
{
    rt_DataList_sort(str->var);
    return str;
}

rt_Data_t rt_DataStr_toi64(const rt_DataStr_t *str)
{
    int64_t length = rt_DataStr_length(str);
    int64_t val = 0;
    for (int64_t i = 0; i < length; i++) {
        char ch = rt_DataList_getref(str->var, i)->data.chr;
        if (ch < '0' || ch > '9') rt_throw("invalid character '%c'", ch);
        val = val * 10 + (ch - '0');
    }
    return rt_Data_i64(val);
}

rt_Data_t rt_DataStr_tof64(const rt_DataStr_t *str)
{
    int64_t length = rt_DataStr_length(str);
    double val = 0;
    double div = 1;
    bool dot = false;
    for (int64_t i = 0; i < length; i++) {
        char ch = rt_DataList_getref(str->var, i)->data.chr;
        if (ch == '.') {
            if (dot) rt_throw("invalid character '%c'", ch);
            dot = true;
            continue;
        }
        if (ch < '0' || ch > '9') rt_throw("invalid character '%c'", ch);
        if (dot) div *= 10;
        val = val * 10 + (ch - '0');
    }
    return rt_Data_f64(val / div);
}

char *rt_DataStr_getref_errnull(const rt_DataStr_t *str, int64_t idx)
{
    if (idx >= 0 && idx < rt_DataStr_length(str))
        return &rt_DataList_getref_errnull(str->var, idx)->data.chr;
    return NULL;
}

rt_Data_t *rt_DataStr_getref(const rt_DataStr_t *str, int64_t idx)
{
    if (idx >= 0 && idx < rt_DataStr_length(str))
        return rt_DataList_getref(str->var, idx);
    else rt_throw("string out of bounds for index '%" PRId64 "'", idx);
    return NULL;
}

void rt_DataStr_del_index(rt_DataStr_t *str, int64_t idx)
{
    if (idx >= 0 && idx < rt_DataStr_length(str)) {
        rt_DataList_del_index(str->var, idx);
    }
    else rt_throw("string out of bounds for index '%" PRId64 "'", idx);
}

void rt_DataStr_del_val(rt_DataStr_t *str, char var)
{
    rt_DataList_del_val(str->var, rt_Data_chr(var));
}

char *rt_DataStr_tostr(const rt_DataStr_t *str)
{
    int64_t length = rt_DataStr_length(str);
    char *s = (char*) malloc((length + 1) * sizeof(char));
    if (!s) io_errndie("rt_DataStr_tostr:" ERR_MSG_MALLOCFAIL);
    for (int64_t i = 0; i < length; i++)
        s[i] = rt_DataList_getref(str->var, i)->data.chr;
    s[length] = '\0';
    return s;
}

#else
    #warning re-inclusion of module 'runtime/data/DataStr.c.h'
#endif
