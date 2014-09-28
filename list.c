#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* your list function definitions */

void listadd(node **head, int i) {
	
	//create new node for entry
	node *n = malloc(sizeof(node));
	n->val = i;
	
	//if the list is empty or if the head is larger than
	//the head then make the new node the head
	if(*head == NULL || (**head).val > i){
		n->next = *head;
		*head = n;
		return;
	}
	
	//initialize variables for running through the list
	node *runner = *head;
	node *previous = *head;
	runner = runner -> next;
	
	//loop through list until current node is greater than new node
	//or until the end is reached
	while(runner != NULL) {
		if(runner->val > i){
			break;
		}
		previous = runner;
		runner = runner -> next;
	}
	
	//place new node in the proper location
	previous->next = n;
	n->next = runner;
}

void listdestroy(node *list) {
	// Iterate through list and free all nodes
    while (list != NULL) {
        node *tmp = list;
        list = list->next;
        free(tmp);
    }
}

void listprint(node *list) {
	printf("*** List Contents Begin ***\n");
	// Iterate through list and print all nodes
    while (list != NULL) {
        printf("%d\n", list->val);
        list = list->next;
    }
	printf("*** List Contents End ***\n");
}















