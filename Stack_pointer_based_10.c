#include <stdio.h>

struct ElementType {
	int value;
};

struct Node {
	struct ElementType e;
	struct Node *next;
};

typedef struct Node *Stack;
typedef struct Node *StackNode;

Stack create_stack(){
	Stack S = malloc(sizeof(struct Node));
	S->next = NULL;
	return S;
}

int is_empty(Stack S){
	if (S==NULL) {
		printf("You must use create_stack function first");
		return 1;
	}		
	else 
		return S->next == NULL;
}

void make_null(Stack S){
	if (S == NULL) {
		printf("You must use create_stack function first");
		return 1;
	}		
	else 
		S->next = NULL;
}

void push(Stack S, struct ElementType e){
	StackNode newItem = malloc(sizeof(struct Node));
	newItem->e = e;
	newItem->next = S->next;
	S->next = newItem;
}

void pop(Stack S) {
	if (!is_empty(S))
	{
		StackNode topNode = S->next;
		S->next = S->next->next;
		free(topNode);
	} else {
		printf("The stack is empty!!!\n");
	}
}

StackNode top(Stack S) {
	if (is_empty(S)) {
		printf("The stack is empty!!!\n");
	} else {
		return S->next;
	}
}

void show_stack(Stack S){
	if (is_empty(S)) {
		printf("The stack is empty!!!");
	} else {
		S = S->next;
		printf("Current state of the stack is: ");
		while (S!=NULL) {
			printf("%d ",S->e.value);
			S = S->next;
		}		
	}
	printf("\n");
}

int main(){
	struct ElementType e1,e2,e3,e4;
	e1.value = 5; e2.value = 7; e3.value = -10; e4.value = 1;
	
	Stack S = create_stack();
	push(S,e1);push(S,e2);push(S,e3);push(S,e4);
	show_stack(S);
	pop(S);pop(S);
	show_stack(S);
	
	StackNode topNode = top(S);
	printf("Value of the top Node is: %d\n",topNode->e.value);
	pop(S);pop(S);pop(S);
	
	
	return 0;
}