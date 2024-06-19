#ifndef RT_FN_MODULE_DBG_H
#define RT_FN_MODULE_DBG_H

#include "runtime/data/Data.h"

rt_Data_t rt_fn_dbg_typename();
rt_Data_t rt_fn_dbg_rtsize();
rt_Data_t rt_fn_dbg_refcnt();
rt_Data_t rt_fn_dbg_id();
rt_Data_t rt_fn_dbg_callproc();
rt_Data_t rt_fn_dbg_filename();
rt_Data_t rt_fn_dbg_lineno();
rt_Data_t rt_fn_dbg_timenow();
rt_Data_t rt_fn_dbg_timenow_parameterized();

#endif
