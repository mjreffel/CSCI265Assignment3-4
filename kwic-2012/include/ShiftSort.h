/********** ShiftSort module---interface specification **********/

/***** overview *****
The ShiftSort module computes a shifted and sorted version of the lines
stored in the LineStorage module.  Lines and words are made available
by line number and word number within line, as for the LineStorage
module.  However, ShiftSort provides access to the shifted and sorted
version.

The ShiftSort implementation stores line and word numbers but no
character strings; these are accessed when needed from the LineStorage
module.

No shifts are generated for the noise words specified in the WordTable
module interface specification.  That is, no line has a noise word in
the first position.

ASSUMPTIONS:

SSInit is called before any other ShiftSort function.

LSInit is called before any ShiftSort function other than SSInit.

SSShiftSort is called before any ShiftSort function except SSInit.

For any ShiftSort function except SSInit and SSShiftSort:  if a change
is made to the contents of the LineStorage module, SSShiftSort must be
called again.
*/

/***** constants*****/

/***** types*****/

/***** exported functions *****/

/*
* Initialize the module to have 0 lines
*/
void SSInit(void);

/*
* Remove all lines and words, freeing any dynamically allocated storage
*/
void SSReset(void);

/*
* attempt to compute the shifted and sorted lines
* if not enough memory is available then
*	return KWMEMORYERROR
* else
*	return KWSUCCESS
*/
KWStatus SSShiftSort(void);

/*
* if lineNum in [0..SSNumLines()-1] and wordNum in [0..SSNumWords()-1] then
*	return word wordNum from line lineNum
* else
*	return 0
*/
const char* SSGetWord(int lineNum,int wordNum);

/*
* if lineNum in [0..SSNumLines()-1] then
*	return the number of words in line lineNum
* else
*	return KWRANGEERROR
*/
int SSNumWords(int lineNum);

/*
* if lineNum in [0..SSNumLines()-1] then
*	return the number of left circular shifts that were applied to the
*	original line to generate line lineNum
* else
*	return 0
*/
int SSGetShiftNum(int lineNum);

/*
* return the total number of lines currently stored
*/
int SSNumLines(void);

/*
* Display the internal module state on stdout.
* NOTE: for testing use only.
*/
void SSPrintState(void);

/*****usage example*****

If the LineStorage module contains the lines:
	"The C Programming Language"
	"The Cat in the Hat"

And the following calls are invoked:
	SSInit();
	SSShiftSort();

ShiftSort will provide access to the following lines:
        "C", "Programming", "Language", "The"
        "Cat", "in", "the", "Hat", "The"
        "Hat", "The", "Cat", "in", "the"
        "Language", "The", "C", "Programming"
        "Programming", "Language", "The", "C"

As illustrated by the following calls:
	SSNumLines() will return 5
	SSNumWords(0) will return 4
	SSGetWord(0,0) will return "C"
	SSGetShiftNum(0) will return 3
*/
