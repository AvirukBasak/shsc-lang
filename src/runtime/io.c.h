#ifndef RT_IO_C_H
#define RT_IO_C_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "errcodes.h"
#include "runtime.h"
#include "runtime/io.h"

void rt_throw(const char *fmt, ...)
{
    fprintf(stderr, "shsc: %s:%d: ", rt_currfile, rt_currline);
    fflush(stderr);
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fflush(stderr);
    fprintf(stderr, "\n");
    exit(ERR_RUNTIME);
}

#else
    #warning re-inclusion of module 'runtime/io.c.h'
#endif
