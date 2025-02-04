#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORDLENGTH 100  // Maximum length of a word

int main(int argc, char* argv[]) {
    FILE *file = fopen("words", "r");  // Open file for reading
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char word[MAXWORDLENGTH];  // Buffer to hold each word
    int no_words = 0;  // Initialize word count to 0

    // Calculate the number of words
    while (fgets(word, sizeof(word), file) != NULL) {
        word[strcspn(word, "\n")] = 0;
        no_words++;
    }
    char* all_words[no_words];

    // Reset the file pointer to the beginning of the file
    rewind(file);

    // Read each line (word) from the file and store them in all_words
    int i = 0;
    while (fgets(word, sizeof(word), file) != NULL) {
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
        printf("Word read: %s\n", all_words[i]);
        i++;
    }
    // Close the file
    fclose(file);

    return 0;
}