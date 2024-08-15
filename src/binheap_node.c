#include <binheap_node.h>

struct binheap_node *init_binheap_node(remote_ref *value){
	if(value == NULL) return NULL;
	struct binheap_node *new_node = calloc(1, sizeof(struct binheap_node));
	if(new_node == NULL) return new_node;
	new_node->parent = NULL;
	new_node->next = NULL;
	new_node->child = NULL;
	new_node->degree = UNDEFINED_DEGREE;
	new_node->value = value;
	return new_node;
}

uint16_t get_node_score(struct binheap_node *node){
	if(node == NULL) return UINT16_MAX;
	return (node->value)->score;
}

void free_binheap_node(struct binheap_node **node){
	if(node == NULL) return;
	if(*node == NULL) return;
	free(*node);
	*node = NULL;
}
