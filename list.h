#ifndef __LIST_H__
#define __LIST_H__

/* your list data structure declarations */


typedef struct node {
	int val;
	struct node *next;
} node;

/* your function declarations associated with the list */

void listadd(node **head, int i);
void listdestroy(node *head);
void listprint(node *head);


#endif // __LIST_H__
