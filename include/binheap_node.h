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

struct binheap_node *binheap_node_init(remote_ref *value);
remote_ref* get_node_value(struct binheap_node *node);
void binheap_node_free(struct binheap_node **node);
#endif
