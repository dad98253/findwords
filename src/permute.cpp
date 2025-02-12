//============================================================================
// Name        : permute.cpp
// Author      : dad
// Version     : Rev 0.2
// Copyright   : (c)John Kuras 2025
// License     : dwtfywwi
// Description : find all word purmutations of a string
//============================================================================
// usage:
// ./permute FFERO |sort|uniq>in.txt ; comm -23 in.txt <(aspell list < in.txt) 2>/dev/null
//
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <locale.h>

#include "../config.h"
#define IN_MAIN
#include "permute.h"
#include "gitversion.h"
#include "gettext.h"

#define _(String) gettext(String)

void FindPermutations(char *str, int n, int r, int start, char *result);

int main( int argc, char **argv ) {

    char str[] = "ADOB"; // default string (used for debug)
    char * str2;
    char * str3;
    char * result;
    int n; // Take permutations of size n
    int c;
    int tempint;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
    char * CurrentLocale = NULL;
    char * CurrentDirnam = NULL;
    char * CurrentDomain = NULL;
#pragma GCC diagnostic pop

    const char* env_var = getenv("LANGUAGE");
     if (env_var != NULL) {
             if ( strlen(env_var) ) {
#ifdef DEBUG
                     printf("Value of LANGUAGE: %s\n", env_var);
#endif
                     setenv("LANGUAGE", "", 1);
             } else {
#ifdef DEBUG
                     printf("LANGUAGE is blank\n");
#endif
             }
     }
#ifdef DEBUG
     else {
             printf("LANGUAGE not found\n");
     }
#endif

//      setlocale (LC_ALL, "en_US.UTF-8");
//     CurrentLocale = setlocale (LC_ALL, "ms_MY.UTF-8");
     CurrentLocale = setlocale (LC_ALL, "");
#ifdef DEBUG
     if (CurrentLocale) {
             printf("locale set to %s\n",CurrentLocale);
     } else {
             fprintf(stderr,"setlocale failed\n");
             exit(1);
     }
//    bindtextdomain (PACKAGE, LOCALEDIR);
//     printf("LOCALEDIR = %s\n",LOCALEDIR);
#endif
     CurrentDirnam = bindtextdomain ("permute", "/home/dad/workspace/permute/locales");
#ifdef DEBUG
     if (CurrentDirnam) {
             printf("dirname set to %s\n",CurrentDirnam);
     } else {
             fprintf(stderr,"bindtextdomain failed\n");
             exit(2);
     }
#endif
     CurrentDomain = textdomain ("permute");
#ifdef DEBUG
     if (CurrentDomain) {
             printf("domain set to %s\n",CurrentDomain);
     } else {
             fprintf(stderr,"textdomain failed\n");
             exit(3);
     }
#endif

    while (1) {
        int option_index = 0;
        static struct option long_options[] = {
            {"min-word-size",  required_argument, 0, 'm'},
            {"max-word-size",  required_argument, 0, 'x'},
			{"help",  no_argument, 0, '?'},
			{"version",  no_argument, 0, 'v'},
            {0,         0,                 0,  0 }
        };

        c = getopt_long(argc, argv, "m:x:?v",
                        long_options, &option_index);
        if (c == -1)
            break;

        switch (c) {
        case 0:
            fprintf(stderr,_(" option %s"), long_options[option_index].name);
            if (optarg)
                fprintf(stderr," with arg %s", optarg);
            fprintf(stderr,"\n");
            break;

        case 'm':
            tempint = atoi((const char *)optarg);
            if ( tempint < 0 ) {
            	fprintf(stderr,_(" warning : the minimum word size cannot be negative, using \"1\"\n"));
		minWordSize = 1;
            } else {
                minWordSize = tempint;
            }
            break;

        case 'x':
            tempint = atoi((const char *)optarg);
            if ( tempint > MAXSETSIZE ) {
            	fprintf(stderr,_(" warning : the maximum word size cannot be greater than \"%u\". Using \"%u\".\n"),MAXSETSIZE,MAXSETSIZE);
		maxWordSize = MAXSETSIZE;
            } else if ( tempint < 0 ) {
                fprintf(stderr,_(" warning : the maximum word size cannot be negative, using \"1\"\n"));
                maxWordSize = 1;
	    } else {
                maxWordSize = tempint;
            }
            break;

        case '?':
            fprintf(stderr, _("Usage: %s [OPTION]... [STRING]\n"), argv[0]);
            fprintf(stderr, _("Find the permutations of a string.\n"));
			fprintf(stderr, _("  -m, --min-word-size=N    the minimum size of a derived word\n"));
			fprintf(stderr, _("  -x, --max-word-size=X    the maximum size of a derived word\n"));
			fprintf(stderr, _("  -?, --help               display this help and exit\n"));
			fprintf(stderr, _("  -v, --version            output version information and exit\n"));
			fprintf(stderr, _("  STRING                   the string of characters to be permuted\n"));               		                        
            fprintf(stderr, _("       default for N = 3\n"));
            fprintf(stderr, _("       default for X = length of STRING\n"));
            fprintf(stderr, _("       default for STRING = \"ADOB\"\n"));
            fprintf(stderr, _("       to find the permutations of STRING taken M at a time (i.e., P(STRING,M))\n"));
            fprintf(stderr, _("       enter: permute -m M -x M STRING\n"));
            exit(EXIT_SUCCESS);
            break;

        case 'v':
            fprintf(stderr, _("%s version %s, gittag %s\n\n"), argv[0],VERSION,gittag);
            exit(EXIT_SUCCESS);
            break;

        default:
            fprintf(stderr,_(" ?? getopt returned character code 0%o ??\n"), c);
        }
    }

    if (optind < argc) {
    	str2 = argv[optind++];
    } else {
		str2=str;
	}

	n = strlen(str2);
	if ( n > MAXSETSIZE ) {
		fprintf(stderr,_(" ///// ERROR : The length of your string is %u.\n               The maximum allowed is %u.\n"), n , MAXSETSIZE );
		exit(4);
	}
	str3 = (char*)malloc(n+2);
	result = (char*)calloc(n+2,1);
        if ( n < (int)maxWordSize ) maxWordSize = (long unsigned int)n;
        
        // check for min siz greater than max size
        if ( minWordSize > maxWordSize ) {
                fprintf(stderr,_(" ///// ERROR : The minimum word size cannot be greater than the maximum word size.\n"));
                exit(5);		
	}
        
	fprintf(stderr,_(" finding all of the permutations of %s that are between %lu and %lu characters long\n"),str2,minWordSize,maxWordSize);
	// find all permutations taken r at a time where r goes from minWordSize to maxWordSize
    for (int r=(int)minWordSize;r<(int)(maxWordSize+1);r++){
      strcpy(str3,str2);
      FindPermutations(str3, n, r, 0, result);
    }

    free(str3);
    free(result);
    return 0;
}


