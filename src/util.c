#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <time.h>
#include <errno.h>

#include "globals.h"
#include "io.h"
#include "util.h"

#ifdef _WIN32
    #include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
    #include <sys/time.h>
#else
    #include <sys/time.h>
    #include <unistd.h>
#endif

int util_rand()
{
    srand(global_rng_state_seed);
    global_rng_state_seed ^= rand() ^ util_gettime_ms();
    return rand();
}

uint64_t util_gettime_ms()
{
#ifdef _WIN32
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    uint64_t time = (((uint64_t)ft.dwHighDateTime << 32) | ft.dwLowDateTime) / 10000;
    return time;
#else
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    uint64_t time_in_mill = (ts.tv_sec * 1000) + (ts.tv_nsec / 1000000);
    return time_in_mill;
#endif
}


void util_sleep_ms(int milliseconds)
{
#ifdef _WIN32
    Sleep(milliseconds);
#elif _POSIX_C_SOURCE >= 199309L
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
#else
    if (milliseconds >= 1000) {
        sleep(milliseconds / 1000);
    }
    usleep((milliseconds % 1000) * 1000);
#endif
}

int util_system(const char *command, char **outbuff, char **errbuff)
{
    const char *outfile = ".outfile.tmp",
               *errfile = ".errfile.tmp";

    const char *outredirect = " > ",
               *errredirect = " 2> ";
    char *cmdbuffer = malloc(16
         + strlen(command)
         + strlen(outredirect)
         + strlen(outfile)
         + strlen(errredirect)
         + strlen(errfile)
    );

    sprintf(cmdbuffer, "%s %s %s %s %s", command, outredirect, outfile, errredirect, errfile);
    int ret = system(cmdbuffer);
    free(cmdbuffer);

    if (*outbuff) {
        io_errndie("util_system: 'outbuff' should be NULL");
    }
    if (*errbuff) {
        io_errndie("util_system: 'errbuff' should be NULL");
    }

    FILE *out = fopen(outfile, "r");
    if (!out) {
        io_errnexit("Error reading stdout: %s", strerror(errno));
    }
    else {
        *outbuff = io_readfile(out);
    }
    fclose(out);

    FILE *err = fopen(errfile, "r");
    if (!err) {
        io_errnexit("Error reading stderr: %s", strerror(errno));
    }
    else {
        *errbuff = io_readfile(err);
    }
    fclose(err);

    if (*outbuff && (*outbuff)[0] == '\0') {
        free(*outbuff);
        *outbuff = NULL;
    }
    if (*errbuff && (*errbuff)[0] == '\0') {
        free(*errbuff);
        *errbuff = NULL;
    }

    if (*outbuff && (*outbuff)[strlen(*outbuff) - 1] == '\n') {
        (*outbuff)[strlen(*outbuff) - 1] = '\0';
    }
    if (*errbuff && (*errbuff)[strlen(*errbuff) - 1] == '\n') {
        (*errbuff)[strlen(*errbuff) - 1] = '\0';
    }

    remove(outfile);
    remove(errfile);
    return ret;
}

char *util_sjoin(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    size_t len = vsnprintf(NULL, 0, fmt, args);
    va_end(args);
    char *buffer = malloc(len + 1);
    if (!buffer) {
        io_errndie("util_sjoin: couldn't allocate memory");
    }
    va_start(args, fmt);
    vsnprintf(buffer, len + 1, fmt, args);
    va_end(args);
    return buffer;
}

char *util_dirname(const char *path)
{
    char *buffer = strdup(path);
    char *last_slash = strrchr(buffer, '/');
    if (last_slash) {
        *last_slash = '\0';
    }
    return buffer;
}
