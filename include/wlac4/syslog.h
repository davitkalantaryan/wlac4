//
// file:			syslog.h
// path:			include/wlac4/syslog.h
// created on:		2022 Sep 11
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef WLAC4_INCLUDE_WLAC4_SYSLOG_H
#define WLAC4_INCLUDE_WLAC4_SYSLOG_H

#include <wlac4_exports.h>
#include <stdio.h>
#include <stdarg.h>

WLAC4_BEGIN_C


#define LOG_PID				0
#define LOG_DAEMON			1
#define LOG_INFO			2
#define LOG_CRIT			3
#define LOG_ERR				4
#define LOG_WARNING			5
#define LOG_NOTICE			6
#define LOG_DEBUG			7


WLAC4_WLAC4_EXPORT void syslog(int priority, const char* format, ...);
WLAC4_WLAC4_EXPORT void openlog(const char* ident, int option, int facility);
WLAC4_WLAC4_EXPORT void closelog(void);
WLAC4_WLAC4_EXPORT void vsyslog(int priority, const char* format, va_list ap);


WLAC4_END_C


#endif  // #ifndef WLAC4_INCLUDE_WLAC4_SYSLOG_H
