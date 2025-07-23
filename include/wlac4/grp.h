//
// repo:            wlac4
// file:			grp.h
// path:			include/wlac4/grp.h
// created on:		2025 Jul 23
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef WLAC4_INCLUDE_WLAC4_GRP_H
#define WLAC4_INCLUDE_WLAC4_GRP_H


#include <cinternal/internal_header.h>
#include <wlac4_exports.h>
#include <other/redesigned/sys/types.h>


WLAC4_BEGIN_C

WLAC4_WLAC4_EXPORT int getgrouplist(const char* a_user, gid_t a_group, gid_t* a_groups, int* a_ngroups) CPPUTILS_NOEXCEPT;

WLAC4_END_C

#endif  //  #ifndef WLAC4_INCLUDE_WLAC4_GRP_H
