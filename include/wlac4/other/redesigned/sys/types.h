//
// repo:            wlac4
// file:			types.h
// path:			include/wlac4/other/redesigned/sys/types.h
// created on:		2025 Jul 23
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef WLAC4_INCLUDE_WLAC4_OTHER_REDESIGNED_SYS_TYPES_H
#define WLAC4_INCLUDE_WLAC4_OTHER_REDESIGNED_SYS_TYPES_H


#include <cinternal/internal_header.h>

#if defined(_MSC_VER)

#include <wlac4_exports.h>
#ifndef WLAC4_SYS_TYPES_H_REDIRECT_DONE
#pragma include_alias( <sys/types.h>, <sys/types.h> )
#pragma include_alias( "sys/types.h", "sys/types.h" )
#define WLAC4_SYS_TYPES_H_REDIRECT_DONE
#endif
#include <cinternal/disable_compiler_warnings.h>
#include <sys/types.h>
#include <stdint.h>
#include <cinternal/undisable_compiler_warnings.h>


CPPUTILS_BEGIN_C

#ifndef uid_t_defined
typedef uint32_t uid_t;
#define uid_t_defined
#endif
#ifndef gid_t_defined
typedef uint32_t gid_t;
#define gid_t_defined
#endif
#ifndef pid_t_defined
#define pid_t_defined
//typedef DWORD pid_t;
typedef uint32_t pid_t;
#endif

CPPUTILS_END_C


#endif  //  #if defined(_MSC_VER)
#endif  //  #ifndef WLAC4_INCLUDE_WLAC4_OTHER_REDESIGNED_SYS_TYPES_H
