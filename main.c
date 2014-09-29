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
#include <limits.h>

char** tokenify(const char *s) {
	//duplicate string for parsing
    char *str = strdup(s);
    int numSpaces = 0;
	
	//count the number of spaces in the line
    for (int i=0;i<strlen(str);i++) {
        if(isspace(str[i])) {
            numSpaces++;
        }
    }
	
	//make space for the returned array of tokens
    char **ret = malloc((sizeof (char*))* (numSpaces+2));
    char *tok = strtok(str," \t\n");

	//loop through tokens and place each one in
	//the array to be returned
    int index = 0;
    while (tok != NULL) {
        ret[index] = strdup(tok);
        tok = strtok(NULL," \t\n");
        index++;
    }
	//null terminate the array, free the passed in str
	//and return the array
    ret[index] = NULL;
    free(str);
    return ret;
}

void parseToken(char *unconverted, node **head) {
	//Initialize variables
    long result;
    int converted;
    errno = 0;
    char *end;
	
	//loop through token, if you find a . then
	//it is an invalid token and return
    for (int i=0;i<strlen(unconverted);i++) {
        if(unconverted[i]=='.') {
            return;
        }
    }
    //this is some code to verify the size of the token is
	//within the size limits for int, i.e.  -2^31 to 2^31 - 1
    result = strtol(unconverted, &end, 10);
    if(result < INT_MIN || result > INT_MAX) {
		//Can print too big int if we want
        //printf("%s\n", "Too big");
        return;
    }
	
	//Plase typecast final result into variable
    converted = (int)result;
	
	//If there was no error and strtol actually did something
    if(errno != ERANGE && end!=unconverted) {
        listadd(head,converted);
    }
}

void free_tokens(char **tokens) {
	// free each string
	for(int i = 0; tokens[i] != NULL; i++){
        free(tokens[i]);
    }
	// then free the array
    free(tokens); 
}

node* create_list(FILE *input_file){
	// Initialize variables
    size_t size = 0;
    char *line = NULL;
	node *head = NULL;

	//Go through all lines of input
    while(getline(&line,&size,input_file) != -1) {
		//Loop through line and if you find a # then 
		//replace it with null terminator and break
        for (int i=0;i<strlen(line);i++) {
            if (line[i] == '#') {
                line[i] = '\0';
				break;
            }
        }
		//tokenify the line and parse each token
        char **tokens = tokenify(line);
		for(int i = 0; tokens[i] != NULL; i++){
			parseToken(tokens[i],&head);
        }
		//free the tokens
        free_tokens(tokens);
    }
	//free the line that getline used
    free(line);
    return head;
}

void process_data(FILE *input_file) {
	//Call create list function then print and destroy created list
	node *head = create_list(input_file);
	listprint(head);
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

    struct timeval usertime; //Possibly include in separate function
    struct timeval systime;  //If it does not affect reported time.      
    struct rusage usage;
    if(getrusage(RUSAGE_SELF, &usage)==-1) { 
    	printf("getrusage error %s\n", strerror(errno));//This should never happen
    	exit(-1);
    }
    usertime = usage.ru_utime;
    systime = usage.ru_stime;
    printf("User time: %f\n", (double)usertime.tv_sec+(double)usertime.tv_usec/1000000);
    printf("System time: %f\n", (double)systime.tv_sec+(double)systime.tv_usec/1000000);

    return 0;
}
#endif