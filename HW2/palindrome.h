#ifndef _REENTRANT
#define _REENTRANT
#endif

#ifndef PALINDROME_H
#define PALINDROME_H

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <stdbool.h>
#include <string.h>

bool palindrome_check(char *word);

double palindrome_init(char *all_words[], int no_words, bool is_palindrome[], bool is_semordnilap[], int thread_count);

#endif
