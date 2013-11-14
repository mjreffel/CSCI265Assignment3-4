/********** ShiftSort module---implementation **********/

#include <stdio.h>
#include <stdlib.h>
#include "kwic.h"
#include "LineStorage.h"
#include "ShiftSort.h"

/***** local constants *****/

/***** local types *****/

typedef struct {
        int lineNum;
        int shiftNum;
} LineList,*LineListPtr;

/***** local variables *****/

static LineListPtr lineList;
static int lineCount;

/***** state invariant *****

1. lineCount >= 0

2. if lineCount == 0 then
	lineList == NULL

3. if lineCount > 0
	lineList is a pointer to an array of lineCount lineLists's

4. forall i in [0..lineCount-1]
	lineList[i].lineNum in [0..LSNumLines()-1]
	lineList[i].shiftNum in [0..LSNumWords(lineList[i].lineNum)-1]

*/

/***** local functions *****/

/* return word wordNum from the shifted LineStorage line specified by linePtr */
static const char* getWord(LineListPtr linePtr,int wordNum)
{
        int shiftedWordNum;

        shiftedWordNum = (wordNum+linePtr->shiftNum) %
		LSNumWords(linePtr->lineNum);
        return LSGetWord(linePtr->lineNum,shiftedWordNum);
}

/*
* if line0 < line1
*       return a negative value
* else if line0 == line1
*       return 0
* else
*       return a positive value
*/
static int lineCompare(LineListPtr line0,LineListPtr line1)
{
        int i,j,minNumWords,minLine;

        if (LSNumWords(line0->lineNum) < LSNumWords(line1->lineNum))
                minNumWords = LSNumWords(line0->lineNum);
        else
                minNumWords = LSNumWords(line1->lineNum);
        for (i = 0; i < minNumWords; i++) {
                j = strcmp(getWord(line0,i),getWord(line1,i));
                if (j != 0)
                        return j;
        }
        /* assert: line0 and line1 are equal for the first min words */
        return LSNumWords(line0->lineNum) - LSNumWords(line1->lineNum);
}

/*****exported functions*****/

void SSInit(void)
{
        lineList = NULL;
        lineCount = 0;
}

void SSReset(void)
{
        if (lineList != NULL)
                free(lineList);
        lineList = NULL;
        lineCount = 0;
}

KWStatus SSShiftSort(void)
{
        int i,j,k;

        /* compute the size of lineList */
        lineCount = 0;
        for (i = 0; i < LSNumLines(); i++) {
		for (j = 0; j < LSNumWords(i); j++) {
			/* exclude lines that start with a noise word */
			if (!WTIsMember(LSGetWord(i,j)))
				lineCount++;
		}
        }

        /* allocate space for lineList */
        lineList = calloc(lineCount, sizeof(LineList));
        if (lineList == NULL) {
		lineCount = 0;
                return KWMEMORYERROR;
	}

        /* fill lineList */
        k = 0;
        for (i = 0; i < LSNumLines(); i++) {
                for (j = 0; j < LSNumWords(i); j++) {
			/* exclude lines that start with a noise word */
			if (!WTIsMember(LSGetWord(i,j))) {
				lineList[k].lineNum = i;
				lineList[k].shiftNum = j;
				k++;
			}
                }
        }

        /* sort the shifted lines */
        qsort(lineList,lineCount,sizeof(LineList),
                (int (*)(const void *, const void *))lineCompare);

        return KWSUCCESS;
}

const char* SSGetWord(int lineNum,int wordNum)
{
        if (lineNum < 0 || lineNum >= lineCount || wordNum < 0 ||
			wordNum >= LSNumWords(lineList[lineNum].lineNum))
                return NULL;
        else
                return getWord(&lineList[lineNum],wordNum);
}

int SSNumWords(int lineNum)
{
        if (lineNum < 0 || lineNum >= lineCount)
                return(KWRANGEERROR);
        else
                return(LSNumWords(lineList[lineNum].lineNum));
}

int SSGetShiftNum(int lineNum)
{
        if (lineNum < 0 || lineNum >= lineCount)
                return(KWRANGEERROR);
        else
                return(lineList[lineNum].shiftNum);
}

int SSNumLines(void)
{
        return(lineCount);
}

void SSPrintState(void)
{
        int i;

        for (i = 0; i < lineCount; i++)
                printf("lineList[%d]: lineNum=%d shiftNum=%d\n",
                        i,lineList[i].lineNum,lineList[i].shiftNum);
}
