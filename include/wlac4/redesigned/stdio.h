//
// file:			wlac_stdio.h
// path:			include/wlac/wlac_stdio.h
// created on:		2022 Sep 11
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef WLAC4_INCLUDE_WLAC4_REDESIGNED_STDIO_H
#define WLAC4_INCLUDE_WLAC4_REDESIGNED_STDIO_H

#include <wlac4_exports.h>
#pragma include_alias( <stdio.h>, <stdio.h> )
#pragma include_alias( "stdio.h", "stdio.h" )
#include <stdio.h>

WLAC4_BEGIN_C

#ifndef ssize_t_defined
typedef int ssize_t;
#endif

WLAC4_WLAC4_EXPORT ssize_t getline(char** lineptr, size_t* n, FILE* stream);
extern WLAC4_WLAC4_EXPORT int STDIN_FILENO;


WLAC4_END_C

#endif  //  #ifndef WLAC4_INCLUDE_WLAC4_REDESIGNED_STDIO_H
