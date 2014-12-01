#include <stdio.h>
#include <stdlib.h>
#include "M_hash.h"
#include <errno.h>
#include <string.h>

const char* HASH_LOG_FILE_NAME = "hash_log.txt";

hash_table* hash_table_create(int size){
	
	int i = 0;
	hash_table* new_table = (hash_table*) calloc (1, sizeof(hash_table));
	
	if (new_table == NULL) {
		
		errno = ENOMEM;
		abort();
		
	}
	
	new_table -> size = size;
	new_table -> data = (list**) calloc (size, sizeof(list*));
	
	if (new_table -> data == NULL) {
		
		errno = ENOMEM;
		abort();
		
	}
	
	for (i = 0; i < size; ++i){
		
		new_table -> data[i] = list_create();
		
	}
	
	new_table -> number_elem = 0;
	
	if (hash_table_valide(new_table)) return new_table;
	
}
///###########################################################
int hash_table_add(hash_table* table, elem_t elem,unsigned  int (*hash_gen) (elem_t*)){
	
	int number_list = 0;
	
	if (hash_table_valide(table)) {
	
	number_list = hash_gen(&elem) % (table -> size);
		
	if (add_elem(table -> data[number_list], elem)){
		
		++table -> number_elem;
		return number_list;
	
	}
	
	}		
	
	return -1;
	
}
///###########################################################
int hash_table_valide(hash_table* table){
	
	#ifndef DEBUG_HASH

	return 1;

	#endif

	
	const int OK = 1;
	const int INVAL = 0;
	int i = 0;
	
	if (table == NULL) {
		
		FILE* log = fopen(HASH_LOG_FILE_NAME, "w");
		fprintf(log, "\nHash table not exist");
		fclose(log);
		return INVAL;
	
	}
	
	if (table -> data == NULL) {
		
		FILE* log = fopen(HASH_LOG_FILE_NAME, "w");
		fprintf(log, "\nHash table data not exist");
		fclose(log);
		return INVAL;
	
	}
	
	if (table -> size <= 0) {
		
		FILE* log = fopen(HASH_LOG_FILE_NAME, "w");
		fprintf(log, "\nHash table size incorrect - %d", table -> size);
		fclose(log);
		return INVAL;
		
	}
	
	for(i = 0; i < table -> size; ++i){
		
		if (!(list_valide(table -> data[i]))){
			
			errno = EINVAL;
			hash_table_dump(table);
			return INVAL;
		
		}
		
	}
	
	return OK;
}
///###########################################################
int hash_table_dump(hash_table* table){
	int i = 0;
	
	for(i = 0; i < table -> size; ++i){
		
		if ((list_valide(table -> data[i]))){
			FILE* file = fopen("list_log.txt", "a");
			fprintf(file, "\n%d\n", i);
			fclose(file);
			list_dump(table -> data[i]);
		
		}
		
	}
	
	return 0;
}
///###########################################################
int hash_table_delete(hash_table* table){
	
	int i = 0;
	
	if (hash_table_valide(table)){
		
		for (i = 0; i < table -> size; ++i){
			
			list_delete(table -> data[i]);
			
		}
		
		free(table -> data);
		table -> data = NULL;
		free(table);
		table = NULL;
		
	}
	
}
///###########################################################

list_elem* hash_table_find(hash_table* table,unsigned  int (*hash_gen) (elem_t*), elem_t found_elem){
	
	if (hash_table_valide(table)) {
		
		list_elem* current_elem = 0;		
		int current_list = hash_gen(&found_elem) % table -> size;
		
		current_elem = find_elem(table -> data[current_list], found_elem, strcmp,\
									list_tail(table -> data[current_list]), L_HEAD);
									
		return current_elem;
		
	}

	return 0;
	
}
