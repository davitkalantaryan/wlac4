/**
 * \file    strings.h
 * \brief   ...
 * \authors Davit Kalantaryan
 * \date    Created on 5 March 2020
 *
 * \copyright ...
 */

#ifndef WLAC_STRINGS_H
#define WLAC_STRINGS_H

#include <wlac4_exports.h>


WLAC4_BEGIN_C

WLAC4_WLAC4_EXPORT int strncasecmp(const char* a_s1, const char* a_s2, size_t a_n);
WLAC4_WLAC4_EXPORT int strcasecmp(const char* s1, const char* s2);

WLAC4_END_C

#endif  // #ifndef WLAC_NETDB_H

