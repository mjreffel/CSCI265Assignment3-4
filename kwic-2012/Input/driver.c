/********** Input module---test driver **********/

#include <stdio.h>
#include "kwic.h"
#include "Input.h"
#include "LineStorage.h"

int main(int argc,char* argv[])
{
	INInit();
	if (argc == 1)
		INLoad(NULL);
	else
		INLoad(argv[1]);
	return 0;
}
