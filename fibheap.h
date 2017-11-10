#ifndef FIBHEAP_H
#define FIBHEAP_H

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
	//mark
} Fibheap;

Heap* heap_memory_allocation(Heap*);
//Insert
Fibheap* fibheap_memory_allocation();
Heap* fibheap_insert(Heap*, int, int);
void fibheap_add_node(Fibheap*, Fibheap*);
//Search min
Fibheap* fibheap_min(Heap*);
//Union
Heap* fibheap_union(Heap*, Heap*);
Heap* fibheap_union_list(Heap*, Heap*);
//Delete min node
Heap* fibheap_delete_min_node(Heap*);
Heap* fibheap_consolidate(Heap* heap);
double fibheap_max_degree(Heap* heap);
//Litle key
//Delete node
void fibheap_delete_node(Heap*, Fibheap*);
//Print heap
void fibheap_print(Heap*);

#endif