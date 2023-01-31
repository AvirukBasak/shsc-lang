#ifndef __HELPERFN_H__
#define __HELPERFN_H__

#include "stdhead.h"
#include "avl.h"

void __avl_traverse(avlnode_t *node, void (*callback)(avlnode_t*));

#endif
