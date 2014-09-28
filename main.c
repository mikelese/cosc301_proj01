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

void parseToken(char *unconverted, node **head) {
    long result;
    int converted;
    for (int i=0;i<strlen(unconverted);i++) {
        if(unconverted[i]=='.') {
            return;
        }
    }
    errno = 0;
    char *end;
    result = strtol(unconverted, &end, 10);
    if(result < INT_MIN || result > INT_MAX) {
        printf("%s\n", "Too big");
        return;
    }

    converted = (int)result;

    if(errno != ERANGE && end!=unconverted) {
        listadd(head,converted);
    }
}

void free_tokens(char **tokens) {
    int i = 0;
    while (tokens[i] != NULL) {
        free(tokens[i]); // free each string
        i++;
    }
    free(tokens); // then free the array
}

node* create_list(FILE *input_file){
    size_t size = 0;
    int status = 0;
    char *line = NULL;
    status = getline(&line,&size,input_file);
    node *head = NULL;

    while(status != -1) {
        for (int i=0;i<strlen(line);i++) {
            if (line[i] == '#') {
                line[i] = '\0';
            }
        }
        int index = 0;
        char **tokens = tokenify(line);
        char *unconverted = tokens[index];
        while (unconverted != NULL) {
            parseToken(unconverted, &head);
            index++;
            unconverted = tokens[index];
        }
        free_tokens(tokens);
        status = getline(&line,&size,input_file);
    }
    free(line);
    return head;
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
    getrusage(RUSAGE_SELF, &usage);
    usertime = usage.ru_utime;
    systime = usage.ru_stime;
    printf("User time: %f\n", (double)usertime.tv_sec+(double)usertime.tv_usec/1000000);
    printf("System time: %f\n", (double)systime.tv_sec+(double)systime.tv_usec/1000000);

    return 0;
}
#endif