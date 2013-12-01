/********** Output module---implementation **********/

#include <stdio.h>
#include "kwic.h"
#include "Output.h"
#include "ShiftSort.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
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
    
    // need to move it inside the loop and initialize it to length of num words 
    // when done, delete the contant of the array and resize it. 
    const char * tmpString[80];
    const char * Fword;
    const char * second[80];
    const char * first[80];
    clock_t cstart = clock();
  	clock_t cend = 0;
        for (i = 0; i < SSNumLines(); i++) {
          int f = 0;
    	  int s = 0;
          int kw = 0;
          int Fcount = 0; 
          int Kcount = 0;
          int Scount = 0;
                int numWords = SSNumWords(i);
                for (j = 0; j < numWords; j++) {
                        int shiftNum = SSGetShiftNum(i);
                        // need to store spaces in the array including comma 
                        tmpString[j] = SSGetWord(i,j);
                }
               
                for(d=0; d<numWords; d++)
                {
                int sizeOffirst = 0;
                                if(d == 0){
                                Fword = tmpString[d];
                                
                        }
                        
                        if(d <= numWords - SSGetShiftNum(i) - 1 && d !=0) {
                                second[s] = tmpString[d];
                                s++; 
                        }
                        
                        if(d > numWords - SSGetShiftNum(i) - 1){
                                first[f] = tmpString[d];
                                f++;
                	} 
                
                }
               
            for (h = 0; h < f; h++) { 
            int len = strlen(first[h]);
  				
  				Fcount = Fcount + len +1;
            	printf("%s ", first[h]);
            }
             Kcount = strlen(Fword); 
            printf("%s ", Fword);
               
            for (e = 0; e < s; e++) {
            
            int Slen = strlen(second[e]);
            Scount = Scount + Slen;
               printf("%s ", second[e]);
            }
        /*************/
                printf("\n");
                
              for (b = 0; b < Fcount; b++){
                printf(" ");
                }
               // printf(" ");
                for (c =0; c < Kcount; c++){
                printf("-");
                }
                for (a=0; a < Scount; a++){
                printf(" ");
                }
                printf("\n");
     //   printf(" :beforeKey: %d\n", Fcount);
       // printf(" :Key: %d\n", Kcount);   
       // printf(" :after: %d\n", Scount); 
                               
        }
          
       cend = clock();
       printf ("%.3f cpu sec\n", ((double)cend - (double)cstart)* 1.0e-6);
}