//
// file:			wlac4_redesigned_string.cpp
// path:			src/core/wlac4/wlac4_redesigned_string.cpp
// created on:		2022 Sep 12
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <redesigned/string.h>


WLAC4_BEGIN_C


WLAC4_WLAC4_EXPORT void* memmem(const void* a_haystack, size_t a_haystacklen, const void* a_needle, size_t a_needlelen)
{
    if (a_haystack == NULL) return NULL; // or assert(haystack != NULL);
    if (a_haystacklen == 0) return NULL;
    if (a_needle == NULL) return NULL; // or assert(needle != NULL);
    if (a_needlelen == 0) return NULL;

    for (const char* h = a_haystack;
        a_haystacklen >= a_needlelen;
        ++h, --a_haystacklen) {
        if (!memcmp(h, a_needle, a_needlelen)) {
            return (char*)h;
        }
    }
    return NULL;
}




WLAC4_END_C
