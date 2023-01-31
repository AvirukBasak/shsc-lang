#include "helperfn.h"

void __avl_traverse(avlnode_t *node, void (*callback)(avlnode_t*))
{
    if (!callback) abort();
    if (!node) return;
    else {
        __avl_traverse(node->lc, callback);
        callback(node);
        __avl_traverse(node->rc, callback);
    }
}
