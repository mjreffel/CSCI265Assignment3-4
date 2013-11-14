/********** Output module---interface specification **********/

/***** overview *****
The Output module writes the lines provided by the ShiftSort module to stdout.
*/

/***** constants*****/

/***** types*****/

/***** exported functions *****/

/*
Initialize the Output module.
*/
void OUInit(void);

/*
Write the lines provided by the ShiftSort module to stdout.
Assumption: OUInit has been called.
*/
void OUPrint(void);

/***** usage example *****

If the LineStorage module contains the lines:
	"The C Programming Language"
	"The Cat in the Hat"

And the following calls are invoked:
	SSInit();
	SSShiftSort();
	OUInit();
	OUPrint();

Then invoking OUPrint will write the following lines to stdout:
	C Programming Language, The
	Cat in the Hat, The
	Hat, The Cat in the
	Language, The C Programming
	Programming Language, The C
	The C Programming Language
	The Cat in the Hat
	in the Hat, The Cat
	the Hat, The Cat in
*/
