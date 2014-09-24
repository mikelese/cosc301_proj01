/*
 *
 * author name(s), date, and other info here
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "list.h"

char** tokenify(const char *s) {
    char *str = strdup(s);
    int numSpaces = 0;

    for (int i=0;i<strlen(str);i++) {
        if(isspace(str[i])) {
            numSpaces++;
        }
    }

    char **ret = malloc((sizeof (char*))* (numSpaces+2));
    char *tok = strtok(str," \t\n");

    int index = 0;
    while (tok != NULL) {
        ret[index] = strdup(tok);
        tok = strtok(NULL," \t\n");
        index++;
    }
    ret[index] = NULL;

    free(str);
    return ret;
}

void check(char *in, int *result){
	result[0] = -1;
	if(isdigit(in[0])){					//This causes an implicit declaration warning
		result[0] = (int)strtol(in, (char**)NULL, 10);
	}
	return;
}

node* create_list(FILE *input_file){
	char in[2] = "\0\0"; 
	int result = -1;
	node* head = malloc(sizeof(node));
	node* runner = head;
	while(fgets(in,2,input_file) != NULL){
		check(in,&result);
		if(result != -1){
			runner->val = result;
			node* temp = malloc(sizeof(node));
			runner->next = temp;
			runner = temp;
		}
	}
	return head;
}

void process_data(FILE *input_file) {
	node *head = create_list(input_file);
	printf("%d\n",head->val);
	printf("%u\n",sizeof(node));
	listdestroy(head);
}

void usage(char *program) {
    fprintf(stderr, "usage: %s [<datafile>]\n", program);
    exit(1);
}

#ifndef AUTOTEST
int main(int argc, char **argv) {
    FILE *datafile = NULL;

    /* find out how we got invoked and deal with it */
    switch (argc) {
        case 1:
            /* only one program argument (the program name) */ 
            /* just equate stdin with our datafile */
            datafile = stdin;        
            break;

        case 2:
            /* two arguments: program name and input file */
            /* open the file, assign to datafile */
            datafile = fopen(argv[1], "r");
            if (datafile == NULL) {
                printf("Unable to open file %s: %s\n", argv[1], strerror(errno));
                exit(-1);
            }
            break;

        default:
            /* more than two arguments?  throw hands up in resignation */
            usage(argv[0]);
    }

    /* 
     * you should be able to just read from datafile regardless 
     * whether it's stdin or a "real" file.
     */
    process_data(datafile);
    fclose(datafile);
    return 0;
}
#endif
