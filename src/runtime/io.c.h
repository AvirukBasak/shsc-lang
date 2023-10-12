#ifndef RT_IO_C_H
#define RT_IO_C_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "errcodes.h"
#include "runtime.h"
#include "runtime/io.h"

#define RT_THROW_PRINT_FN      "%s::%s: "
#define RT_THROW_DONT_PRINT_FN ""

void rt_throw(const char *fmt, ...)
{
    fprintf(stderr, "shsc: " RT_THROW_DONT_PRINT_FN "%s:%d: ",
        /* RT_modulename_get()->identifier_name, */
            /* RT_procname_get()->identifier_name, */
                rt_currfile, rt_currline);
    fflush(stderr);
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fflush(stderr);
    fprintf(stderr, "\n");
#ifdef DEBUG
    abort();
#else
    exit(ERR_RUNTIME);
#endif
}

#else
    #warning re-inclusion of module 'runtime/io.c.h'
#endif
