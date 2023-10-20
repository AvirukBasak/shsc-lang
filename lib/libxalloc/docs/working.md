# Working
###### TODO
## About Allocator Initialization
The first call to `xmalloc` causes `libxalloc` to allocate `128 KB` of free memory.

This is an optimization done to reduce the number of `sbrk` calls.
Linux system calls take time, so by reserving a significant amount of memory early, we are saving time.

During this process, `128 KB` + `40 B` is allocated, `40 B` holding the data used to manage the `128 KB`.
