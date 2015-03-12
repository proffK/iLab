#ifndef _my_stack_t_
#define _my_stack_t_
#include <climits>
#include <cstdlib>

#define DEBUG

#ifdef DEBUG

#include <fstream>

#endif

template <typename stack_elem>

class pk_Stack
{
public:

    pk_Stack();
    pk_Stack(unsigned int size);
    ~pk_Stack();
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
    
    #ifdef DEBUG

    const char* LOG_FILE_NAME = "stack_log.txt";
    std::ofstream stack_log;

    #endif

};


template <typename stack_elem>
pk_Stack<stack_elem>::pk_Stack()
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

template <typename stack_elem>
pk_Stack<stack_elem>::pk_Stack(unsigned int size)
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

template <typename stack_elem>
pk_Stack<stack_elem>::~pk_Stack()
{
    size_ = 0;
    free(data_);

    head_ = 0;
    mode_ = NOT_VALIDETED;
}

template <typename stack_elem>
int pk_Stack<stack_elem>::is_empty()
{
    if (!(this->is_OK())) return -1;

    if (head_ == 0) {
        return true;
    } else {
        return false;
    }
}

template <typename stack_elem>
int pk_Stack<stack_elem>::is_full()
{
    if (!(this->is_OK())) return -1;
    
    if (head_ == size_) {
        return true;
    } else {
        return false;
    }
}

template <typename stack_elem>
int pk_Stack<stack_elem>::push(stack_elem new_elem)
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

template <typename stack_elem>
stack_elem pk_Stack<stack_elem>::pop() 
{
    if (!(this->is_OK())) return -1;

    if (this->is_empty()) {

        errno_ = POP_EMPTY_STACK;
        this->dump();
        return -1;

    }
    --head_;
    return data_[head_];
}

template <typename stack_elem>
unsigned int pk_Stack<stack_elem>::get_size()
{   
    return size_;
}

template <typename stack_elem>
int pk_Stack<stack_elem>::set_size(unsigned int new_size)
{
    if (!(this->is_OK())) return -1;
    
    data_ = (stack_elem*) realloc(data_, 
            sizeof(stack_elem) * size_);
            
    if (!(this->is_OK())) return -1;

    return 0;
}

template <typename stack_elem>
unsigned int pk_Stack<stack_elem>::get_head()
{
    return head_;
}

template <typename stack_elem>
bool pk_Stack<stack_elem>::is_OK()
{
#ifdef DEBUG

    if (data_ == NULL) {

        errno_ = NOT_DATA_MEMORY;
        this->dump();
        return false;

    }

    if (head_ > size_) {

        errno_ = INVAL;
        this->dump();
        return false;

    }

#endif

    return true;
}

template <typename stack_elem>
int pk_Stack<stack_elem>::dump()
{
#ifdef DEBUG

    stack_log.open(LOG_FILE_NAME);

    switch (errno_) {
        using namespace std;
        case STACK_OK:
            break;
        case NOT_DATA_MEMORY:
            stack_log << "Not data memory" << endl;
            break;
        case STACK_CANT_EXPAND:
            stack_log << "Size of Stack = " << size_ << endl
                    << "Stack can't expand" << endl;
            break;
        case POP_EMPTY_STACK:
            stack_log << "Pop in empty stack" << endl;
            break;
        case NO_ENOUGH_MEMORY:
            stack_log << "Size of Stack = " << size_ << endl
                    << "No enough memory" << endl;
            break;
        case INVAL:
            stack_log << "Size of stack = " << size_ << endl
                    << "Head of stack = " << head_ << endl
                    << "Data of stack = " << data_;
            break;
        default:
            break;
    }

    stack_log.close();

#endif

    return 0;
}

#endif
