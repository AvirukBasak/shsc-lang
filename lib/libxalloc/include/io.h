#include "stdhead.h"

void __xalloc_print_str(int fd, const char *s);
void __xalloc_print_ui64(int fd, const ui64_t n);
void __xalloc_print_i64(int fd, const i64_t n);
void __xalloc_print_ptr(int fd, const ptr_t p);
void __xalloc_print_err(const char *s);
