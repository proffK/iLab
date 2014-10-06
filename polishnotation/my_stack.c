#include "my_stack.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>
	
stack* stack_create(int Size){
	stack* new_stack = (stack*) calloc (1, sizeof(stack*));
	
	if (new_stack == 0) {
		
		errno = ENOMEM;
		perror("Error in function stack_create: no memory for stack\n");
		abort();
		
	}
	
	(new_stack -> size) = Size;
	(new_stack -> data) = (double*) calloc (Size, sizeof(double*));
	
	if ((new_stack -> data) == 0) {
		
		errno = ENOMEM;
		perror("Error in function stack_create: no memory for data of stack\n");
		abort();
	
	}
	
	(new_stack -> head) = -1;
	return new_stack;
}

double pop(stack* stk){
	
	assert(stack_is_valide(stk));
	
	if (stack_is_empty(stk)){
		
		errno = EACCES;
		perror("ERROR: stack is empty\n");
		return -1;
		
	}
	
	(stk -> head)--;
	return ((stk -> data)[stk -> head + 1]);
}

int push(stack* stk, double a){
	
	assert(stack_is_valide(stk));
	
	if (stack_is_full(stk)){
		
		errno = EACCES;
		perror("ERROR: stack is full\n");
		return -1;
		
	}
	
	(stk -> data)[stk -> head + 1] = a;
	(stk -> head)++;
	return 0;
}

int stack_is_full(stack* stk){
	
	assert(stack_is_valide(stk));
	
	if ((stk -> head + 2) == (stk -> size))
		return 1;
		
	return 0;
}

int stack_is_empty(stack* stk){
	
	assert(stack_is_valide(stk));
	
	if ((stk -> head) == -1) 
		return 1;
	
	return 0;	
}

long stack_head(stack* stk){
	
	assert(stack_is_valide(stk));
	
	return (stk -> head);

}

void stack_clear(stack* stk){
	
	assert(stack_is_valide(stk));
	
	do	
		*((stk -> data) + (stk -> head)) = 0;
	while (-1 == --(stk -> head));
}	
	
void stack_delete(stack* stk){
	
	assert(stack_is_valide(stk));
	
	free(stk -> data);
	(stk -> data) = NULL;
	(stk -> size) = 0;
	(stk -> head) = 0;
}	

double stack_peek(stack* stk){
	
	assert(stack_is_valide(stk));
	
	return *((stk -> data) + (stk -> head) - 1);

}

int stack_is_valide(stack* stk){

	if (!(stk -> size - 1 >= stk -> head && stk -> head >= -1)){
		errno = EINVAL;
		perror("invalid head value\n");
		return 0;
	}
	
	if ((stk -> data) == 0) {
		
		errno = EINVAL;
		perror("invalide data adres\n");
		return 0;
	}
	
	return 1;
}
