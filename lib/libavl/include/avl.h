#ifndef __AVL_H__
#define __AVL_H__

#include "stdhead.h"

typedef struct AVL AVL;
typedef struct avlnode_t avlnode_t;

struct AVL {
    avlnode_t *root;
};

struct avlnode_t {
    ptr_t      data;  // data
    avlnode_t *pr;    // parent
    avlnode_t *lc;    // left child
    avlnode_t *rc;    // right child
    int        bf;    // node balance factor
};

typedef int (*avl_compare_t)    (ptr_t, ptr_t);
typedef int (*avl_keycompare_t) (ptr_t, ptr_t);

// helper functions
void __avl_calcbf     (avlnode_t *node);
int __avl_height      (avlnode_t *node);
void __avl_balance    (AVL *head, avlnode_t *node);
void __avl_ll_rot     (AVL *head, avlnode_t *node);
void __avl_lr_rot     (AVL *head, avlnode_t *node);
void __avl_rr_rot     (AVL *head, avlnode_t *node);
void __avl_rl_rot     (AVL *head, avlnode_t *node);

bool avl_attach       (AVL *head, avlnode_t *node, avl_compare_t callback);
avlnode_t *avl_detach (AVL *head, ptr_t key, avl_keycompare_t callback);
ptr_t avl_search      (AVL *head, ptr_t key, avl_keycompare_t callback);

void avl_traverse     (AVL *head, void (*callback)(avlnode_t*));

#endif
