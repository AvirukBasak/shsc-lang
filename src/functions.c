#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "errcodes.h"
#include "functions.h"
#include "io.h"
#include "runtime/io.h"
#include "runtime/data.h"
#include "runtime/data/string.h"
#include "runtime/data/list.h"
#include "runtime/data/map.h"
#include "runtime/vartable.h"

/*
- print
- input */

bool fn_isvalid_input_type(int64_t type);

void fn_input_bul(bool *val);
void fn_input_chr(char *val);
void fn_input_i64(int64_t *val);
void fn_input_f64(double *val);
int fn_input_str(char **val);

FN_FunctionDescriptor_t FN_FunctionsList_getfn(const char *fname)
{
    if (!strcmp(fname, "print"))    return FN_PRINT;
    if (!strcmp(fname, "input"))    return FN_INPUT;
    if (!strcmp(fname, "type"))     return FN_TYPE;
    if (!strcmp(fname, "typename")) return FN_TYPENAME;
    if (!strcmp(fname, "len"))      return FN_LEN;
    if (!strcmp(fname, "refcnt"))   return FN_REFCNT;
    if (!strcmp(fname, "tostr"))    return FN_TOSTR;
    if (!strcmp(fname, "isnull"))   return FN_ISNULL;
    return FN_UNDEFINED;
}

RT_Data_t FN_FunctionsList_call(FN_FunctionDescriptor_t fn)
{
    RT_Data_t ret = RT_Data_null();
    switch (fn) {
        case FN_PRINT: {
            int bytes = 0;
            for (int i = 0; i < RT_TMPVAR_CNT; ++i) {
                const RT_Data_t data = *RT_VarTable_getref_tmpvar(i);
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
            ret = RT_Data_i64(bytes);
            break;
        }
        case FN_INPUT: {
            const RT_Data_t prompt = *RT_VarTable_getref_tmpvar(0);
            const RT_Data_t type_ = *RT_VarTable_getref_tmpvar(1);
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
            if (!fn_isvalid_input_type(type_.data.i64))
                rt_throw(
                    "input: invalid type parameter\n"
                    "  valid parameters are bul, chr, i64, f64 or str\n"
                    "  respective values are %d, %d, %d, %d or %d",
                    RT_DATA_TYPE_BUL, RT_DATA_TYPE_CHR, RT_DATA_TYPE_I64, RT_DATA_TYPE_F64, RT_DATA_TYPE_STR);
            RT_Data_print(prompt);
            switch (type) {
                case RT_DATA_TYPE_BUL: {
                    bool val;
                    fn_input_bul(&val);
                    ret = RT_Data_bul(val);
                    break;
                }
                case RT_DATA_TYPE_CHR: {
                    char val;
                    fn_input_chr(&val);
                    ret = RT_Data_chr(val);
                    break;
                }
                case RT_DATA_TYPE_I64: {
                    int64_t val;
                    fn_input_i64(&val);
                    ret = RT_Data_i64(val);
                    break;
                }
                case RT_DATA_TYPE_F64: {
                    double val;
                    fn_input_f64(&val);
                    ret = RT_Data_f64(val);
                    break;
                }
                case RT_DATA_TYPE_STR: {
                    char *val = NULL;
                    fn_input_str(&val);
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
            break;
        }
        case FN_TYPE: {
            const RT_Data_t data = *RT_VarTable_getref_tmpvar(0);
            switch (data.type) {
                case RT_DATA_TYPE_BUL:
                    ret = RT_VarTable_typeid_bul;
                    break;
                case RT_DATA_TYPE_CHR:
                    ret = RT_VarTable_typeid_chr;
                    break;
                case RT_DATA_TYPE_I64:
                    ret = RT_VarTable_typeid_i64;
                    break;
                case RT_DATA_TYPE_F64:
                    ret = RT_VarTable_typeid_f64;
                    break;
                case RT_DATA_TYPE_STR:
                    ret = RT_VarTable_typeid_str;
                    break;
                case RT_DATA_TYPE_INTERP_STR:
                    ret = RT_VarTable_typeid_interp_str;
                    break;
                case RT_DATA_TYPE_LST:
                    ret = RT_VarTable_typeid_lst;
                    break;
                case RT_DATA_TYPE_MAP:
                    ret = RT_VarTable_typeid_map;
                    break;
                case RT_DATA_TYPE_ANY:
                    ret = RT_Data_isnull(data) ?
                        RT_VarTable_rsv_null : RT_VarTable_typeid_any;
                    break;
            }
            break;
        }
        case FN_TYPENAME: {
            const RT_Data_t data = *RT_VarTable_getref_tmpvar(0);
            const char *typename = RT_Data_typename(data);
            ret = RT_Data_str(RT_DataStr_init(typename));
            break;
        }
        case FN_LEN: {
            const RT_Data_t data = *RT_VarTable_getref_tmpvar(0);
            switch (data.type) {
                case RT_DATA_TYPE_STR:
                case RT_DATA_TYPE_INTERP_STR:
                    ret = RT_Data_i64(RT_DataStr_length(data.data.str));
                    break;
                case RT_DATA_TYPE_LST:
                    ret = RT_Data_i64(RT_DataList_length(data.data.lst));
                    break;
                case RT_DATA_TYPE_MAP:
                    ret = RT_Data_i64(RT_DataMap_length(data.data.mp));
                    break;
                default:
                    ret = RT_Data_i64(1);
                    break;
            }
            break;
        }
        case FN_REFCNT: {
            const RT_Data_t data = *RT_VarTable_getref_tmpvar(0);
            switch (data.type) {
                case RT_DATA_TYPE_STR:
                case RT_DATA_TYPE_INTERP_STR:
                    ret = RT_Data_i64(data.data.str->rc);
                    break;
                case RT_DATA_TYPE_LST:
                    ret = RT_Data_i64(data.data.lst->rc);
                    break;
                case RT_DATA_TYPE_MAP:
                    ret = RT_Data_i64(data.data.mp->rc);
                    break;
                default:
                    ret = RT_Data_i64(1);
                    break;
            }
            break;
        }
        case FN_TOSTR: {
            const RT_Data_t data = *RT_VarTable_getref_tmpvar(0);
            ret = RT_Data_str(RT_DataStr_init(RT_Data_tostr(data)));
            break;
        }
        case FN_ISNULL: {
            const RT_Data_t data = *RT_VarTable_getref_tmpvar(0);
            ret = RT_Data_bul(RT_Data_isnull(data));
            break;
        }
        case FN_UNDEFINED:
            io_errndie("FN_FunctionsList_call: undefined procedure for desc: '%d'", fn);
            break;
    }
    return ret;
}

bool fn_isvalid_input_type(int64_t type)
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

void fn_input_bul(bool *val)
{
    if (!val) io_errndie("fn_input_bul:" ERR_MSG_NULLPTR);
    char *str;
    int len = fn_input_str(&str);
    if (!strncmp("1", str, len)) *val = true;
    else if (!strncmp("0", str, len)) *val = false;
    else if (!strncmp("true", str, len)) *val = true;
    else if (!strncmp("false", str, len)) *val = false;
    else rt_throw("input: invalid input for type bul: '%s'", str);
    free(str);
}

void fn_input_chr(char *val)
{
    if (!val) io_errndie("fn_input_chr:" ERR_MSG_NULLPTR);
    char *str;
    int len = fn_input_str(&str);
    if (len == 1) *val = str[0];
    else if (len == 0) *val = 0;
    else rt_throw("input: invalid input for type chr: '%s'", str);
    free(str);
}

void fn_input_i64(int64_t *val)
{
    if (!val) io_errndie("fn_input_i64:" ERR_MSG_NULLPTR);
    char *str;
    fn_input_str(&str);
    char *endptr;
    errno = 0;
    *val = (int64_t) strtoll(str, &endptr, 10);
    if (errno || *endptr != '\0')
        rt_throw("input: invalid input for type i64: '%s'", str);
    free(str);
}

void fn_input_f64(double *val)
{
    if (!val) io_errndie("fn_input_f64:" ERR_MSG_NULLPTR);
    char *str;
    fn_input_str(&str);
    char *endptr;
    errno = 0;
    *val = (double) strtod(str, &endptr);
    if (errno || *endptr != '\0')
        rt_throw("input: invalid input for type f64: '%s'", str);
    free(str);
}

int fn_input_str(char **val)
{
    if (!val) io_errndie("fn_input_str:" ERR_MSG_NULLPTR);
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
