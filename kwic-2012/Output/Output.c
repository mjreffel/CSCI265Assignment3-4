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
    
    // temporary string to hold single line
    const char * tmpString[80];
    // char variable to hold key word
    const char * KeyWord;
    // copy all words that will be after key word 
    const char * second[80];
    // copy all words before key words 
    const char * first[80];
    //calculate the time for outputing sorted words
    clock_t cstart = clock();
  	clock_t cend = 0;
  	// loop each line
        for (i = 0; i < SSNumLines(); i++) {
          int f = 0;
    	  int s = 0;
          int kw = 0;
          int Fcount = 0; 
          int Kcount = 0;
          int Scount = 0;
                int numWords = SSNumWords(i);
                // loop each line for words
                for (j = 0; j < numWords; j++) {
                        int shiftNum = SSGetShiftNum(i);
                        // copy each word in tmp
                        tmpString[j] = SSGetWord(i,j);
                }
               
               //divide each word in its category 
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
            // calculate length  and print words
            for (h = 0; h < f; h++) { 
            	int len = strlen(first[h]);
  				Fcount = Fcount + len +1;
            	printf("%s ", first[h]);
            }
            // length of key word 
            Kcount = strlen(Fword); 
            printf("%s ", Fword);
            // length of second words    
            for (e = 0; e < s; e++) {
            	int Slen = strlen(second[e]);
            	Scount = Scount + Slen;
               	printf("%s ", second[e]);
            }
        /*************/
                printf("\n");
              // print spaces under each first word  
              for (b = 0; b < Fcount; b++){
                printf(" ");
                }
               // print underscore under key word
                for (c =0; c < Kcount; c++){
                printf("-");
                }
                // print spaces after key word
                for (a=0; a < Scount; a++){
                printf(" ");
                }
                printf("\n");                           
        }
          
       cend = clock();
       //printf ("%.3f cpu sec\n", ((double)cend - (double)cstart)* 1.0e-6);
}