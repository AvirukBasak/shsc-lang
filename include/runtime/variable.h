#ifndef RT_VARIABLE_H
#define RT_VARIABLE_H

#include <stdbool.h>
#include <inttypes.h>

typedef struct RT_Variable_t RT_Variable_t;
typedef struct RT_VarList_t RT_VarList_t;

/* based on the mapping of datatype IDs provided
   by the Scsh IR Spec
   https://github.com/AvirukBasak/scsh-runtime/docs/ScshIrSpec.md */
enum RT_DataType_t {
    RT_DATA_TYPE_BUL = 0,        /* boolean        : 1 B */
    RT_DATA_TYPE_CHR = 1,        /* char           : 1 B */
    RT_DATA_TYPE_I64 = 2,        /* int64_t        : 8 B */
    RT_DATA_TYPE_F64 = 3,        /* double         : 8 B */
    RT_DATA_TYPE_STR = 4,        /* char*          : variable  */
    RT_DATA_TYPE_INTERP_STR = 5, /* parsable char* : variable  */
    RT_DATA_TYPE_LST = 6,        /* list           : variable  */
    RT_DATA_TYPE_ANY = 7,        /* void*          : undefined */
};

struct RT_VarList_t {
    RT_Variable_t *var;
    int64_t length;
    size_t capacity;
};

struct RT_Variable_t {
    union {
        bool bul;
        char chr;
        int64_t i64;
        double f64;
        char *str;
        RT_VarList_t *lst;
        void *any;
    } data;
    enum RT_DataType_t type;
};

RT_Variable_t rt_variable_bul(bool val);
RT_Variable_t rt_variable_chr(char val);
RT_Variable_t rt_variable_i64(int64_t val);
RT_Variable_t rt_variable_f64(double val);
RT_Variable_t rt_variable_str(char *str);
RT_Variable_t rt_variable_interp_str(char *str);
RT_Variable_t rt_variable_list(RT_VarList_t *lst);
RT_Variable_t rt_variable_any(void *ptr);
void rt_variable_destroy(RT_Variable_t var);

char *rt_varable_parse_interp_str(char *str);
char *rt_variable_tostr(RT_Variable_t var);
void rt_variable_print_list(RT_VarList_t *lst);
void rt_variable_print(RT_Variable_t var);

RT_VarList_t *rt_varlist_init();
void rt_varlist_destroy(RT_VarList_t **ptr);
void rt_varlist_append(RT_VarList_t *lst, RT_Variable_t var);
void rt_varlist_set(RT_VarList_t *lst, int64_t idx, RT_Variable_t var);
RT_Variable_t rt_varlist_get(RT_VarList_t *lst, int64_t idx);
void rt_varlist_del_index(RT_VarList_t *lst, int64_t idx);
void rt_varlist_del_val(RT_VarList_t *lst, RT_Variable_t var);

#endif
