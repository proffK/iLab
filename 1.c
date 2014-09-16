#include <stdio.h>

float calculate(float, float, char);

int main(){
	char a = 0;
	float  x = 0, y = 0;	
	scanf ("%f %c %f", &x, &a, &y);	

	printf("= %g\n", calculate(x, y, a));
	return 0;
}

float calculate(float x, float y, char a){	
	switch (a){
		case '+':
		return  x + y;
		break;
		case '*':
		return x * y;
		break;
		case '/':
		return x / y;
		break;
		case '-':
		return x - y;
		break;
	}
}

