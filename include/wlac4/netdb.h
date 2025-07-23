/**
 * \file    netdb.h
 * \brief   ...
 * \authors Davit Kalantaryan
 * \date    Created on 5 March 2020
 *
 * \copyright ...
 */

#ifndef WLAC_NETDB_H
#define WLAC_NETDB_H

#include <wlac4_exports.h>
#include <cinternal/disable_compiler_warnings.h>
#include <stddef.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <cinternal/undisable_compiler_warnings.h>


WLAC4_BEGIN_C

WLAC4_WLAC4_EXPORT int gethostbyname_r(const char* name,struct hostent* ret, char* buf, size_t buflen,struct hostent** result, int* h_errnop);

WLAC4_END_C

#endif  // #ifndef WLAC_NETDB_H

