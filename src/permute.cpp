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

void FindPermutations(char *str, int n, int start, int len);

int main( int argc, char **argv ) {

    char str[] = "ADOB"; // default string (used for debug)
    char * str2;
    int n; // Take permutations of size n
    int c;
    char * CurrentLocale = NULL;
    char * CurrentDirnam = NULL;
    char * CurrentDomain = NULL;

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
			{"help",  no_argument, 0, '?'},
			{"version",  no_argument, 0, 'v'},
            {0,         0,                 0,  0 }
        };

        c = getopt_long(argc, argv, "m:?v",
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
            minWordSize = atoi((const char *)optarg);
            if ( minWordSize < 0 ) {
            	fprintf(stderr,_(" warning : the minimum word size cannot be negative, using \"0\"\n"));
				minWordSize = 0;
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
            fprintf(stderr, _("       default for N = 2\n"));
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
	fprintf(stderr,_(" finding all of the permutations of %s that are more than %i characters long\n"),str2,minWordSize);
    FindPermutations(str2, n, 0, 0);

    return 0;
}


