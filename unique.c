#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define FILE_INDEX 1
#define NUM_ARGS 2 

int validate_args(int argc, char *argv[]) {

    if (argc != NUM_ARGS) {
        fprintf(stderr, "No file given, utilize stdin:\n"); 
	return 1;
    }

    return 0; 
}

FILE* open_file(int argc, char *argv[]) {
    FILE* my_file = NULL; 

    if (validate_args(argc, argv)) {
        my_file = stdin;
    } else {
        my_file = fopen(argv[FILE_INDEX], "r");
    }

    if (my_file) {
        return my_file; 
    } else {
        fprintf(stderr, "ERROR: File does not exist\n"); 
        exit(1); 
    }
}

void unique_lines(FILE* file) {
    char *line = NULL; 
    char *one = NULL; 
    char *two = NULL; 
    size_t size = 10; 
   
    while(getline(&line, &size, file) > 0) { 
        free(two); 
        two = one; 
        one = strdup(line); 

        if (two == NULL) {
            fprintf(stdout, "%s", one); 
        } else if (strcmp(one, two)) { 
            fprintf(stdout, "%s", one); 
        }
    }

    free(line);
    free(one); 
    free(two);  
}

int main(int argc, char *argv[]) {  

	FILE* my_file = open_file(argc, argv); 
        unique_lines(my_file); 
        fclose(my_file);

	return 0; 
}
