# X Alloc
Custom heap memory allocator using `brk` and `sbrk`.

## Usage
- Build with `make`.
- Copy library from `target/`.
- Copy header file from `target/`.
- Visit [test.c](tests/test.c) for example use.
- Follow the api below.

## API
`libxalloc` provides an api similar to `*alloc` from `libc`.

It includes the following functions:
- [`void *xmalloc(size_t)`](#xmalloc)
- [`void *xcalloc(size_t, size_t)`](#xcalloc)
- [`void *xrealloc(void *, size_t)`](#xrealloc)
- [`size_t xfree(void *)`](#xfree)

#### xmalloc
- param: allocation size
- return: non-NULL pointer to allocation
- return: `NULL` if size is 0

Note that `xmalloc` never returns `NULL` unless size of allocation is `0`.

In case an allocation fails, `xmalloc` will directly call `abort`.

Therefore it's unnecessary to check for a `NULL` pointer when using `xmalloc`.

This trend is followed by all the allocator functions as all of them use `xmalloc` internally.

#### xcalloc
- param: allocation count
- param: size per count
- return: non-NULL pointer to allocation
- return: `NULL` if size is 0

Internally, `xcalloc` calls `xmalloc` and `memsets` the entire bloc with `0`.

#### xrealloc
- param: pervious pointer
- param: new allocation size
- return: non-NULL pointer to allocation
- return: `NULL` if size is 0

#### xfree
- param: pointer
- return: total bytes released to OS

There are a few things to be noted when it comes to `xfree`.

If pointer is `NULL`, `xfree` returns `0` and does nothing else.

If pointer is not derived from `libxalloc` or was previously freed, `xfree` will call `abort` with error message `invalid pointer`.

#### Insight into xfree
Suppose the argument to `xfree` is a pointer `ptr`, and suppose `ptr` points to a valid memory bloc.
The return value of `xfree` isn't the size of that memory bloc.

Instead, `xfree` returns the amount of bytes of memory that `libxalloc` was able to return to the OS during that `xfree` call.

For allocation and optimization purposes, `xfree` may only mark our memory bloc as free and then reserve it for recycling.
This is because allocation of new memory in the heap is costly (and slow due to system calls involved).
By reserving and recycling, we avoid that.

If such reserved memory is released back to the OS during `xfree` call then the total of all memory released is returned.

## Warning
- Overflowing buffer allocated by `libxalloc` may cause an `abort` (see [Test Fail](tests/README.md#test-fail-results)).
- Segmentation faults during execution can be attributed to `libc`.
- `libc` will break functionality of library.

## How libc affects libxalloc
`libc` uses `brk` and `sbrk` calls to allocate memory, and `libxalloc` also uses the same.

As a result, the two libraries will end up corrupting the memory tracking data structures of each other.

This will result in undefined behaviour.

To know how `libxalloc` works, visit [working.md](docs/working.md).

## Test results
- Visit [tests](tests/README.md) for details.
- Visit [test-no-malloc](tests/README.md#test-no-malloc-results) for insight into how the allocator works.
