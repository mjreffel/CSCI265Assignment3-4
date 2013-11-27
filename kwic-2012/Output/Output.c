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
    const char * first[10];
    const char * second[10];

        for (i = 0; i < SSNumLines(); i++) {
                int numWords = SSNumWords(i);
                for (j = 0; j < numWords; j++) {
                        int shiftNum = SSGetShiftNum(i);
                        // need to store spaces in the array including comma 
                        second[j] = SSGetWord(i,j);
                        //d++;
                }
                const char *key = second[0];
                for (w = 0; w < 10; w++){
                	if (w >= SSGetShiftNum(i) && second[w] != "") {
                		first[d] = second[w];
                		second[w]= "";
                		d++;
                	}
                }
                printf("%s\n", key);
                 for (k = 0; k < numWords-SSGetShiftNum(i); k++ ) {
                 //printf("second: ");
                 printf("%s", second[k]);
                 if (j != SSNumWords(i)-1){
                   printf(" ");
                    }
                    }
                    
                for (k = 0; k < SSGetShiftNum(i); k++ ) {
                 printf("%s", first[k]);
                 if (j != SSNumWords(i)-1){
                   printf(" ");
                    }
        		
        		}
                printf("\n");
        }
       
}