/********** LineStorage module---interface specification **********/

/***** overview *****
The LineStorage module stores a list of lines, where each line is a
list of C strings.  The lines and the words within a line are indexed
zero-relative.

Lines are added a word at a time, in an append-only fashion.  Each word
is added to the end of the highest-numbered line currently stored.
Word and line deletion are not supported.

Any word in any line can be retrieved at any time.
*/

/***** constants *****/

/***** types *****/

/***** exported functions *****/

/*
* Initialize the module with 0 lines
*/
void LSInit(void);

/*
* Remove all lines and words, free'ing any dynamically allocated storage
*/
void LSReset(void);

/*
* if not enough memory is available to add a new line then
*	return KWMEMORYERR
* else
*	add a line, containing no words, in position LSNumLines()
*	return KWSUCCESS
*/
KWStatus LSAddLine(void);

/*
* if LSNumLines() == 0 then
*	return KWRANGEERR
* else if not enough memory is available to store word then
*	return KWMEMORYERR
* else
*	add word to the end of line LSNumLines()-1
*	return KWSUCCESS
*/
KWStatus LSAddWord(char* word);

/*
* if lineNum in [0..LSNumLines()-1] and wordNum in [0..LSNumWords()-1] then
*	return word wordNum from line lineNum
* else
*	return NULL
*/
const char* LSGetWord(int lineNum,int wordNum);

/*
* if lineNum in [0..LSNumLines()-1] then
*	return the number of words in line lineNum
* else
*	return KWRANGEERR
*/
int LSNumWords(int lineNum);

/*
* return the total number of lines currently stored
*/
int LSNumLines(void);

/*
* Display all the lines and words to stdout.
* NOTE: for testing use only.
*/
void LSPrintState(void);

/***** usage example *****

To store the lines:
	"The C Programming Language"
	"The Cat in the Hat"

Issue the calls:
	LSInit();
	LSAddLine();
	LSAddWord("The");
	LSAddWord("C");
	LSAddWord("Programming");
	LSAddWord("Language");
	LSAddLine();
	LSAddWord("The");
	LSAddWord("Cat");
	LSAddWord("in");
	LSAddWord("the");
	LSAddWord("Hat");

After these calls:
	LSNumLines() will return 2
	LSNumWords(0) will return 4
	LSGetWord(0,2) will return "Programming"
	LSGetWord(1,5) will return 0
*/
