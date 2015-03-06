#ifndef m_stack
#define m_stack
 
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
stack* stack_create(int Size);

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
int stack_is_full(stack* stk);


/*! This function check stack 
 * \return 0 if stack not empty, 1 - if stack empty
 */
int stack_is_empty(stack* stk);

/*! This function return head of stack
 */
long stack_head(stack* stk);

/*! This function clear stack
 */
int stack_clear(stack* stk);

/*! This function delete stack and free memory
 */
int stack_delete(stack* stk);

/*! This function read top element of stack 
 */
double stack_peek(stack* stk);

/*! This function chek stack
 * \return 1 if stack valide, 0 if stack invalide
 */
int stack_is_valide(stack* stk);

/*! This function change stack size, but save all elements
 * \param stk - changing stack
 * \param new_size - new size stack
 * \return number of copied element, 0 if operation impossible.
 */
stack* stack_resize(stack* stk, int new_size);

/*! This function send error messenge in log file stack_log.txt
 */
int stack_dump(stack* stk,int stack_err);

#endif

