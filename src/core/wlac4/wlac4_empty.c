//
// file:			wlac4_empty.cpp
// path:			src/core/wlac4/wlac4_empty.cpp
// created on:		2022 Sep 12
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <redesigned/time.h>
#include <redesigned/stdio.h>
#include <syslog.h>
#include <getopt.h>
#include <stdlib.h>
#include <malloc.h>


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


WLAC4_WLAC4_EXPORT int getopt_long(int a_argc, char* const a_argv[],const char* a_optstring,const struct option* a_longopts, int* a_longindex)
{
	(void)a_argc;
	(void)a_argv;
	(void)a_optstring;
	(void)a_longopts;
	(void)a_longindex;
	return 0;
}


WLAC4_WLAC4_EXPORT ssize_t getline(char** a_lineptr, size_t* a_n, FILE* a_stream)
{
	(void)a_lineptr;
	(void)a_n;
	(void)a_stream;
	return 0;
}


WLAC4_WLAC4_EXPORT char* optarg = NULL;
WLAC4_WLAC4_EXPORT int   optind = 1;


static void cleanup_dl_wlac_empty(void) {
	free(optarg);
	optarg = NULL;
}

LIBDNL_C_CODE_INITIALIZER(initialize_dl_wlac_empty) {
	optarg = (char*)malloc(4096);
	if (optarg) {
		optarg[0] = 0;
	}
}



WLAC4_END_C
