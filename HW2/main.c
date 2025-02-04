#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXWORDLENGTH 100  // Maximum length of a word

#include "palindrome.c"

int main(int argc, char* argv[]) {

    //----------------------------READING----------------------------

    FILE *infile = fopen("words", "r");  // Open file for reading
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

    palindrome_init(all_words, no_words, is_palindrome, atoi(argv[1]));

    for(int i = 0; i < no_words; i++) {
        if(is_palindrome[i]) puts(all_words[i]);
    }

    //---------------------------------WRITING------------------------
    /*
    FILE *outfile = fopen("results.txt", "w");  // Open file for reading
    if (outfile == NULL) {
        perror("Error opening file");
        return 1;
    }
    */
    return 0;
}
