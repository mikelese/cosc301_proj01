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



int* check(char *in){
	int *returnvalue = malloc(sizeof(int));
	returnvalue[0] = -1;
	printf("Here\n");
	if(isdigit(in[0])){							//This causes an implicit declaration warning
		returnvalue[0] = atoi(&in[0]);
	}
	return returnvalue;
}

node* create_list(FILE *input_file){	q12
	char in[2] = "\0\0"; 
	int *result;
	while(1 || fgets(in,2,input_file) != NULL){
		in[0] = 'a';
		result = check(in);
		printf("%\n",result[0]);
		break;
	}
	free(result);
	
	node* head = malloc(sizeof(node));
	return head;
}

void process_data(FILE *input_file) {
	node *head = create_list(input_file);
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
