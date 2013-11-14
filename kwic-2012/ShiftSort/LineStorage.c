/********** LineStorage module---test stub **********/

#include <stdio.h>
#include "kwic.h"
#include "LineStorage.h"

/***** local constants *****/

/***** local types *****/

/***** local variables *****/

#define NUMLINES 6
#define MAXWORDS 6

static struct {
	int numWords;
	char* wordList[MAXWORDS];
} lineList[NUMLINES] = {
	/* tests specifically for lineCompare */
	{2,"A","B"},
	{1,"A"},
	{1,"A"},
	{2,"A","C"},

	/* general-purpose tests */
	{5,"The","Cat","in","the","Hat"},
	{4,"The","C","Programming","Language"}
};

/*****exported functions*****/

int LSNumLines(void)
{
	return NUMLINES;
}

int LSNumWords(int lineNum)
{
	return lineList[lineNum].numWords;
}

const char* LSGetWord(int lineNum,int wordNum)
{
	if (lineNum < 0 || lineNum >= NUMLINES ||
	wordNum < 0 || wordNum >= lineList[lineNum].numWords)
		return NULL;
	else
		return lineList[lineNum].wordList[wordNum];
}
