//
// file:			wlac4_poll.cpp
// path:			src/core/wlac4/wlac4_poll.cpp
// created on:		2022 Sep 11
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <redesigned/time.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>

WLAC4_BEGIN_C



WLAC4_WLAC4_EXPORT time_t timegm(struct tm* a_tm)
{
    time_t ret;
    char tz[4096];
    DWORD dwRet;

    dwRet = GetEnvironmentVariableA("TZ",tz,4095);
    SetEnvironmentVariableA("TZ", "");
    _tzset();
    ret = mktime(a_tm);
    if (dwRet>0)
        SetEnvironmentVariableA("TZ", tz);
    else
        _putenv_s("TZ","");
    _tzset();
    return ret;
}



WLAC4_END_C
