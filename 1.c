#include <stdio.h>

int main(int argc, const char* argv[]){
	char a = 0;
	int  x = 0, y = 0;	
	sscanf(argv[1], "%d", &x);
	sscanf(argv[2], "%c", &a);
	sscanf(argv[3], "%d", &y);
	
	switch (a){
		case '+':
		printf("%d\n", x + y);
		break;
		case '*':
		printf("%d\n", x * y);
		break;
		case '/':
		printf("%d\n", x / y);
		break;
		case '-':
		printf("%d\n", x - y);
		break;
	}
	
	return 0;
}
