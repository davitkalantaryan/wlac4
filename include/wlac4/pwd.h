//
// repo:            wlac4
// file:			pwd.h
// path:			include/wlac4/pwd.h
// created on:		2025 Jul 23
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef WLAC4_INCLUDE_WLAC4_PWD_H
#define WLAC4_INCLUDE_WLAC4_PWD_H


#include <cinternal/internal_header.h>
#include <wlac4_exports.h>
#include <other/redesigned/sys/types.h>


WLAC4_BEGIN_C

#ifndef struct_passwd_defined
struct passwd {
    char* pw_name;       /* username */
    char* pw_passwd;     /* user password */
    uid_t   pw_uid;        /* user ID */
    gid_t   pw_gid;        /* group ID */
    char* pw_gecos;      /* user information */
    char* pw_dir;        /* home directory */
    char* pw_shell;      /* shell program */
};
#define struct_passwd_defined
#endif

WLAC4_WLAC4_EXPORT struct passwd* getpwuid(uid_t a_uid) CPPUTILS_NOEXCEPT;

WLAC4_END_C

#endif  //  #ifndef WLAC4_INCLUDE_WLAC4_PWD_H
