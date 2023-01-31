#ifndef __LIBAVL_H__
#define __LIBAVL_H__

#include <stddef.h>
#include <stdbool.h>

/**
 * @brief AVL head type.
 * Needs to be manually allocated on the heap.
 */
typedef struct AVL AVL;

/**
 * @brief AVL tree node.
 * Needs to be manually allocated on the heap.
 */
typedef struct avlnode_t avlnode_t;

/**
 * @brief AVL head type.
 * Needs to be manually allocated on the heap.
 */
struct AVL {
    /**
     * @brief Pointer to root node.
     * Auto managed, DO NOT modify.
     * @type avlnode_t*
     */
    avlnode_t *__root;
};

/**
 * @brief AVL tree node type.
 * Needs to be manually allocated on the heap.
 */
struct avlnode_t {
    /**
     * @brief Data pointer. Needs to be manually linked to data.
     */
    void *data;
    /**
     * @brief Pointer to parent node.
     * Auto managed, DO NOT modify.
     * @type avlnode_t*
     */
    avlnode_t *__pr;
    /**
     * @brief Pointer to left child node.
     * Auto managed, DO NOT modify.
     * @type avlnode_t*
     */
    avlnode_t *__lc;
    /**
     * @brief Pointer to right child node.
     * Auto managed, DO NOT modify.
     * @type avlnode_t*
     */
    avlnode_t *__rc;
    /**
     * @brief Node balance factor.
     * Auto managed, DO NOT modify.
     * @type int
     */
    int __bf;
};

/**
 * @brief Callback function, compares data to data b/w nodes.
 * @param void* AVL tree node data
 * @param void* AVL tree node data
 * @return int.
 * @return If 0, match found.
 * @return If -ve i.e. decrease, libavl goes to left subtree.
 * @return If +ve i.e. increase, libavl goes to right subtree.
 */
typedef int (*avl_compare_t)(void*, void*);

/**
 * @brief Callback function, compares a key to data b/w nodes.
 * @param void* Pointer to key which is to be searched
 * @param void* AVL tree node data
 * @return int.
 * @return If 0, match found.
 * @return If -ve i.e. decrease, libavl goes to left subtree.
 * @return If +ve i.e. increase, libavl goes to right subtree.
 */
typedef int (*avl_keycompare_t)(void*, void*);

/**
 * @brief Attaches a node to the tree
 * @param head AVL head
 * @param node Node to be attached
 * @param callback int (*)(void*, void*)
 * @return bool true on attach success
 */
bool avl_attach(AVL *head, avlnode_t *node, avl_compare_t callback);

/**
 * @brief Detaches a node from the tree
 * @param head AVL head
 * @param key Pointer to key which is present in the data member of a node
 * @param callback int (*)(void*, void*)
 * @return avlnode_t* Pointer to node to be freed
 */
avlnode_t *avl_detach(AVL *head, void *key, avl_keycompare_t callback);

/**
 * @brief Searches for a key among the tree nodes
 * @param head AVL head
 * @param key Pointer to key which is to be searched
 * @param callback int (*)(void*, void*)
 * @return void* Pointer to data containing key
 */
void *avl_search(AVL *head, void *key, avl_keycompare_t callback);

/**
 * @brief Runs a callback function on each AVL tree node in order
 * @@param head AVL head
 * @param callback void (*)(avlnode_t*)
 */
void avl_traverse(AVL *head, void (*callback)(avlnode_t*));

#endif
