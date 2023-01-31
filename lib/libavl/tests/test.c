/**
 * Implementation of an ordered map using a self balancing BST.
 * Implemented using libavl.
 * @author Aviruk Basak
 * @date 10.12.2022
 */

#include <stdio.h>
#include <stdlib.h>

#include "libavl.h"

typedef AVL map_t;

// map implementation using libavl
map_t *map_new();
void map_delete(map_t **mp);
void map_print(map_t *mp);
bool map_insert(map_t *mp, int id, char *name);
char *map_search(map_t *mp, int id);
char *map_remove(map_t *mp, int id);

int main()
{
    map_t *mp = map_new();
    map_insert(mp, 45, "Jonathan");
    map_insert(mp, 23, "Joe");
    map_insert(mp, 37, "James");
    map_insert(mp, 12, "John");
    map_insert(mp, 38, "Johnny");
    const char *name12 = map_search(mp, 12);
    const char *name23 = map_search(mp, 23);
    printf("%d => %s\n"
           "%d => %s\n", 12, name12, 23, name23);
    printf("avl_map = ");
    map_print(mp);
    map_delete(&mp);
}

// data struct
typedef struct {
    int id;
    char *name;
} mapdata_t;

// helper functions
void __map_print(avlnode_t *node);
void __map_free(avlnode_t *node);
int __map_ncomp(void *d1, void *d2);
int __map_nkcomp(void *id, void *d);

map_t *map_new() {
    return malloc(sizeof(AVL));
}

// function definitions
void map_delete(map_t **mp) {
    if (!mp || !*mp) return;
    avl_traverse(*mp, __map_free);
    free(*mp);
    *mp = NULL;
}

void map_print(map_t *mp) {
    if (!mp) return;
    printf("{\n");
    avl_traverse(mp, __map_print);
    printf("}\n");
}

bool map_insert(map_t *mp, int id, char *name) {
    mapdata_t *data = malloc(sizeof(mapdata_t));
    avlnode_t *node = malloc(sizeof(avlnode_t));
    node->data = data;
    data->id = id;
    data->name = name;
    return avl_attach(mp, node, __map_ncomp);
}

char *map_search(map_t *mp, int id) {
    mapdata_t *data = (mapdata_t*) avl_search(mp, &id, __map_nkcomp);
    return data ? data->name : "NULL";
}

char *map_remove(map_t *mp, int id) {
    avlnode_t *node = avl_detach(mp, &id, __map_nkcomp);
    mapdata_t *data = node ? ((mapdata_t*) node->data) : NULL;
    char *name = data ? data->name : "NULL";
    free(node);
    free(data);
    return name;
}

// helper function definitions
void __map_free(avlnode_t *node) {
    free(node->data);
    free(node);
}

void __map_print(avlnode_t *node) {
    mapdata_t *data = node->data;
    if (!data) return;
    printf("    %d => \"%s\"\n", data->id, data->name);
}

int __map_ncomp(void *d1, void *d2) {
    return ((mapdata_t*) d1)->id - ((mapdata_t*) d2)->id;
}

int __map_nkcomp(void *id, void *d) {
    /* if id < data, -ve or decrease data, i.e. go to left subtree
     * if id > data, +ve or increase data, i.e. go to right subtree
     * if equal 0, match found
     */
    return *(int*)id - ((mapdata_t*) d)->id;
}
