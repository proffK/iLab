#include "my_stack_t.cpp"

#include <iostream>

int main(){

    pk_Stack<int> stk;

    stk.push(10);
        std::cout << stk.get_head() << std::endl; 
    stk.push(21);
        std::cout << stk.get_head() << std::endl; 
    stk.push(43);
        std::cout << stk.get_head() << std::endl; 

    int i = stk.pop();
    int j = stk.pop();
    int k = stk.pop();

    std::cout << i << std::endl << j << std::endl << k;
        
    //std::cout << stk.get_head() << ' ' << stk.pop() << std::endl << stk.get_head()
    //          << ' ' << stk.pop() << std::endl << stk.get_head() << ' ' << stk.pop();

    std::cout << "\n33" << "22" << "11";

    return 0;

}
