#ifndef RT_EVAL_COMMASEPLIST_C_H
#define RT_EVAL_COMMASEPLIST_C_H

#include "ast.h"
#include "ast/api.h"
#include "runtime/data/DataList.h"
#include "runtime/eval.h"
#include "runtime/VarTable.h"

void rt_eval_CommaSepList(const ast_CommaSepList_t *comma_list)
{
    /* This is commented out so that empty lists which are
       represented using NULL are also created instead of
       just returning a null data
    if (!comma_list) {
        rt_VarTable_acc_setval(rt_Data_null());
        return;
    } */
    const ast_CommaSepList_t *ptr = comma_list;
    rt_DataList_t *new_list = rt_DataList_init();
    while (ptr) {
        rt_eval_Expression(ptr->expression);
        rt_DataList_append(new_list, *RT_VTABLE_ACC);
        ptr = ptr->comma_list;
    }
    rt_VarTable_acc_setval(
        rt_Data_list(new_list));
}

#else
    #warning re-inclusion of module 'runtime/eval/commaseplist.c.h'
#endif
