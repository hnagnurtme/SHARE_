#include <stdio.h>

#define EMPTY_POS -1
#define MIN_STACK_SIZE 5

struct ElementType {
	char value;
};

struct StackRecord {
	unsigned int stack_size;
	int tos;
	struct ElementType *stack_array;
};

typedef struct StackRecord *Stack;

int is_empty(Stack s) {
	return s->tos == EMPTY_POS;
}

void make_empty(Stack s) {
	s->tos = EMPTY_POS;
}

void dispose(Stack s) {
	if (s!=NULL) {
		free(s->stack_array);
		free(s);
	}
}

Stack create_stack(unsigned int max_elements){
	if (max_elements < MIN_STACK_SIZE){
		printf("Stack size is too small!!!\n");
		return NULL;
	}
	
	Stack s = malloc(sizeof(struct StackRecord));
	if (s == NULL) {
		printf("Out of space!\n");
		return NULL;
	}
	s->stack_array = malloc(sizeof(struct ElementType)*max_elements);
	if (s->stack_array == NULL){
		printf("Out of space!\n");
		return NULL;
	}
	s->stack_size = max_elements;
	s->tos = EMPTY_POS;
	return s;
}

int is_full(Stack s) {
	return s->tos == (s->stack_size - 1);
}

void push(Stack s, struct ElementType e) {
	if (is_full(s)) 
		printf("The stack is full already!!!\n");
	else 
		s->stack_array[++s->tos] = e;	
}

struct ElementType pop(Stack s) {
	if (is_empty(s)) 
		printf("The stack is currently empty. You cannot pop an empty stack!!!\n");
	else 
		return s->stack_array[s->tos--];
}

struct ElementType top(Stack s) {
	if (is_empty(s)) 
		printf("The stack is currently empty. You cannot top an empty stack!!!\n");
	else 
		return s->stack_array[s->tos];
} 

void show_stack(Stack s){
	if (is_empty(s)) {
		printf("The stack is empty!!!\n");
		return;
	}		
	printf("Current state of the stack is: ");
	for (int i = s->tos; i>=0;i--) {
		printf("%d ",s->stack_array[i].value);
	}
	printf("\n");
}

int main(){
	char *a = "[i + 5 *(17 - j/(6*k))]";
	Stack s = create_stack(100);
	struct ElementType open, close;
	for (int i = 0; i < strlen(a); i++)
	{
		if (a[i] == '(' || a[i] == '[')
		{
			open.value = a[i];
			push(s, open);
		}
		if (a[i] == ')')
		{
			open =pop(s);
			if (open.value != '(' )
			{
				printf("Not balanced\n");
				return;
			}
		}
		if (a[i] == ']')
		{
			open = pop(s);
			if (open.value != '[')
			{
				printf("Not balanced\n");
				return;
			}
		}
	}
	
	if (is_empty(s))
	{
		printf("Balanced\n");
	}
	else
	{
		printf("Not balanced\n");
		}	
	return 0;
}