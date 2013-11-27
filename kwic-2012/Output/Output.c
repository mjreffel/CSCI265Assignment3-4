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
    int i,j,k,w,h,a,b,c,e;
    int d = 0;
    const char * tmpString[10];
    const char * Fword[10];
    const char * second[10];
	const char * first[10];
	int f = 0;
    int s = 0;
    int kw = 0;
    
    // char * second;

        for (i = 0; i < SSNumLines(); i++) {
        int fCharCount = 0;
                int numWords = SSNumWords(i);
                for (j = 0; j < numWords; j++) {
                        int shiftNum = SSGetShiftNum(i);
                        // need to store spaces in the array including comma 
                        tmpString[j] = SSGetWord(i,j);
                }
               
                for(d=0; d<numWords; d++)
                {
               	 	if(d == 0){
                		Fword[kw] = tmpString[d];
                	}
                	
                	if(d <= numWords - SSGetShiftNum(i) - 1 && d !=0) {
                		second[s] = tmpString[d];
                		s++; 
                	}
                	
                	if(d > numWords - SSGetShiftNum(i) - 1){
                	
                	/***********Calculating length of first**********/
                		const char * tmpF = tmpString[d];
                		for(a = 0; tmpF[a]; a++)
               		 	{
               		 		
                			if(tmpF[a] != ' '){
                				fCharCount++;
                			}
                		
                		}
                		first[f] = tmpF;
                		f++;
                		fCharCount++;
                	}               	
                } 
                
                
                /*******print first*******/
                
                
               for ( w = 0; w < f; w++) {
              printf ("%s ", first[w]);
              }
              
                
                
                //calculating length of all words before the key word
                /*int fCharCount = 0;
                for (b = 0; b < f; b++) {
                 	for(a = 0; first[b]; a++)
               		 {
               		 	const char * tmpF = first[b];
                		if(tmpF[b] != ' '){
                			fCharCount++;
                		}
                		fCharCount++;
                }*/
                
       //         printf ("%d\n", fCharCount);
                
                
                //const char * tmpFirst = first[0]
              //  for (a = 0; a < f; a++)
                	//const char * tmpFirst = first[a];
               		
                
                
            	/**********print k word********/
                printf("%s ", Fword[0]);
                
                //***********calculating key word length************
                
                const char * tmpKeyWord = Fword[0];
                
                int kwCharCount = 0;
                
                for(h = 0; tmpKeyWord[h]; h++)
                {
                if(tmpKeyWord[h] != ' ')
                	kwCharCount++;
                }
                
                /*******printing length of key word******/
    //            printf("%d\n", kwCharCount);
                
                /**********print second***********/ 
                for ( k = 0; k < s; k++ ){
                printf("%s ", second[k]);
                }      
                printf("\n"); 
                
                
                //**********printing number of spaces**********
                for(  c = 0; c < fCharCount; c++)
                {
                	printf(" ");
                }
                                
                //**********printing number of underscores********
                
               // for( e = 0; e<kwCharCount; e++)
               // {
                	//printf("-");
             //   }
                printf("\n");
        	        	
        }
        
       
}