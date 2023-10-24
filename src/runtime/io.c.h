#ifndef RT_IO_C_H
#define RT_IO_C_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "ast/api.h"
#include "errcodes.h"
#include "runtime.h"
#include "runtime/io.h"
#include "runtime/VarTable.h"

#define RT_THROW_PRINT_FN      "%s:%s: "
#define RT_THROW_DONT_PRINT_FN ""

void rt_throw(const char *fmt, ...)
{
    fprintf(stderr, "shsc: " RT_THROW_DONT_PRINT_FN "%s:%d: ",
        /* rt_modulename_get()->identifier_name, */
            /* rt_procname_get()->identifier_name, */
                rt_currfile, rt_currline);
    fflush(stderr);
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fflush(stderr);
    fprintf(stderr, "\n");

    /* print stack trace */
    while (rt_VarTable_proc_top()) {
        fprintf(stderr, "    at " RT_THROW_PRINT_FN "(%s:%d)\n",
            rt_VarTable_proc_top()->modulename->identifier_name,
            rt_VarTable_proc_top()->procname->identifier_name,
            rt_VarTable_proc_top()->filepath,
            rt_VarTable_proc_top()->current_line
        );
        rt_VarTable_pop_proc();
    }
    fflush(stderr);

#ifdef DEBUG
    abort();
#else
    exit(ERR_RUNTIME);
#endif
}

#else
    #warning re-inclusion of module 'runtime/io.c.h'
#endif
