//
// repo:            wlac4
// file:			unistd.h
// path:			include/wlac4/unistd.h
// created on:		2025 Jul 23
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef WLAC4_INCLUDE_WLAC4_UNISTD_H
#define WLAC4_INCLUDE_WLAC4_UNISTD_H


#include <cinternal/internal_header.h>

#if defined(_MSC_VER)

#include <wlac4_exports.h>
#include <other/redesigned/sys/types.h>
#include <cinternal/disable_compiler_warnings.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <cinternal/undisable_compiler_warnings.h>

#ifndef MAXHOSTNAMELEN
#define        MAXHOSTNAMELEN  64
#endif


CPPUTILS_BEGIN_C

WLAC4_WLAC4_EXPORT uid_t getuid(void);
WLAC4_WLAC4_EXPORT gid_t getgid(void);

CPPUTILS_END_C


#endif  //  #if defined(_MSC_VER)
#endif  //  #ifndef WLAC4_INCLUDE_WLAC4_UNISTD_H
