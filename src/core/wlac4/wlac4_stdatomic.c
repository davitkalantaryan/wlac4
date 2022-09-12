//
// file:			wlac4_stdatomic.cpp
// path:			src/core/wlac4/wlac4_stdatomic.cpp
// created on:		2022 Sep 12
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <stdatomic.h>


WLAC4_BEGIN_C


WLAC4_WLAC4_EXPORT void atomic_init(atomic_uint* a_object, unsigned int a_value)
{
	*a_object = a_value;
}



WLAC4_WLAC4_EXPORT unsigned int atomic_fetch_sub(atomic_uint* a_object, unsigned int a_operand)
{
	(*a_object) -= a_operand;
	return (*a_object);
}




WLAC4_END_C
