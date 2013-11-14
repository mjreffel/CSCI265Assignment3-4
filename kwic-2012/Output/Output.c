/********** Output module---implementation **********/

#include <stdio.h>
#include "kwic.h"
#include "Output.h"
#include "ShiftSort.h"

/***** local constants *****/

/***** local types *****/

/***** exported functions *****/

void OUInit(void)
{
	/* intentionally empty */
}

void OUPrint(void)
{
	int i,j;

	for (i = 0; i < SSNumLines(); i++) {
		int numWords = SSNumWords(i);
		for (j = 0; j < numWords; j++) {
			int shiftNum = SSGetShiftNum(i);
			printf("%s",SSGetWord(i,j));

			/* no comma if line is unshifted
			 * otherwise comma follows last word on original line
			 */
			if (shiftNum != 0 && j == numWords-shiftNum-1)
				printf(",");

			/* space follows every word but the last */
			if (j != SSNumWords(i)-1)
				printf(" ");
		}
		printf("\n");
	}
}
