//
// repo:            wlac4
// file:			ldap.h
// path:			include/wlac4/ldap.h
// created on:		2025 Jul 22
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef WLAC4_INCLUDE_WLAC4_LDAP_H
#define WLAC4_INCLUDE_WLAC4_LDAP_H


#include <cinternal/internal_header.h>

#if defined(_MSC_VER)

#ifdef LDAP_UNICODE
#undef LDAP_UNICODE
#endif
#define LDAP_UNICODE 0
#include <wlac4_exports.h>
#include <cinternal/disable_compiler_warnings.h>
#include <string.h>
#include <malloc.h>
#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <Winldap.h>
#endif
#include <cinternal/undisable_compiler_warnings.h>

WLAC4_BEGIN_C

WLAC4_WLAC4_EXPORT int ldap_initialize(LDAP** ldp, const char* uri);
#ifdef ldap_simple_bind_s
#undef ldap_simple_bind_s
#endif
static inline int ldap_simple_bind_s_inline(LDAP* a_ld, const char* a_who, const char* a_passwd) CPPUTILS_NOEXCEPT {
    const size_t whoLengthPlus1 = strlen(a_who) + 1;
    const size_t passwdLengthPlus1 = strlen(a_passwd) + 1;
    char* const pcWho = (char*)_alloca(whoLengthPlus1);
    char* const pcPasswd = (char*)_alloca(passwdLengthPlus1);
    memcpy(pcWho, a_who, whoLengthPlus1);
    memcpy(pcPasswd, a_passwd, passwdLengthPlus1);
    return ldap_simple_bind_sA(a_ld, pcWho, pcPasswd);
}
#define ldap_simple_bind_s ldap_simple_bind_s_inline
#define ldap_unbind_ext(_ld,_sctrls,_cctrls)	ldap_unbind((_ld))

#ifndef LDAP_OPT_NETWORK_TIMEOUT
#define LDAP_OPT_NETWORK_TIMEOUT    LDAP_OPT_TIMELIMIT
#endif
#ifndef LDAP_OPT_TIMEOUT
#define LDAP_OPT_TIMEOUT            LDAP_OPT_TIMELIMIT
#endif
#ifndef LDAP_OPT_SUCCESS
#define LDAP_OPT_SUCCESS            LDAP_SUCCESS
#endif
#ifndef LDAP_SCOPE_BASEOBJECT
#define LDAP_SCOPE_BASEOBJECT       3
#endif
#ifndef LDAP_SCOPE_ONE
#define LDAP_SCOPE_ONE              4
#endif
#ifndef LDAP_SCOPE_SUB
#define LDAP_SCOPE_SUB              5
#endif
#ifndef LDAP_SCOPE_SUBORDINATE
#define LDAP_SCOPE_SUBORDINATE      6
#endif
#ifndef LDAP_SCOPE_CHILDREN
#define LDAP_SCOPE_CHILDREN         7
#endif
#ifndef LDAP_SCOPE_DEFAULT
#define LDAP_SCOPE_DEFAULT          8
#endif

WLAC4_END_C

#endif  //  #if defined(_MSC_VER)

#endif  //  #ifndef WLAC4_INCLUDE_WLAC4_LDAP_H
