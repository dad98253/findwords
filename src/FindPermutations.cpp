/*
 * FindPermutations.cpp
 *
 *  Created on: Jan 22, 2025
 *      Author: dad
 */

#include <stdio.h>
#include <string.h>

#include "permute.h"


void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void FindPermutations(char *str, int n, int r, int start, char *result) {
    if (r == 0) {
    	if ( strlen(result) > minWordSize ) printf("%s\n", result);  // Print the current permutation
        return;
    }

    for (int i = start; i < n; i++) {
    	// Swap characters to generate new permutations
        swap((str + i), (str + start));
        result[r - 1] = str[start];
        FindPermutations(str, n, r - 1, start + 1, result);
        // Backtrack - swap characters back to original position
        swap((str + i), (str + start));
    }
}

