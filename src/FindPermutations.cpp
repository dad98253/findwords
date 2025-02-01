/*
 * FindPermutations.cpp
 *
 *  Created on: Jan 22, 2025
 *      Author: dad
 */

#include <stdio.h>

#include "permute.h"

void FindPermutations(char *str, int n, int start, int len) {
    if (len == n) {
    	char temp2 = str[n];
    	str[n] = '\000';
        if ( n > minWordSize ) printf("%.*s\n", n, str); // Print the current permutation
        str[n] = temp2;
        if (len > 1 && n > 1){
        	FindPermutations(str+1, n-1, 0 , 0 );
        }
        return;
    }

    for (int i = start; i < n; i++) {
        // Swap characters to generate new permutations
        char temp = str[start];
        str[start] = str[i];
        str[i] = temp;
        FindPermutations(str, n, start + 1, len + 1);
        // Backtrack - swap characters back to original position
        temp = str[start];
        str[start] = str[i];
        str[i] = temp;
    }
}
