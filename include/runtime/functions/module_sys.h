#ifndef RT_FN_MODULE_SYS_H
#define RT_FN_MODULE_SYS_H

#include "runtime/data/Data.h"

rt_Data_t rt_fn_sys_exit();
rt_Data_t rt_fn_sys_getenv();
rt_Data_t rt_fn_sys_platform();
rt_Data_t rt_fn_sys_system();

#endif
