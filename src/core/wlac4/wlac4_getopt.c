//
// file:			wlac4_poll.cpp
// path:			src/core/wlac4/wlac4_poll.cpp
// created on:		2022 Sep 11
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <getopt.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>


WLAC4_BEGIN_C


#define __P(x) x
#define _DIAGASSERT(x) assert(x)
#define	BADCH	(int)'?'
#define	BADARG	(int)':'
#define	EMSG	""
#define __progname_m(_path)	(strrchr(_path,'\\')+1)

WLAC4_WLAC4_EXPORT int  optind = 1;
WLAC4_WLAC4_EXPORT int	optreset;
WLAC4_WLAC4_EXPORT int	optopt;
WLAC4_WLAC4_EXPORT int	opterr;
WLAC4_WLAC4_EXPORT char* optarg = WLAC4_NULL;

/*
 * getopt --
 *	Parse argc/argv argument vector.
 */
	static int
	getopt_internal(nargc, nargv, ostr)
	int nargc;
	const char** nargv;
	const char* ostr;
{
	static const char* place = EMSG;		/* option letter processing */
	char* oli;				/* option letter list index */

	_DIAGASSERT(nargv != NULL);
	_DIAGASSERT(ostr != NULL);

	if (optreset || !*place) {		/* update scanning pointer */
		optreset = 0;
		if (optind >= nargc || *(place = nargv[optind]) != '-') {
			place = EMSG;
			return (-1);
		}
		if (place[1] && *++place == '-') {	/* found "--" */
			/* ++optind; */
			place = EMSG;
			return (-2);
		}
	}					/* option letter okay? */
	if ((optopt = (int)*place++) == (int)':' ||
		!(oli = strchr(ostr, optopt))) {
		/*
		 * if the user didn't specify '-' as an option,
		 * assume it means -1.
		 */
		if (optopt == (int)'-')
			return (-1);
		if (!*place)
			++optind;
		if (opterr && *ostr != ':')
			(void)fprintf(stderr,
				"%s: illegal option -- %c\n", __progname_m(nargv[0]), optopt);
		return (BADCH);
	}
	if (*++oli != ':') {			/* don't need argument */
		optarg = NULL;
		if (!*place)
			++optind;
	}
	else {				/* need an argument */
		if (*place)			/* no white space */
			optarg = (char*)place;
		else if (nargc <= ++optind) {	/* no arg */
			place = EMSG;
			if ((opterr) && (*ostr != ':'))
				(void)fprintf(stderr,
					"%s: option requires an argument -- %c\n",
					__progname_m(nargv[0]), optopt);
			return (BADARG);
		}
		else				/* white space */
			optarg = (char*)nargv[optind];
		place = EMSG;
		++optind;
	}
	return (optopt);			/* dump back option letter */
}


/*
 * getopt_long --
 *	Parse argc/argv argument vector.
 */
WLAC4_WLAC4_EXPORT int getopt_long(int nargc, const char* nargv[], const char* options, const struct option* long_options, int* index)
{
	int retval;

	_DIAGASSERT(options != NULL);
	_DIAGASSERT(long_options != NULL);
	/* index may be NULL */

	if ((retval = getopt_internal(nargc, nargv, options)) == -2) {
		const char* current_argv = nargv[optind++] + 2, * has_equal;
		int i, match = -1;
		size_t current_argv_len;

		if (*current_argv == '\0') {
			return(-1);
		}
		if ((has_equal = strchr(current_argv, '=')) != NULL) {
			current_argv_len = has_equal - current_argv;
			has_equal++;
		}
		else
			current_argv_len = strlen(current_argv);

		for (i = 0; long_options[i].name; i++) {
			if (strncmp(current_argv, long_options[i].name, current_argv_len))
				continue;

			if (strlen(long_options[i].name) == current_argv_len) {
				match = i;
				break;
			}
			if (match == -1)
				match = i;
		}
		if (match != -1) {
			if (long_options[match].has_arg == required_argument ||
				long_options[match].has_arg == optional_argument) {
				if (has_equal)
					optarg = (char*)has_equal;
				else
					optarg = (char*)nargv[optind++];
			}
			if ((long_options[match].has_arg == required_argument)
				&& (optarg == NULL)) {
				/*
				 * Missing argument, leading :
				 * indicates no error should be generated
				 */
				if ((opterr) && (*options != ':'))
					(void)fprintf(stderr,
						"%s: option requires an argument -- %s\n",
						__progname_m(nargv[0]), current_argv);
				return (BADARG);
			}
		}
		else { /* No matching argument */
			if ((opterr) && (*options != ':'))
				(void)fprintf(stderr,
					"%s: illegal option -- %s\n", __progname_m(nargv[0]), current_argv);
			return (BADCH);
		}
		if (long_options[match].flag) {
			*long_options[match].flag = long_options[match].val;
			retval = 0;
		}
		else
			retval = long_options[match].val;
		if (index)
			*index = match;
	}
	return(retval);
}


WLAC4_WLAC4_EXPORT int getopt(int nargc, const char* nargv[], const char* ostr)
{
	static const char* __progname = NULL;
	static const char* place = EMSG;		/* option letter processing */
	char* oli;				/* option letter list index */
	__progname = __progname ? __progname : __progname_m(*nargv);

	_DIAGASSERT(nargv != NULL);
	_DIAGASSERT(ostr != NULL);

	if (optreset || !*place) {		/* update scanning pointer */
		optreset = 0;
		if (optind >= nargc || *(place = nargv[optind]) != '-') {
			place = EMSG;
			return (-1);
		}
		if (place[1] && *++place == '-'	/* found "--" */
			&& place[1] == '\0') {
			++optind;
			place = EMSG;
			return (-1);
		}
	}					/* option letter okay? */
	if ((optopt = (int)*place++) == (int)':' ||
		!(oli = strchr(ostr, optopt))) {
		/*
		 * if the user didn't specify '-' as an option,
		 * assume it means -1.
		 */
		if (optopt == (int)'-')
			return (-1);
		if (!*place)
			++optind;
		if (opterr && *ostr != ':')
			(void)fprintf(stderr,
				"%s: illegal option -- %c\n", __progname, optopt);
		return (BADCH);
	}
	if (*++oli != ':') {			/* don't need argument */
		optarg = NULL;
		if (!*place)
			++optind;
	}
	else {					/* need an argument */
		if (*place)			/* no white space */
			optarg = (char*)place;
		else if (nargc <= ++optind) {	/* no arg */
			place = EMSG;
			if (*ostr == ':')
				return (BADARG);
			if (opterr)
				(void)fprintf(stderr,
					"%s: option requires an argument -- %c\n",
					__progname, optopt);
			return (BADCH);
		}
		else				/* white space */
			optarg = (char*)nargv[optind];
		place = EMSG;
		++optind;
	}
	return (optopt);			/* dump back option letter */
}


WLAC4_END_C
