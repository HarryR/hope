#ifndef MOD_LOOP
#define MOD_LOOP

#ifndef KNL_H_
#include "knl.h"
#endif


static char* mod_loop_run( int argc, const char **argv, void *_knl, void *ctx )
{
	knl_t *knl = (knl_t*)_knl;
	int i;

	while( 1 )
	{
		for( i = 0; i < argc; i++ )
		{
			knl_eval(knl, argv[i]);
		}
	}

	return 0;
}

obj_t mod_loop = {{'L','O','O','P'}, mod_loop_run};


// MOD_LOOP
#endif