#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct elem {
	/* This struct describes every number or character
	 * if elem.type == 1 this element is number
	 * if elem.type == -1 this element is operation*/
	float num;
	int type;
	char oper;
};

int sgetline(char line[], int maxline);

int elem_parsing(char str[], int length, struct elem a[]);

/*This function converted string str to array of elem a[]*/

void elem_arrayshift(struct elem a[], int n, int l, int step);

/*This function shift step array a[] begins of number n*/

void elem_arrayrevers(struct elem a[], int size);

/*This function revers array a[]*/

int elem_search(struct elem a[], int size);

/*This function search combination of type : 1 1 -1*/

float calculate(float , float , char );

float add(float, float);

float sub(float, float);

float mul(float, float);

float divi(float, float);


int main(){
	struct elem formule[100];
	int i = 0, l = 0, size = 0, sh = 0;
	char s[1000] = {};
	
	for (i = 0; i <= 100; ++i){
		formule[i].num = 0;
		formule[i].type = 0;
		formule[i].oper = '0';
	}
	printf("Input expression in Revers polish notation and press ENTER:\n(enable character +, -\
, *, /, ^)\n");
	l = sgetline(s , 1000);
	size = elem_parsing(s ,l, formule);
	elem_arrayrevers(formule, size); /*Input data in array of elem formule*/
	while (formule[1].type != 0){
		sh = elem_search(formule, size); /*search necessary combination to calculate it*/
		formule[sh].num = calculate(formule[sh].num, formule[sh + 1].num, formule[sh + 2].oper);
		elem_arrayshift(formule, sh + 1, size, 2);
	}
			printf("Result: %g\n", formule[0].num);
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

int sgetline(char s[], int lim){
	int c, i;
	
	for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i){
		s[i] = c;
	}
	if (c=='\n'){
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	++i;
	if (s[0] == '\0')
		i = 0;
	return i;
}

int elem_parsing(char str[], int length, struct elem a[]){
	int i = 0, j = 0, s = 0;
	
	for (i = 0; i <= length; ++i){
		if (str[length - i] == ' '){
			j = 0;
			s++;
		}
		if (str[length - i] == '+' || str[length - i] == '-' \
			|| str[length - i] == '/' || str[length - i] == '*' \
			|| str[length - i] == '^'){
			a[s].type = -1;
			a[s].oper = str[length - i];
			j = 0;
		}
		else if ((str[length - i] <= '9' && str[length - i] >= '0') || str[length - i] == '.'){
			if (str[length - i] == '.') {
				a[s].num = a[s].num * pow(10, j * -1);
				j = 0;
			} 
			if (str[length - i] <= '9' && str[length - i] >= '0'){
				a[s].num += (str[length - i] - '0') * pow(10, j);
				a[s].type = 1;
				j++;
			}
		}
	}
	
	return s + 1;
}
					
void elem_arrayrevers(struct elem a[], int size){
	int i = 0;
	struct elem temp = {0 ,0 ,0};
	for (i = 0; i <= (size / 2) - 1; ++i){
		temp = a[i];
		a[i] = a[size - i -1];
		a[size - i -1] = temp;
	}
}

void elem_arrayshift(struct elem a[], int n, int l , int step){
	int i = 0;
	
	for (i = n; i <= l; ++i){
		a[i] = a[i + step];
	}
}

int elem_search(struct elem a[], int size){
	int i = 0;
	for (i = 0; i < size; ++i){
		if (a[i].type == 1 && a[i + 1].type == 1 && a[i + 2].type == -1) return i;
	}
	return 1;
}
		
