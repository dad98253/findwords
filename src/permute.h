/*
 * permute.h
 *
 *  Created on: Jan 22, 2025
 *      Author: dad
 */

#ifndef PERMUTE_H_
#define PERMUTE_H_

#define MAXSETSIZE	15

#ifdef IN_MAIN
#define EXTERN
#define INT2	=3
#define MXSZ	=MAXSETSIZE
#else
#define EXTERN		extern
#define INT2
#define MXSZ
#endif

#define MAXSETSIZE	15

EXTERN long unsigned int minWordSize INT2;
EXTERN long unsigned int maxWordSize MXSZ;

#endif /* PERMUTE_H_ */
