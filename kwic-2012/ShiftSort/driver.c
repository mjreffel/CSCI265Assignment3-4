/********** ShiftSort module---test driver **********/

#include <stdio.h>
#include "kwic.h"
#include "LineStorage.h"
#include "ShiftSort.h"

#define MAXWORDS 6

static struct {
	int numWords;
	int shiftNum;
	char* wordList[MAXWORDS];
} lineList[] = {
	{1,0,"A"},
	{1,0,"A"},
	{2,0,"A","B"},
	{2,0,"A","C"},
	{2,1,"B","A"},
	{2,1,"C","A"},
	{4,1,"C","Programming","Language","The"},
	{5,1,"Cat","in","the","Hat","The"},
	{5,4,"Hat","The","Cat","in","the"},
	{4,3,"Language","The","C","Programming"},
	{4,2,"Programming","Language","The","C"},
	{0} /* terminator */
};

static int errorCount = 0;

static void runTest()
{
	int i,j,status,numLines;
	int rangeErr[4];
	const char* word;

	/* count the number of lines */
	numLines = 0;
	for (i = 0; lineList[numLines].numWords != 0; i++)
		numLines++;

	printf("check that the lines have been shifted and sorted\n");
	if (SSNumLines() != numLines) {
		printf("Error in SSNumLines. Actual:%d Expected:%d\n",
			SSNumLines(),numLines);
		errorCount++;
	}
	for (i = 0; i < numLines; i++) {
		printf("\tline %d\n",i);
		if (SSNumWords(i) != lineList[i].numWords) {
			printf("Error in SSNumWords. Actual:%d Expected:%d\n",
				SSNumWords(i),lineList[i].numWords);
			errorCount++;
		}
		if (SSGetShiftNum(i) != lineList[i].shiftNum) {
			printf("Error in SSGetShiftNum. Actual:%d Expected:%d\n",
				SSGetShiftNum(i),lineList[i].shiftNum);
			errorCount++;
		}
		for (j = 0; j < lineList[i].numWords; j++) {
			printf("\t\tword %d\n",j);
			if (strcmp(SSGetWord(i,j),lineList[i].wordList[j])) {
				printf("Error in SSGetWord(%d,%d).",i,j);
				printf(" Actual:!%s! Expected:!%s!\n",
					SSGetWord(i,j),lineList[i].wordList[j]);
				errorCount++;
			}
		}
	}

	printf("check that line number range errors are properly signaled\n");
	rangeErr[0] = -1000;
	rangeErr[1] = -1;
	rangeErr[2] = numLines+1;
	rangeErr[3] = numLines+1000;
	for (i = 0; i < 4; i++) {
		printf("\tline %d\n",rangeErr[i]);
		word = SSGetWord(rangeErr[i],0);
		if (word != 0) {
			printf("Error in SSGetWord return value.");
			printf(" Actual:!%s! Expected:%d\n",word,0);
			errorCount++;
		}
		status = SSNumWords(rangeErr[i]);
		if (status != KWRANGEERROR) {
			printf("Error in SSNumWords return value.");
			printf(" Actual:%d Expected:%d\n",status,KWRANGEERROR);
			errorCount++;
		}
		status = SSGetShiftNum(rangeErr[i]);
		if (status != KWRANGEERROR) {
			printf("Error in SSGetShiftNum return value.");
			printf(" Actual:%d Expected:%d\n",status,KWRANGEERROR);
			errorCount++;
		}
	}

	printf("check that word number range errors are properly signaled\n");
	rangeErr[0] = -1000;
	rangeErr[1] = -1;
	rangeErr[2] = lineList[0].numWords+1;
	rangeErr[3] = lineList[0].numWords+1000;
	for (i = 0; i < 4; i++) {
		printf("\tline 0, word %d\n",rangeErr[i]);
		word = SSGetWord(0,rangeErr[i]);
		if (word != 0) {
			printf("Error in SSGetWord return value.");
			printf(" Actual:!%s! Expected:%d\n",word,0);
			errorCount++;
		}
	}
}

int main()
{
	SSInit();

	printf("invoke SSShiftSort\n");
	SSShiftSort();
	printf("run the tests\n");
	runTest();

	printf("invoke SSReset\n");
	SSReset();

	printf("invoke SSShiftSort again\n");
	SSShiftSort();
	printf("run the tests again\n");
	runTest();

	if (errorCount == 0)
		printf("\n\nNo errors detected!\n");

	return errorCount;
}
