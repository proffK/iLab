#include <stdio.h>
#include <stdlib.h>


float calculate(float, float, char);
float add(float, float);
float sub(float, float);
float mul(float, float);
float divi(float, float);

int main(){
	char a = 0;
	float  x = 0, y = 0;
	printf("Input Two mumbers and operation at format:\nNUM OP NUM\n");	
	scanf ("%f %c %f", &x, &a, &y);	

	printf("= %g\n", calculate(x, y, a));
	return 0;
}

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
	}
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



