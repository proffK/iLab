#ifndef my_stack
#define my_stack

/*! This struct realise stack
 * \param data - pointer of free memory
 * \param head - number of elements in stack
 * \param size - max number of elements in stack
 * */
typedef struct {
	double* data;
	long head;
	int size;
} stack;

/*! This function creates stack
 * \param Size - size new stack
 * \param st - uninitialization stack
 * \return pointer of st
 */ 
stack* stack_create(int Size,stack st);

/*! This function get top element from stack and decrement head
 * \return top element
 */
double pop(stack* stk);

/*! This function push new element from stack and increment head
 * \return 0 - if operation complete 1 - if stack full
 */
int push(stack* stk, double a);

/*! This function check stack 
 * \return 0 if stack not full, 1 - if stack full
 */
int stack_full(stack* stk);


/*! This function check stack 
 * \return 0 if stack not empty, 1 - if stack empty
 */
int stack_empty(stack* stk);

/*! This function return head of stack
 */
long stack_head(stack* stk);

/*! This function clear stack
 */
void stack_clear(stack* stk);

/*! This function delete stack and free memory
 */
void stack_delete(stack* stk);

/*! This function read top element of stack 
 */
double stack_peek(stack* stk);
#endif
