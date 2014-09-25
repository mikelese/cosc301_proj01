#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* your list function definitions */

void listadd(node *head, int i) {
	
	node *n = malloc(sizeof(node));
	n->val = i;
	
	if(head == NULL){
		n->next = NULL;
		head = n;
		return;
	}
	
	if(head->val > i){
		n->next = head;
		head = n;
		return;
	}
	node *previous = head;
	head = head -> next;
	while(head->next != NULL) {
		if(head->val > i){
			break;
		}
		head = head -> next;
	}
	previous->next = n;
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
    printf("In list_print\n");
    while (list != NULL) {
		printf("head not null\n");
        printf("List item %d: %d\n", i++, list->val);
        list = list->next;
    }
}















