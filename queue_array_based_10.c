#include <stdio.h>
#include <limits.h>

#define EMPTY_VALUE -INT_MAX
#define MIN_SIZE 5

struct ElementType {
	int value;
};

struct QueueRecord {
	unsigned int capacity;
	int front;
	int rear;
	int count;
	struct ElementType *queue_array;
};

typedef struct QueueRecord *Queue;

int is_empty(Queue Q) {
	return Q->count == 0;
}
int is_full(Queue Q) {
	return Q->count == Q->capacity;
}

int reset(Queue Q) {
	Q->count = 0;
	Q->rear = 0;
	Q->front = 1;
}

Queue create_queue(unsigned int capacity) {
	if (capacity<MIN_SIZE) {
		printf("The queue's capacity is at least %d",MIN_SIZE);
		return NULL;
	}
	Queue Q = malloc(sizeof(struct QueueRecord));
	if (Q == NULL) {
		printf("Not enough memory!\n");
		return NULL;
	}
	Q->queue_array = malloc(sizeof(struct ElementType)*capacity);
	if (Q->queue_array == NULL) {
		printf("Not enough memory!\n");
		return NULL;
	}
	Q->capacity = capacity;
	reset(Q);
	return Q;
} 

int increase(int index, unsigned int capacity) {
	index++;
	if (index == capacity)
		index = 0;
	return index;
}

void enqueue(struct ElementType e, Queue Q) {
	if (is_full(Q)){
		printf("The queue is full already!\n");
		return;
	}
	Q->rear = increase(Q->rear,Q->capacity);
	Q->queue_array[Q->rear] = e;
	Q->count++;
}

struct ElementType dequeue(Queue Q) {
	if (is_empty(Q)) {
		printf("The queue is empty!\n");
		struct ElementType e;
		e.value = EMPTY_VALUE;
		return e;
	} 
	struct ElementType e = Q->queue_array[Q->front];
	Q->front = increase(Q->front,Q->capacity);
	Q->count--;
	return e;
}

void show_queue(int index, Queue Q) {
	if (is_empty(Q)) {
		printf("The queue is empty!\n");
		return;
	}
	if (index == Q->rear) {
		printf("%d ",Q->queue_array[index]);
	} else {
		show_queue(increase(index,Q->capacity), Q);
		printf("%d ",Q->queue_array[index]);
	}
} 

int main () {
	struct ElementType e,e1,e2,e3,e4;
	e1.value = 2; e2.value = 4; e3.value = 1;e4.value = 3;
	Queue Q = create_queue(10);
	Q->front = 8; Q->rear = 7;
	enqueue(e1,Q); enqueue(e2,Q); enqueue(e3,Q); enqueue(e4,Q); 
	show_queue(Q->front,Q);
	printf("\n");
	
	e = dequeue(Q);
	printf("e = %d\n",e.value);
	show_queue(Q->front,Q);
	printf("\n");
	
	e = dequeue(Q);
	printf("e = %d\n",e.value);
	show_queue(Q->front,Q);
	printf("\n");
	
	e = dequeue(Q);
	printf("e = %d\n",e.value);
	show_queue(Q->front,Q);
	printf("\n");
	
	e = dequeue(Q);
	printf("e = %d\n",e.value);
	show_queue(Q->front,Q);
	printf("\n");
	
	return 0;
}