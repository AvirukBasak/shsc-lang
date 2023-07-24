#ifndef RT_IO_H
#define RT_IO_H

#include <stdio.h>

void rt_throw(const char *fmt, ...) __attribute__((format(printf, 1, 2)));

#endif
