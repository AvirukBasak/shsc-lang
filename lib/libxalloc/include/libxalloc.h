#ifndef __LIBXALLOC_H__
#define __LIBXALLOC_H__

#include <stddef.h>

/**
 * @brief Alloctes specified size
 * @param size Size of allocation
 * @return void* Pointer to new allocation
 * @return NULL If size is zero
 */
void *xmalloc(size_t size);

/**
 * @brief Alloctes specified size and initializes with 0
 * @param count Count of allocations
 * @param size Size of 1 allocation
 * @return void* Pointer to new allocation
 * @return NULL If count or size is zero
 */
void *xcalloc(size_t count, size_t size);

/**
 * @brief Reallocates an allocated bloc.
 * Resizes allocated block if possible, or copies data around.
 * @param ptr Pointer to allocated bloc or NULL
 * @param size Size of re-allocation
 * @return void* Pointer to new re-allocation
 * @return NULL If size is zero
 */
void *xrealloc(void *ptr, size_t size);

/**
 * @brief Marks pointer to block for cleanup
 * @param ptr Pointer to be freed
 * @return size_t Size actually freed using brk
 */
size_t xfree(void *ptr);

#endif
