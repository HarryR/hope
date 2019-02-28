#ifndef MOD_HELP
#define MOD_HELP

#ifndef KNL_H_
#include "knl.h"
#endif

#include <stdio.h>


// DISPLAY LIST OF COMMANDS + HELP
static char* mod_help_run( int argc, const char **argv, void *_knl, void *ctx )
{
	knl_t *knl = (knl_t*)_knl;
	obj_t *iter = knl_iter(knl);

	if( argc == 0 )
	{
		while( iter != 0 )
		{
			printf("%.4s\n", iter->name);

			iter = obj_next(iter);
		}		
	}
	else {
		printf("? %s\n", argv[0]);
	}

	return 0;
}
obj_t mod_help = {{'H','E','L','P'}, mod_help_run};


// MOD_HELP
#endif