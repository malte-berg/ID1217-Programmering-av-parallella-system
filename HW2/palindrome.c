#include "palindrome.h"
#include <string.h>
/*
bool palindrome_check(char *word){

    int half_length = (int)strlen(word)/2;
    char temp[half_length]; //Temporary string will be used in comparison
    int temp_index = half_length - 1;

    //Splits the word around the middle point, works even or odd
    for(int i = 0; i < half_length; i++) {
        temp[temp_index--] = word[i];
    }

    // Start index for where to begin comparing in the word
    int compare_index = half_length + (strlen(word) % 2); // Add string length modulo 2 to avoid middle character if odd length

    for(int i = 0; i < half_length; i++) {
        if(temp[i] != word[compare_index++]) return false;
    }
    return true;
}*/

int check_pal_sem(int word_index, int no_words, char *all_words[]) {
    int len = strlen(all_words[word_index]);
    char *reverse = (char *)malloc(len + 1);
    strcpy(reverse, all_words[word_index]);
    int l = 0;
    int r = len - 1;
    char temp;
    while (l < r) {
        temp = reverse[l];
        reverse[l] = reverse[r];
        reverse[r] = temp;

        l++;
        r--;
    }
    if (strcasecmp(reverse, all_words[word_index]) == 0) {
        free(reverse);
        return 0; // Return 0 for palindrome
    }
    for (int i = 0; i < no_words; i++) {
        if (i == word_index) continue;
        if (strcasecmp(reverse, all_words[i]) == 0) {
            free(reverse);
            return 1; // Return 1 for semordnilap
        }
    }
    free(reverse);
    return -1; // Return -1 if neither
}

void palindrome_init(char *all_words[], int no_words, bool is_palindrome[], bool is_semordnilap[], int thread_count){

    //Initialize bool array
    memset(is_palindrome, false, no_words * sizeof(bool));
    memset(is_semordnilap, false, no_words * sizeof(bool));

    //Loop through all of the words and look for Palindromes
    //Parallelize the for loop, currently not even workload look into scheduling
    omp_set_num_threads(thread_count);
#   pragma omp parallel
    {
#       pragma omp for
            for (int i = 0; i < no_words; i++){
                //is_palindrome[i] = palindrome_check(all_words[i]);
                int check = check_pal_sem(i, no_words, all_words);
                if (check == 0) {
                    is_palindrome[i] = true;
                } else if (check == 1) {
                    is_semordnilap[i] = true;
                } else {
                    // Do nothing
                }
            }
    //All words have been checked for palindromes
    }
    printf("Done!\n");
    return;
}
