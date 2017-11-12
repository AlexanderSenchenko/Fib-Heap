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
	heap = fibheap_insert(heap, 3, 4);
	heap = fibheap_insert(heap, 5, 6);
	heap = fibheap_insert(heap, 7, 8);
	fibheap_print(heap);

	printf("Heap_b\n");
	Heap *heap_b = NULL;
	heap_b = heap_memory_allocation(heap_b);
	if (heap_b == NULL)
		return 0;
	heap_b = fibheap_insert(heap_b, 9, 10);
	heap_b = fibheap_insert(heap_b, 1, 2);
	heap_b = fibheap_insert(heap_b, 11, 12);
	fibheap_print(heap_b);

	printf("Heap union\n");
	Heap* heap_c = NULL;
	heap_c = fibheap_union(heap, heap_b);
	fibheap_print(heap_c);

	printf("Delete node\n");
	/*fibheap_delete_node(heap_c, heap_c->min->right->right);
	fibheap_print(heap_c);
	fibheap_delete_node(heap_c, heap_c->min->right->right);
	fibheap_print(heap_c);
	*/

	heap_c = fibheap_delete_min_node(heap_c);
	fibheap_print(heap_c);

	return 0;
}
