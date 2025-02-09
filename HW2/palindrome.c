#include "palindrome.h"
#include <string.h>

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
    //Check for palindrome Non case sensitive comparison
    if (strcasecmp(reverse, all_words[word_index]) == 0) {
        free(reverse);
        return 0; // Return 0 for palindrome
    }
    //Check for semordnilap, Parallelize?
    for (int i = 0; i < no_words; i++) {
        if (i == word_index) continue;
        //Non case sensitive comparison
        if (strcasecmp(reverse, all_words[i]) == 0) {
            free(reverse);
            return 1; // Return 1 for semordnilap
        }
    }
    free(reverse);
    return -1; // Return -1 if neither
}

double palindrome_init(char *all_words[], int no_words, bool is_palindrome[], bool is_semordnilap[], int thread_count){

    //Initialize bool array and values to false
    memset(is_palindrome, false, no_words * sizeof(bool));
    memset(is_semordnilap, false, no_words * sizeof(bool));

    //Loop through all of the words and look for Palindromes
    //Parallelize the for loop, currently not even workload look into scheduling
    
    double start_time = omp_get_wtime();

#   pragma omp parallel for num_threads(thread_count)
        for (int i = 0; i < no_words; i++){
        int check = check_pal_sem(i, no_words, all_words);
            //Switch?
        if (check == 0) {
            is_palindrome[i] = true;
        } else if (check == 1) {
            is_semordnilap[i] = true;
        }
    }

    double end_time = omp_get_wtime();
    printf("Done!\n");
    return (end_time - start_time);
}
