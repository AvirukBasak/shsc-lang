#ifndef RT_FN_MODULE_IO_H
#define RT_FN_MODULE_IO_H

#include "runtime/data/Data.h"

rt_Data_t rt_fn_io_print();
rt_Data_t rt_fn_io_println();
rt_Data_t rt_fn_io_input();
rt_Data_t rt_fn_io_fexists();
rt_Data_t rt_fn_io_fread();
rt_Data_t rt_fn_io_fwrite();
rt_Data_t rt_fn_io_fappend();
rt_Data_t rt_fn_io_libopen();
rt_Data_t rt_fn_io_libsym();

#endif
