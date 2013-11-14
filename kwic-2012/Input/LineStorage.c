/********** LineStorage module---test stub **********/

#include <stdio.h>
#include "kwic.h"
#include "LineStorage.h"

static int numLines = 0;

/***** exported functions *****/

KWStatus LSAddLine(void)
{
	numLines++;
	printf("LSAddLine()\n");
	return KWSUCCESS;
}

KWStatus LSAddWord(char* word)
{
	printf("LSAddWord(%s)\n",word);
	return KWSUCCESS;
}

int LSNumLines(void)
{
	return numLines;
}
