#ifndef MOD_REPL
#define MOD_REPL

#ifndef KNL_H_
#include "knl.h"
#endif

#ifndef LIB_H_
#include "lib.h"
#endif

#include <stdio.h>
#include <stdlib.h>


static char* mod_repl_run( int argc, const char **argv, void *_knl, void *ctx )
{
	knl_t *knl = (knl_t*)_knl;
	char line[2048];	// XXX: overflow?

	while( 1 )
	{
		printf("> ");

		if( 0 == gets(line) )
			break;

		if( 0 == sicmp4(line, "EXIT") )
			break;

		char* retval = knl_eval( knl, line );

		if( retval )
		{
			printf("= %s\n", retval);
			free(retval);
		}
		else {
			printf("!\n");
		}
	}
	return 0;
}

obj_t mod_repl = {{'R','E','P','L'}, mod_repl_run};


// MOD_REPL
#endif
