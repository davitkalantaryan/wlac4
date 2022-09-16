//
// file:			wlac4_poll.cpp
// path:			src/core/wlac4/wlac4_poll.cpp
// created on:		2022 Sep 11
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <poll.h>


WLAC4_BEGIN_C


// We will not use WSAPoll (https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-wsapoll) 
// because of some restrictions
WLAC4_WLAC4_EXPORT int poll(struct pollfd a_fds[], nfds_t a_nfds, int a_timeout)
{
	fd_set rdfds, wrfds, erfds;
	fd_set* prdfds = NULL, * pwrfds = NULL, * perfds = NULL;
	struct timeval to;
	nfds_t i, nready, fdmax = 0;

	FD_ZERO(&rdfds); FD_ZERO(&wrfds); FD_ZERO(&erfds);

	for (i = 0; i < a_nfds; i++)
	{
		if (((nfds_t)a_fds[i].fd) > fdmax) fdmax = (nfds_t)a_fds[i].fd;
		if (a_fds[i].events & POLLIN) { FD_SET(a_fds[i].fd, &rdfds); prdfds = &rdfds; }
		if (a_fds[i].events & POLLOUT) { FD_SET(a_fds[i].fd, &wrfds); pwrfds = &wrfds; }
		FD_SET(a_fds[i].fd, &erfds);
		perfds = &erfds;
		a_fds[i].revents = 0;
	}
	to.tv_sec = a_timeout / 1000; to.tv_usec = (a_timeout % 1000) * 1000;
	nready = select(fdmax + 1, prdfds, pwrfds, perfds, &to);
	if (nready > 0)
	{
		for (i = 0; i < a_nfds; i++)
		{
			if (prdfds != NULL && a_fds[i].events & POLLIN && FD_ISSET(a_fds[i].fd, prdfds))
			{
				a_fds[i].revents |= POLLIN;
			}
			if (pwrfds != NULL && a_fds[i].events & POLLOUT && FD_ISSET(a_fds[i].fd, pwrfds))
			{
				a_fds[i].revents |= POLLOUT;
			}
			if (perfds != NULL && FD_ISSET(a_fds[i].fd, perfds))
			{
				a_fds[i].revents |= POLLERR;
			}
		}
	}
	return (int)nready;
}



WLAC4_END_C
