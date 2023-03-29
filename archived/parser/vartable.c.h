#ifndef PARSE_VARTABLE_C_H
#define PARSE_VARTABLE_C_H

#include <stdbool.h>
#include <stdint.h>

typedef struct VarEntry VarEntry;
typedef enum VarTypes VarTypes;
typedef union VarData VarData;

enum VarTypes {
    VT_CHR,
    VT_I64,
    VT_F64,
    VT_STR,
    VT_ANY,
};

union VarData {
    char chr;
    int64_t i64;
    double f64;
    char *str;
    void *any;
};

struct VarEntry {
  const char *const idf;
  VarTypes type;
  VarData data;
};

VarEntry *vartable_newdata(VarTypes vt, VarData data);

void vartable_insert(const char *idf, VarEntry *ve);
bool vartable_clone(const char *dest, const char *src);

#endif
