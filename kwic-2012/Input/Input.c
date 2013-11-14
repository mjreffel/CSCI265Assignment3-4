/********** Input module---implementation **********/

/* modified to take the requirements of Exercise 5 into account */

#include <stdio.h>
#include <ctype.h>
#include "kwic.h"
#include "Input.h"
#include "LineStorage.h"

/***** local constants *****/

/***** local types *****/

/***** local functions *****/

/***** exported functions *****/

void INInit(void)
{
	/* intentionally empty */
}


KWStatus INLoad( char *filename )
{
	char w[KWMAXWORDLENGTH+1];
	int c,length,newLine;
	KWStatus returnCode;
	FILE *inputFile;

	/* determine the input source */
	if (filename == NULL)
		inputFile = stdin;
	else {
		inputFile = fopen(filename, "r");
		if (inputFile == NULL)
			return KWFILEERROR;
	}

	c = '\n';
	for( ; ; ) {

		/* skip white space, checking for newlines */
		newLine = 0;
		while(isspace(c)) {
			if (c == '\n')
				newLine = 1;
			c = fgetc(inputFile);
		}
		if (c == EOF)
			break;

		/* process a new line if required */
		if (newLine) {
			returnCode = LSAddLine();
			if (returnCode != KWSUCCESS)
				return returnCode;
		}

		/* read one word */
		length = 0;
		do {
			if (length < KWMAXWORDLENGTH)
				w[length++] = c;
			c = fgetc(inputFile);
		} while(!isspace(c) && c != EOF);
		w[length] = '\0';
		returnCode = LSAddWord(w);
		if (returnCode != KWSUCCESS)
			return returnCode;
	}
	if (inputFile != stdin)
		fclose(inputFile);
	return KWSUCCESS;
}
