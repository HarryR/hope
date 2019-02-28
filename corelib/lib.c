#ifndef LIB_C_
#define LIB_C_

#ifndef LIB_H_
#include "lib.h"
#endif

#include <ctype.h>


int strnicmp(const char *s, const char *t, unsigned n)
{
	while( n && *s != '\0' )
	{
		int rc = tolower((unsigned char)*s) - tolower((unsigned char)*t);

		if( rc != 0 )
		{
			return rc;
		}

		s++;
		t++;
		n--;
	}

	return 0;
}


int sicmp4( const char *a, const char *b )
{
	return strnicmp( a, b, 4);
}


// LIB_C_
#endif
