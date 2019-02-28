#ifndef BUF_H_
#define BUF_H_

struct buf_s {	
	unsigned int len;
	char data;
};

typedef struct buf_s buf_t;


buf_t *buf_new( const char *data, unsigned int len );

buf_t *buf_from_str( const char *str );

unsigned int buf_len( buf_t *buf );

char *buf_data( buf_t *buf );

void buf_free( buf_t *buf );

// BUF_H_
#endif
