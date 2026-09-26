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

void *__util_memrchr(const void *s, int c, size_t n)
{
    const unsigned char *sp = (const unsigned char *)s + n;
    while (n--) {
        if (*--sp == (unsigned char)c)
            return (void *)sp;
    }
    return NULL;
}

/* dirname - return directory part of PATH.
   Copyright (C) 1996-2024 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.
   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.
   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */
char *__util_dirname(char *path)
{
  static const char dot[] = ".";
  char *last_slash;
  /* Find last '/'.  */
  last_slash = path != NULL ? strrchr (path, '/') : NULL;
  if (last_slash != NULL && last_slash != path && last_slash[1] == '\0')
    {
      /* Determine whether all remaining characters are slashes.  */
      char *runp;
      for (runp = last_slash; runp != path; --runp)
	if (runp[-1] != '/')
	  break;
      /* The '/' is the last character, we have to look further.  */
      if (runp != path)
	last_slash = __util_memrchr (path, '/', runp - path);
    }
  if (last_slash != NULL)
    {
      /* Determine whether all remaining characters are slashes.  */
      char *runp;
      for (runp = last_slash; runp != path; --runp)
	if (runp[-1] != '/')
	  break;
      /* Terminate the path.  */
      if (runp == path)
	{
	  /* The last slash is the first character in the string.  We have to
	     return "/".  As a special case we have to return "//" if there
	     are exactly two slashes at the beginning of the string.  See
	     XBD 4.10 Path Name Resolution for more information.  */
	  if (last_slash == path + 1)
	    ++last_slash;
	  else
	    last_slash = path + 1;
	}
      else
	last_slash = runp;
      last_slash[0] = '\0';
    }
  else
    /* This assignment is ill-designed but the XPG specs require to
       return a string containing "." in any case no directory part is
       found and so a static and constant string is required.  */
    path = (char *) dot;
  return path;
}


char *util_dirname(const char *path)
{
    char *buffer = strdup(path); // free target
    char *ptr = buffer;          // working memory

#ifdef _WIN32
    // windows specific pre-processing
    char driveletter = '\0';
    if (
        (('A' <= ptr[0] && ptr[0] <= 'Z') 
            || ('a' <= ptr[0] && ptr[0] <= 'z'))
        && ptr[1] == ':'
        && (ptr[2] == '/' || ptr[2] == '\\')
    ) {
        // ignore drive letter
        driveletter = ptr[0];
        ptr = &ptr[2];
    }
    // replace all '\' with '/' before calling dirname
    bool has_backslash = false;
    for (char *p = ptr; *p; ++p) {
        if (*p == '\\') {
            has_backslash = true;
            *p = '/';
        }
    }
#endif

    {
        char *tmp = strdup(__util_dirname(ptr));
        free(buffer);
        ptr = buffer = tmp;
    }

#ifdef _WIN32
    // windows specific post-processing
    if (has_backslash) {
        for (char *p = ptr; *p; ++p) {
            if (*p == '/') {
                *p = '\\';
            }
        }
    }
    if (driveletter != '\0') {
        const char *slash = "";
        if (ptr[0] != '/' && ptr[0] != '\\') {
            if (has_backslash) slash = "\\";
            else slash = "/";
        }
        char *tmp = util_sjoin("%c:%s%s", driveletter, slash, ptr);
        free(buffer);
        ptr = buffer = tmp;
    }
#endif

    return ptr;
}
