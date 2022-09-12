//
// file:			wlac4_entry_point.cpp
// path:			src/core/wlac4/wlac4_entry_point.cpp
// created on:		2022 Sep 11
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <wlac4_internal_header.h>
#include "wlac4_private_data.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <stdbool.h>


WLAC4_BEGIN_C


#pragma comment(lib,"Ws2_32.lib")

WLAC4_DLL_PRIVATE bool  g_hasPossibleThreads = false;
static bool s_bIsLibraryInited = false;


static _inline BOOL InitializeWlac4(void) 
{
    if (!s_bIsLibraryInited) {
        WORD wVersionRequested;
        WSADATA wsaData;

        wVersionRequested = MAKEWORD(2, 2);

        if (WSAStartup(wVersionRequested, &wsaData) != 0) { return FALSE; }
        if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
            WSACleanup();
            return FALSE;
        }
        g_hasPossibleThreads = true;
        s_bIsLibraryInited = true;
    }

    return TRUE;
}


static void CleanupWlac4(void) 
{
    if (s_bIsLibraryInited) {
        WSACleanup();
        s_bIsLibraryInited = false;
    }
}


#if defined(_DLL) || defined(WLAC4_WLAC4_COMPILING_SHARED_LIB)


BOOL WINAPI DllMain(
    HINSTANCE a_hinstDLL,  // handle to DLL module
    DWORD a_fdwReason,     // reason for calling function
    LPVOID a_lpvReserved)  // reserved
{
    WLAC4_STATIC_CAST(void, a_hinstDLL);

    // Perform actions based on the reason for calling.
    switch (a_fdwReason){
    case DLL_PROCESS_ATTACH:
        return InitializeWlac4();

    case DLL_THREAD_ATTACH: case DLL_THREAD_DETACH:
        // For thread-specific initialization/cleanup.
        break;

    case DLL_PROCESS_DETACH:
        if (a_lpvReserved != WLAC4_NULL){
            // In windows during process termination ("a_lpvReserved != WLAC4_NULL" => means process termination), no thread exist at this point
            g_hasPossibleThreads = false;
        }
        CleanupWlac4();
        break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}


#endif  // #if defined(_DLL) || defined(WLAC4_WLAC4_COMPILING_SHARED_LIB)



WLAC4_END_C
