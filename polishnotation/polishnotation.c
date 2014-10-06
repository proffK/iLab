#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "my_stack.h"
#include "calculate.h"
#include "errno.h"

#define MAXLINE  100

/*! This function convert part of string in double
 * \param str - input string
 * \param start - number of first digit or sign
 * \param target - pointer of output double
 * \return number first non-digital character
 */  
double float_reader(char* str, int start, double* target);

int main(){
    
	char buf[MAXLINE] = "";
	double num1 = 0,num2 = 0, num = 0;
	int i = 0;
	stack* stk = stack_create(MAXLINE);
	
	fgets(buf, MAXLINE, stdin);

	while(buf[i] != '\n'){

		switch (buf[i]) {
			case '+': case '*': case '/': case '^':
			  
				assert((stk -> head) >= 2);
				
				num1 = pop(stk);
				num2 = pop(stk);
				num = calculate(num2, num1, buf[i]);
				push(stk, num);
				break;
			case '-':
				if (buf[i + 1] == ' '){
					
					assert((stk -> head) >= 2);
					
					num1 = pop(stk);
					num2 = pop(stk);
					num = calculate(num2, num1, buf[i]);
					push(stk, num);
				}
				else {  
					i = float_reader(buf, i, &num);
					push(stk, num);
				}
				break;
			case '1': case '2': case '3': case '4': case '5': \
			case '6': case '7': case '8': case '9': case '0':
				i = float_reader(buf, i, &num);
				push(stk, num);
				break;
		}
		++i;
	}
	
	if ((stk -> head) != 1){
	errno = EINVAL;
	perror("Incorrect input expression");
	abort();
	}
		
	printf("%lg\n", pop(stk));
	stack_delete(stk);
	return 0;
}

double float_reader(char* str, int start, double* target){
	int i = 0, a = 0, b = 0;
	int sign = 1, sign_a = 1, sign_b = 0;
	double result = 0;
	
	if 	(str[start] == '-') {
		sign = -1;
		start++;
	}
	if 	(str[start] == '+') {
		sign = 1;
		start++;
	}
	
	i = start;

	while (('0' <= str[i] && str[i] <= '9') || str[i] == '.'){
		
		if ('0' <= str[i] && str[i] <= '9') {
			b += sign_b;
			result = result * pow(10, a) + (str[i] - '0') * pow(10, b);
			a += sign_a;	
		}
		
		if (str[i] == '.') {
			a = 0;
			sign_a = 0;
			sign_b = -1;
		}
		
		i++;
	}

	*target = result * sign;
	
	return i;
	
}
