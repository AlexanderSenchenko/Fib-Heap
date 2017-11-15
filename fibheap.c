#include "fibheap.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Heap* heap_memory_allocation()
{
	Heap* heap = malloc(sizeof(Heap));
	if (heap == NULL)
		return NULL;
	heap->min = NULL;
	heap->amount = 0;
	return heap;
}

Fibheap* fibheap_memory_allocation()
{
	Fibheap *node = malloc(sizeof(Fibheap));
	if (node == NULL)
		return NULL;
	return node;
}

Heap* fibheap_insert(Heap* heap, int key, int value)
{
	Fibheap *node = fibheap_memory_allocation();
	if (node == NULL)		
		return NULL;
	node->key = key;
	node->value = value;
	node->degree = 0;
	//node->mark = false;
	node->parent = NULL;
	node->child = NULL;
	node->left = node;
	node->right = node;
	fibheap_add_node(node, heap->min);
	if (heap->min == NULL || node->key < heap->min->key)
		heap->min = node;
	heap->amount++;
	return heap;
}

void fibheap_add_node(Fibheap* node, Fibheap* min)
{
	if (min == NULL)
		return;
	if (min->left == min) {
		min->left = node;
		min->right = node;
		node->right = min;
		node->left = min;
	} else {
		node->left = min->left;
		node->left->right = node;
		min->left = node;
		node->right = min;
	}
}

Fibheap* fibheap_min(Heap* heap)
{
	return heap->min;
}

Heap* fibheap_union(Heap* heap_a, Heap* heap_b)
{
	Heap* heap = NULL;
	heap = heap_memory_allocation(heap);
	heap->min = fibheap_min(heap_a);
	fibheap_union_list(heap->min, heap_b->min);
	if (heap->min == NULL || heap->min->key > heap_b->min->key)
		heap->min = heap_b->min;
	heap->amount = heap_a->amount + heap_b->amount;
	free(heap_a);
	free(heap_b);
	return heap;
}

void fibheap_union_list(Fibheap* min_a, Fibheap* min_b)
{
	if (min_a == NULL || min_b == NULL)
		return;
	min_a->right->left = min_b->left;
	min_b->left->right = min_a->right;
	min_a->right = min_b;
	min_b->left = min_a;
}


Heap* fibheap_delete_min_node(Heap* heap)
{
	Fibheap* min = fibheap_min(heap), *node = NULL;
	if (min == NULL)
		return NULL;

	while (node != min->child) {
		if (node == NULL)
			node = min->child;
		node->parent = NULL;
		node = node->right;
	}

	fibheap_union_list(min, min->child);

	fibheap_delete_node_from_list(min);

	if (min == min->right) {
		return NULL;
	} else {
		heap->min = min->right;
		heap = fibheap_consolidate(heap);

	}
	heap->amount--;
	free(min);

	return heap;
}

Heap* fibheap_consolidate(Heap* heap)
{
	int degree = fibheap_max_degree(heap), n = 0;
	Fibheap** arr_node = malloc(sizeof(Fibheap) * degree);
	Fibheap* node = NULL;

	for (int i = 0; i <= degree; i++) {
		arr_node[i] = NULL;
	}

	while (node != heap->min) {
		if (node == NULL)
			node = heap->min;
		n++;
		node = node->right;
	}

	for (int i = 0; i < n; i++) {
		int n_degree = node->degree;
		while (arr_node[n_degree] != NULL) {
			if (arr_node[n_degree]->key < node->key) {
				if (arr_node[n_degree]->child != NULL) {
					fibheap_link(arr_node[n_degree], node);
				} else {
					arr_node[n_degree]->child = node;
					fibheap_delete_node_from_list(node);
					node->left = node;
					node->right = node;
					arr_node[n_degree]->degree++;
					node->parent = arr_node[n_degree];
				}
				node = arr_node[n_degree];
			} else {
				if (node->child != NULL) {
					fibheap_link(node, arr_node[n_degree]);
				} else {
					node->child = arr_node[n_degree];
					fibheap_delete_node_from_list(arr_node[n_degree]);
					arr_node[n_degree]->left = arr_node[n_degree];
					arr_node[n_degree]->right = arr_node[n_degree];
					node->degree++;
					arr_node[n_degree]->parent = node;
				}
			}
			arr_node[n_degree] = NULL;
			n_degree++;
		}	
		arr_node[n_degree] = node;
		node = node->right;
	}

	for (int i = 0; i <= degree; i++) {
		if (arr_node[i] != NULL) {
			if (heap->min == NULL || heap->min->key > arr_node[i]->key) {
				heap->min = arr_node[i];
			}
		}
	}

	return heap;
}

void fibheap_link(Fibheap* node, Fibheap* child)
{
	node->degree++;
	fibheap_delete_node_from_list(child);
	child->parent = node;
	fibheap_add_node(child, node->child);
	child->mark = 0;
}

int fibheap_max_degree(Heap* heap)
{
	return floor(log(heap->amount));
}

void fibheap_decrease_key(Heap* heap, Fibheap* node, int new_key)
{
	Fibheap* parent = node->parent;
	if (node->key < new_key)
		return;
	node->key = new_key;
	if (parent != NULL && parent->key > node->key) {
		fibheap_cut(heap, node, parent);
		fibheap_cascading_cut(heap, parent);
	}
	if (heap->min == NULL || node->key < heap->min->key) {
		heap->min = node;
	}
}

void fibheap_cut(Heap* heap, Fibheap* node_c, Fibheap* node_p)
{
	if (node_c == node_p->child && node_c != node_c->right) {
		node_p->child = node_c->right;
	} else {
		node_p->child = NULL;
	}

	node_c->left->right = node_c->right;
	node_c->right->left = node_c->left;

	node_c->right = heap->min;
	node_c->left = heap->min->left;
	heap->min->left->right = node_c;
	heap->min->left = node_c;

	node_c->parent = NULL;
	node_p->degree--;
	node_c->mark = 0;
}

void fibheap_cascading_cut(Heap* heap, Fibheap* node)
{
	if (node->parent == NULL)
		return;
	if (node->mark == 0) {
		node->mark = 1;
	} else {
		fibheap_cut(heap, node, node->parent);
		fibheap_cascading_cut(heap, node->parent);
	}
}

void fibheap_delete_node_from_list(Fibheap* node)
{
	node->left->right = node->right;
	node->right->left = node->left;
}

void fibheap_print(Fibheap* min)
{
	printf("<");
	Fibheap* node = NULL;
	while (node != min) {
		if (node == NULL)
			node = min; 
		printf("%d_%d ", node->key, node->value);
		if (node->child != NULL)
			fibheap_print(node->child);
		node = node->right;
	}
	printf(">\n");
}