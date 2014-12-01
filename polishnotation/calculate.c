#include <stdio.h>
#include "calculate.h"
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
	
double calculate(double a, double b, char operation){	
	switch (operation){
		case '+':
		return add(a, b);
		break;
		case '*':
		return mul(a, b);
		break;
		case '/':
		return Div(a, b);
		break;
		case '-':
		return sub(a, b);
		break;
		case '^':
		return pow(a, b);
		break;
		case 'l':
		return logarithm(a, b);
		break;
		
		default:
		errno = EINVAL;
		return -1;
	}
	return 0;
}

double add(double a, double b){
	return a + b;
}

double sub(double a, double b){
    return a - b;
}

double mul(double a, double b){
    return a * b;
}

double Div(double a, double b){
	if (b == 0) {
		errno = EINVAL;
		assert ("dil 0" == 0);
	}
	
        return a / b;
} 

double logarithm(double a, double b){
	if (a <= 0 || b <= 0 || b == 1) {
		errno = EINVAL;
		return 0;
	}

	return (log(a) / log(b));
}
