//
// file:			stdatomic.h
// path:			include/wlac4/stdatomic.h
// created on:		2022 Sep 11
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef WLAC4_INCLUDE_WLAC4_STDATOMIC_H
#define WLAC4_INCLUDE_WLAC4_STDATOMIC_H

#include <wlac4_exports.h>

WLAC4_BEGIN_C


#ifndef atomic_uint_defined
#define atomic_uint_defined
typedef unsigned int atomic_uint;
#endif

WLAC4_WLAC4_EXPORT void  atomic_init(atomic_uint*object, unsigned int value);
WLAC4_WLAC4_EXPORT unsigned int atomic_fetch_sub(atomic_uint* object, unsigned int operand);


WLAC4_END_C


#endif  // #ifndef WLAC4_INCLUDE_WLAC4_STDATOMIC_H
