#include "my_stack.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>
	
stack* stack_create(int Size){
	stack* new_stack = (stack*) calloc (1, sizeof(stack*));
	
	if (new_stack == 0) {///NULL
		
		errno = ENOMEM;
		perror("Error in function stack_create: no memory for stack");
		abort();
		
	}
	(new_stack -> size) = Size;
	(new_stack -> data) = (double*) calloc (Size, sizeof(double*));
	
	if ((new_stack -> data) == 0) {
		errno = ENOMEM;//correct
		perror("Error in function stack_create: no memory for stacks data");
		abort();
	
	}
	
	(new_stack -> head) = 0;//-1
	return new_stack;
}

double pop(stack* stk){
	if (stack_empty(stk)){
		
		errno = EACCES;
		fprintf(stderr, "ERROR: stack is empty");//!!!!
		return -1;
		
	}
	(stk -> head)--;//!!!
	return (*((stk -> data) + (stk -> head)));//!!!
}

int push(stack* stk, double a){
	if (stack_full(stk)){
		
		errno = EACCES;
		fprintf(stderr, "ERROR: stack is full");
		return -1;
		
	}
	
	*((stk -> data) + (stk -> head)) = a;
	(stk -> head)++;
	return 0;
}

int stack_full(stack* stk){
	
	if ((stk -> head) >= (stk -> size))
		return 1;
		
	return 0;
}

int stack_empty(stack* stk){
	
	if ((stk -> head) <= 0) 
		return 1;
	
	return 0;	
}

long stack_head(stack* stk){
	return (stk -> head);
}

void stack_clear(stack* stk){
	do	
		*((stk -> data) + (stk -> head)) = 0;
		while ((stk -> head)--);
}	
	
void stack_delete(stack* stk){
	
	if (stk -> data == NULL){
		
		errno = EINVAL;
		perror("Stack non initialize");
		abort();
	
	}
	
	free(stk -> data);
	(stk -> data) = NULL;
	(stk -> size) = 0;
	(stk -> head) = 0;
}	

double stack_peek(stack* stk){
	return *((stk -> data) + (stk -> head) - 1);
}
