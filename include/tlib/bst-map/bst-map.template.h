/**
 * Implementation of an ordered map using a self balancing BST.
 * Implemented using libavl.
 * @author Aviruk Basak
 * @date 10.12.2022
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "libavl.h"

#undef new
#undef delete

/**
 * new function: returns a pointer to a struct type passed by allocating
 * memory using calloc
 */
#define new(struct_t) ({                                                              \
    struct struct_t *tmp = calloc(1, sizeof(struct struct_t));                        \
    if (!tmp) abort();                                                                \
    tmp;                                                                              \
})

/**
 * delete function: frees pointer and sets it to null
 */
#define delete(ptr) ({                                                                \
    if (ptr) {                                                                        \
        free(ptr);                                                                    \
        ptr = NULL;                                                                   \
    }                                                                                 \
})

#define BstMap(vtype) bst_map_##vtype
#define BstMapFunc(vtype, func, ...) bst_map_##vtype##_##func(__VA_ARGS__)

/**
 * Generates function prototype definitions and typedefs for the map
 * vtype should be a primary datatype or typdefed (aliased) pointer
 * format: BstMapDeclarePrototypes(vtype)
 */
#define BstMapDeclarePrototypes(vtype)                                                \
                                                                                      \
typedef AVL *bst_map_##vtype;                                                         \
                                                                                      \
typedef struct bst_map_data_##vtype {                                                 \
    unsigned long int key;                                                            \
    vtype value;                                                                      \
} *bst_map_data_##vtype;                                                              \
                                                                                      \
bst_map_##vtype bst_map_##vtype##_newmap();                                           \
unsigned long int bst_map_##vtype##_hashString(const char *strkey);                   \
vtype bst_map_##vtype##_get(bst_map_##vtype m, unsigned long int key, bool *found);   \
bool bst_map_##vtype##_set(bst_map_##vtype m, unsigned long int key, vtype val);      \
bool bst_map_##vtype##_del(bst_map_##vtype m, unsigned long int key);                 \
void bst_map_##vtype##_print(bst_map_##vtype m);                                      \
void bst_map_##vtype##_free(bst_map_##vtype *m);

/**
 * Defines the chosen map from template: generates the necessary function definitions
 * vtype should be a primary datatype or typdefed (aliased) pointer
 * format: BstMapDefine(vtype, func_print(const value))
 * NOTE: requires BstMapDeclarePrototypes(vtype)
 */
#define BstMapDefine(vtype, func_print)                                               \
                                                                                      \
/* helper functions */                                                                \
void bst_map_##vtype##__map_print(avlnode_t *node);                                   \
void bst_map_##vtype##__map_free(avlnode_t *node);                                    \
int bst_map_##vtype##__map_ncomp(void *d1, void *d2);                                 \
int bst_map_##vtype##__map_nkcomp(void *id, void *d);                                 \
                                                                                      \
bst_map_##vtype bst_map_##vtype##_newmap()                                            \
{                                                                                     \
    return calloc(1, sizeof(AVL));                                                    \
}                                                                                     \
                                                                                      \
unsigned long int bst_map_##vtype##_hashString(const char *strkey)                    \
{                                                                                     \
    unsigned long int hash = 0;                                                       \
    size_t i, len = strlen(strkey);                                                   \
    for (i = 0; i < len; i++) {                                                       \
        hash = hash * 2 + (strkey[i] ^ hash);                                         \
    }                                                                                 \
    return hash;                                                                      \
}                                                                                     \
                                                                                      \
vtype bst_map_##vtype##_get(bst_map_##vtype m, unsigned long int key, bool *found)    \
{                                                                                     \
    if (!m) abort();                                                                  \
    bst_map_data_##vtype data = avl_search(m, &key, bst_map_##vtype##__map_nkcomp);   \
    if (data) {                                                                       \
        if (found) *found = true;                                                     \
        return data->value;                                                           \
    }                                                                                 \
    if (found) *found = false;                                                        \
    return (vtype) 0;                                                                 \
}                                                                                     \
                                                                                      \
bool bst_map_##vtype##_set(bst_map_##vtype m, unsigned long int key, vtype val)       \
{                                                                                     \
    if (!m) abort();                                                                  \
    bst_map_data_##vtype data = avl_search(m, &key, bst_map_##vtype##__map_nkcomp);   \
    if (data) {                                                                       \
        data->value = val;                                                            \
        return true;                                                                  \
    }                                                                                 \
    data = malloc(sizeof(struct bst_map_data_##vtype));                                      \
    avlnode_t *node = malloc(sizeof(avlnode_t));                                      \
    node->data = data;                                                                \
    data->key = key;                                                                  \
    data->value = val;                                                                \
    return avl_attach(m, node, bst_map_##vtype##__map_ncomp);                         \
}                                                                                     \
                                                                                      \
bool bst_map_##vtype##_del(bst_map_##vtype m, unsigned long int key)                  \
{                                                                                     \
    if (!m) abort();                                                                  \
    avlnode_t *node = avl_detach(m, &key, bst_map_##vtype##__map_nkcomp);             \
    if (!node) return false;                                                          \
    free(node);                                                                       \
    if (node->data) free(node->data);                                                 \
    return true;                                                                      \
}                                                                                     \
                                                                                      \
void bst_map_##vtype##_print(bst_map_##vtype m)                                       \
{                                                                                     \
    if (!m) return;                                                                  \
    printf("{\n");                                                                    \
    avl_traverse(m, bst_map_##vtype##__map_print);                                   \
    printf("}\n");                                                                    \
}                                                                                     \
                                                                                      \
void bst_map_##vtype##_free(bst_map_##vtype *m)                                       \
{                                                                                     \
    if (!m || !(*m)) return;                                                          \
    avl_traverse(*m, bst_map_##vtype##__map_free);                                    \
    delete(*m);                                                                       \
}                                                                                     \
                                                                                      \
/* helper function definitions */                                                     \
void bst_map_##vtype##__map_free(avlnode_t *node) {                                   \
    free(node->data);                                                                 \
    free(node);                                                                       \
}                                                                                     \
                                                                                      \
void bst_map_##vtype##__map_print(avlnode_t *node) {                                  \
    bst_map_data_##vtype data = node->data;                                           \
    if (!data) return;                                                                \
    printf("    %lu -> ", data->key);                                                 \
    const vtype value = data->value;                                                  \
    {                                                                                 \
        const bst_map_##vtype m = NULL;                                               \
        const bst_map_##vtype data = NULL;                                            \
        (m, data);                                                                    \
        func_print;                                                                   \
    }                                                                                 \
    printf("\n");                                                                     \
}                                                                                     \
                                                                                      \
int bst_map_##vtype##__map_ncomp(void *d1, void *d2) {                                \
    return ((bst_map_data_##vtype) d1)->key - ((bst_map_data_##vtype) d2)->key;     \
}                                                                                     \
                                                                                      \
int bst_map_##vtype##__map_nkcomp(void *key, void *d) {                               \
    /* if id < data, -ve or decrease data, i.e. go to left subtree                    \
     * if id > data, +ve or increase data, i.e. go to right subtree                   \
     * if equal 0, match found                                                        \
     */                                                                               \
    return *(unsigned long int*) key - ((bst_map_data_##vtype) d)->key;              \
}                                                                                     \
