#ifndef MOD_LINE
#define MOD_LINE

#ifndef KNL_H_
#include "knl.h"
#endif

#include <stdio.h>
#include <string.h>


static char* mod_line_run( int argc, const char **argv, void *_knl, void *ctx )
{
	char line[2048];

	if( 0 == gets(line) )
		return 0;

	return strdup(line);
}
obj_t mod_line = {{'L','I','N','E'}, mod_line_run};


// MOD_ECHO
#endif