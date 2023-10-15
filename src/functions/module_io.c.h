#ifndef FN_MODULE_IO_C_H
#define FN_MODULE_IO_C_H

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "errcodes.h"
#include "functions.h"
#include "functions/module_io.h"
#include "io.h"
#include "runtime/io.h"
#include "runtime/data/Data.h"
#include "runtime/data/DataStr.h"
#include "runtime/data/DataList.h"
#include "runtime/VarTable.h"

bool fn_io_input_type_isvalid(enum RT_DataType_t type);
void fn_io_input_bul(bool *val);
void fn_io_input_chr(char *val);
void fn_io_input_i64(int64_t *val);
void fn_io_input_f64(double *val);
int fn_io_input_str(char **val);

RT_Data_t FN_io_print()
{
    RT_Data_t args = *RT_VarTable_getref("$");
    if (args.type != RT_DATA_TYPE_LST)
        io_errndie("FN_io_print: "
                   "received arguments list as type '%s'", RT_Data_typename(args));
    int bytes = 0;
    for (int i = 0; i < RT_DataList_length(args.data.lst); ++i) {
        const RT_Data_t data = *RT_DataList_getref(args.data.lst, i);
        if (RT_Data_isnull(data)) continue;
        /* print a space before data conditions:
           - no space before 1st element
           - no space before `lf` */
        /* i is not 1st element AND data is not a character */
        if ((i > 0 && data.type != RT_DATA_TYPE_CHR) ||
            /* i is not 1st element BUT if data is character it should not be lf */
            (i > 0 && data.type == RT_DATA_TYPE_CHR && data.data.chr != '\n'))
                printf(" ");
        bytes += RT_Data_print(data);
    }
    return RT_Data_i64(bytes);
}

RT_Data_t FN_io_input()
{
    RT_Data_t args = *RT_VarTable_getref("$");
    if (args.type != RT_DATA_TYPE_LST)
        io_errndie("FN_io_input: "
                   "received arguments list as type '%s'", RT_Data_typename(args));
    const RT_Data_t prompt = *RT_DataList_getref(args.data.lst, 0);
    const RT_Data_t type_ = *RT_DataList_getref(args.data.lst, 1);
    RT_Data_t ret = RT_Data_null();
    if (type_.type != RT_DATA_TYPE_I64) {
        char *s = RT_Data_tostr(type_);
        rt_throw(
            "input: invalid type parameter: '%s'\n"
            "  valid parameters are bul, chr, i64, f64 or str\n"
            "  respective values are %d, %d, %d, %d or %d", s,
            RT_DATA_TYPE_BUL, RT_DATA_TYPE_CHR, RT_DATA_TYPE_I64, RT_DATA_TYPE_F64, RT_DATA_TYPE_STR);
        free(s);
    }
    enum RT_DataType_t type = type_.data.i64;
    if (!fn_io_input_type_isvalid(type_.data.i64))
        rt_throw(
            "input: invalid type parameter\n"
            "  valid parameters are bul, chr, i64, f64 or str\n"
            "  respective values are %d, %d, %d, %d or %d",
            RT_DATA_TYPE_BUL, RT_DATA_TYPE_CHR, RT_DATA_TYPE_I64, RT_DATA_TYPE_F64, RT_DATA_TYPE_STR);
    RT_Data_print(prompt);
    switch (type) {
        case RT_DATA_TYPE_BUL: {
            bool val = false;
            fn_io_input_bul(&val);
            ret = RT_Data_bul(val);
            break;
        }
        case RT_DATA_TYPE_CHR: {
            char val = '\0';
            fn_io_input_chr(&val);
            ret = RT_Data_chr(val);
            break;
        }
        case RT_DATA_TYPE_I64: {
            int64_t val = 0;
            fn_io_input_i64(&val);
            ret = RT_Data_i64(val);
            break;
        }
        case RT_DATA_TYPE_F64: {
            double val= 0.0;
            fn_io_input_f64(&val);
            ret = RT_Data_f64(val);
            break;
        }
        case RT_DATA_TYPE_STR: {
            char *val = NULL;
            fn_io_input_str(&val);
            ret = RT_Data_str(RT_DataStr_init(val));
            free(val);
            break;
        }
        default: rt_throw(
            "input: invalid type parameter\n"
            "  valid parameters are bul, chr, i64, f64 or str\n"
            "  respective values are %d, %d, %d, %d or %d",
            RT_DATA_TYPE_BUL, RT_DATA_TYPE_CHR, RT_DATA_TYPE_I64, RT_DATA_TYPE_F64, RT_DATA_TYPE_STR);
            break;
    }
    return ret;
}

bool fn_io_input_type_isvalid(enum RT_DataType_t type)
{
    switch (type) {
        case RT_DATA_TYPE_BUL:
        case RT_DATA_TYPE_CHR:
        case RT_DATA_TYPE_I64:
        case RT_DATA_TYPE_F64:
        case RT_DATA_TYPE_STR:
            return true;
        default: return false;
    }
    return false;
}

void fn_io_input_bul(bool *val)
{
    if (!val) io_errndie("fn_io_input_bul:" ERR_MSG_NULLPTR);
    char *str;
    int len = fn_io_input_str(&str);
    if (!strncmp("1", str, len)) *val = true;
    else if (!strncmp("0", str, len)) *val = false;
    else if (!strncmp("true", str, len)) *val = true;
    else if (!strncmp("false", str, len)) *val = false;
    else rt_throw("input: invalid input for type bul: '%s'", str);
    free(str);
}

void fn_io_input_chr(char *val)
{
    if (!val) io_errndie("fn_io_input_chr:" ERR_MSG_NULLPTR);
    char *str;
    int len = fn_io_input_str(&str);
    if (len == 1) *val = str[0];
    else if (len == 0) *val = 0;
    else rt_throw("input: invalid input for type chr: '%s'", str);
    free(str);
}

void fn_io_input_i64(int64_t *val)
{
    if (!val) io_errndie("fn_io_input_i64:" ERR_MSG_NULLPTR);
    char *str;
    fn_io_input_str(&str);
    char *endptr;
    errno = 0;
    *val = (int64_t) strtoll(str, &endptr, 10);
    if (errno || *endptr != '\0')
        rt_throw("input: invalid input for type i64: '%s'", str);
    free(str);
}

void fn_io_input_f64(double *val)
{
    if (!val) io_errndie("fn_io_input_f64:" ERR_MSG_NULLPTR);
    char *str;
    fn_io_input_str(&str);
    char *endptr;
    errno = 0;
    *val = (double) strtod(str, &endptr);
    if (errno || *endptr != '\0')
        rt_throw("input: invalid input for type f64: '%s'", str);
    free(str);
}

int fn_io_input_str(char **val)
{
    if (!val) io_errndie("fn_io_input_str:" ERR_MSG_NULLPTR);
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
