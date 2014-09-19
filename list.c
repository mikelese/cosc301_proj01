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