//
// file:			time.h
// path:			include/wlac4/redesigned/time.h
// created on:		2022 Sep 12
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef WLAC4_INCLUDE_WLAC4_REDESIGNED_TIME_H
#define WLAC4_INCLUDE_WLAC4_REDESIGNED_TIME_H

#include <wlac4_exports.h>
#pragma include_alias( <time.h>, <time.h> )
#pragma include_alias( "time.h", "time.h" )
#include <time.h>

WLAC4_BEGIN_C


WLAC4_WLAC4_EXPORT time_t timegm(struct tm* tm);


WLAC4_END_C

#endif  //  #ifndef DENOVOLAB_INCLUDE_WLAC_WLAC_STDIO_H
