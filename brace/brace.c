#include <stdio.h>
#include <stdlib.h>
#include "my_stack.h"

const int STACK_SIZE = 100;

int main(){
	stack* stk = stack_create(STACK_SIZE);
	int c = 0;
	while ((c = getchar()) != '\n'){
		switch (c){
			case '(':case'{':case'[':
				push(stk, c);
				break;
			case ')':case'}':case']':
				if (stack_is_empty(stk) \
				|| ((c -= pop(stk)) != 1 && c != 2)){
					printf("invalide\n");
					return 0;
				}
				break;
		}
	}
	if (stack_is_empty(stk))
		printf("valide\n");
	else 
		printf("invalide\n");
	return 0;
}
