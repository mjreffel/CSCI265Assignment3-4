/********** WordTable module---test driver **********/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kwic.h"
#include "WordTable.h"

char* inWordList[] = {
	"a", "an", "and", "and/or", 
	"as", "at", "for", "from", "in",
	"of", "on", "or", "the", "to", "with",

	/* upper case variations: */
	"And", "aNd", "anD",

	0 /* terminator */
};

char* notInWordList[] = {
	/* words containing words in inWordList */
	"thereupon", "into", "stool",

	/* special strings */
        "", " ", ",",

	0 /* terminator */
};

static int errorCount = 0;

int main()
{
	int b,i;

	if (WTInit("testNoiseWords") != KWSUCCESS) {
		printf("could not read testNoiseWords file\n");
		exit(1);
	}

	printf("Check words that should be in WordTable\n");
	for (i = 0; inWordList[i]; i++) {
		printf("\tChecking word: \"%s\"\n",inWordList[i]);
		b = WTIsMember(inWordList[i]);
		if (!b) {
			printf("Error in WTIsMember return value.");
			printf("Actual: %d  Expected: 1\n",b);
			errorCount++;
		}
	}

	printf("\nCheck words that should not be in WordTable\n");
	for (i = 0; notInWordList[i]; i++) {
		printf("\tChecking word: \"%s\"\n",notInWordList[i]);
		b = WTIsMember(notInWordList[i]);
		if (b) {
			printf("Error in WTIsMember return vlaue.");
			printf("Actual: %d  Expected: 0",b);
			errorCount++;
		}
	}

	if (errorCount == 0)
		printf("\n\nNo errors detected!\n");
	return errorCount;
}
