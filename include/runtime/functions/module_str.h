#ifndef RT_FN_MODULE_STR_H
#define RT_FN_MODULE_STR_H

#include "runtime/data/Data.h"

rt_Data_t rt_fn_str_equals();
rt_Data_t rt_fn_str_compare();
rt_Data_t rt_fn_str_tolower();
rt_Data_t rt_fn_str_toupper();
rt_Data_t rt_fn_str_append();
rt_Data_t rt_fn_str_insert();
rt_Data_t rt_fn_str_erase();
rt_Data_t rt_fn_str_concat();
rt_Data_t rt_fn_str_reverse();
rt_Data_t rt_fn_str_substr();
rt_Data_t rt_fn_str_find();
rt_Data_t rt_fn_str_split();
rt_Data_t rt_fn_str_toi64();
rt_Data_t rt_fn_str_tof64();
rt_Data_t rt_fn_str_sort();

#endif
