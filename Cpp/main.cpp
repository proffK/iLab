#include <iostream>
#include "pk_int.h"

int main()
{
   pk_int num1(5);
   pk_int num2(18);
   pk_int num3;

   num3 = num1 + num2;

   std::cout << num3.dump() << std::endl;
   return 0;
}
