//
// repo:            wlac4
// file:			wlac4_user_group_handling.h
// path:			include/wlac4/wlac4_user_group_handling.h
// created on:		2025 Jul 23
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef WLAC4_INCLUDE_WLAC4_WLAC4_USER_GROUP_HANDLING_H
#define WLAC4_INCLUDE_WLAC4_WLAC4_USER_GROUP_HANDLING_H


#include <cinternal/internal_header.h>
#include <wlac4_exports.h>
#include <other/redesigned/sys/types.h>


WLAC4_BEGIN_C

struct passwd;

//  WLAC4_WLAC4_EXPORT gid_t getgid(void) CPPUTILS_NOEXCEPT;
//  WLAC4_WLAC4_EXPORT struct passwd* getpwuid(uid_t uid) CPPUTILS_NOEXCEPT

typedef uid_t (*Wlac4TypeGetUid)(void);
typedef gid_t (*Wlac4TypeGetGid)(void);
typedef struct passwd* (*Wlac4TypeGetpwuid)(uid_t);
typedef int (*Wlac4TypeGetgrouplist)(const char*, gid_t, gid_t*, int*);

WLAC4_WLAC4_EXPORT Wlac4TypeGetUid Wlac4SetGetUidFunction(Wlac4TypeGetUid a_fnc) CPPUTILS_NOEXCEPT;
WLAC4_WLAC4_EXPORT Wlac4TypeGetGid Wlac4SetGetGidFunction(Wlac4TypeGetGid a_fnc) CPPUTILS_NOEXCEPT;
WLAC4_WLAC4_EXPORT Wlac4TypeGetpwuid Wlac4SetGetpwuidFunction(Wlac4TypeGetpwuid a_fnc) CPPUTILS_NOEXCEPT;
WLAC4_WLAC4_EXPORT Wlac4TypeGetgrouplist Wlac4SetGetgrouplistFunction(Wlac4TypeGetgrouplist a_fnc) CPPUTILS_NOEXCEPT;


WLAC4_END_C

#endif  //  #ifndef WLAC4_INCLUDE_WLAC4_WLAC4_USER_GROUP_HANDLING_H
