//
// file:			poll.h
// path:			include/wlac4/poll.h
// created on:		2022 Sep 11
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef WLAC4_INCLUDE_WLAC4_POLL_H
#define WLAC4_INCLUDE_WLAC4_POLL_H

#include <wlac4_exports.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>


WLAC4_BEGIN_C


#ifndef nfds_t_defined
#define nfds_t_defined
typedef unsigned long int nfds_t;
#endif


WLAC4_WLAC4_EXPORT int poll(struct pollfd fds[], nfds_t nfds, int timeout);


WLAC4_END_C


#endif  // #ifndef WLAC4_INCLUDE_WLAC4_POLL_H
