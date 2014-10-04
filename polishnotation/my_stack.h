#ifndef my_stack
#define my_stack

typedef struct {
	double* data;
	long head;
	int size;
} stack;

stack* stack_create(int Size,stack st);

double pop(stack* stk);

int push(stack* stk, double a);

int stack_full(stack* stk);

int stack_empty(stack* stk);

long stack_head(stack* stk);

void stack_clear(stack* stk);

void stack_delete(stack* stk);

double float_reader(char* str, int start, double* target);
#endif
