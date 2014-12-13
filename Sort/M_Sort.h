#ifndef M_SORT
#define M_SORT

long n_comparison;

long n_assign; 

void bubble_sort(int a[], int begin, int end);

void selection_sort(int a[], int begin, int end); 

void insert_sort(int a[], int begin, int end);

void merge_sort(int a[], int begin, int end);

void merge(int a[], int begin, int end, int m);

void quick_sort(int a[], int begin, int end);

void comb_sort(int a[], int begin, int end);

void swap(int* a, int* b);

#endif
