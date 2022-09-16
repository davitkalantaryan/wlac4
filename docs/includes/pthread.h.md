# pthread.h  
  
This header implements some data and functions decelared in the corresponding 
[GNU header](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/pthread.h.html).  
[file in the repo](../../include/wlac4/pthread.h)  
  
  
## functions 
  
 1.  ``pthread_mutex_init``				[linux docs](https://linux.die.net/man/3/pthread_mutex_init)  
 2.  ``pthread_mutex_destroy``			[linux docs](https://linux.die.net/man/3/pthread_mutex_destroy)  
 3.  ``pthread_mutex_lock``				[linux docs](https://linux.die.net/man/3/pthread_mutex_lock)  
 4.  ``pthread_mutex_unlock``			[linux docs](https://linux.die.net/man/3/pthread_mutex_unlock)  
 5.  ``pthread_rwlock_init``			[linux docs](https://linux.die.net/man/3/pthread_rwlock_init)  
 6.  ``pthread_rwlock_destroy``			[linux docs](https://linux.die.net/man/3/pthread_rwlock_destroy)  
 7.  ``pthread_rwlock_rdlock``			[linux docs](https://linux.die.net/man/3/pthread_rwlock_rdlock)  
 8.  ``pthread_rwlock_unlock``			[linux docs](https://linux.die.net/man/3/pthread_rwlock_unlock)  
 9.  ``pthread_rwlock_wrlock``			[linux docs](https://linux.die.net/man/3/pthread_rwlock_wrlock)  
 10. ``pthread_setspecific``			[linux docs](https://linux.die.net/man/3/pthread_setspecific)  
 11. ``pthread_attr_init``				[linux docs](https://linux.die.net/man/3/pthread_attr_init)  
 12. ``pthread_attr_setdetachstate``	[linux docs](https://linux.die.net/man/3/pthread_attr_setdetachstate)  
 13. ``pthread_create``					[linux docs](https://linux.die.net/man/3/pthread_create)  
 14. ``pthread_attr_destroy``			[linux docs](https://linux.die.net/man/3/pthread_attr_destroy)  
 15. ``pthread_join``					[linux docs](https://linux.die.net/man/3/pthread_join)  
 16. ``pthread_key_create``				[linux docs](https://linux.die.net/man/3/pthread_key_create)  
 17. ``pthread_key_delete``				[linux docs](https://linux.die.net/man/3/pthread_key_delete)   
 18. ``pthread_getspecific``			[linux docs](https://linux.die.net/man/3/pthread_getspecific)  
 19. ``pthread_kill``					[linux docs](https://linux.die.net/man/3/pthread_kill)  
  
  
## data  
  
   
  
## types  
  
 1.  ``typedef struct pthread_mutex_s*	pthread_mutex_t;``  
 2.  ``typedef struct pthread_mutexattr_s* pthread_mutexattr_t;``  
 3.  ``typedef struct pthread_rwlock_s* pthread_rwlock_t;``  
 4.  ``typedef struct pthread_rwlockattr_s* pthread_rwlockattr_t;``  
 5.  ``typedef struct pthread_s* pthread_t;``  
 6.  ``typedef struct pthread_key_s* pthread_key_t;``  
 7.  ``typedef struct pthread_attr_s* pthread_attr_t;``   
  
  
## macroses  
  
 1.  ``#define PTHREAD_RWLOCK_INITIALIZER		LIBDNL_NULL``  
 2.  ``#define PTHREAD_MUTEX_INITIALIZER		LIBDNL_NULL``  
 3.  ``#define PTHREAD_CREATE_JOINABLE			0``  
 4.  ``#define PTHREAD_CREATE_DETACHED			1``   
