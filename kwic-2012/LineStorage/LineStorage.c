/********** LineStorage module---implementation **********/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kwic.h"
#include "LineStorage.h"

/***** local constants *****/

/***** local types *****/

/*Each line is a list of WordNodes.*/
typedef struct WordNode {
	char* word;
	struct WordNode* nextWordPtr;
} WordNode;
typedef WordNode* WordNodePtr;

/*The LineStorage module stores a list of LineNodes*/
typedef struct LineNode {
	struct LineNode* nextLinePtr;
	WordNodePtr headWordPtr;
	WordNodePtr tailWordPtr;
	int wordCount;
} LineNode;
typedef LineNode* LineNodePtr;

/***** local variables *****/

static LineNodePtr headLinePtr, tailLinePtr;
static int lineCount;

/***** state invariant *****

1. if lineCount == 0 then
	headlinePtr == NULL
	taillinePtr == NULL
   else
	headLinePtr points to a null-terminated linked list of LineNodes.
	tailLinePtr points to the last LineNode in this list.
	There are lineCount LineNodes in this list.

2. for every LineNode allocated by LineStorage
	if wordCount == 0 then
	    headWordPtr == NULL
	    tailWordPtr == NULL
	else
	    headWordPtr points to a null-terminated linked list of WordNodes.
	    tailWordPtr points to the last WordNode in this list.
	    There are wordCount WordNodes in this list.

3. For every WordNode allocated word is a null-terminated array of characters.

4. All of the dynamic memory allocated by LineStorage (and not yet freed)
   is in the list structure headed by headLinePtr.
*/

/***** local functions *****/

/*
* if headLinePtr contains at least i+1 LineNodes then
*	return the address of the ith LineNode
* else
*	return NULL
* Assumed: the state invariant holds
*/
static LineNodePtr getLine(int i)
{
	LineNodePtr tmpLinePtr;

	if (i < 0)
		return NULL;
	for (tmpLinePtr = headLinePtr;
			i-- > 0 && tmpLinePtr != NULL;
			tmpLinePtr = tmpLinePtr->nextLinePtr)
		;
	return tmpLinePtr;
}

/*
* if wordNodePtr != NULL && the list headed by wordNodePtr has >= i words then
*	return a pointer to the ith word in the list headed by wordNodePtr
* else
*	return NULL
* Assumed: wordNodePtr is either NULL or a pointer to a list of WordNodes
*/
static WordNodePtr getWord(WordNodePtr wordNodePtr,int i)
{
	if (i < 0)
		return NULL;
	while (i-- > 0 && wordNodePtr != NULL) {
		wordNodePtr = wordNodePtr->nextWordPtr;
	}
	return wordNodePtr;
}

/***** exported functions *****/

void LSInit(void)
{
	headLinePtr = NULL;
	tailLinePtr = NULL;
	lineCount = 0;
}

void LSReset(void)
{
	LineNodePtr tmpLinePtr;
	WordNodePtr tmpWordPtr0,tmpWordPtr1;

	while (headLinePtr != NULL) {
		tmpWordPtr0 = headLinePtr->headWordPtr;
		while (tmpWordPtr0 != NULL) {
			tmpWordPtr1 = tmpWordPtr0->nextWordPtr;
			free(tmpWordPtr0->word);
			free(tmpWordPtr0);
			tmpWordPtr0 = tmpWordPtr1;
		}
		tmpLinePtr = headLinePtr;
		headLinePtr = headLinePtr->nextLinePtr;
		free(tmpLinePtr);
	}
	lineCount = 0;
	tailLinePtr = NULL;
}

KWStatus LSAddLine(void)
{
	LineNodePtr newLinePtr;

	/* create and fill a LineNode */
	newLinePtr = malloc(sizeof(LineNode));
	if (newLinePtr == NULL)
		return KWMEMORYERROR;
	lineCount++;
	newLinePtr->nextLinePtr = NULL;
	newLinePtr->headWordPtr = NULL;
	newLinePtr->tailWordPtr = NULL;
	newLinePtr->wordCount = 0;

	/* link in the new LineNode */
	if (tailLinePtr == NULL) {
		headLinePtr = newLinePtr;
	} else {
		tailLinePtr->nextLinePtr = newLinePtr;
	}
	tailLinePtr = newLinePtr;
	return KWSUCCESS;
}

KWStatus LSAddWord(char* word)
{
	WordNodePtr newWordPtr;

	if (tailLinePtr == NULL)
		return KWRANGEERROR;

	/* create and fill a WordNode */
	newWordPtr = malloc(sizeof(WordNode));
	if (newWordPtr == NULL)
		return KWMEMORYERROR;
	newWordPtr->word = malloc(strlen(word)+1);
	if (newWordPtr->word == NULL) {
		free(newWordPtr);
		return KWMEMORYERROR;
	}
	tailLinePtr->wordCount++;
	strcpy(newWordPtr->word,word);
	newWordPtr->nextWordPtr = NULL;

	/* link in the new WordNode */
	if (tailLinePtr->tailWordPtr == NULL) { /* empty line */
		tailLinePtr->headWordPtr = newWordPtr;
	} else {
		tailLinePtr->tailWordPtr->nextWordPtr = newWordPtr;
	}
	tailLinePtr->tailWordPtr = newWordPtr;
	return KWSUCCESS;
}

const char* LSGetWord(int lineNum,int wordNum)
{
	LineNodePtr tmpLinePtr;
	WordNodePtr tmpWordPtr;

	if (lineNum >= lineCount)
		return NULL;

	/* find line LineNum */
	tmpLinePtr = getLine(lineNum);
	if (tmpLinePtr == NULL)
		return NULL;

	/* find word wordNum */
	tmpWordPtr = getWord(tmpLinePtr->headWordPtr,wordNum);
	if (tmpWordPtr == NULL)
		return NULL;
	return tmpWordPtr->word;
}

int LSNumWords(int lineNum)
{
	LineNodePtr tmpLinePtr;

	/* find line lineNum */
	tmpLinePtr = getLine(lineNum);
	if (tmpLinePtr == NULL) {
		return KWRANGEERROR;
	}
	/* count the words in line lineNum */
	return tmpLinePtr->wordCount;
}

int LSNumLines(void)
{
	return lineCount;
}

void LSPrintState(void)
{
	LineNodePtr tmpLinePtr;
	WordNodePtr tmpWordPtr;

	printf("lineCount:%d\n",lineCount);
	for (tmpLinePtr = headLinePtr;
			tmpLinePtr != NULL;
			tmpLinePtr = tmpLinePtr->nextLinePtr) {
		printf("\twordCount:%d\n\t",tmpLinePtr->wordCount);
		for (tmpWordPtr = tmpLinePtr->headWordPtr;
				tmpWordPtr != NULL;
				tmpWordPtr = tmpWordPtr->nextWordPtr) {
			printf("!%s",tmpWordPtr->word);
		}
		printf("!\n");
	}
}
