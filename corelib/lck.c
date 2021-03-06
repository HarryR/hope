#ifndef LCK_C_
#define LCK_C_

#ifndef LCK_H_
#include "lck.h"
#endif


#ifdef WIN32

#include <windows.h>


lck_t lck_new()
{
	return CreateMutex(NULL, FALSE, NULL);
}


lck_t lck_del(lck_t x)
{
	if( x != INVALID_HANDLE_VALUE )
		CloseHandle(x);

	return INVALID_HANDLE_VALUE;
}


void lck_get(lck_t x)
{
	if( x != INVALID_HANDLE_VALUE )
		WaitForSingleObject(x, INFINITE);
}


void lck_rel(lck_t x)
{
	if( x != INVALID_HANDLE_VALUE )
		ReleaseMutex(x);
}


// WIN32
#else

#include <stdlib.h>
#include <pthread.h>


lck_t lck_new()
{
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

	pthread_mutex_t *mtx = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mtx, &attr);

	pthread_mutexattr_destroy(&attr);

	return (lck_t)mtx;
}


lck_t lck_del(lck_t x)
{
	pthread_mutex_t *mtx = (pthread_mutex_t *)x;
	pthread_mutex_destroy(mtx);
	free(mtx);
	return 0;
}


void lck_get(lck_t x)
{
	pthread_mutex_t *mtx = (pthread_mutex_t *)x;
	pthread_mutex_lock(mtx);
}


void lck_rel(lck_t x)
{
	pthread_mutex_t *mtx = (pthread_mutex_t *)x;
	pthread_mutex_unlock(mtx);
}


// non-win32
#endif


// LCK_C
#endif
