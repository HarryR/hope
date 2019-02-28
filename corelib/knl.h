#ifndef KNL_H_
#define KNL_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef OBJ_H_
#include "obj.h"
#endif

#ifndef LCK_H_
#include "lck.h"
#endif


struct knl_s {
	obj_t *cmds;
	lck_t lock;
};
typedef struct knl_s knl_t;


void knl_init( knl_t *knl );

void knl_destroy( knl_t *knl, void *ctx );

char *knl_eval( knl_t *knl, const char *commandline );

char *knl_runv( knl_t *knl, int argc, const char **argv );

obj_t *knl_iter( knl_t *knl );

obj_t *knl_get( knl_t *knl, const char *cmd_name );

void knl_add( knl_t *knl, obj_t *cmd );

void knl_del( knl_t *knl, obj_t *cmd );

void knl_lock( knl_t *knl );

void knl_unlock( knl_t *knl );


#ifdef __cplusplus
}
#endif


// KNL_H_
#endif
