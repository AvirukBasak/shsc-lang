#include <unistd.h>    // functions: brk, sbrk

#include "stdhead.h"
#include "io.h"
#include "xalloc.h"

/** bloc data list head allocated in global memory */
XALLOC_mhead_t _XALLOC_mhead;
XALLOC_mhead_t *XALLOC_mhead = NULL;

/** head of linked list */
struct XALLOC_mhead_t
{
    size_t blocc;
    XALLOC_mbloc_t *start;
    XALLOC_mbloc_t *end;
};

/** data of a memory bloc */
struct XALLOC_mbloc_t
{
    XALLOC_mbloc_t *prv;
    XALLOC_mbloc_t *nxt;
    ptr_t ptr;
    size_t size;
    bool isfree;
};

void __xalloc_alloc_init()
{
    if (XALLOC_mhead) return;
    XALLOC_mhead = &_XALLOC_mhead;
    XALLOC_mhead->blocc = 0;
    XALLOC_mhead->start = NULL;
    XALLOC_mhead->end = NULL;
    /* initial allocation to avoid excess sbrk calls
     * this block is large so if it can be split
     * xmalloc will attempt to reuse this block
     */
    void *ptr = xmalloc(INIT_ALLOCATION);
    if (ptr) XALLOC_mhead->start->isfree = true;
}

bool __xalloc_integrity_verify()
{
    if (!XALLOC_mhead)
        __xalloc_alloc_init();
    XALLOC_mbloc_t *p = XALLOC_mhead->start;
    while (p) {
        /* without buffer overflow memory corruption, the following is false:
         * p->nxt && p->nxt->prev != p
         * but if memory is corrupted, so will prev and next pointers and above
         * condition becomes true
         */
        if (p->nxt && p->nxt->prv != p) {
            __xalloc_print_str(2, "libxalloc: aborted: buffer at '");
            __xalloc_print_ptr(2, p->ptr);
            __xalloc_print_str(2, "' overflowed\n");
            abort();
        }
        p = p->nxt;
    }
    return true;
}

void __xalloc_mbloc_link(XALLOC_mbloc_t *node)
{
    NULLPTR_CHECK(node);
    // setting last node links
    if (XALLOC_mhead->end)
        XALLOC_mhead->end->nxt = node;
    // setting new node links
    node->prv = XALLOC_mhead->end;
    node->nxt = NULL;
    // updating meta data at head
    if (!XALLOC_mhead->start)
        XALLOC_mhead->start = node;
    XALLOC_mhead->end = node;
    XALLOC_mhead->blocc++;
}

XALLOC_mbloc_t *__xalloc_mbloc_new(size_t size)
{
    XALLOC_mbloc_t *node = sbrk(sizeof(XALLOC_mbloc_t) + size);
    NULLPTR_CHECK(node);
    ptr_t ptr = (ptr_t) (node + sizeof(XALLOC_mbloc_t));
    NULLPTR_CHECK(ptr);
    node->ptr = ptr;
    node->size = size;
    node->isfree = false;
    __xalloc_mbloc_link(node);
    return node;
}

/** searches for a specific bloc data based on its address */
XALLOC_mbloc_t *__xalloc_mbloc_find(ptr_t ptr)
{
    NULLPTR_CHECK(ptr);
    XALLOC_mbloc_t *p = XALLOC_mhead->start;
    while (p) {
        if (p->ptr == ptr) return p;
        p = p->nxt;
    }
    __xalloc_print_err("invalid pointer");
    return NULL;
}

XALLOC_mbloc_t *__xalloc_mbloc_split(XALLOC_mbloc_t *bloc, size_t req_sz)
{
    NULLPTR_CHECK(bloc);
    if (req_sz == bloc->size) return bloc;
    if (req_sz > bloc->size) __xalloc_print_err("post split size exceeds bloc size");
    size_t leftover_sz = bloc->size - req_sz - sizeof(XALLOC_mbloc_t);
    /* if remaining memory is less-equal double the size of a memory head,
     * then no changes are made
     */
    if (leftover_sz <= 2 * sizeof(XALLOC_mbloc_t)) return bloc;
    XALLOC_mbloc_t *leftover = (XALLOC_mbloc_t*) (bloc->ptr + req_sz);
    leftover->isfree = true;
    leftover->ptr = (ptr_t) (leftover + sizeof(XALLOC_mbloc_t));
    leftover->size = leftover_sz;
    leftover->prv = bloc;
    leftover->nxt = bloc->nxt;
    bloc->nxt = leftover;
    bloc->size = req_sz;
    return bloc;
}

XALLOC_mbloc_t *__xalloc_mbloc_merge(XALLOC_mbloc_t *bloc, size_t req_sz)
{
    NULLPTR_CHECK(bloc);
    if (req_sz == bloc->size) return bloc;
    if (bloc->size > req_sz) __xalloc_print_err("bloc size exceeds post merge size");
    size_t avlb_sz = bloc->size;
    XALLOC_mbloc_t *node = bloc->nxt;
    while (avlb_sz < req_sz && node && node->isfree) {
        avlb_sz += node->size + sizeof(XALLOC_mbloc_t);
        if (avlb_sz < req_sz) node = node->nxt;
        else break;
    }
    if (avlb_sz < req_sz)
        return NULL;
    if (avlb_sz > req_sz)
        node = __xalloc_mbloc_split(node, node->size - (avlb_sz - req_sz));
    if (node->nxt) node->nxt->prv = bloc;
    bloc->nxt = node->nxt;
    bloc->size = req_sz;
    return bloc;
}

/** alloctes specified size */
ptr_t xmalloc(size_t size)
{
    __xalloc_integrity_verify();
    if (!size) return NULL;
    // attempting to recycle old empty bloc
    if (XALLOC_mhead->start) {
        XALLOC_mbloc_t *reusable = XALLOC_mhead->start;
        while (reusable)
            if (reusable->isfree && reusable->size >= size) break;
            else reusable = reusable->nxt;
        if (reusable) {
            reusable->isfree = false;
            if (reusable->size == size) return reusable->ptr;
            return __xalloc_mbloc_split(reusable, size)->ptr;
        }
    }

    // fallback: allocating new bloc
    return __xalloc_mbloc_new(size)->ptr;
}

ptr_t xcalloc(size_t count, size_t size)
{
    __xalloc_integrity_verify();
    if (!count || !size) return NULL;
    ptr_t p = xmalloc(count * size);
    memset(p, 0, count * size);
    return p;
}

/** resizes allocated bloc if possible, or copies data around */
ptr_t xrealloc(ptr_t ptr, size_t size)
{
    __xalloc_integrity_verify();
    if (!size) return NULL;
    if (!ptr) return xmalloc(size);
    XALLOC_mbloc_t *bloc = __xalloc_mbloc_find(ptr);
    if (bloc->size == size) return ptr;

    // splitting blocs if new size is smaller
    if (size < bloc->size)
        return __xalloc_mbloc_split(bloc, size)->ptr;

    // if bloc is too large
    if (bloc->size > COPY_THRESHOLD) {
        // last bloc: update brk
        if (!bloc->nxt) {
            sbrk(size - bloc->size);
            bloc->size = size;
            return ptr;
        }
        // consecutive empty blocs
        else if (bloc->nxt->isfree) {
            XALLOC_mbloc_t *merged = __xalloc_mbloc_merge(bloc, size);
            if (merged) return merged->ptr;
        }
    }

    // fallback: new bloc allocation and copy data
    ptr_t newptr = xmalloc(size);
    memcpy(newptr, bloc->ptr, MIN(bloc->size, size));
    bloc->isfree = true;
    return newptr;
}

/** marks pointer to bloc for cleanup */
size_t xfree(ptr_t ptr)
{
    __xalloc_integrity_verify();

    // marking bloc of current ptr free
    if (ptr) {
        XALLOC_mbloc_t *tomark = __xalloc_mbloc_find(ptr);
        tomark->isfree = true;
    }

    // cleaning up free blocs from the end of list
    XALLOC_mbloc_t *bloc = XALLOC_mhead->end;
    size_t freed_size = 0;
    ptr_t brk_ptr = NULL;
    while (bloc && !bloc->nxt && bloc->isfree) {
        XALLOC_mbloc_t *tofree = bloc;
        freed_size += tofree->size;
        XALLOC_mhead->end = bloc = tofree->prv;
        if (tofree->prv) tofree->prv->nxt = NULL;
        else {
            XALLOC_mhead->start = NULL;
            XALLOC_mhead->end = NULL;
        }
        XALLOC_mhead->blocc--;
        brk_ptr = tofree;
    }
    if (brk_ptr) brk(brk_ptr);
    return freed_size;
}
