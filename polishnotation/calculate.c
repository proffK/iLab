#ifndef my_stack
#define my_stack

#include <stdio.h>
#include "calculate.h"
#include <math.h>
#include <stdlib.h>
#include <errno.h>
	
float calculate(float x, float y, char a){	
	switch (a){
		case '+':
		return add(x, y);
		break;
		case '*':
		return mul(x, y);
		break;
		case '/':
		return divi(x, y);
		break;
		case '-':
		return sub(x, y);
		break;
		case '^':
		return pow(x, y);
		break;
		case 'l':
		return logarithm(x, y);
		break;
	}
	return 0;
}

float add(float a, float b){
	return a + b;
}

float sub(float a, float b){
        return a - b;
}

float mul(float a, float b){
        return a * b;
}

float divi(float a, float b){
	if (b == 0) {
		errno = EINVAL;
		perror("ERROR: divide by zero\n");
		return 0;
	}
	
        return a / b;
} 

float logarithm(float a, float b){
	if (a <= 0 || b <= 0 || b == 1) {
		errno = EINVAL;
		perror("ERROR: invalid arg in logarithm\n");
		return 0;
	}

	return (log(a) / log(b));
}
#endif
