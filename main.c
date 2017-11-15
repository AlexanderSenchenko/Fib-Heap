#include "fibheap.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	printf("Heap\n");
	Heap *heap = NULL;
	heap = heap_memory_allocation(heap);
	if (heap == NULL)
		return 0;
	heap = fibheap_insert(heap, 3, 3);
	heap = fibheap_insert(heap, 5, 5);
	heap = fibheap_insert(heap, 7, 7);
	fibheap_print(heap->min);

	printf("Heap_b\n");
	Heap *heap_b = NULL;
	heap_b = heap_memory_allocation(heap_b);
	if (heap_b == NULL)
		return 0;
	heap_b = fibheap_insert(heap_b, 9, 9);
	heap_b = fibheap_insert(heap_b, 1, 1);
	heap_b = fibheap_insert(heap_b, 11, 11);
	fibheap_print(heap_b->min);

	printf("Heap union\n");
	Heap* heap_c = NULL;
	heap_c = fibheap_union(heap, heap_b);
	fibheap_print(heap_c->min);

	printf("Delete min node\n");
	heap_c = fibheap_delete_min_node(heap_c);
	fibheap_print(heap_c->min);

	return 0;
}
