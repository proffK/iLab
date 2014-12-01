#ifndef _M_LIST_
#define _M_LIST_

//#define LIST_DEBUG

typedef char* elem_t;



#define PRINTF_ELEM_T(y, x) fprintf(y, " %s ", x)


struct list_el{
	
	elem_t data;
	struct list_el* next;
	struct list_el* prev;
	
};

typedef struct list_el list_elem; 

typedef struct {
	
	list_elem* head;
	list_elem* tail;
	int size;
	
} list;

enum directions{
	L_TAIL = -1,
	L_HEAD = 1
};


list* list_create(void);

int list_delete(list* deleted_list);

list_elem* add_elem(list* lst, elem_t new_elem);

list_elem* insert_elem(list* lst, elem_t new_elem, list_elem* next_elem);

int delete_elem(list* lst, list_elem* deleted_elem);

list_elem* find_elem(list* lst, elem_t found_elem, int (*cmp) (elem_t, elem_t),\
					  list_elem* current_elem, int direction);

int list_valide(list* lst);

int list_dump(list* lst);

list_elem* next_elem(list_elem* current_elem);

list_elem* prev_elem(list_elem* current_elem);

list_elem* list_tail(list* lst);

list_elem* list_head(list* lst);

void clear_log(void);

#endif
