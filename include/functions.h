#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "runtime/data.h"

typedef enum {
    FN_PRINT,
    FN_INPUT,
    FN_TYPE,
    FN_LEN,
    FN_REFCNT,
    FN_UNDEFINED,
} FN_FunctionDescriptor_t;

FN_FunctionDescriptor_t FN_FunctionsList_getfn(const char *fname);
RT_Data_t FN_FunctionsList_call(FN_FunctionDescriptor_t fn);

#endif
