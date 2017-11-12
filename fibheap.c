#include "fibheap.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Heap* heap_memory_allocation(Heap* heap)
{
	heap = malloc(sizeof(Heap));
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
	heap = fibheap_union_list(heap, heap_b);
	if (heap->min == NULL || heap->min->key > heap_b->min->key)
		heap->min = heap_b->min;
	heap->amount = heap_a->amount + heap_b->amount;
	free(heap_a);
	free(heap_b);
	return heap;
}

Heap* fibheap_union_list(Heap* heap, Heap* heap_b)
{
	if (heap == NULL || heap_b == NULL)
		return NULL;
	heap->min->right->left = heap_b->min->left;
	heap_b->min->left->right = heap->min->right;
	heap->min->right = heap_b->min;
	heap_b->min->left = heap->min;
	return heap;
}


Heap* fibheap_delete_min_node(Heap* heap)
{
	Fibheap* min = fibheap_min(heap), *node = NULL;
	if (min == NULL)
		return NULL;
	for (int i = 0; i < min->degree; i++) {
		node = min->child;
		min->child = node->right;

		fibheap_add_node(node, min);

		node->parent = NULL;
	}

	fibheap_delete_node(min);

	if (min == min->right) {
		return NULL;
	} else {
		heap->min = min->right;
		heap = fibheap_consolidate(heap);

	}
	heap->amount--;

	return heap;
}

Heap* fibheap_consolidate(Heap* heap)
{
	int degree = fibheap_max_degree(heap);
	Fibheap** arr_node = malloc(sizeof(Fibheap) * degree);
	Fibheap* node = fibheap_min(heap);

	for (int i = 0; i < degree; i++) {
		arr_node[i] = NULL;
	}

	//while () {
		if (arr_node[node->degree] == NULL) {
			arr_node[node->degree] = node;
		} else {
			if (arr_node[degree]->key < node->key) {
				if (arr_node[node->degree]->child != NULL) {
					fibheap_delete_node(node);
					fibheap_add_node(node, arr_node[node->degree]->child);
				} else {
					arr_node[node->degree]->child = node;
				}
				arr_node[node->degree]->degree++;
				node->parent = arr_node[node->degree];
			} else {
				if (arr_node[node->degree]->child != NULL) {
					fibheap_delete_node(arr_node[node->degree]->child);
					fibheap_add_node(arr_node[node->degree]->child, node);
				} else {
					node->child = arr_node[node->degree];
				}
				node->degree++;
				arr_node[node->degree]->parent = node;
				arr_node[node->degree] = node;
			}
			arr_node[node->degree]->degree++;


		}
		node = node->right;
	//}

	return heap;
}

void fibheap_swap(Fibheap* node_a, Fibheap* node_b)
{
	node_a->right = node_b->right;
	node_a->right->left = node_a;
	node_b->left = node_a->left;
	node_b->left->right = node_b;
	node_a->left = node_b;
	node_b->right = node_a; 
}

int fibheap_max_degree(Heap* heap)
{
	return round(log(heap->amount));
}

void fibheap_delete_node(Fibheap* node)
{
	node->left->right = node->right;
	node->right->left = node->left;
	//heap->amount--;
	//free(node);
}

void fibheap_print(Heap* heap)
{
	Fibheap* node = fibheap_min(heap);
	for (int i = 0; i < heap->amount; i++) {
		printf("%d_%d\t", node->key, node->value);
		node = node->right;
	}
	printf("\n");
}