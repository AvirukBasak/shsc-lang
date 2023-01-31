#include "stdhead.h"
#include "helperfn.h"
#include "avl.h"

/**
 * @brief Attaches a node to the tree
 * @param head AVL head
 * @param node Node to be attached
 * @param callback int (*)(ptr_t, ptr_t)
 * @return bool true on attach success
 */
bool avl_attach(AVL *head, avlnode_t *node, avl_compare_t callback)
{
    if (!callback) abort();
    if (!head || !node) return NULL;
    if (!head->root) {
        head->root = node;
        node->pr = NULL;
        goto avl_attach_node_init;
    }
    avlnode_t *p = head->root;
    avlnode_t *trail = NULL;
    while (p) {
        /* if key < data, -ve or decrease data, i.e. go to left subtree
         * if key > data, +ve or increase data, i.e. go to right subtree
         * if equal 0, match found
         */
        if (callback(node->data, p->data) < 0) {
            trail = p;
            p = p->lc;
        } else if (callback(node->data, p->data) > 0) {
            trail = p;
            p = p->rc;
        } else return false;
    }
    if (callback(node->data, trail->data) < 0)
        trail->lc = node;
    else
        trail->rc = node;
    node->pr = trail;
avl_attach_node_init:
    node->lc = NULL;
    node->rc = NULL;
    node->bf = 0;
    __avl_balance(head, node->pr);
    return true;
}

/**
 * @brief Detaches a node from the tree
 * @param head AVL head
 * @param key Pointer to key which is present in the data member of a node
 * @param callback int (*)(ptr_t, ptr_t)
 * @return avlnode_t* Pointer to node to be freed
 */
avlnode_t *avl_detach(AVL *head, ptr_t key, avl_keycompare_t callback)
{
    if (!callback) abort();
    if (!head || !head->root || !key) return NULL;
    // if at root
    avlnode_t *root = head->root;
    if (!callback(key, root->data) && !root->lc && !root->rc) {
        head->root = NULL;
        return root;
    }
    // find key
    avlnode_t *p = root;
    while (p)
        /* if key < data, -ve or decrease data, i.e. go to left subtree
         * if key > data, +ve or increase data, i.e. go to right subtree
         * if equal 0, match found
         */
        if (callback(key, p->data) < 0) p = p->lc;
        else if (callback(key, p->data) > 0) p = p->rc;
        else break;
    // key not found
    if (!p) return NULL;
    // if p has rc, attempt going to inorder successor
    if (p->rc) {
        avlnode_t *tmp = p->rc;
        // loop down to inorder successor
        while (tmp->lc)
            tmp = tmp->lc;
        // swap data b/w inord. successor and to-be-del node
        void *tmpdata = p->data;
        p->data = tmp->data;
        tmp->data = tmpdata;
        // other pointer manup.
        if (tmp->pr == p) p->rc = tmp->rc;
        else tmp->pr->lc = tmp->rc;
        // disconn. to-be-del node
        tmp->lc = tmp->rc = NULL;
        __avl_balance(head, tmp->pr);
        tmp->pr = NULL;
        return tmp;
    } else if (p->pr) {
        // if p has no inorder successor, remove it
        avlnode_t *tmp = p;
        // parent of p takes custody of p's child
        if (p->pr->lc == p)
            p->pr->lc = p->lc;
        else
            p->pr->rc = p->lc;
        // disconn. to-be-del node
        tmp->lc = NULL;
        __avl_balance(head, tmp->pr);
        tmp->pr = NULL;
        return tmp;
    } else {
        // if p has no parent i.e. root and p has no inord. successor
        avlnode_t *tmp = p;
        // lc of p promoted to root
        head->root = p->lc;
        // disconn. to-be-del node
        tmp->lc = NULL;
        return tmp;
    }
    return NULL;
}

/**
 * @brief Searches for a key among the tree nodes
 * @param head AVL head
 * @param key Pointer to key which is to be searched
 * @param callback int (*)(ptr_t, ptr_t)
 * @return ptr_t Pointer to data containing key
 */
ptr_t avl_search(AVL *head, ptr_t key, avl_keycompare_t callback)
{
    if (!callback) abort();
    if (!head || !head->root || !key) return NULL;
    avlnode_t *p = head->root;
    while (p)
        /* if key < data, -ve or decrease data, i.e. go to left subtree
         * if key > data, +ve or increase data, i.e. go to right subtree
         * if equal 0, match found
         */
        if (callback(key, p->data) < 0) p = p->lc;
        else if (callback(key, p->data) > 0) p = p->rc;
        else return p->data;
    return NULL;
}

void avl_traverse(AVL *head, void (*callback)(avlnode_t*))
{
    if (!head) return;
    else if (!head->root) return;
    if (!callback) abort();
    __avl_traverse(head->root, callback);
}
