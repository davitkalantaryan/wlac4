//
// repo:            wlac4
// file:			lber.h
// path:			include/wlac4/lber.h
// created on:		2025 Jul 22
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef WLAC4_INCLUDE_WLAC4_LBER_H
#define WLAC4_INCLUDE_WLAC4_LBER_H


#include <cinternal/internal_header.h>

#if defined(_MSC_VER)

#include <wlac4_exports.h>
#include <cinternal/disable_compiler_warnings.h>
#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <WinBer.h>
#endif
#include <cinternal/undisable_compiler_warnings.h>


CPPUTILS_BEGIN_C


CPPUTILS_END_C


#endif  //  #if defined(_MSC_VER)

#endif  //  #ifndef WLAC4_INCLUDE_WLAC4_LBER_H
