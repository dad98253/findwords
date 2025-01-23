//============================================================================
// Name        : findwords.cpp
// Author      : dad
// Version     : Rev 0.1
// Copyright   : (c)John Kuras 2025
// License     : dwtfywwi
// Description : find all word purmutations of a string
//============================================================================
// usage:
// ./findwords FFERO |sort|uniq>in.txt ; comm -23 in.txt <(aspell list < in.txt) 2>/dev/null
//
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>

#define IN_MAIN
#include "findwords.h"

void permute(char *str, int n, int start, int len);

int main( int argc, char **argv ) {

    char str[] = "ADOB"; // default string (used for debug)
    char * str2;
    int n; // Take permutations of size n
    int c;

    while (1) {
        int option_index = 0;
        static struct option long_options[] = {
            {"min-word-size",  required_argument, 0, 'm'},
			{"help",  no_argument, 0, '?'},
			{"version",  no_argument, 0, '?'},
            {0,         0,                 0,  0 }
        };

        c = getopt_long(argc, argv, "m:?",
                        long_options, &option_index);
        if (c == -1)
            break;

        switch (c) {
        case 0:
            fprintf(stderr," option %s", long_options[option_index].name);
            if (optarg)
                fprintf(stderr," with arg %s", optarg);
            fprintf(stderr,"\n");
            break;

        case 'm':
            minWordSize = atoi((const char *)optarg);
            if ( minWordSize < 0 ) {
            	fprintf(stderr," warning : the minimum word size cannot be negative, using \"0\"\n");
				minWordSize = 0;
            }
            break;

        case '?':
            fprintf(stderr, "Usage: %s [-m,--min-word-size n] [string]\n", argv[0]);
            fprintf(stderr, "       finds all of the permutations of a string that are more that n characters in length.\n");
            fprintf(stderr, "       default for n = 2\n");
            fprintf(stderr, "       default for string = \"ADOB\"\n");
            exit(EXIT_FAILURE);
            break;

        default:
            fprintf(stderr," ?? getopt returned character code 0%o ??\n", c);
        }
    }

    if (optind < argc) {
    	str2 = argv[optind++];
    } else {
		str2=str;
	}

	n = strlen(str2);
	fprintf(stderr," finding all of the permutations of %s that are more than %i characters long\n",str2,minWordSize);
    permute(str2, n, 0, 0);

    return 0;
}


