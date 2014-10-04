#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "my_stack.h"
#include "calculate.h"

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
	
	stack st;
	
	stack* stk = stack_create(MAXLINE, st);
	
	fgets(buf, MAXLINE, stdin);

	while(buf[i] != '\n'){

		switch (buf[i]) {
			  case '+': case '*': case '/':
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
	
	printf("%lg", pop(stk));
	stack_delete(stk);
	return 0;
}

double float_reader(char* str, int start, double* target){
	int i = start, a = 0, len = 0;
	int sign = 1;
	double result = 0;
	
	if 	(str[start] == '-') {
		sign = -1;
		start++;
	}
	
	while(('0' <= str[i] && str[i] <= '9') || str[i] == '.') i++;
	
	len = i;
	i--;
	
	while(('0' <= str[i] && str[i] <= '9') || str[i] == '.') {
		if (str[i] == '.') result *= pow(10, -a);
		
		if (str[i] != '.'){
			result = result + (str[i] - '0') * pow(10, a);
		}
		i--;
		a++;
	}
	
	*target = result * sign;
	
	return len;
	
}
