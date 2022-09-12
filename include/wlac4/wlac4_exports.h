//
// file:			wlac4_exports.h
// path:			include/wlac4/wlac4_exports.h
// created on:		2022 Sep 12
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef WLAC4_INCLUDE_WLAC4_WLAC4_EXPORTS_H
#define WLAC4_INCLUDE_WLAC4_WLAC4_EXPORTS_H

#include <wlac4_internal_header.h>

#ifndef WLAC4_WLAC4_EXPORT
#if defined(WLAC4_WLAC4_COMPILING_SHARED_LIB)
#define WLAC4_WLAC4_EXPORT WLAC4_DLL_PUBLIC
#elif defined(WLAC4_WLAC4_USING_STATIC_LIB_OR_OBJECTS)
#define WLAC4_WLAC4_EXPORT
#elif defined(WLAC4_WLAC4_LOAD_FROM_DLL)
#define WLAC4_WLAC4_EXPORT WLAC4_IMPORT_FROM_DLL
#else
#define WLAC4_WLAC4_EXPORT WLAC4_DLL_PRIVATE
#endif
#endif



#endif  // #ifndef WLAC4_INCLUDE_WLAC4_WLAC4_EXPORTS_H
