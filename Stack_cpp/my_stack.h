#ifndef _my_stack_
#define _my_stack_
#include <climits>

#ifdef DEBUG

const char* LOG_FILE_NAME = "stack_log.txt"

#endif

typedef double stack_elem;

const unsigned int MAX_STACK_SIZE = UINT_MAX;

const unsigned int AUTO_START_SIZE = 100;

const unsigned int AUTO_RESIZE_STEP = 10;

enum stack_modes
{
    NOT_VALIDETED = 0,
    FIXED = 1,
    EXPANDED = 2

};

enum stack_error
{
    STACK_OK = 0,
    NOT_DATA_MEMORY = 1,
    STACK_CANT_EXPAND = 2,
    POP_EMPTY_STACK = 3,
    NO_ENOUGH_MEMORY = 4,
    INVAL = 5
};

class Stack
{
public:

    Stack();
    Stack(unsigned int size);
    ~Stack();
    int is_empty();
    int is_full();
    int push(stack_elem new_elem);
    stack_elem pop();
    unsigned int get_size();
    unsigned int get_head();
    int set_size(unsigned int new_size);
    bool is_OK();

private:

    unsigned int size_;
    stack_elem* data_;
    unsigned int head_;
    int mode_;
    int errno_;
    int dump();

};

#endif
