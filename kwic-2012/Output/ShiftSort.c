/********** ShiftSort module---test stub **********/

#include "kwic.h"
#include "LineStorage.h"
#include "ShiftSort.h"

/***** local constants *****/

#define NUMLINES 9
#define MAXWORDS 6

/***** local variables *****/

static struct {
	int numWords;
	int shiftNum;
	char* wordList[MAXWORDS];
} lineList[NUMLINES] = {
	{4,1,"C","Programming","Language","The"},
	{5,1,"Cat","in","the","Hat","The"},
	{5,4,"Hat","The","Cat","in","the"},
	{4,3,"Language","The","C","Programming"},
	{4,2,"Programming","Language","The","C"},
	{4,0,"The","C","Programming","Language"},
	{5,0,"The","Cat","in","the","Hat"},
	{5,2,"in","the","Hat","The","Cat"},
	{5,3,"the","Hat","The","Cat","in"}
};

/***** exported functions *****/

const char* SSGetWord(int lineNum,int wordNum)
{
	return lineList[lineNum].wordList[wordNum];
}

int SSNumWords(int lineNum)
{
	return lineList[lineNum].numWords;
}

int SSGetShiftNum(int lineNum)
{
	return lineList[lineNum].shiftNum;
}

int SSNumLines(void)
{
	return NUMLINES;
}
