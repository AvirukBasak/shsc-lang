# AVL Tree
C library to implement AVL tree.

Note that `libavl` doesn't actually abstract away the entire AVL tree.
Instead it only takes the job of attaching, detaching and searching nodes.

Therefore things like memory management, node allocation and freeing are to be done manually.

#### Why libavl is minimalistic?
The library attempts to not depend on `libc`.
Therefore it provides the AVL tree algorithm only.
To make things function, one must manually handle the data to be stored in the tree.

This makes it general purpose.

You'll most likely need a few wrapper libraries around `libavl` to get the functionality you want.

See the [example](tests/test.c) which implements an ordered map using `libavl`.

## Usage
- Build with `make`.
- Copy library from `target/`.
- See the [api](#api) and [example](tests/test.c).

#### Note
- Library uses `avl` or `avl_` prefix.

## API
Library defined types:
- [`AVL`](#avl-type)
- [`avlnode_t`](#avlnode_t)

Functions:
- [`avl_attach`](#avl_attach)
- [`avl_detach`](#avl_detach)
- [`avl_search`](#avl_search)
- [`avl_traverse`](#avl_traverse)

Callback function types:
- [`avl_compare_t`](#avl_compare_t)
- [`avl_keycompare_t`](#avl_keycompare_t)

#### AVL type
The data type for the head node of the AVL tree.

The head needs to be manually allocated and freed. See [example](tests/test.c#L53).
Initialization can be handled by `libavl`.

#### avlnode_t
A library defined struct type.
It's the data type for nodes in the AVL tree.

The `data` member (which is a `void*`) of this struct should point to the data that you want to put in the AVL tree.
See [example](tests/test.c#L74).

A node needs to be manually allocated and freed.
Initialization can be handled by `libavl`.

#### avl_attach
```c
bool avl_attach(AVL *head, avlnode_t *node, avl_compare_t callback);
```

Attaches a node to the tree.

- param: `head` AVL head
- param: `node` Node to be attached
- param: `callback` Function [`avl_compare_t`](#avl_compare_t)
- return: `true` On attach success

Calls [`avl_compare_t`](#avl_compare_t) type callback function to compare data b/w two nodes.

#### avl_detach
```c
avlnode_t *avl_detach(AVL *head, void *key, avl_keycompare_t callback);
```

Detaches a node from the tree.

- param: `head` AVL head
- param: `key` Pointer to key which is present in the data member of a node
- param: `callback` Function [`avl_keycompare_t`](#avl_keycompare_t)
- return: `avlnode_t*` Pointer to node to be freed

Calls [`avl_keycompare_t`](#avl_keycompare_t) type callback function to compare `key` to data b/w two nodes.

Detach doesn't free a node by itself, so you'll need to do the memory cleanup.

#### avl_search
```c
void *avl_search(AVL *head, void *key, avl_keycompare_t callback);
```

Searches for a key among the tree nodes.

- param: `head` AVL head
- param: `key` Pointer to key which is to be searched
- param: `callback` Function [`avl_keycompare_t`](#avl_keycompare_t)
- return: `void*` Pointer to data containing `key`

Calls [`avl_keycompare_t`](#avl_keycompare_t) type callback function to compare `key` to data b/w two nodes.

#### avl_traverse
```c
void avl_traverse(AVL *head, void (*callback)(avlnode_t*));
```

Runs a callback function on each AVL tree node in order.

- param: `head` AVL head
- param: `callback` Function w/ prototype `void (avlnode_t*)`

#### avl_compare_t
```c
int (*)(void *d1, void *d2);
```

Callback function type.
Compares data to data b/w nodes.

Has prototype `int (void*, void*)`.

- param: `void*` AVL tree node data
- param: `void*` AVL tree node data
- return: `int` If 0, match found
- return: `int` If -ve i.e. decrease, `libavl` goes to left subtree
- return: `int` If +ve i.e. increase, `libavl` goes to right subtree

#### avl_keycompare_t
```c
int (*)(void *key, void *d);
```

Callback function type.
Compares a key to data b/w nodes.

Has prototype `int (void*, void*)`.

- param: `void*` Pointer to `key` which is to be searched
- param: `void*` AVL tree node data
- return: `int` If 0, match found
- return: `int` If -ve i.e. decrease, `libavl` goes to left subtree
- return: `int` If +ve i.e. increase, `libavl` goes to right subtree
