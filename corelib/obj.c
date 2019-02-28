#ifndef OBJ_C_
#define OBJ_C_

#ifndef OBJ_H_
#include "obj.h"
#endif


#include <string.h>


// link/unlink/next/prev = object can exist in only one list, but many lists is ok
// has destructor/free to clean and `run` for a argc/argv style


void obj_init( obj_t *self, const char *name, obj_free_f fn_free, obj_run_f fn_run, void *ctx )
{
	strncpy(self->name, name, 4);
	self->ctx = ctx;
	self->fn_free = fn_free;
	self->fn_run = fn_run;
	self->next = 0;
	self->prev = 0;
}


char *obj_run( obj_t *self, void *knl, int argc, const char **argv )
{
	if( self->fn_run )
	{
		return self->fn_run(argc, argv, knl, self->ctx);
	}

	return 0;
}


void obj_free( obj_t *self, void *knl )
{
	if( self->fn_free )
	{
		self->fn_free( knl, self->ctx );
	}
}


obj_t *obj_link( obj_t *head, obj_t *item )
{
	item->prev = 0;
	item->next = head;

	if( head ) 
	{
		head->prev = item;
	}
	return item;
}


obj_t *obj_unlink( obj_t *head, obj_t *item )
{
	obj_t *new_head = head;

	if( item == head )
	{
		new_head = item->next;
	}

	if( item->prev )
	{
		item->prev->next = item->next;
		// assert(item->prev->next == item)
	}

	if( item->next )
	{
		item->next->prev = item->prev;
		// assert(item->next->prev == item)
	}

	return new_head;
}


obj_t *obj_prev( obj_t *self )
{
	return self->prev;
}


obj_t *obj_next( obj_t *self )
{
	return self->next;
}


int obj_apply( obj_t *iter, obj_map_f map_fn, void *subctx )
{
	void *next = 0;
	int i = 0;

	while( iter != 0 )
	{
		map_fn(iter, subctx);

		iter = obj_next(iter);

		i = i + 1;
	}

	return i;
}


// OBJ_C_
#endif
