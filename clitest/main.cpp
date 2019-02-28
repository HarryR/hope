
#include "../mods/eval.c"
#include "../mods/help.c"
#include "../mods/repl.c"
#include "../mods/loop.c"
#include "../mods/echo.c"
#include "../mods/line.c"


int main( int argc, char **argv )
{
	char *ret;
	knl_t ctx;

	knl_init(&ctx);

	// Add commands
	knl_add( &ctx, &mod_eval );
	knl_add( &ctx, &mod_help );
	knl_add( &ctx, &mod_repl );
	knl_add( &ctx, &mod_loop );
	knl_add( &ctx, &mod_echo );
	knl_add( &ctx, &mod_line );

	// replace with:
	// knl_eval( &ctx, "LOOP \"ECHO [ EVAL $LINE ]\"" );
	ret = knl_eval( &ctx, "repl" );
	if( ret ) {
		free( ret );
	}

	knl_destroy(&ctx, 0);

	return 0;
}
