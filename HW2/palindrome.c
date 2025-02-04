#include "palindrome.h"

bool palindrome_check(char *word){

    int half_length = (int)strlen(word)/2;
    char temp[half_length]; //Temporary string will be used in comparison
    int temp_index = half_length - 1;

    //Splits the word around the middle point, works even or odd
    for(int i = 0; i < half_length; i++) {
        temp[temp_index--] = word[i];
    }

    int compare_index = half_length + (strlen(word) % 2); // Start index for where to begin comparing in the word

    for(int i = 0; i < half_length; i++) {
        if(temp[i] != word[compare_index++]) return false;
    }
    return true;
}

void palindrome_init(char *all_words[], int no_words, bool is_palindrome[], int thread_count){

    //Initialize bool array

    //Loop through all of the words and look for Palindromes
    //Parallelize the for loop, currently not even workload look into scheduling
#   pragma omp parallel for num_threads(thread_count)
    for (int i = 0; i < no_words; i++){
        is_palindrome[i] = palindrome_check(all_words[i]);
    }
    //All words have been checked for palindromes

    return;
}
