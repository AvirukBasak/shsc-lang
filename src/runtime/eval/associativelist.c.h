#ifndef RT_EVAL_ASSOCIATIVELIST_C_H
#define RT_EVAL_ASSOCIATIVELIST_C_H

#include "ast.h"
#include "ast/api.h"
#include "runtime/data/Data.h"
#include "runtime/data/DataMap.h"
#include "runtime/eval.h"
#include "runtime/VarTable.h"

void rt_eval_AssociativeList(const ast_AssociativeList_t *assoc_list)
{
    /* This is commented out so that empty lists which are
       represented using NULL are also created instead of
       just returning a null data
    if (!assoc_list) {
        rt_VarTable_acc_setval(rt_Data_null());
        return;
    } */
    const ast_AssociativeList_t *ptr = assoc_list;
    rt_DataMap_t *new_map = rt_DataMap_init();
    while (ptr) {
        rt_eval_Literal(ptr->key);
        char *key_cstr = rt_Data_tostr(*RT_VTABLE_ACC);
        /* note that the rt_Data_t string returned above is not
           manually cleaned coz it's reference counted l, and is
           freed when accumulator value is changed below */
        rt_eval_Expression(ptr->value);
        rt_DataMap_insert(new_map, key_cstr, *RT_VTABLE_ACC);
        ptr = ptr->assoc_list;
        free(key_cstr);
    }
    rt_VarTable_acc_setval(
        rt_Data_map(new_map));
}

#else
    #warning re-inclusion of module 'runtime/eval/associativelist.c.h'
#endif
