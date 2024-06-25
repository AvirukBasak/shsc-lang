#ifndef RT_IO_H
#define RT_IO_H

void rt_throw_exitcode(int exitcode, const char *fmt, ...) __attribute__((format(printf, 2, 3)));
void rt_throw(const char *fmt, ...) __attribute__((format(printf, 1, 2)));

#endif
