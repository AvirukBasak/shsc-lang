#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdlib.h>
#define VERSION "0.3 Alpha"
#define GLOBAL_BYTES_BUFFER_LEN (128)

extern const char *global_currfile;

void *shsc_malloc(size_t size);
void *shsc_calloc(size_t count, size_t size);
void *shsc_realloc(void *ptr, size_t size);
size_t shsc_free(void *ptr);

#endif
