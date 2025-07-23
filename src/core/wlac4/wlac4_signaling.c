//
// file:			empty_doocs_wlac_source_template.c
//
#include <wlac4_internal_header.h>
#include <cinternal/disable_compiler_warnings.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <memory.h>
#include <other/redesigned/signal.h>
#include <stdlib.h>
#include <string.h>
//#include "doocs_wlac_mini_common_private_include.h"
#include <cinternal/undisable_compiler_warnings.h>


WLAC4_BEGIN_C
// WLAC_CORE_EXPORT

#ifndef WLAC_LIKELY
#define WLAC_LIKELY(_x) (_x)
#endif
#ifndef WLAC_UNLIKELY
#define WLAC_UNLIKELY(_x) (_x)
#endif

static void __CRTDECL DefaultSystemSignalHandler(int a_sig);
static void InitSigActionFromSystemTable(int a_sig, struct sigaction* a_pThreadAction);
static struct SThreadLocalData* WlacGetThreadLocalData(void);
static DWORD						s_indexForThreadLocalData;

struct StrSignalData {
    struct sigaction	vActions[_SIGSET_NWORDS];
    siginfo_t			sigInfo;
};

struct SThreadLocalData {
    struct StrSignalData sigData;
};

struct StrThreadLocalItem {
    struct StrThreadLocalItem* next;
    //struct SThreadLocalData*	pThreadLocalData;
};

static struct StrThreadLocalItem* s_firstItem = CPPUTILS_NULL;
static struct StrThreadLocalItem* s_lastItem = CPPUTILS_NULL;
static struct StrSignalData		s_processSignalData;
static HANDLE					s_mutexForProcessSigData;
static HANDLE						s_mutexForThreadLocalData;

WLAC4_WLAC4_EXPORT int sigemptyset(sigset_t* a_set)
{
	memset(a_set->__val, 0, sizeof(a_set->__val));
	return 0;
}


WLAC4_WLAC4_EXPORT int sigaddset(sigset_t* __set, int __signo)
{
	if (__set && (__signo < _SIGSET_NWORDS)) {
		__set->__val[__signo] = 1;
	}
	return 0;
}


WLAC4_WLAC4_EXPORT int sigaction(int a_sig, const struct sigaction * a_act, struct sigaction * a_oact)
{
	int nReturn = -1;
	if(WLAC_LIKELY(a_sig< _SIGSET_NWORDS)){
		struct SThreadLocalData* pThreadData = WlacGetThreadLocalData();
		if(WLAC_LIKELY(pThreadData)){
			InitSigActionFromSystemTable(a_sig, &pThreadData->sigData.vActions[a_sig]);
			if(a_oact){
				memcpy(a_oact,&pThreadData->sigData.vActions[a_sig],sizeof(struct sigaction));
			}
			if(a_act){
				// todo: masks should be taken into account
				memcpy(&pThreadData->sigData.vActions[a_sig],a_act,sizeof(struct sigaction));
				// now let's make windows specific signal initialization
				// the aim to do this is to respond any windows signal
				// by terminal, by system, etc.
				WaitForSingleObject(s_mutexForProcessSigData,INFINITE);
				memcpy(&(s_processSignalData.vActions[a_sig]),&(pThreadData->sigData.vActions[a_sig]),sizeof(struct sigaction));
				ReleaseMutex(s_mutexForProcessSigData);

				signal(a_sig, &DefaultSystemSignalHandler);
			}
			nReturn = 0;
		}
	}
	
	return nReturn;
}


/*/////////////////// statics ////////////////////*/


static void __CRTDECL DefaultSystemSignalHandler(int a_sig)
{

	WaitForSingleObject(s_mutexForProcessSigData,INFINITE);

	if (s_processSignalData.vActions[a_sig].sa_handler) {
		if (s_processSignalData.vActions[a_sig].sa_flags & SA_SIGINFO) {
			s_processSignalData.sigInfo.si_signo = a_sig;
			(*s_processSignalData.vActions[a_sig].sa_sigaction)(a_sig, &s_processSignalData.sigInfo, CPPUTILS_NULL);
		}
		else {
			(*s_processSignalData.vActions[a_sig].sa_handler)(a_sig);
		}
		if (!(s_processSignalData.vActions[a_sig].sa_flags & SA_RESETHAND)) {
			signal(a_sig, &DefaultSystemSignalHandler);
		}
		ReleaseMutex(s_mutexForProcessSigData);
		return; // we handlede signal, return in order skip exit(2)
	}  // if (WLAC_LIKELY(pThreadData)) {

	ReleaseMutex(s_mutexForProcessSigData);
	_exit(2); // default signal handler on UNIX
}


static void InitSigActionFromSystemTable(int a_sig, struct sigaction* a_pThreadAction)
{
	if (!a_pThreadAction->is_inited) {
		_crt_signal_t  pCurrentSignal = signal(a_sig, SIG_GET);
		a_pThreadAction->sa_flags = 0; // we use one argument handler
		a_pThreadAction->sa_handler = pCurrentSignal;
	}
}


static struct SThreadLocalData* WlacGetThreadLocalData(void)
{
    struct SThreadLocalData* pThreadLocalData = CPPUTILS_STATIC_CAST(struct SThreadLocalData*, TlsGetValue(s_indexForThreadLocalData));

    if (WLAC_UNLIKELY(!pThreadLocalData)) {
        //struct StrThreadLocalItem* pThrLocalDataItem = WLAC_STATIC_CAST(struct StrThreadLocalItem*, malloc(sizeof(struct StrThreadLocalItem)+sizeof(struct SThreadLocalData)));
        struct StrThreadLocalItem* pThrLocalDataItem = CPPUTILS_STATIC_CAST(struct StrThreadLocalItem*, calloc(sizeof(struct StrThreadLocalItem) + sizeof(struct SThreadLocalData), 1));
        if (WLAC_UNLIKELY(!pThrLocalDataItem)) { return CPPUTILS_NULL; }
        //pThrLocalDataItem->next = WLAC_NULL;
        pThreadLocalData = CPPUTILS_REINTERPRET_CAST(struct SThreadLocalData*, CPPUTILS_REINTERPRET_CAST(char*, pThrLocalDataItem) + sizeof(struct StrThreadLocalItem));
        TlsSetValue(s_indexForThreadLocalData, pThreadLocalData);
        WaitForSingleObject(s_mutexForThreadLocalData, INFINITE);
        if (s_lastItem) {
            s_lastItem->next = pThrLocalDataItem;
        }
        else {
            s_firstItem = pThrLocalDataItem;
        }
        s_lastItem = pThrLocalDataItem;
        ReleaseMutex(s_mutexForThreadLocalData);
    }

    return pThreadLocalData;
}


static void DoocsWlacSignalizngCleanupRoutine(void)
{
    CloseHandle(s_mutexForProcessSigData);
    TlsFree(s_indexForThreadLocalData);
}


CPPUTILS_C_CODE_INITIALIZER(DoocsWlacSignalizngInitializationRoutine)
{
    atexit(&DoocsWlacSignalizngCleanupRoutine);
    s_indexForThreadLocalData = TlsAlloc();
    s_mutexForProcessSigData = CreateMutex(CPPUTILS_NULL, FALSE, CPPUTILS_NULL);
    memset(&s_processSignalData, 0, sizeof(struct StrSignalData));  // this is not needed
}


WLAC4_END_C
