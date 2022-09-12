//
// file:			wlac4_empty.cpp
// path:			src/core/wlac4/wlac4_empty.cpp
// created on:		2022 Sep 12
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <redesigned/time.h>
#include <syslog.h>


WLAC4_BEGIN_C




WLAC4_WLAC4_EXPORT time_t timegm(struct tm* a_tm)
{
	(void)a_tm;
	return 0;
}


WLAC4_WLAC4_EXPORT void syslog(int a_priority, const char* a_format, ...)
{
	(void)a_priority;
	(void)a_format;
}


WLAC4_WLAC4_EXPORT void openlog(const char* a_ident, int a_option, int a_facility)
{
	(void)a_ident;
	(void)a_option;
	(void)a_facility;
}


WLAC4_WLAC4_EXPORT void closelog(void)
{
}


WLAC4_WLAC4_EXPORT void vsyslog(int a_priority, const char* a_format, va_list a_ap)
{
	(void)a_priority;
	(void)a_format;
	(void)a_ap;
}



WLAC4_END_C
