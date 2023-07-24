#ifndef RT_IO_C_H
#define RT_IO_C_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "runtime.h"
#include "runtime/io.h"
#include "errcodes.h"

void rt_throw(const char *fmt, ...)
{
    fprintf(stderr, "scsh: %s:%d: ", rt_currfile, rt_currline);
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
