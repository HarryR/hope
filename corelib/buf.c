#ifndef BUF_C_
#define BUF_C_

#ifndef BUF_H_
#include "buf.h"
#endif

#include <stdlib.h>
#include <string.h>


buf_t *buf_new( const char *data, unsigned int len )
{
	buf_t *buf = malloc( sizeof(unsigned int) + len );

	buf->len = len;

	memcpy( &buf->data, data, len );

	return buf;
}


buf_t *buf_from_str( const char *str )
{
	return buf_new( str, strlen(str) + 1 );
}


unsigned int buf_len( buf_t *buf )
{
	return buf->len;
}


char *buf_data( buf_t *buf )
{
	return &buf->data;
}


void buf_free( buf_t *buf )
{
	buf->len = 0;
	free(buf);
}


// BUF_C_
#endif
