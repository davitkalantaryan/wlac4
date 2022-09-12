//
// file:			wlac4_pthread.cpp
// path:			src/core/wlac4/wlac4_pthread.cpp
// created on:		2022 Sep 11
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <pthread.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdint.h>
#include <signal.h>

WLAC4_BEGIN_C


struct pthread_mutex_s {
	HANDLE		mut;
};

// for the beggining let's make simple mutex
struct pthread_rwlock_s {
	HANDLE		mut;
};


struct pthread_key_s {
	DWORD flsKey;
};


struct pthread_attr_s {
	union {
		uint64_t all;
		struct {
			uint64_t  shouldBeDetached : 1;
			uint64_t  reserved01 : 63;
		}b;
	}flags;
};


struct pthread_s {
	HANDLE thr;
	void* (*start_routine)(void*);
	void* arg;
	struct pthread_attr_s attrs;
	DWORD  thrId;
};



WLAC4_WLAC4_EXPORT int pthread_mutex_init(pthread_mutex_t* a_mutex, const pthread_mutexattr_t* a_attr)
{
	(void)a_attr;

	*a_mutex = (struct pthread_mutex_s*)malloc(sizeof(struct pthread_mutex_s));
	if (!(*a_mutex)) {
		return ENOMEM;
	}

	(*a_mutex)->mut = CreateMutexA(WLAC4_NULL, FALSE, WLAC4_NULL);
	if (!((*a_mutex)->mut)) {
		int nRet = (int)GetLastError();
		free(*a_mutex);
		return nRet;
	}

	return 0;
}


WLAC4_WLAC4_EXPORT int pthread_mutex_destroy(pthread_mutex_t* a_mutex)
{
	if (!CloseHandle((*a_mutex)->mut)) {
		return (int)GetLastError();
	}
	free(*a_mutex);
	*a_mutex = WLAC4_NULL;
	return 0;
}


WLAC4_WLAC4_EXPORT int pthread_mutex_lock(pthread_mutex_t* a_mutex)
{
	if (!(*a_mutex)) {
		struct pthread_mutex_s* pMutex;
		int nRet = pthread_mutex_init(&pMutex, WLAC4_NULL);
		if (nRet) {return nRet;}
		if (InterlockedCompareExchangePointer((volatile PVOID*)a_mutex, (PVOID)pMutex, WLAC4_NULL)) {
			pthread_mutex_destroy(&pMutex);
		}
	}

	if (WAIT_OBJECT_0 == WaitForSingleObjectEx((*a_mutex)->mut, INFINITE, TRUE)) {
		return 0;
	}

	return (int)GetLastError();
}


WLAC4_WLAC4_EXPORT int pthread_mutex_unlock(pthread_mutex_t* a_mutex)
{
	if (ReleaseMutex((*a_mutex)->mut)) {
		return 0;
	}
	return (int)GetLastError();
}


WLAC4_WLAC4_EXPORT int pthread_rwlock_rdlock(pthread_rwlock_t* a_rwlock)
{
	if (!(*a_rwlock)) {
		struct pthread_rwlock_s* pRwLock;
		int nRet = pthread_rwlock_init(&pRwLock, WLAC4_NULL);
		if (nRet) { return nRet; }
		if (InterlockedCompareExchangePointer((volatile PVOID*)a_rwlock, (PVOID)pRwLock, WLAC4_NULL)) {
			pthread_rwlock_destroy(&pRwLock);
		}
	}

	if (WAIT_OBJECT_0 == WaitForSingleObjectEx((*a_rwlock)->mut, INFINITE, TRUE)) {
		return 0;
	}

	return (int)GetLastError();
}


WLAC4_WLAC4_EXPORT int pthread_rwlock_unlock(pthread_rwlock_t* a_rwlock)
{
	if (ReleaseMutex((*a_rwlock)->mut)) {
		return 0;
	}
	return (int)GetLastError();
}


WLAC4_WLAC4_EXPORT int pthread_rwlock_wrlock(pthread_rwlock_t* a_rwlock)
{
	if (!(*a_rwlock)) {
		struct pthread_rwlock_s* pRwLock;
		int nRet = pthread_rwlock_init(&pRwLock, WLAC4_NULL);
		if (nRet) { return nRet; }
		if (InterlockedCompareExchangePointer((volatile PVOID*)a_rwlock, (PVOID)pRwLock, WLAC4_NULL)) {
			pthread_rwlock_destroy(&pRwLock);
		}
	}

	if (WAIT_OBJECT_0 == WaitForSingleObjectEx((*a_rwlock)->mut, INFINITE, TRUE)) {
		return 0;
	}
	return (int)GetLastError();
}


WLAC4_WLAC4_EXPORT int pthread_rwlock_init(pthread_rwlock_t* a_rwlock, const pthread_rwlockattr_t* a_attr)
{
	(void)a_attr;

	*a_rwlock = (struct pthread_rwlock_s*)malloc(sizeof(struct pthread_rwlock_s));
	if (!(*a_rwlock)) {
		return ENOMEM;
	}

	(*a_rwlock)->mut = CreateMutexA(WLAC4_NULL, FALSE, WLAC4_NULL);
	if (!((*a_rwlock)->mut)) {
		int nRet = (int)GetLastError();
		free(*a_rwlock);
		return nRet;
	}

	return 0;
}


WLAC4_WLAC4_EXPORT int pthread_rwlock_destroy(pthread_rwlock_t* a_rwlock)
{
	if (!CloseHandle((*a_rwlock)->mut)) {
		return (int)GetLastError();
	}
	free(*a_rwlock);
	*a_rwlock = WLAC4_NULL;
	return 0;
}


WLAC4_WLAC4_EXPORT int pthread_setspecific(pthread_key_t a_key, const void* a_value)
{
	if (FlsSetValue(a_key->flsKey, (void*)a_value)) {
		return 0;
	}
	return (int)GetLastError();
}


static _inline void pthread_attr_init_inline(struct pthread_attr_s* a_attr_p) {
	a_attr_p->flags.all = 0;
}


WLAC4_WLAC4_EXPORT int pthread_attr_init(pthread_attr_t* a_attr)
{
	*a_attr = (struct pthread_attr_s*)malloc(sizeof(struct pthread_attr_s));
	if (!(*a_attr)) {
		return ENOMEM;
	}

	pthread_attr_init_inline(*a_attr);
	return 0;
}



int pthread_attr_setdetachstate(pthread_attr_t* a_attr, int a_detachstate)
{
	switch (a_detachstate) {
	case PTHREAD_CREATE_JOINABLE: case PTHREAD_CREATE_DETACHED:
		break;
	default:
		return EINVAL;
	}  // switch (a_detachstate) {

	(*a_attr)->flags.b.shouldBeDetached = a_detachstate;
	return 0;
}


static _inline clear_pthread_resource(struct pthread_s* a_pThread){
	CloseHandle(a_pThread->thr);
	free(a_pThread);
}


static DWORD WINAPI PTHREAD_START_ROUTINE_STATIC(LPVOID a_lpThreadParameter) {
	struct pthread_s* pThread = (struct pthread_s*)a_lpThreadParameter;
	DWORD dwRet = (DWORD)((size_t)((*pThread->start_routine)(pThread->arg)));

	if (pThread->attrs.flags.b.shouldBeDetached) {
		clear_pthread_resource(pThread);
	}

	ExitThread(dwRet);
	//return dwRet;
}


WLAC4_WLAC4_EXPORT int pthread_create(pthread_t* a_thread, const pthread_attr_t* a_attr, void* (* a_start_routine)(void*), void* a_arg)
{
	*a_thread = (struct pthread_s*)malloc(sizeof(struct pthread_s));
	if (!(*a_thread)) {
		return ENOMEM;
	}
	
	pthread_attr_init_inline(&((*a_thread)->attrs));
	(*a_thread)->attrs = *(*a_attr);
	(*a_thread)->start_routine = a_start_routine;
	(*a_thread)->arg = a_arg;

	(*a_thread)->thr = CreateThread(WLAC4_NULL, 0, &PTHREAD_START_ROUTINE_STATIC, *a_thread, 0, &((*a_thread)->thrId));
	if (!((*a_thread)->thr)) {
		int nRet = (int)GetLastError();
		free(*a_thread);
		return nRet;
	}

	//if ((*a_attr)->flags.b.shouldBeDetached) {
	//	CloseHandle((*a_thread)->thr);
	//	(*a_thread)->thr = WLAC4_NULL;
	//}

	return 0;
}



WLAC4_WLAC4_EXPORT int pthread_attr_destroy(pthread_attr_t* a_attr)
{
	free(*a_attr);
	return 0;
}


WLAC4_WLAC4_EXPORT int pthread_join(pthread_t a_thread, void** a_retval)
{
	if (WAIT_OBJECT_0 == WaitForSingleObjectEx(a_thread->thr, INFINITE, TRUE)) {
		DWORD dwExitCode;
		GetExitCodeThread(a_thread->thr, &dwExitCode);
		*a_retval = (void*)((size_t)dwExitCode);
		clear_pthread_resource(a_thread);
		return 0;
	}
	return (int)GetLastError();
}


WLAC4_WLAC4_EXPORT int pthread_key_create(pthread_key_t* a_key, void (*a_destructor)(void*))
{
	*a_key = (struct pthread_key_s*)malloc(sizeof(struct pthread_key_s));
	if (!(*a_key)) {
		return ENOMEM;
	}

	(*a_key)->flsKey = FlsAlloc(a_destructor);
	if ((*a_key)->flsKey == FLS_OUT_OF_INDEXES) {
		free(*a_key);
		return FLS_OUT_OF_INDEXES;
	}

	return 0;
}


WLAC4_WLAC4_EXPORT int pthread_key_delete(pthread_key_t a_key)
{
	if (FlsFree(a_key->flsKey)) {
		free(a_key);
		return 0;
	}
	return (int)GetLastError();
}


WLAC4_WLAC4_EXPORT void* pthread_getspecific(pthread_key_t a_key)
{
	return FlsGetValue(a_key->flsKey);
}



static VOID NTAPI PAPCFUNC_INTERRUPT_STATIC(_In_ ULONG_PTR a_parameter) {
	raise((int)a_parameter);
}


WLAC4_WLAC4_EXPORT int pthread_kill(pthread_t a_thread, int a_sig)
{
	QueueUserAPC(&PAPCFUNC_INTERRUPT_STATIC, a_thread->thr, (ULONG_PTR)a_sig);
	return 0;
}



WLAC4_END_C
