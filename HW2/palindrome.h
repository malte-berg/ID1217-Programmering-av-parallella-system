#ifndef _REENTRANT
#define _REENTRANT
#endif

#ifndef PALINDROME_H
#define PALINDROME_H

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <stdbool.h>

bool palindrome_check(char *word);

void palindrome_init(char *all_words[], int no_words, bool is_palindrome[], int thread_count);

#endif
