#ifndef RT_INITLIBLOADER_C_H
#define RT_INITLIBLOADER_C_H

#include "runtime/data/Data.h"
#include "runtime/data/DataList.h"
#include "runtime/data/DataMap.h"
#include "runtime/data/DataStr.h"
#include "runtime/io.h"
#include "runtime/functions.h"
#include "runtime/operators.h"
#include "runtime/VarTable.h"
#include "runtime/util/loadfn.h"

#include "libshsc/include/shscinit.h"

void rt_util_libloader(void *handle) {

    shsc_init_apifn_data_t     dyn_init_apifn_data     = rt_util_loadfn(handle, "shsc_init_apifn_data");
    shsc_init_apifn_vartable_t dyn_init_apifn_vartable = rt_util_loadfn(handle, "shsc_init_apifn_vartable");
    shsc_init_apifn_list_t     dyn_init_apifn_list     = rt_util_loadfn(handle, "shsc_init_apifn_list");
    shsc_init_apifn_map_t      dyn_init_apifn_map      = rt_util_loadfn(handle, "shsc_init_apifn_map");
    shsc_init_apifn_str_t      dyn_init_apifn_str      = rt_util_loadfn(handle, "shsc_init_apifn_str");
    shsc_init_apifn_others_t   dyn_init_apifn_others   = rt_util_loadfn(handle, "shsc_init_apifn_others");
    shsc_init_apifn_ops_t      dyn_init_apifn_ops      = rt_util_loadfn(handle, "shsc_init_apifn_ops");

    dyn_init_apifn_data(
        rt_Data_bul,
        rt_Data_chr,
        rt_Data_i64,
        rt_Data_f64,
        rt_Data_str,
        rt_Data_list,
        rt_Data_map,
        rt_Data_any,
        rt_Data_null,
        rt_Data_clone,
        rt_Data_destroy,
        rt_Data_isnull,
        rt_Data_isnumeric,
        rt_Data_isequal,
        rt_Data_compare,
        rt_Data_tobool,
        rt_Data_tostr,
        rt_Data_cast,
        rt_Data_typename,
        rt_Data_assert_type,
        rt_Data_greater_type,
        rt_Data_print
    );

    dyn_init_apifn_vartable(
        rt_VarTable_modf
    );

    dyn_init_apifn_list(
        rt_DataList_init,
        rt_DataList_clone,
        rt_DataList_length,
        rt_DataList_destroy,
        rt_DataList_isequal,
        rt_DataList_compare,
        rt_DataList_append,
        rt_DataList_concat,
        rt_DataList_insert,
        rt_DataList_erase,
        rt_DataList_reverse,
        rt_DataList_find,
        rt_DataList_sublist,
        rt_DataList_join,
        rt_DataList_sort,
        rt_DataList_getref_errnull,
        rt_DataList_getref,
        rt_DataList_del_index,
        rt_DataList_del_val,
        rt_DataList_tostr
    );

    dyn_init_apifn_map(
        rt_DataMap_init,
        rt_DataMap_clone,
        rt_DataMap_length,
        rt_DataMap_destroy,
        rt_DataMap_insert,
        rt_DataMap_del,
        rt_DataMap_concat,
        rt_DataMap_getkey_copy,
        rt_DataMap_getref_errnull,
        rt_DataMap_getref,
        rt_DataMap_tostr
    );

    dyn_init_apifn_str(
        rt_DataStr_init,
        rt_DataStr_clone,
        rt_DataStr_length,
        rt_DataStr_destroy,
        rt_DataStr_toupper,
        rt_DataStr_tolower,
        rt_DataStr_append,
        rt_DataStr_concat,
        rt_DataStr_insert,
        rt_DataStr_insert_str,
        rt_DataStr_erase,
        rt_DataStr_reverse,
        rt_DataStr_isequal,
        rt_DataStr_compare,
        rt_DataStr_find,
        rt_DataStr_find_str,
        rt_DataStr_substr,
        rt_DataStr_split,
        rt_DataStr_split_str,
        rt_DataStr_sort,
        rt_DataStr_toi64,
        rt_DataStr_tof64,
        rt_DataStr_getref_errnull,
        rt_DataStr_getref,
        rt_DataStr_del_index,
        rt_DataStr_del_char,
        rt_DataStr_tostr
    );

    dyn_init_apifn_others(
        rt_throw,
        rt_fn_get_valid_args,
        rt_fn_call_handler,
        rt_fn_lambda_call_handler
    );

    dyn_init_apifn_ops(
        rt_op_ampersand,
        rt_op_arith_rshift,
        rt_op_assign,
        rt_op_asterix,
        rt_op_bang,
        rt_op_bitwise_lshift,
        rt_op_bitwise_rshift,
        rt_op_caret,
        rt_op_decrement,
        rt_op_dot,
        rt_op_exponent,
        rt_op_floor_divide,
        rt_op_fslash,
        rt_op_increment,
        rt_op_lbrace_angular,
        rt_op_logical_and,
        rt_op_logical_equal,
        rt_op_logical_greater_equal,
        rt_op_logical_lesser_equal,
        rt_op_logical_or,
        rt_op_logical_unequal,
        rt_op_minus,
        rt_op_percent,
        rt_op_pipe,
        rt_op_plus,
        rt_op_rbrace_angular,
        rt_op_tilde,
        rt_op_fnargs_indexing,
        rt_op_fncall,
        rt_op_indexing,
        rt_op_nop,
        rt_op_ternary_cond
    );
}

#else
    #warning "re-inclusion of src/runtime/util/libloader.c.h"
#endif
