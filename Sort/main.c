#include <stdio.h>
#include <stdlib.h>
#include "M_Sort.h"

void create_test_file(FILE* test);

void sort_file(FILE* test, FILE* out, FILE* out_statistic, void (*sort) (int* , int , int));

const int MIN_SORT_AMOUNT = 10;

const int MAX_SORT_AMOUNT = 5000;

const int SORT_AMOUNT_STEP = 10;

int main(){
	void (*sort) (int* , int , int) = NULL;
	FILE* out;
	FILE* outs;
	FILE* test = fopen("test.txt", "w");
	out = fopen("out.txt", "w");
	outs = fopen("outs.cvs", "w");
	create_test_file(test);
	rewind(test);
	test = fopen("test.txt", "r");
	
	sort = bubble_sort;
	
	sort_file(test, out, outs, sort); 
	
	rewind(test);
	
	sort = selection_sort;
	
	sort_file(test, out, outs, sort);
	
	rewind(test);

	sort = insert_sort;
	
	sort_file(test, out, outs, sort);
	
	rewind(test);

	n_comparison = 0;
	n_assign = 0;

	sort = merge_sort;
	
	sort_file(test, out, outs, sort);
	
	rewind(test);

	n_comparison = 0;
	n_assign = 0;

	sort = quick_sort;
	
	sort_file(test, out, outs, sort);	
		
	return 0;
	
}

void create_test_file(FILE* test){
	int i = 0, j = 0;
	for (i = MIN_SORT_AMOUNT; i <= MAX_SORT_AMOUNT; i += SORT_AMOUNT_STEP){
		fprintf(test, "\n%d\n", i);
		j = i + 1;
		while (--j) {
			fprintf(test, " %d ", (rand() % 100000));
			if (j % SORT_AMOUNT_STEP == 0) fprintf(test, "\n");
		}
	printf("%d%%\n", i / (MAX_SORT_AMOUNT / 100));
	fflush(stdout);	
	}
	fprintf(test, "\nend\n");
	printf("Creating test file complete\n");
}

void sort_file(FILE* test, FILE* out, FILE* out_statistic, void (*sort) (int* , int , int)){
	int n = 0;
	double i = 0;
	int* a = NULL;
	while (fscanf(test, "%d", &n)) {
		a = (int*) calloc (n , sizeof(int));
		
		while (i < n){
			fscanf(test, "%d", &a[(int) i]);
			++i;
		}
		
		sort(a, 0, n - 1);
		//fprintf(out, "%d\n", n);
		fprintf(out_statistic, "sort %d elements, %ld, %ld\n", n, n_comparison, n_assign);		

		/*while (i < n){
			fprintf(out, " %d ", a[i]);
			if (i % 10 == 0 && i != 0) fprintf(out, "\n");
			++i;
		}
		fprintf(out, "\nend\n");*/
		printf("%lg%%\n", i / (MAX_SORT_AMOUNT / 100));
		free(a);
		a = NULL;
		i = 0;
	}
	printf("Sort complete\n");
	return;
}
