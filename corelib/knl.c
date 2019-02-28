#ifndef KNL_C_
#define KNL_C_

#ifndef KNL_H_
#include "knl.h"
#endif

#ifndef ARG_H_
#include "arg.h"
#endif

#ifndef LIB_H_
#include "lib.h"
#endif


#include <stdlib.h>

#include <string.h>


// INPUT ARGUMENTS ARE EVALUATED THEN PASSED TO KNL-RUNV
static char* _eval_run_inner( int argc, const char **argv, knl_t *knl, void *_ctx, int *skip )
{
	char *ret = 0;
	int i;
	const char **new_argv = 0;
	int new_argc = 0;
	const char *arg;
	const char *new_arg = 0;
	const char *tmp_argv;
	int tmp = 0;
	int skip_tmp = 0;
	int do_exec = 0;
	
	if( ! skip )
		skip = &skip_tmp;

	for( i = 0; i < argc; i++ )
	{
		arg = argv[i];

		if( ! arg )	// skip empty
			continue;

		// only first char of symbol matters
		switch( arg[0] )
		{
		// sub-expression calls self to parse, then skips N args		
		case '[':
			// Parse sub-expression until ']'
			new_arg = _eval_run_inner( argc - i - 1, &argv[i + 1], knl, _ctx, &tmp );
			i += tmp;
			break;

		case ']':
			*skip = i;
			return knl_runv( knl, new_argc, new_argv );

		case '$': // Call symbol, use result as argument
			tmp_argv = &arg[1];
			new_arg = knl_runv( knl, 1, &tmp_argv );
			break;
		
		case ';': // evaluate current call, begin next one
			do_exec = 1;
			break;

		default:
			new_arg = arg;
			break;
		}

		// collect argument into new argc/argv
		if( new_arg )
		{
			new_argc += 1;
			new_argv = (const char**)realloc((char*)new_argv, sizeof(char*) * new_argc);
			new_argv[new_argc - 1] = new_arg;
			new_arg = 0;
		}

		// evaluate collected arguments...
		if( do_exec || i >= (argc - 1) )
		{
			if( ret )
			{
				free(ret);
			}

			ret = knl_runv( knl, new_argc, new_argv );

			if( new_argv )
			{
				free((char*)new_argv);
				new_argv = 0;
			}

			new_argc = 0;		
			do_exec = 0;
		}
	}

	return ret;
}


// parses command-line string into argc/argv, evaluates tokens
char *knl_eval( knl_t *knl, const char *args )
{
	int argc = 0;

	char **argv = CommandLineToArgvA(args, &argc);

	int skip = 0;

	char *ret = _eval_run_inner( argc, (const char **)argv, (knl_t*)knl, knl, &skip );

	if( argv )
	{
		free(argv);
	}

	return ret;
}


void knl_init( knl_t *knl )
{
	knl->lock = lck_new();

	knl->cmds = 0;
}


void knl_lock( knl_t *knl )
{
	lck_get(knl->lock);
}


void knl_unlock( knl_t *knl )
{
	lck_rel(knl->lock);
}


char *knl_runv( knl_t *knl, int argc, const char **argv )
{
	obj_t *cmd;

	if( argc <= 0 )
		return 0;

	cmd = knl_get(knl, argv[0]);

	if( ! cmd )
		return 0;

	return cmd->fn_run( argc-1, &argv[1], knl, cmd->ctx );
}


obj_t *knl_iter( knl_t *knl ) 
{
	return knl->cmds;
}


void knl_add( knl_t *knl, obj_t *cmd )
{
	knl_lock(knl);

		knl->cmds = obj_link(knl->cmds, cmd);

	knl_unlock(knl);
}


obj_t *knl_get( knl_t *knl, const char *name )
{
	obj_t *iter = knl->cmds;

	knl_lock( knl );

		while( iter != 0 )
		{
			if( 0 == sicmp4(iter->name, name) )
			{
				knl_unlock( knl );

				return iter;
			}

			iter = obj_next(iter);
		}

	knl_unlock( knl );

	return 0;
}


void knl_del( knl_t *knl, obj_t *cmd )
{
	knl_lock(knl);

		obj_free(cmd, knl);

		knl->cmds = obj_unlink(knl->cmds, cmd);

	knl_unlock(knl);
}


static void _map_del_fn( obj_t *item, void *ctx )
{
	knl_del( (knl_t*)ctx, item );
}


void knl_destroy( knl_t *knl, void *ctx )
{	
	lck_get(knl->lock);

		obj_apply( knl->cmds, _map_del_fn, knl );

	lck_del(knl->lock);
}


// KNL_C_
#endif
