#include <stdlib.h>
#include "M_tree.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
///#################################################################################

#define MAX_ELEM_SIZE 100

char* get_node(char* begin, elem_t* data);

int create_new_branch(node* end, char* parent, char* new_nd); 

///#################################################################################

int main(){
	FILE* base = NULL;
	node* tree = NULL;
	node* temp_nd = NULL;
	char answer[MAX_ELEM_SIZE] = "";
	char question[MAX_ELEM_SIZE] = "";

	tree = node_new();
	base = fopen("out.txt", "r");
	create_tree(base, tree, get_node);
	temp_nd = tree;
	printf("1");
	while (strcmp(answer, "q\n")) {
		printf("2");
		if ((strcmp(answer, "r\n") == 0)) {
			node_dump(tree, base);
			create_tree(base, tree, get_node);
			temp_nd = tree;
		}

		fflush(stdin);
		fputs(temp_nd -> data, stdout);
		fgets(answer,MAX_ELEM_SIZE ,stdin);
		printf("%s", answer);

		if (strcmp(answer, "y\n") == 0){
			
			if (temp_nd -> left == NULL && temp_nd -> right == NULL){

				printf("Я знал что угадаю.Введите q чтобы выйти.   					    Введите r для рестарта.\n");
				
			}

			else if (temp_nd -> left != NULL) {

				temp_nd = temp_nd -> left;

			}
		}

		if (strcmp(answer, "n\n") == 0){

			if (temp_nd -> left == NULL && temp_nd -> right == NULL){
				printf("Вы знаете другие операционные системы с таки					    ми свойствами? Введите ее название:\n");
				fflush(stdin);
				fgets(answer, MAX_ELEM_SIZE, stdin);
				answer[strlen(answer) - 1] = '\0';
				printf("Задайте вопрос определяющий вашу             					    операционнуюю систему:\n");
				fflush(stdin);	
				fgets(question,MAX_ELEM_SIZE , stdin);
				question[strlen(question) - 1] = '\0';
				create_new_branch(temp_nd, question, answer);
				printf("Ваш вариант добавлен в базу данных.Введите 					    q чтобы выйти.Введите r для рестарта.\n");
					
			}
			else if (temp_nd -> right != NULL){

				temp_nd = temp_nd -> right;

			}
		}
	}
	fclose(base);
	base = fopen("out.txt", "w");
	node_dump(tree, base);
	fclose(base);
//	node_dtor(tree);

        return 0;
}       

//##################################################################################

char* get_node(char* begin, elem_t* data){
	int i = 0;
	++begin;
	if (*begin != '"') return NULL;
	
	*data = (char*) calloc (MAX_ELEM_SIZE, sizeof(char));
	
	do {
		(*data)[i++] = *begin;
		++begin;
	} while (*begin != '"');
	(*data)[i] = *begin;
	++begin;

	return begin;
}

//##################################################################################

int create_new_branch(node* end, char* parent, char* nd){
	char* buf_parent = NULL;
	char* buf_nd = NULL;
	node* new_nd = NULL;
	node* new_temp = NULL;
	
	new_nd = node_new();
	new_temp = node_new();
	new_temp -> data = end -> data;
	buf_parent = (char*) calloc (strlen(parent), sizeof(char));
	strcpy(buf_parent, parent);
	node_ctor(buf_parent, end);

	buf_nd = (char*) calloc (strlen(nd), sizeof(char));
	strcpy(buf_nd, nd);
	node_ctor(buf_nd, new_nd);

	add_node_left(end, new_nd);
	add_node_right(end, new_temp);

	return 0;
}






