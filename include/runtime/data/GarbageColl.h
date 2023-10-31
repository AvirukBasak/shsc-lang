#ifndef RT_GARBAGE_COLL_H
#define RT_GARBAGE_COLL_H

#include "runtime/data/Data.h"

/** check if rc of passed object is contributed to only by cyclic references */
bool rt_data_GC_has_only_cyclic_refcnt(const rt_Data_t var);

/** count total number of cyclic references back to the passed data object */
int64_t rt_data_GC_cyclic_count(const rt_Data_t var);

#endif
