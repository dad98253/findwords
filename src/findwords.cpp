//============================================================================
// Name        : findwords.cpp
// Author      : dad
// Version     : Rev 0.0
// Copyright   : dwtfywwi
// Description : find all word purmutations of a string
//============================================================================
// usage:
// ./findwords ABCD |sort|uniq>in.txt
// comm -23 in.txt <(aspell list < in.txt)
#include <stdio.h>
#include <string.h>

void permute(char *str, int n, int start, int len) {
    if (len == n) {
    	char temp2 = str[n];
    	str[n] = '\000';
//        printf("%.*s\n", n, str + start); // Print the current permutation
        printf("%.*s\n", n, str); // Print the current permutation
        str[n] = temp2;
        if (len > 1 && n > 1){
        	permute(str+1, n-1, 0 , 0 );
        }
        return;
    }

    for (int i = start; i < n; i++) {
        // Swap characters to generate new permutations
        char temp = str[start];
        str[start] = str[i];
        str[i] = temp;
        permute(str, n, start + 1, len + 1);
        // Backtrack - swap characters back to original position
        temp = str[start];
        str[start] = str[i];
        str[i] = temp;
    }
}

int main( int argc, char **argv ) {

    char str[] = "ADOB"; // default string (used for debug)
    char * str2;
    int n; // Take permutations of size n

	if (argc > 1) {
			if ((strlen(argv[1]) > 0)) str2 = argv[1];
		} else {
			str2=str;
		}
	n = strlen(str2);
    permute(str2, n, 0, 0);

    return 0;
}


