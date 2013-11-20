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
	int i,j,k,w;
    int d = 0;

	for (i = 0; i < SSNumLines(); i++) {
		int numWords = SSNumWords(i);
		for (j = 0; j < numWords; j++) {
			int shiftNum = SSGetShiftNum(i);
			printf("%s\n",SSGetWord(i,j));
            const char * temp = SSGetWord(i,j);
            const char * first;
            const char * second;
            k = 0;
            while(temp[k] != '\0')
            {
                first[d] = &temp[k];
                d++;
                //printf("%c ", temp[k]);
                k++;
            }
            printf("%d \n",k);

			/* no comma if line is unshifted
			 * otherwise comma follows last word on original line
			 */
			//if (shiftNum != 0 && j == numWords-shiftNum-1)
				//printf(",");

			/* space follows every word but the last */
			//if (j != SSNumWords(i)-1)
				//printf(" ");
		}
        
        for(w = 0; w < 100; w++)
        {
            printf("%c ", first[w]);
        }
		printf("\n");
	}
}
