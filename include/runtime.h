#ifndef RUNTIME_H
#define RUNTIME_H

#include "ast.h"
#include "lexer.h"
#include "runtime/data/Data.h"

#if defined(BSD) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__) || defined(__DragonFly__)
    #undef rt_PLATFORM
    #define rt_PLATFORM "BSD"
#elif defined(__sun) || defined(sun)
    #undef rt_PLATFORM
    #define rt_PLATFORM "SOLARIS"
#elif defined(__linux__)
    #undef rt_PLATFORM
    #define rt_PLATFORM "LINUX"
#elif defined(__unix__)
    #undef rt_PLATFORM
    #define rt_PLATFORM "UNIX"
#elif defined(_POSIX_VERSION)
    #undef rt_PLATFORM
    #define rt_PLATFORM "POSIX"
#endif

#if defined(__ANDROID__)
    #undef rt_PLATFORM
    #define rt_PLATFORM "ANDROID"
#endif

#if defined(TARGET_OS_MAC)
    #undef rt_PLATFORM
    #define rt_PLATFORM "MAC"
#elif defined(TARGET_OS_IPHONE)
    #undef rt_PLATFORM
    #define rt_PLATFORM "IOS"
#elif defined(__APPLE__) || defined(__MACH__)
    #undef rt_PLATFORM
    #define rt_PLATFORM "APPLE"
#endif

#if defined(_WIN32) || defined(_WIN64)
    #undef rt_PLATFORM
    #define rt_PLATFORM "WIN"
#endif

int rt_exec(int argc, char **argv);

#endif
