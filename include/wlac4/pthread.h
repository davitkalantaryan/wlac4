//
// file:			pthread.h
// path:			include/wlac4/pthread.h
// created on:		2022 Sep 11
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef WLAC4_INCLUDE_WLAC4_PTHREAD_H
#define WLAC4_INCLUDE_WLAC4_PTHREAD_H

#include <wlac4_exports.h>


WLAC4_BEGIN_C

#define PTHREAD_RWLOCK_INITIALIZER		LIBDNL_NULL
#define PTHREAD_MUTEX_INITIALIZER		LIBDNL_NULL

#define PTHREAD_CREATE_JOINABLE			0
#define PTHREAD_CREATE_DETACHED			1


typedef struct pthread_mutex_s*	pthread_mutex_t;
typedef struct pthread_mutexattr_s* pthread_mutexattr_t;
typedef struct pthread_rwlock_s* pthread_rwlock_t;
typedef struct pthread_rwlockattr_s* pthread_rwlockattr_t;
typedef struct pthread_s* pthread_t;
typedef struct pthread_key_s* pthread_key_t;
typedef struct pthread_attr_s* pthread_attr_t;


WLAC4_WLAC4_EXPORT int   pthread_mutex_init(pthread_mutex_t* mutex, const pthread_mutexattr_t* attr);
WLAC4_WLAC4_EXPORT int   pthread_mutex_destroy(pthread_mutex_t* mutex);
WLAC4_WLAC4_EXPORT int   pthread_mutex_lock(pthread_mutex_t* mutex);
WLAC4_WLAC4_EXPORT int   pthread_mutex_unlock(pthread_mutex_t* mutex);
WLAC4_WLAC4_EXPORT int   pthread_rwlock_init(pthread_rwlock_t* rwlock,const pthread_rwlockattr_t* attr);
WLAC4_WLAC4_EXPORT int   pthread_rwlock_destroy(pthread_rwlock_t* rwlock);
WLAC4_WLAC4_EXPORT int   pthread_rwlock_rdlock(pthread_rwlock_t* rwlock);
WLAC4_WLAC4_EXPORT int   pthread_rwlock_unlock(pthread_rwlock_t* rwlock);
WLAC4_WLAC4_EXPORT int   pthread_rwlock_wrlock(pthread_rwlock_t* rwlock);
WLAC4_WLAC4_EXPORT int   pthread_setspecific(pthread_key_t key, const void* value);
WLAC4_WLAC4_EXPORT int   pthread_attr_init(pthread_attr_t* attr);
WLAC4_WLAC4_EXPORT int   pthread_attr_setdetachstate(pthread_attr_t* attr, int detachstate);
WLAC4_WLAC4_EXPORT int   pthread_create(pthread_t* thread,const pthread_attr_t* attr,void* (*start_routine)(void*),void* arg);
WLAC4_WLAC4_EXPORT int   pthread_attr_destroy(pthread_attr_t* attr);
WLAC4_WLAC4_EXPORT int   pthread_join(pthread_t thread, void** retval);
WLAC4_WLAC4_EXPORT int   pthread_key_create(pthread_key_t* key, void (*destructor)(void*));
WLAC4_WLAC4_EXPORT int   pthread_key_delete(pthread_key_t key);
WLAC4_WLAC4_EXPORT void* pthread_getspecific(pthread_key_t key);
WLAC4_WLAC4_EXPORT int   pthread_kill(pthread_t thread, int sig);


WLAC4_END_C


#endif  // #ifndef WLAC4_INCLUDE_WLAC4_PTHREAD_H
