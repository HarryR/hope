#ifndef OBJ_H_
#define OBJ_H_


typedef struct obj_s obj_t;


typedef void* (*obj_new_f)(void *knl);

typedef char* (*obj_run_f)(int argc, const char **argv, void *knl, void *ctx);

typedef void (*obj_free_f)(void *knl, void *ctx);

typedef void (*obj_map_f)(obj_t *item, void *ctx);


struct obj_s
{
	// META / DEFINITION

	char name[4];	

	obj_run_f fn_run;

	obj_free_f fn_free;

	// STATE VARIABLES

	void *ctx;

	obj_t *next;

	obj_t *prev;
};


void obj_init( obj_t *self, const char *name, obj_free_f fn_free, obj_run_f fn_run, void *ctx );

char *obj_run( obj_t *self, void *knl, int argc, const char **argv );

void obj_free( obj_t *self, void *knl );

obj_t *obj_link( obj_t *head, obj_t *item );

obj_t *obj_unlink( obj_t *head, obj_t *item );

obj_t *obj_prev( obj_t *self );

obj_t *obj_next( obj_t *self );

int obj_apply( obj_t *iter, obj_map_f map_fn, void *subctx );


// OBJ_H_
#endif
