#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXWORDLENGTH 100  // Maximum length of a word

#include "palindrome.c"

/*
Usage:
gcc -fopenmp main.c -o main
./main <number of threads>

input file is changed in line 22
*/

int main(int argc, char* argv[]) {

    //----------------------------READING----------------------------

    FILE *infile = fopen("words", "r");  // Open file of words for reading
    if (infile == NULL) {
        perror("Error opening file");
        return 1;
    }

    char word[MAXWORDLENGTH];  // Buffer to hold each word
    int no_words = 0;  // Initialize word count to 0

    // Calculate the number of words
    while (fgets(word, sizeof(word), infile) != NULL) {
        word[strcspn(word, "\n")] = 0;
        no_words++;
    }
    char* all_words[no_words];

    // Reset the file pointer to the beginning of the file
    rewind(infile);

    // Read each line (word) from the file and store them in all_words
    int i = 0;
    while (fgets(word, sizeof(word), infile) != NULL) {
        // Remove the newline character if present
        word[strcspn(word, "\n")] = 0;

        // Allocate memory for each word and copy it into all_words
        all_words[i] = malloc(strlen(word) + 1);  // +1 for the null terminator
        if (all_words[i] == NULL) {
            perror("Memory allocation failed");
            return 1;
        }
        strcpy(all_words[i], word);

        // Print the word
        //printf("Word read: %s\n", all_words[i]);
        i++;
    }
    // Close the file
    fclose(infile);

    bool is_palindrome[no_words];
    bool is_semomrdnilap[no_words];

    double exec_time = palindrome_init(all_words, no_words, is_palindrome, is_semomrdnilap, atoi(argv[1]));

    printf("Execution time: %f, No. Threads: %d, No. Words: %d \n", exec_time, atoi(argv[1]), no_words);

    //---------------------------------WRITING------------------------
    FILE *outfile = fopen("results.txt", "w");  // Open file for reading
    if (outfile == NULL) {
        perror("Error opening file");
        return 1;
    }
    fputs("Palindromes:\n\n", outfile);
    for (int i = 0; i < no_words; i++) {
        if(is_palindrome[i]) {
            fputs(all_words[i], outfile);
            fputc('\n', outfile);
        }
    }
    fputs("\nSemordnilaps:\n\n", outfile);
    for (int i = 0; i < no_words; i++) {
        if(is_semomrdnilap[i]) {
            fputs(all_words[i], outfile);
            fputc('\n', outfile);
        }
    }
    return 0;
}
