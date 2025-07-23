//
// repo:            wlac4
// file:			wlac4_user_group_handling.c
// path:			src/core/wlac4/wlac4_user_group_handling.c
// created on:		2025 Jul 23
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#include <unistd.h>
#include <wlac4_user_group_handling.h>
#include <cinternal/disable_compiler_warnings.h>
#include <stdlib.h>
#include <cinternal/undisable_compiler_warnings.h>


WLAC4_BEGIN_C


static uid_t getUidStatic(void) CPPUTILS_NOEXCEPT
{
    return 0;
}


static gid_t getGidStatic(void) CPPUTILS_NOEXCEPT
{
    return 0;
}


static struct passwd* getpwuidStatic(uid_t a_uid) CPPUTILS_NOEXCEPT
{
    CPPUTILS_STATIC_CAST(void, a_uid);
    return CPPUTILS_NULL;
}


static int getgrouplistStatic(const char* a_user, gid_t a_group, gid_t* a_groups, int* a_ngroups) CPPUTILS_NOEXCEPT
{
    CPPUTILS_STATIC_CAST(void, a_user);
    CPPUTILS_STATIC_CAST(void, a_group);
    CPPUTILS_STATIC_CAST(void, a_groups);
    CPPUTILS_STATIC_CAST(void, a_ngroups);
    return 0;
}


static Wlac4TypeGetUid  s_getUid = &getUidStatic;
static Wlac4TypeGetGid  s_getGid = &getGidStatic;
static Wlac4TypeGetpwuid  s_getPwuid = &getpwuidStatic;
static Wlac4TypeGetgrouplist  s_getGrouplist = &getgrouplistStatic;


WLAC4_WLAC4_EXPORT uid_t getuid(void) CPPUTILS_NOEXCEPT
{
    return (*s_getUid) ();
}


WLAC4_WLAC4_EXPORT uid_t geteuid(void) CPPUTILS_NOEXCEPT
{
    return (*s_getUid) ();
}


WLAC4_WLAC4_EXPORT gid_t getgid(void) CPPUTILS_NOEXCEPT
{
    return (*s_getGid) ();
}


WLAC4_WLAC4_EXPORT gid_t getegid(void) CPPUTILS_NOEXCEPT
{
    return (*s_getGid) ();
}


WLAC4_WLAC4_EXPORT struct passwd* getpwuid(uid_t a_uid) CPPUTILS_NOEXCEPT
{
    return (*s_getPwuid)(a_uid);
}


WLAC4_WLAC4_EXPORT int getgrouplist(const char* a_user, gid_t a_group, gid_t* a_groups, int* a_ngroups) CPPUTILS_NOEXCEPT
{
    return (*s_getGrouplist)(a_user,a_group,a_groups,a_ngroups);
}


WLAC4_WLAC4_EXPORT Wlac4TypeGetUid Wlac4SetGetUidFunction(Wlac4TypeGetUid a_fnc) CPPUTILS_NOEXCEPT
{
    const Wlac4TypeGetUid fnRet = s_getUid;
    if (a_fnc) {
        s_getUid = a_fnc;
    }
    return fnRet;
}


WLAC4_WLAC4_EXPORT Wlac4TypeGetGid Wlac4SetGetGidFunction(Wlac4TypeGetGid a_fnc) CPPUTILS_NOEXCEPT
{
    const Wlac4TypeGetGid fnRet = s_getGid;
    if (a_fnc) {
        s_getGid = a_fnc;
    }
    return fnRet;
}


WLAC4_WLAC4_EXPORT Wlac4TypeGetpwuid Wlac4SetGetpwuidFunction(Wlac4TypeGetpwuid a_fnc) CPPUTILS_NOEXCEPT
{
    const Wlac4TypeGetpwuid fnRet = s_getPwuid;
    if (a_fnc) {
        s_getPwuid = a_fnc;
    }
    return fnRet;
}


WLAC4_WLAC4_EXPORT Wlac4TypeGetgrouplist Wlac4SetGetgrouplistFunction(Wlac4TypeGetgrouplist a_fnc) CPPUTILS_NOEXCEPT
{
    const Wlac4TypeGetgrouplist fnRet = s_getGrouplist;
    if (a_fnc) {
        s_getGrouplist = a_fnc;
    }
    return fnRet;
}


static void Wlac4UserGroupHandlingClean(void) CPPUTILS_NOEXCEPT
{
}


CPPUTILS_C_CODE_INITIALIZER(Wlac4UserGroupHandlingInitialize)
{
    atexit(&Wlac4UserGroupHandlingClean);
    s_getUid = &getUidStatic;
    s_getGid = &getGidStatic;
    s_getPwuid = &getpwuidStatic;
    s_getGrouplist = &getgrouplistStatic;
}


WLAC4_END_C
