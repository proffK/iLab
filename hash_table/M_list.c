#include <stdio.h>
#include <stdlib.h>
#include "M_list.h"
#include <string.h>
#include <errno.h>

const char* LOG_FILE_NAME = "list_log.txt";

list* list_create(void){
	
	list* new_list = (list*) calloc (1, sizeof(list));
	
	if (new_list == NULL) {
		
		errno = ENOMEM;
		abort();
		
	}
	
	new_list -> head = NULL;
	new_list -> tail = NULL;
	
	return new_list;
} 

int list_delete(list* deleted_list){
	
	if (deleted_list != NULL) {
		
		free(deleted_list);
		deleted_list = NULL;
		return 0;
		
	}
	return -1;
}
	


list_elem* add_elem(list* lst, elem_t new_elem){
	
	if (list_valide(lst)) {
		
	list_elem* new_list_elem = (list_elem*) calloc (1, sizeof(list_elem));
	
	if (new_list_elem == NULL) {
               
                errno = ENOMEM;
                abort();
               
    }
	
	new_list_elem -> data = new_elem;
	
	if (lst -> size != 0) lst -> head -> next = new_list_elem;
	
	new_list_elem -> prev = lst -> head;
	lst -> head = new_list_elem;
	
	
	if (lst -> size == 0) {
		
		lst -> tail = new_list_elem;
		
	}
	
	++(lst -> size);
	
	return new_list_elem;	
	
	}
	
	return 0;
}

list_elem* insert_elem(list* lst, elem_t new_elem, list_elem* next_elem){
							
	if (list_valide(lst)) {
	
	list_elem* new_list_elem = (list_elem*) calloc (1, sizeof(list_elem));
		
	if (new_list_elem == NULL) {
		
		errno = ENOMEM;
		abort();
		
	}
	
	if (next_elem -> prev == NULL) {
		
		new_list_elem -> data = new_elem;
		next_elem -> prev = new_list_elem;
		new_list_elem -> next = next_elem;
		lst -> tail = new_list_elem;
		++(lst -> size);
		
		return new_list_elem;
	}
	
	new_list_elem -> data = new_elem;
	new_list_elem -> prev = next_elem -> prev;
	next_elem -> prev -> next = new_list_elem;
	next_elem -> prev = new_list_elem;
	new_list_elem -> next = next_elem;
	lst -> head = new_list_elem;
	++(lst -> size);
	
	return new_list_elem;	
	
	}
	
	return 0;
	
}

int delete_elem(list* lst, list_elem* deleted_elem){
	
	if (list_valide(lst) && lst -> size != 0) {
	
	if (deleted_elem -> next == NULL) {
		if (deleted_elem -> prev == NULL) {
			
			lst -> head = NULL;
			lst -> tail = NULL;
			--lst -> size;
			
			free(deleted_elem);
		}
		
		else {
			
			lst -> head = deleted_elem -> prev;
			--lst -> size;
			
			deleted_elem -> prev -> next = NULL;
			deleted_elem -> prev = NULL;
			
			free(deleted_elem);
		}
	}
	else if (deleted_elem -> prev == NULL) {
					
		lst -> tail = deleted_elem -> next;
		--lst -> size;
		
		deleted_elem -> next -> prev = NULL;
		deleted_elem -> next = NULL;
		free(deleted_elem);
	}
	else {
			
		--lst -> size;
		
		deleted_elem -> next -> prev = deleted_elem -> prev;
		deleted_elem -> prev -> next = deleted_elem -> next;
		deleted_elem -> next = NULL;
		deleted_elem -> prev = NULL;
		free(deleted_elem);
		
	}
	
	return 0;
	
	}
	
	return 1;	
}
	

list_elem* find_elem(list* lst, elem_t found_elem, int (*cmp) (elem_t, elem_t)\
					  , list_elem* current_elem, int direction){
	
	if (list_valide(lst)) {
						
	int i = 0;
	
	if (direction > 0) {
	
		for (i = 0; i < lst -> size; ++i){
		
			if (!(cmp(current_elem -> data, found_elem))){
				
				return current_elem;
				
			}
			
			if (current_elem -> next == NULL) {
				
				current_elem = lst -> tail;
			
			}
			else{
				
				current_elem = current_elem -> next;
			
			}
		}
	}
	
	if (direction < 0) {
	
		for (i = 0; i < lst -> size; ++i){
		
			if (!(cmp(current_elem -> data, found_elem)))
				return current_elem;
			
			if (current_elem -> prev == NULL) {
				current_elem = lst -> head;
			}
			
			current_elem = current_elem -> prev;
			
		}
	}
	
	}
	
	return 0;
}	
	
int list_valide(list* lst){
	
#ifndef LIST_DEBUG

return 1;

#endif
	
	const int OK = 1;
	const int INVAL = 0;
	int i = 0;
	
	if (lst == NULL) {
		
		errno = ENOMEM;
		return INVAL;
		
	}
	
	if (lst -> size == 0) {
		
		if (lst -> tail == NULL && lst -> head == NULL)
			return OK;
			
		else {
			
			errno = EINVAL;
			list_dump(lst);
			return INVAL;
			
		}
	}
	
	if (lst -> size > 0) {
		
		list_elem* current_elem = lst -> tail;
		
		if (lst -> head == NULL || lst -> tail == NULL){
			
			errno = EINVAL;
			list_dump(lst);
			return INVAL;
			
		}
		
		for (i = 0; i < lst -> size - 1; ++i) {
			
			if (current_elem -> next == NULL) {
				
				errno = EINVAL;
				list_dump(lst);
				return INVAL;
				
			}
			
			if (current_elem -> next -> prev != current_elem) {
				
				errno = EINVAL;
				list_dump(lst);
				return INVAL;
				
			}
			
			current_elem = current_elem -> next;
			
		}
		
		if (current_elem != lst -> head) {
				
				errno = EINVAL;
				list_dump(lst);
				return INVAL;
				
		}
		
		while(i--) {
			
			if (current_elem -> prev == NULL) {
				
				errno = EINVAL;
				list_dump(lst);
				return INVAL;
				
			}
			
			if (current_elem -> prev -> next != current_elem) {
				
				errno = EINVAL;
				list_dump(lst);
				return INVAL;
				
			}
			
			current_elem = current_elem -> prev;
			
		}
		
		if (current_elem != lst -> tail) {
				
				errno = EINVAL;
				list_dump(lst);
				return INVAL;
				
		}
		
		return OK;
	}
	
	return INVAL;
}
			
int list_dump(list* lst){
	
	FILE* log = fopen(LOG_FILE_NAME, "a");
	int i = 0;
	
	if (lst == NULL) {
		
		fprintf(log, "list not exist");
		fclose(log);
		return 0;
		
	}
	
	if (lst -> size < 0) {
		
		fprintf(log, "invalid value list size - %d\n", lst -> size);
		fclose(log);
		return 0;
	
	}
	
	if (lst -> size == 0) {
		
		fprintf(log, "\nlist adress = %p\nlist head = %p\nlist tail = %p\nlist size = %d",\
				lst,lst -> head, lst -> tail, lst -> size);
		fclose(log);
		return 0;
	
	}
	
	if (lst -> size > 0) {
		
		list_elem* current_elem = lst -> tail; 
		
		fprintf(log, "list adress = %p\nlist head = %p\nlist tail = %p\nlist size = %d",\
				lst,lst -> head, lst -> tail, lst -> size);
		
		if (lst -> tail != NULL) {
		
			fprintf(log, "\n  element adress   |  prev element adress   |  element \
| next element adress\n\n");
				
			for (i = 0; i < lst -> size; ++i) {
			
				if (current_elem) {
				
					fprintf(log, "    %p              %p       ", current_elem, \
					current_elem -> prev);
					PRINTF_ELEM_T(log, current_elem -> data);
					fprintf(log, "        %p    \n", current_elem -> next);
					current_elem = current_elem -> next;
				
				}
			}
			 	
		}
		
		fclose(log);
		return 0;
	
	}
	
	return 0;
}

list_elem* list_head(list* lst){
	
	if (list_valide(lst)) {
		return lst -> head;
	}
	
	return 0;
}

list_elem* list_tail(list* lst){
	
	if (list_valide(lst)) {
		return lst -> tail;
	}
	
	return 0;
}

void clear_log(void){
	
	FILE* log = fopen("list_log.txt", "w");
	
	fclose(log);
	
}
