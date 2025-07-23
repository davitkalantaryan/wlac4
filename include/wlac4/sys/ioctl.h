/**
 * \file    sys/ioctl.h
 * \brief   ...
 * \authors Davit Kalantaryan
 * \date    Created on 5 March 2020
 *
 * \copyright ...
 */

#ifndef WLAC_SYS_IOCTL_H
#define WLAC_SYS_IOCTL_H

#include <wlac4_exports.h>


WLAC4_BEGIN_C

WLAC4_WLAC4_EXPORT int ioctl(int d, int request, ...);

WLAC4_END_C

#endif  // #ifndef WLAC_SYS_IOCTL_H
