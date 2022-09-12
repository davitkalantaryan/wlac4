/*
 *	File: <getopt.h> For WINDOWS MFC
 *
 *	Created on: Dec 10, 2015
 *	Author    : Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 * 
 *
 *
 */

#ifndef WLAC4_INCLUDE_WLAC4_GETOPT_H
#define WLAC4_INCLUDE_WLAC4_GETOPT_H

#include <wlac4_exports.h>


WLAC4_BEGIN_C

#define	no_argument		        0
#define required_argument	    1
#define optional_argument	    2


extern WLAC4_WLAC4_EXPORT char* optarg;
extern WLAC4_WLAC4_EXPORT int   optind;

WLAC4_WLAC4_EXPORT int getopt_long(int a_argc, const char* a_argv[],const char* a_optstring, const struct option* a_longopts, int* a_longindex);
WLAC4_WLAC4_EXPORT int getopt(int a_argc, const char* a_argv[], const char* a_optstring);


struct option {
#if (defined (__STDC__) && __STDC__) || defined(__cplusplus)
    const char* name;
#else
    char* name;
#endif
    int has_arg;
    int* flag;
    int val;
};


WLAC4_END_C

#endif //  #ifndef WLAC4_INCLUDE_WLAC4_GETOPT_H
