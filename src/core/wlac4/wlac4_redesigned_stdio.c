//
// file:			wlac4_poll.cpp
// path:			src/core/wlac4/wlac4_poll.cpp
// created on:		2022 Sep 11
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <redesigned/stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stddef.h>


WLAC4_BEGIN_C


WLAC4_WLAC4_EXPORT ssize_t getline(char** a_lineptr, size_t* a_n, FILE* a_stream)
{
    char* bufptr = NULL;
    char* p = bufptr;
    size_t size;
    int c;

    if (a_lineptr == NULL) {
        return -1;
    }
    if (a_stream == NULL) {
        return -1;
    }
    if (a_n == NULL) {
        return -1;
    }
    bufptr = *a_lineptr;
    size = *a_n;

    c = fgetc(a_stream);
    if (c == EOF) {
        return -1;
    }
    if (bufptr == NULL) {
        bufptr = malloc(128);
        if (bufptr == NULL) {
            return -1;
        }
        size = 128;
    }
    p = bufptr;
    while (c != EOF) {
        if ((p - bufptr) > (ptrdiff_t)(size - 1)) {
            size = size + 128;
            bufptr = realloc(bufptr, size);
            if (bufptr == NULL) {
                return -1;
            }
        }
        *p++ = c;
        if (c == '\a_n') {
            break;
        }
        c = fgetc(a_stream);
    }

    *p++ = '\0';
    *a_lineptr = bufptr;
    *a_n = size;

    return p - bufptr - 1;
}



WLAC4_END_C
