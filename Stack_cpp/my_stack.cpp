#include "my_stack.h"
#include <cstdlib>
#include <cstdio>

#ifdef DEBUG

std::FILE* stack_log;

#endif

Stack::Stack()
{
    size_ = AUTO_START_SIZE;
    data_ = (stack_elem*) calloc (size_,
                                  sizeof(stack_elem));    
    if (data_ == NULL) {
        errno_ = NO_ENOUGH_MEMORY;
        this->dump();
    }

    errno_ = STACK_OK;

    head_ = 0;
    mode_ = EXPANDED;
}

Stack::Stack(unsigned int size)
{
    size_ = size;
    data_ = (stack_elem*) calloc (size_,
                                  sizeof(stack_elem));
    
    if (data_ == NULL) {
        errno_ = NO_ENOUGH_MEMORY;
        this->dump();
    }
    
    errno_ = STACK_OK;

    head_ = 0;
    mode_ = FIXED;
}

Stack::~Stack()
{
    size_ = 0;
    free(data_);

    head_ = 0;
    mode_ = NOT_VALIDETED;
}

int Stack::is_empty()
{
    if (!(this->is_OK())) return -1;

    if (head_ != 0) {
        return true;
    } else {
        return false;
    }
}

int Stack::is_full()
{
    if (!(this->is_OK())) return -1;
    
    if (head_ == size_) {
        return true;
    } else {
        return false;
    }
}

int Stack::push(stack_elem new_elem)
{
    if (!(this->is_OK())) return -1;

    if (this->is_full()) {

        if (mode_ == FIXED) {

            errno_ = NO_ENOUGH_MEMORY;
            this->dump();
            return -1;
        }

        if (mode_ == EXPANDED) {

            if (size_ + AUTO_RESIZE_STEP
                 < MAX_STACK_SIZE) {

                size_ += AUTO_RESIZE_STEP;

            } else {

                errno_ = STACK_CANT_EXPAND;
                this->dump();
                return -1;
            }

            data_ = (stack_elem*) realloc(data_,
                     sizeof(stack_elem) * size_);
            
            if (!(this->is_OK())) return -1;

            data_[head_] = new_elem;
            ++head_;

        }

    } else {

        data_[head_] = new_elem;
        ++head_;

    }

    return 0;
}

stack_elem Stack::pop() 
{
    if (!(this->is_OK())) return -1;

    if (this->is_empty()) {

        errno_ = POP_EMPTY_STACK;
        this->dump();
        return -1;

    }

    --head_;

    return data_[head_ - 1];
}

unsigned int Stack::get_size()
{   
    return size_;
}

int Stack::set_size(unsigned int new_size)
{
    if (!(this->is_OK())) return -1;
    
    data_ = (stack_elem*) realloc(data_, 
            sizeof(stack_elem) * size_);
            
    if (!(this->is_OK())) return -1;

    return 0;
}

unsigned int Stack::get_head()
{
    return head_;
}

bool Stack::is_OK()
{
#ifdef DEBUG

    if (data_ == NULL) {

        errno_ = NOT_DATA_MEMORY;
        this->dump();
        return false;

    }

    if (head_ > size) {

        errno_ = INVAL;
        this->dump();
        return false;

    }

#endif

    return true;
}

int Stack::dump()
{
#ifdef DEBUG

    switch (errno_) {
        using namespace std
        case STACK_OK:
            break;
        case NOT_DATA_MEMORY:
            fprintf(stack_log, "Not data memory");
            break;
        case STACK_CANT_EXPAND:
            fprintf(stack_log, "Size of Stack = %d \n \
                    Stack can't expand", size_);
            break;
        case POP_EMPTY_STACK:
            fprintf(stack_log, "Pop in empty stack");
            break;
        case NO_ENOUGH_MEMORY:
            fprintf(stack_log, "Size of stack = %d \n \
                    No enough memory", size_);
            break;
        case INVAL:
            fprintf(stack_log, "Size of stack = %d \n \
                    Head of stack = %d \n \
                    Data of stack = %p \n", size_, head_,
                    data_);
            break;
        default:
            break;
    }

#endif

    return 0;
}
