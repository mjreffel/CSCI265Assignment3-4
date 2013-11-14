/********** WordTable module---implementation **********/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kwic.h"
#include "WordTable.h"

/***** local constants *****/
#define KWMAXNOISEWORD 15

/***** local types *****/

/***** local variables *****/
static int numWords;
static char** wordList;

/***** state invariant *****

1. wordList contains numWords pointers to null-terminated C strings.

2. The WordList strings are sorted in ascending order.
*/

/***** local functions *****/

/* if there is a `noise word' remaining in fp then
*	Store that word from in a static buffer and return its address.
*	Words longer than KWMAXNOISEWORD characters are truncated.
* else
*	Return NULL
*/
static char *getNextWord(FILE *fp)
{
	static char result[KWMAXNOISEWORD+1];
	char *cp;
	int c,len;

	/* skip leading white space characters */
	do {
		c = getc(fp);
		if (c == EOF)
			return NULL;
	} while(isspace(c));

	/* read the noise word */
	len = 0;
	do {
		result[len++] = c;
		c = getc(fp);
		if (c == EOF)
			return NULL;
	} while(len < KWMAXNOISEWORD && !isspace(c));
	result[len] = '\0';

	/* skip trailing junk on the line */
	while(c != '\n') {
		c = getc(fp);
		if (c == EOF)
			return NULL;
	}
	return result;
}

/***** exported functions *****/

KWStatus WTInit(char *noiseWdFileName)
{
#define DFLTNUMNOISEWORDS	100
	FILE *fp;
	int retCode,arrayLength;
	char *newWord;

	fp = fopen(noiseWdFileName,"r");	
	if (fp == NULL) {
		perror(noiseWdFileName);
		return KWFILEERROR;
	}

	numWords = 0;
	arrayLength = DFLTNUMNOISEWORDS;
	wordList = calloc(arrayLength,sizeof(char *));
	if (wordList == NULL) {
		fclose(fp);
		return KWMEMORYERROR;
	}

	retCode = KWSUCCESS;
	for( ; ; ) {
		newWord = getNextWord(fp);
		if (newWord == NULL) break;
		if (numWords >= arrayLength) {
			arrayLength *= 2;
			wordList = realloc(wordList,
					arrayLength*sizeof(char*));
			if (wordList == NULL) {
				retCode = KWMEMORYERROR;
				break;
			}
		}
		wordList[numWords] = malloc(strlen(newWord)+1);
		if (wordList[numWords] == NULL) {
			retCode = KWMEMORYERROR;
			break;
		}
		strcpy(wordList[numWords],newWord);
		numWords++;
	}
	fclose(fp);
	return retCode;
#undef DFLTNUMNOISEWORDS
}

int WTIsMember(char* s)
{
        int high,low,mid,cmpVal;

	low = 0;
	high = numWords - 1;
        while (low <= high) {
                mid = (low+high)/2;
                cmpVal = strcasecmp(s,wordList[mid]);
                if (cmpVal < 0)
                        high = mid-1;
                else if (cmpVal == 0)
                        return 1;
                else
                        low = mid+1;
        }
        return 0;
}

void WTPrintState(void)
{
        int i;
	printf("\tnumWords: %d\n",numWords);
        for (i = 0; i < numWords; i++)
                printf("\t%s\n",wordList[i]);
}
