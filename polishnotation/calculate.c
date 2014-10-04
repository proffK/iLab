#include "calculate.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
	
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
	if (b == 0){
		printf("ERROR: divide by zero\n");
		exit(0);
	}
        return a / b;
} 

