#ifndef RT_PLATFORM_H
#define RT_PLATFORM_H

#if defined(BSD) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__) || defined(__DragonFly__)
    #define rt_PLATFORM_BSD
#endif

#if defined(__sun) || defined(sun)
    #define rt_PLATFORM_SOLARIS
#endif

#if defined(__linux__)
    #define rt_PLATFORM_LINUX
#endif

#if defined(__unix__)
    #define rt_PLATFORM_UNIX
#endif

#if defined(_POSIX_VERSION)
    #define rt_PLATFORM_POSIX
#endif

#if defined(__ANDROID__)
    #define rt_PLATFORM_ANDROID
#endif

#if defined(TARGET_OS_MAC)
    #define rt_PLATFORM_MAC
#endif

#if defined(TARGET_OS_IPHONE)
    #define rt_PLATFORM_IOS
#endif

#if defined(__APPLE__) || defined(__MACH__)
    #define rt_PLATFORM_APPLE
#endif

#if defined(_WIN32) || defined(WIN32)
    #define rt_PLATFORM_WIN
#endif

#if defined(rt_PLATFORM_WIN)
    #define rt_PLATFORM "WIN"
#elif defined(rt_PLATFORM_MAC)
    #define rt_PLATFORM "MAC"
#elif defined(rt_PLATFORM_IOS)
    #define rt_PLATFORM "IOS"
#elif defined(rt_PLATFORM_APPLE)
    #define rt_PLATFORM "APPLE"
#elif defined(rt_PLATFORM_ANDROID)
    #define rt_PLATFORM "ANDROID"
#elif defined(rt_PLATFORM_BSD)
    #define rt_PLATFORM "BSD"
#elif defined(rt_PLATFORM_SOLARIS)
    #define rt_PLATFORM "SOLARIS"
#elif defined(rt_PLATFORM_LINUX)
    #define rt_PLATFORM "LINUX"
#elif defined(rt_PLATFORM_UNIX)
    #define rt_PLATFORM "UNIX"
#elif defined(rt_PLATFORM_POSIX)
    #define rt_PLATFORM "POSIX"
#endif

#endif
