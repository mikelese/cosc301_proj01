/*
 * Michael Lese and Jack Sneeringer
 * 
 * COSC 301, Fall 2014
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "list.h"

#include <sys/time.h>
#include <sys/resource.h>

char** tokenify(const char *s, size_t *len) {
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
/*
int check(char *in, size_t len, int start){
	int result = 0;
	for(int i = 0; i<len; i++){
		if(isdigit(in[i])){					//This causes an implicit declaration warning
			result = 10*result + (int)strtol(in, (char**)NULL, 10);
		}
	}
	return result;
}
*/
node* create_list(FILE *input_file){
	
	//new code
	char *in = NULL;
	size_t max = 0; //this is just so the getline function works
	size_t len;
	node * head = NULL;
	while((len = getline(&in,&max,input_file)) > 0){
		tokenify(in,&len);
		for(int i = 0; i < len; i++){
			listadd(&head,in[i]);
		}
	}
	return head;
	
	//end new code
	
	/*
	char in[2] = "\0\0"; 
	int result = -1;
	node* head = NULL;
	while(fgets(in,2,input_file) != NULL){
		check(in,&result);
		if(result != -1){
			listadd(&head,result);
		}
	}
	return head;
	*/
}

void process_data(FILE *input_file) {
	node *head = create_list(input_file);
	listprint(head);
	listdestroy(head);
}

void usage(char *program) {
    fprintf(stderr, "usage: %s [<datafile>]\n", program);
    exit(1);
}

// void printTime() {
//     struct timeval usertime;
//     struct timeval systime;        
//     struct rusage usage;
//     getrusage(RUSAGE_CHILDREN, &usage);
//     usertime = usage.ru_utime;
//     systime = usage.ru_stime;

//     printf("User time: %f\n", (double)usertime.tv_sec+(double)usertime.tv_usec*10000);
//     printf("System time: %f\n", (double)systime.tv_sec+(double)systime.tv_usec*100000);
// }

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

    struct timeval usertime; //Possibly include in separate function
    struct timeval systime;  //If it does not affect reported time.      
    struct rusage usage;
    getrusage(RUSAGE_CHILDREN, &usage);
    usertime = usage.ru_utime;
    systime = usage.ru_stime;

    printf("User time: %f\n", (double)usertime.tv_sec+(double)usertime.tv_usec/100000);
    printf("System time: %f\n", (double)systime.tv_sec+(double)systime.tv_usec/100000);

    return 0;
}
#endif
