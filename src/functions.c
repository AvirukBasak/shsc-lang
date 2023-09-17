#include <string.h>

#include "functions.h"
#include "runtime/data.h"
#include "runtime/io.h"
#include "runtime/vartable.h"

/*
- print
- input */

FN_FunctionDescriptor_t FN_FunctionsList_getfn(const char *fname)
{
    if (!strcmp(fname, "print")) return FN_PRINT;
    if (!strcmp(fname, "input")) return FN_INPUT;
    return FN_UNDEFINED;
}

RT_Data_t FN_FunctionsList_call(FN_FunctionDescriptor_t fn)
{
    RT_Data_t ret = RT_Data_null();
    switch (fn) {
        case FN_PRINT:{
            int bytes = 0;
            for (int i = 0; i < RT_TMPVAR_CNT; ++i) {
                const char var[4] = { ((i % 100) / 10) + '0', (i % 10) + '0', '\0' };
                bytes += RT_Data_print(*RT_VarTable_getref(var));
            }
            ret = RT_Data_i64(bytes);
            break;
        }
        case FN_INPUT:
        case FN_UNDEFINED:
            rt_throw("undefined procedure");
            break;
    }
    return ret;
}
