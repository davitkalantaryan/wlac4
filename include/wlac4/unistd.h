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

#include <wlac4_exports.h>
#include <other/redesigned/sys/types.h>
#include <cinternal/disable_compiler_warnings.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <cinternal/undisable_compiler_warnings.h>


CPPUTILS_BEGIN_C


#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN  64
#endif

WLAC4_WLAC4_EXPORT uid_t getuid(void) CPPUTILS_NOEXCEPT;
WLAC4_WLAC4_EXPORT uid_t geteuid(void) CPPUTILS_NOEXCEPT;
WLAC4_WLAC4_EXPORT gid_t getgid(void) CPPUTILS_NOEXCEPT;
WLAC4_WLAC4_EXPORT gid_t getegid(void) CPPUTILS_NOEXCEPT;

CPPUTILS_END_C


#endif  //  #ifndef WLAC4_INCLUDE_WLAC4_UNISTD_H
