/********** Input module---interface specification **********/

/***** overview *****
The Input module reads a list of lines from stdin and loads those
lines, a word at a time, into the LineStorage module.
*/

/***** constants *****/

/***** types *****/

/***** exported functions *****/

/*
* Initialize the module
*/
void INInit(void);

/*
* Attempt to load the lines into the LineStorage module.
* The lines are read from stdin if filename is NULL;
* otherwise the lines are read from the file whose name
* is specified by filename.
* If the file named by filename cannot be opened for input then
*	return KWFILEERROR
* else if not enough memory is available then
*	return KWMEMORYERR
* else
*	return KWSUCCESS
* 
* Assumption: LSInit has been called.
*/
KWStatus INLoad(char *filename);

/***** usage example *****

To load the following lines, entered through stdin:
	"The C Programming Language"
	"The Cat in the Hat"

Issue the calls:
	INInit();
	LSInit();
	INLoad(NULL);

After these calls:
	LSNumLines() will return 2
	LSNumWords(0) will return 4
	LSGetWord(0,2) will return "Programming"
	LSGetWord(1,5) will return 0
*/
