#ifndef BINHEAP_NODE_H
#define BINHEAP_NODE_H

#include <remote_ref.h>

#define UNDEFINED_DEGREE -1

struct binheap_node { 
	struct binheap_node *parent;
	struct binheap_node *next;
	struct binheap_node *child;

	int degree;
	remote_ref *value;
};

struct binheap_node *init_binheap_node(remote_ref *value);
remote_ref* get_node_value(struct binheap_node *node);
void free_binheap_node(struct binheap_node **node);
#endif
