#ifndef RT_DATA_H
#define RT_DATA_H

#include <stdbool.h>
#include <stdint.h>

#include "ast.h"

typedef struct rt_Data_t rt_Data_t;
typedef struct rt_DataStr_t rt_DataStr_t;
typedef struct rt_DataList_t rt_DataList_t;
typedef struct rt_DataMap_t rt_DataMap_t;
typedef struct rt_DataProc_t rt_DataProc_t;

/* based on the mapping of datatype IDs provided
   by the Shsc IR Spec
   https://github.com/AvirukBasak/shsc-runtime/docs/ShscIrSpec.md */
enum rt_DataType_t {
    rt_DATA_TYPE_BUL = 0,        /* boolean        : 1 B */
    rt_DATA_TYPE_CHR = 1,        /* char           : 1 B */
    rt_DATA_TYPE_I64 = 2,        /* int64_t        : 8 B */
    rt_DATA_TYPE_F64 = 3,        /* double         : 8 B */
    rt_DATA_TYPE_STR = 4,        /* char*          : variable  */
    rt_DATA_TYPE_INTERP_STR = 5, /* parsable char* : variable  */
    rt_DATA_TYPE_LST = 6,        /* list           : variable  */
    rt_DATA_TYPE_ANY = 7,        /* void*          : undefined */
    rt_DATA_TYPE_MAP = 8,        /* hash map       : variable  */
    rt_DATA_TYPE_PROC = 9,       /* procedure      : ??  */
};

struct rt_DataProc_t {
    const ast_Identifier_t *module_name;
    const ast_Identifier_t *proc_name;
    const rt_Data_t *context;
};

struct rt_Data_t {
    union {
        bool bul;
        char chr;
        int64_t i64;
        double f64;
        rt_DataStr_t *str;
        rt_DataList_t *lst;
        rt_DataMap_t *mp;
        rt_DataProc_t proc;
        void *any;
    } data;
    bool is_const;
    bool is_weak;
    enum rt_DataType_t type;
};

rt_Data_t rt_Data_bul(bool val);
rt_Data_t rt_Data_chr(char val);
rt_Data_t rt_Data_i64(int64_t val);
rt_Data_t rt_Data_f64(double val);
rt_Data_t rt_Data_str(rt_DataStr_t *str);
rt_Data_t rt_Data_interp_str(const char *str);
rt_Data_t rt_Data_list(rt_DataList_t *lst);
rt_Data_t rt_Data_map(rt_DataMap_t *mp);
rt_Data_t rt_Data_proc(
    const ast_Identifier_t *module_name,
    const ast_Identifier_t *proc_name
);
rt_Data_t rt_Data_any(void *ptr);
rt_Data_t rt_Data_null(void);

void rt_Data_increfc(rt_Data_t *var);
void rt_Data_decrefc(rt_Data_t *var);

void rt_Data_destroy_circular(rt_Data_t *var, bool flag);
void rt_Data_destroy(rt_Data_t *var);

bool rt_Data_isnull(const rt_Data_t var);
bool rt_Data_isnumeric(const rt_Data_t var);
bool rt_Data_isequal(const rt_Data_t var1, const rt_Data_t var2);
int64_t rt_Data_compare(const rt_Data_t var1, const rt_Data_t var2);
char *rt_Data_interp_str_parse(const char *str);
bool rt_Data_tobool(const rt_Data_t var);
char *rt_Data_tostr(const rt_Data_t var);
const char *rt_Data_typename(const rt_Data_t var);
bool rt_Data_assert_type(
    const rt_Data_t var,
    enum rt_DataType_t expected_type,
    const char *for_varname
);
int rt_Data_print(const rt_Data_t var);

#endif
