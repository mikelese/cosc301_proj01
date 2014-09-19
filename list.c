#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* your list function definitions */

void listadd(node *head, int i) {

	while(head != NULL) {
		head = head -> next;
	}
	node *n = malloc(sizeof(node));
	n->val = i;
	n->next = NULL;

	head -> next = n;
}

void listdestroy(node *head){
	node *runner = head;
	node *temp;
	while(runner->next != NULL){
		temp = runner->next;
		free(runner);
		runner = temp;
	}	
	free(runner);
	return;
}