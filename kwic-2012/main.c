#include <stdio.h>
#include <stdlib.h>

#include "kwic.h"
#include "Input.h"
#include "LineStorage.h"
#include "ShiftSort.h"
#include "Output.h"
#include "WordTable.h"

static char *nwEnvVariableName = "KWICNOISEWORDS";
static char *nwDefaultFileName = "noiseWords";


int main( int argc, char *argv[] )
{
    int returnCode, argnum;
    char *nwFileName = NULL;
    char *cp;

    /*	process command line options -- stopping at the
	first filename argument.  */
    for( argnum = 1;  argnum < argc;  argnum++ ) {
	cp = argv[argnum];
	if (cp[0] == '-') {
	    if (cp[1] == 'n')
		nwFileName = argv[++argnum];
	    else
		fprintf(stderr,
		    "unknown option %s -- ignored\n", cp);
	} else
	    break;
    }

    /*	determine the location of the noise words file and read it  */
    if (nwFileName == NULL) {
	nwFileName = getenv(nwEnvVariableName);
	if (nwFileName == NULL)
	    nwFileName = nwDefaultFileName;
    }
    returnCode = WTInit(nwFileName);
    if (returnCode != KWSUCCESS)
	exit(returnCode);

    /*	initialize various modules  */
    INInit();
    LSInit();
    SSInit();
    OUInit();

    /*	determine the input source(s) and read them  */
    if (argnum >= argc) {
	/* no filename arguments --> read from standard input */
	returnCode = INLoad(NULL);
    } else {
	/* read each file named on command line */
	while(argnum < argc) {
	    returnCode = INLoad(argv[argnum]);
	    if (returnCode != KWSUCCESS) break;
	    argnum++;
	}
	if (returnCode == KWFILEERROR)
	    perror(argv[argnum]);
    }

    if (returnCode != KWSUCCESS)
	exit(returnCode);

    /*	perform the real work  */
    returnCode = SSShiftSort();
    if (returnCode != KWSUCCESS)
	exit(returnCode);

    /*	output the results  */
    OUPrint();

    return 0;
}
