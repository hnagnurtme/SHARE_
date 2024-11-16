#include <stdio.h>

struct HeapNode {
	int value;
};

struct HeapRecord {
	int length;
	int heap_size;
	struct HeapNode *heap_array;
};

typedef struct HeapRecord *Heap;

Heap create_heap(int length) {
	Heap H = malloc(sizeof(struct HeapRecord));
	if (H == NULL) {
		printf("Not enough memory!\n");
		return;
	}
	H->heap_array = malloc(sizeof(struct HeapNode)*(length+1));
	if (H->heap_array == NULL) {
		printf("Not enough memory!\n");
		return;
	}
	H->length = length;
	H->heap_size = length;
	return H;
}

void max_heapify(Heap H, int i) {
	int l,r,largest;
	l = 2*i;
	r = 2*i +1;	
	largest = i;
	if (l<=H->heap_size && H->heap_array[largest].value < H->heap_array[l].value)
		largest = l;
	if (r<=H->heap_size && H->heap_array[largest].value < H->heap_array[r].value)
		largest = r;
	if (i!=largest) {
		struct HeapNode tmp = H->heap_array[i];
		H->heap_array[i] = H->heap_array[largest];
		H->heap_array[largest] = tmp;
		max_heapify(H,largest);
	}
}

void show_heap(Heap H) {
	if (H->heap_size == 0) {
		printf("The heap is empty!\n");
		return;
	}
	printf("The heap: ");
	for (int i=1;i<=H->heap_size;i++)
		printf("%d ",H->heap_array[i].value);
	printf("\n");
}

void show_heap_array(Heap H) {
	if (H->length == 0) {
		printf("The heap array is empty!\n");
		return;
	}
	printf("The heap array: ");
	for (int i=1;i<=H->length;i++)
		printf("%d ",H->heap_array[i].value);
	printf("\n");
}

void build_max_heap(Heap H) {
	H->heap_size = H->length;
	for (int i=H->length/2;i>0;i--) 
		max_heapify(H,i);
}

void heap_sort(Heap H) {
	build_max_heap(H);
	for (int i=H->length;i>1;i--)
	{
		struct HeapNode tmp = H->heap_array[1];
		H->heap_array[1] = H->heap_array[i];
		H->heap_array[i] = tmp;
		H->heap_size--;
		max_heapify(H,1);
	}
}

int main() {
	Heap H = create_heap(10);
	int data[] = {4,1,3,2,16,9,10,14,8,7};
	for (int i=0;i<10;i++) 
		H->heap_array[i+1].value = data[i];
	show_heap(H);
	heap_sort(H);
	show_heap_array(H);
	
	return 0;
}