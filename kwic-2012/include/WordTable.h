/********** WordTable module---interface specification **********/

/***** overview *****
The WordTable module reads a list of words from a file and allows the
user to check whether a given word is in this list.
*/

/***** constants *****/

/***** types *****/

/***** exported functions *****/

/*
* if the file named by the input argument noiseWdFileName is
* unreadable, an error message is printed on the standard error stream
* and
*	return KWFILEERROR
* otherwise, if there is main memory available
* 	load the words in file noiseWords into main memory
* 	words longer than 15 characters should be truncated to 15 characters
* 	return KWSUCCESS
* else
* 	return KWMEMORYERROR
* 
* Assumptions:
* 	The file specified by noiseWdFileName
* 		(a) contains one word per line
* 		(b) is sorted in strictly ascending order
*/
KWStatus WTInit(char *noiseWdFileName);

/*
* Return true if s is one of the words stored and false otherwise,
* ignoring case.
*/
int WTIsMember(char* s);

/*
* Display all the words stored to stdout.
* NOTE: for testing use only.
*/
void WTPrintState(void);

/***** usage example *****

If the file noiseWords contains:
	-
	and
	of
	the

then, following a call to WTInit:
	WTIsMember("of") returns true
	WTIsMember("Of") returns true
	WTIsMember("oF") returns true
	WTIsMember("OF") returns true
	WTIsMember("there") returns false
	WTIsMember("-") returns true
	WTIsMember("+") returns false
*/
