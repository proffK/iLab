#include "M_Sort.h"
#include <stdio.h>
#include <stdlib.h>

void bubble_sort(int a[], int begin, int end){
	int i = 0, j = 0;
	n_comparison = 0;
	n_assign = 0;
	for (i = 0; i < end - begin; ++i){
		for (j = begin; j < end - i; ++j) {
			 if (a[j] > a[j + 1]){
				 swap(a + j, a + j + 1);
				 ++n_comparison;
			 }
		}
	}
}
void selection_sort(int a[], int begin, int end){
	int i = 0, j = 0, min = 0;
	n_comparison = 0;
	n_assign = 0;
	for (i = 0; i < end - begin; ++i){
		min = begin + i;
		for (j = begin + i; j <= end; ++j) {
			 if (a[j] < a[min]){
				 swap(a + j, a + min);
				 ++n_comparison;
			 }
		}
	}
	
} 

void insert_sort(int a[], int begin, int end){
	int i = 0, j = 0;
	n_comparison = 0;
	n_assign = 0;
	for (i = 1; i <= end - begin; ++i){
		for (j = i; j >= begin && a[j] < a[j-1]; --j) {
			swap(a + j, a + j - 1);
			++n_comparison;
		}
	}
}

void merge_sort(int a[], int begin, int end){
	int med = 0;
	
	if (end > begin){
		++n_comparison;
		med = (begin + end) / 2;
		++n_assign;
		merge_sort(a, begin, med);
		merge_sort(a, med + 1, end);
		merge(a, begin, end, med);
	}
}

void quick_sort(int a[], int begin, int end){
	int x = 0, i = 0, j = 0;
	x = a[(end + begin) / 2];
	i = begin;
	j = end;
	n_assign += 3;
	
	do {
		
		while (a[i] < x){
			++i;
			++n_assign;
			++n_comparison;
		}
	
		while (a[j] > x){
			--j;
			++n_assign;
			++n_comparison;
		}
	
		if (i <= j) {
			swap(a + i, a + j);
			++i;
			--j;
			n_assign += 2;
			++n_comparison;
		}
		++n_comparison;
	} while (j >= i);
	if (j > begin) {
		++n_comparison;
		quick_sort(a, begin, j);
	}
	if (i < end){
		++n_comparison;
		quick_sort(a, i, end);
	}	
}

void comb_sort(int a[], int begin, int end){
}

void swap(int* a, int* b){
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
	n_assign += 3;
}
	
void merge(int a[], int begin, int end, int m){
	int pos1 = begin;
	int pos2 = m + 1;
	int pos3 = 0;
	n_assign += 3;
	
	int* temp = (int*) calloc (end - begin + 1, sizeof(int));
	
	while (pos1 <= m && pos2 <= end) {
		n_comparison += 2;
		if (a[pos1] < a[pos2]) {
			temp[pos3++] = a[pos1++];
			++n_assign;
		}
		if (a[pos2] <= a[pos1]) {
			temp[pos3++] = a[pos2++];
			++n_assign;
		}
	}
	
	while (pos2 <= end) {
		temp[pos3++] = a[pos2++];
		++n_assign;
	}
	
	while (pos1 <= m) {
		temp[pos3++] = a[pos1++];
		++n_assign;
	}
	
	for (pos3 = 0; pos3 < end - begin + 1; pos3++){
		a[begin + pos3] = temp[pos3];
    	++n_assign;
	}
	
	free(temp);	
		
}
	
