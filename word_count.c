#include <stdlib.h> 
#include <stdio.h>
#include <ctype.h> 
#define FILE_INDEX 1
#define NUM_ARGS 2 

int validate_args(int argc, char *argv[]) {
    if (argc != NUM_ARGS) {
        fprintf(stderr, "No file argument given, utilize stdin:\n");
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

void file_counter(FILE* file, int *lines, int *chars, int *words) {
    int num_lines = 0;
    int num_chars = 0; 
    int num_words = 0; 
    int space = 1; 

    for (char c = getc(file); c != EOF; c = getc(file)) {
        num_chars++; // count the num of chars in the file

	if (c == '\n') {
	    num_lines++; // count the num of lines in the file    
	}

	if (space && !isspace(c)) {
            num_words++; // count the num of words in the file 
	}

        if (isspace(c)) {
 	    space = 1;
	} else {
	    space = 0; 
	}	
    }

    *lines = num_lines; 
    *chars = num_chars; 
    *words = num_words;    
}

int main(int argc, char *argv[]) {
    int num_lines = 0;
    int num_chars = 0;
    int num_words = 0; 

    FILE* my_file = open_file(argc, argv);  
    file_counter(my_file, &num_lines, &num_chars, &num_words);   
    fclose(my_file);   

    // Print the output 
    printf("Number of lines: %i\n", num_lines); 
    printf("Number of characters: %i\n", num_chars);
    printf("Number of words: %i\n", num_words); 

    return 0;  
}
