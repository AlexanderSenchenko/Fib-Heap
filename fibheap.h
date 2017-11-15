#ifndef FIBHEAP_H
#define FIBHEAP_H

#include <stdbool.h>

typedef struct Heap
{
	struct Fibheap *min;
	int amount;
} Heap;

typedef struct Fibheap
{
	int key;	
	int value;
	struct Fibheap *parent;
	struct Fibheap *child;
	struct Fibheap *left;
	struct Fibheap *right;
	int degree;
	bool mark;
} Fibheap;

Heap* heap_memory_allocation();
//
Fibheap* fibheap_memory_allocation();
Heap* fibheap_insert(Heap*, int, int);
void fibheap_add_node(Fibheap*, Fibheap*);
//
Fibheap* fibheap_min(Heap*);
//
Heap* fibheap_union(Heap*, Heap*);
void fibheap_union_list(Fibheap*, Fibheap*);
//
Heap* fibheap_delete_min_node(Heap*);
Heap* fibheap_consolidate(Heap*);
void fibheap_link(Fibheap*, Fibheap*);
int fibheap_max_degree(Heap*);
void fibheap_delete_node_from_list(Fibheap*);
//
void fibheap_decrease_key(Heap*, Fibheap*, int);
void fibheap_cut(Heap*, Fibheap*, Fibheap*);
void fibheap_cascading_cut(Heap*, Fibheap*);
//
void fibheap_delete_node(Heap*, Fibheap*);
//
void fibheap_print(Fibheap*);

#endif