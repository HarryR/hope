#ifndef MOD_EVAL
#define MOD_EVAL

#ifndef KNL_H_
#include "knl.h"
#endif

#include <stdlib.h>


static char* mod_eval_run( int argc, const char **argv, void *knl, void *_ctx )
{
	int i;
	char *ret = 0;

	for( i = 0; i < argc; i++ )
	{
		if( ret )
		{
			free(ret);
		}

		ret = knl_eval( (knl_t*)knl, argv[i] );
	}

	return ret;
}

obj_t mod_eval = {{'E','V','A','L'}, mod_eval_run};


// MOD_EVAL
#endif
