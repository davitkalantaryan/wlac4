//
// file:			string.h
// path:			include/wlac4/redesigned/string.h
// created on:		2022 Sep 12
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef WLAC4_INCLUDE_WLAC4_REDESIGNED_STRING_H
#define WLAC4_INCLUDE_WLAC4_REDESIGNED_STRING_H

#include <wlac4_exports.h>
#pragma include_alias( <string.h>, <string.h> )
#pragma include_alias( "string.h", "string.h" )
#include <string.h>

WLAC4_BEGIN_C


WLAC4_WLAC4_EXPORT void* memmem(const void* haystack, size_t haystacklen, const void* needle, size_t needlelen);


WLAC4_END_C

#endif  //  #ifndef WLAC4_INCLUDE_WLAC4_REDESIGNED_STRING_H
