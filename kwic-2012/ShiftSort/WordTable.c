/********** WordTable module---test stub **********/

#include <stdio.h>
#include <string.h>
#include "kwic.h"
#include "WordTable.h"

/***** local constants *****/

/***** local types *****/

/***** local variables *****/

/***** exported functions *****/

int WTIsMember(char* s)
{
	return (strcasecmp(s,"in") == 0 || strcasecmp(s,"the") == 0);
}
