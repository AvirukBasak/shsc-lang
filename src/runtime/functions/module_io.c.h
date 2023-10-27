#ifndef RT_FN_MODULE_IO_C_H
#define RT_FN_MODULE_IO_C_H

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "errcodes.h"
#include "io.h"
#include "runtime/io.h"
#include "runtime/data/Data.h"
#include "runtime/data/DataStr.h"
#include "runtime/data/DataList.h"
#include "runtime/functions.h"
#include "runtime/functions/module_io.h"
#include "runtime/VarTable.h"

bool rt_fn_io_input_type_isvalid(enum rt_DataType_t type);
void rt_fn_io_input_bul(bool *val);
void rt_fn_io_input_chr(char *val);
void rt_fn_io_input_i64(int64_t *val);
void rt_fn_io_input_f64(double *val);
int rt_fn_io_input_str(char **val);

rt_Data_t rt_fn_io_print()
{
    rt_Data_t args = *rt_VarTable_getref(RT_VTABLE_ARGSVAR);
    if (args.type != rt_DATA_TYPE_LST)
        io_errndie("rt_fn_io_print: "
                   "received arguments list as type '%s'", rt_Data_typename(args));
    int bytes = 0;
    for (int i = 0; i < rt_DataList_length(args.data.lst); ++i) {
        const rt_Data_t data = *rt_DataList_getref(args.data.lst, i);
        /* if (rt_Data_isnull(data)) continue; */
        /* print a space before data conditions:
           - no space before 1st element
           - no space before `lf` */
        /* i is not 1st element AND data is not a character */
        if ((i > 0 && data.type != rt_DATA_TYPE_CHR) ||
            /* i is not 1st element BUT if data is character it should not be lf */
            (i > 0 && data.type == rt_DATA_TYPE_CHR && data.data.chr != '\n'))
                printf(" ");
        bytes += rt_Data_print(data);
    }
    return rt_Data_i64(bytes);
}

rt_Data_t rt_fn_io_input()
{
    rt_Data_t args = *rt_VarTable_getref(RT_VTABLE_ARGSVAR);
    if (args.type != rt_DATA_TYPE_LST)
        io_errndie("rt_fn_io_input: "
                   "received arguments list as type '%s'", rt_Data_typename(args));
    const rt_Data_t prompt = *rt_DataList_getref(args.data.lst, 0);
    const rt_Data_t type_ = *rt_DataList_getref(args.data.lst, 1);
    rt_Data_t ret = rt_Data_null();
    if (type_.type != rt_DATA_TYPE_I64) {
        char *s = rt_Data_tostr(type_);
        rt_throw(
            "input: invalid type parameter: '%s'\n"
            "valid parameters are bul, chr, i64, f64 or str\n"
            "respective values are %d, %d, %d, %d or %d", s,
            rt_DATA_TYPE_BUL, rt_DATA_TYPE_CHR, rt_DATA_TYPE_I64, rt_DATA_TYPE_F64, rt_DATA_TYPE_STR);
        free(s);
    }
    enum rt_DataType_t type = type_.data.i64;
    if (!rt_fn_io_input_type_isvalid(type_.data.i64))
        rt_throw(
            "input: invalid type parameter\n"
            "valid parameters are bul, chr, i64, f64 or str\n"
            "respective values are %d, %d, %d, %d or %d",
            rt_DATA_TYPE_BUL, rt_DATA_TYPE_CHR, rt_DATA_TYPE_I64, rt_DATA_TYPE_F64, rt_DATA_TYPE_STR);
    rt_Data_print(prompt);
    switch (type) {
        case rt_DATA_TYPE_BUL: {
            bool val = false;
            rt_fn_io_input_bul(&val);
            ret = rt_Data_bul(val);
            break;
        }
        case rt_DATA_TYPE_CHR: {
            char val = '\0';
            rt_fn_io_input_chr(&val);
            ret = rt_Data_chr(val);
            break;
        }
        case rt_DATA_TYPE_I64: {
            int64_t val = 0;
            rt_fn_io_input_i64(&val);
            ret = rt_Data_i64(val);
            break;
        }
        case rt_DATA_TYPE_F64: {
            double val= 0.0;
            rt_fn_io_input_f64(&val);
            ret = rt_Data_f64(val);
            break;
        }
        case rt_DATA_TYPE_STR: {
            char *val = NULL;
            rt_fn_io_input_str(&val);
            ret = rt_Data_str(rt_DataStr_init(val));
            free(val);
            break;
        }
        case rt_DATA_TYPE_INTERP_STR:
        case rt_DATA_TYPE_LST:
        case rt_DATA_TYPE_ANY:
        case rt_DATA_TYPE_MAP:
        case rt_DATA_TYPE_PROC: rt_throw(
            "input: invalid type parameter\n"
            "valid parameters are bul, chr, i64, f64 or str\n"
            "respective values are %d, %d, %d, %d or %d",
            rt_DATA_TYPE_BUL, rt_DATA_TYPE_CHR, rt_DATA_TYPE_I64, rt_DATA_TYPE_F64, rt_DATA_TYPE_STR);
        }
    return ret;
}

bool rt_fn_io_input_type_isvalid(enum rt_DataType_t type)
{
    switch (type) {
        case rt_DATA_TYPE_BUL:
        case rt_DATA_TYPE_CHR:
        case rt_DATA_TYPE_I64:
        case rt_DATA_TYPE_F64:
        case rt_DATA_TYPE_STR:
            return true;
        case rt_DATA_TYPE_INTERP_STR:
        case rt_DATA_TYPE_LST:
        case rt_DATA_TYPE_ANY:
        case rt_DATA_TYPE_MAP:
        case rt_DATA_TYPE_PROC:
            return false;
    }
    return false;
}

void rt_fn_io_input_bul(bool *val)
{
    if (!val) io_errndie("rt_fn_io_input_bul:" ERR_MSG_NULLPTR);
    char *str;
    int len = rt_fn_io_input_str(&str);
    if (!strncmp("1", str, len)) *val = true;
    else if (!strncmp("0", str, len)) *val = false;
    else if (!strncmp("true", str, len)) *val = true;
    else if (!strncmp("false", str, len)) *val = false;
    else rt_throw("input: invalid input for type bul: '%s'", str);
    free(str);
}

void rt_fn_io_input_chr(char *val)
{
    if (!val) io_errndie("rt_fn_io_input_chr:" ERR_MSG_NULLPTR);
    char *str;
    int len = rt_fn_io_input_str(&str);
    if (len == 1) *val = str[0];
    else if (len == 0) *val = 0;
    else rt_throw("input: invalid input for type chr: '%s'", str);
    free(str);
}

void rt_fn_io_input_i64(int64_t *val)
{
    if (!val) io_errndie("rt_fn_io_input_i64:" ERR_MSG_NULLPTR);
    char *str;
    rt_fn_io_input_str(&str);
    char *endptr;
    errno = 0;
    *val = (int64_t) strtoll(str, &endptr, 10);
    if (errno || *endptr != '\0')
        rt_throw("input: invalid input for type i64: '%s'", str);
    free(str);
}

void rt_fn_io_input_f64(double *val)
{
    if (!val) io_errndie("rt_fn_io_input_f64:" ERR_MSG_NULLPTR);
    char *str;
    rt_fn_io_input_str(&str);
    char *endptr;
    errno = 0;
    *val = (double) strtod(str, &endptr);
    if (errno || *endptr != '\0')
        rt_throw("input: invalid input for type f64: '%s'", str);
    free(str);
}

int rt_fn_io_input_str(char **val)
{
    if (!val) io_errndie("rt_fn_io_input_str:" ERR_MSG_NULLPTR);
    *val = NULL;
    size_t bufsize = 0;
    int len = io_getline(val, &bufsize, stdin);
    /* remove the newline from result */
    if (len < 0) {
        fprintf(stderr, "%c", '\n');
        rt_throw("input: unknown error occurred");
    }
    (*val)[len-1] = 0; len--;
    return len;
}

#else
    #warning re-inclusion of module 'functions/module_io.c.h'
#endif
