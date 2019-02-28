#ifndef MOD_ECHO
#define MOD_ECHO

#ifndef KNL_H_
#include "knl.h"
#endif

#include <stdio.h>


static char* mod_echo_run( int argc, const char **argv, void *_knl, void *ctx )
{
	int i;

	for( i = 0; i < argc; i++ )
	{
		printf("%s", argv[i]);
	}

	printf("\n");

	return 0;
}
obj_t mod_echo = {{'E','C','H','O'}, mod_echo_run};


// MOD_ECHO
#endif