#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* your list function definitions */

void listadd(node **head, int i) {
	
	node *n = malloc(sizeof(node));
	n->val = i;
	
	if(*head == NULL){
		n->next = NULL;
		*head = n;
		return;
	}
	
	if((**head).val > i){
		n->next = *head;
		*head = n;
		return;
	}
	
	if((**head).next == NULL){
		(**head).next = n;
		return;
	}

	node *runner = *head;
	node *previous = *head;
	runner = runner -> next;
	while(runner != NULL) {
		if(runner->val > i){
			break;
		}
		runner = runner -> next;
	}
	previous->next = n;
	n->next = runner;
}

void listdestroy(node *list) {
    while (list != NULL) {
        node *tmp = list;
        list = list->next;
        free(tmp);
    }
}

void listprint(node *list) {
    int i = 0;
    while (list != NULL) {
        printf("List item %d: %d\n", i++, list->val);
        list = list->next;
    }
}















