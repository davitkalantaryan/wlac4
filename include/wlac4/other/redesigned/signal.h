//
// repo:            wlac4
// file:			signal.h
// path:			include/wlac4/other/redesigned/signal.h
// created on:		2025 Jul 23
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef WLAC4_INCLUDE_WLAC4_OTHER_REDESIGNED_SIGNAL_H
#define WLAC4_INCLUDE_WLAC4_OTHER_REDESIGNED_SIGNAL_H

#include <wlac4_exports.h>
#include <other/redesigned/sys/types.h>
#ifndef WLAC4_SIGNAL_H_REDIRECT_DONE
#pragma include_alias( <signal.h>, <signal.h> )
#pragma include_alias( "signal.h", "signal.h" )
#define WLAC4_SIGNAL_H_REDIRECT_DONE
#endif
#ifndef WLAC4_TIME_H_REDIRECT_DONE
#pragma include_alias( <time.h>, <time.h> )
#pragma include_alias( "time.h", "time.h" )
#define WLAC4_TIME_H_REDIRECT_DONE
#endif
#include <cinternal/disable_compiler_warnings.h>
#include <signal.h>
#include <time.h>
#include <cinternal/undisable_compiler_warnings.h>

WLAC4_BEGIN_C


#define		__SI_PAD_SIZE	28
#define		_SIGSET_NWORDS	(1024 / (8 * sizeof (size_t)))

#define		SA_SIGINFO		0x1
#define		SA_RESETHAND	0x2
#define		SA_RESTART		0x10000000 /* Restart syscall on signal return.  */

#define	SIGPIPE		13	/* Broken pipe (POSIX).  */
#define	SIGALRM		14	/* Alarm clock (POSIX).  */

//typedef void (*sighandler_t) (int);
typedef _crt_signal_t sighandler_t;

#ifndef __sigchld_clock_t_defined
#define __sigchld_clock_t_defined
typedef clock_t __sigchld_clock_t;
#endif

typedef union sigval
{
    int sival_int;
    void* sival_ptr;
} sigval_t;

typedef struct
{
    int si_signo;		/* Signal number.  */
    int si_errno;		/* If non-zero, an errno value associated with
                   this signal, as defined in <errno.h>.  */
    int si_code;		/* Signal code.  */

    union
    {
        int _pad[__SI_PAD_SIZE];

        /* kill().  */
        struct
        {
            pid_t si_pid;	/* Sending process ID.  */
            uid_t si_uid;	/* Real user ID of sending process.  */
        } _kill;

        /* POSIX.1b timers.  */
        struct
        {
            int si_tid;		/* Timer ID.  */
            int si_overrun;	/* Overrun count.  */
            sigval_t si_sigval;	/* Signal value.  */
        } _timer;

        /* POSIX.1b signals.  */
        struct
        {
            pid_t si_pid;	/* Sending process ID.  */
            uid_t si_uid;	/* Real user ID of sending process.  */
            sigval_t si_sigval;	/* Signal value.  */
        } _rt;

        /* SIGCHLD.  */
        struct
        {
            pid_t si_pid;	/* Which child.  */
            uid_t si_uid;	/* Real user ID of sending process.  */
            int si_status;	/* Exit value or signal.  */
            __sigchld_clock_t si_utime;
            __sigchld_clock_t si_stime;
        } _sigchld;

        /* SIGILL, SIGFPE, SIGSEGV, SIGBUS.  */
        struct
        {
            void* si_addr;	/* Faulting insn/memory ref.  */
        } _sigfault;

        /* SIGPOLL.  */
        struct
        {
            long int si_band;	/* Band event for SIGPOLL.  */
            int si_fd;
        } _sigpoll;

        /* SIGSYS.  */
        struct
        {
            void* _call_addr;	/* Calling user insn.  */
            int _syscall;	/* Triggering system call number.  */
            unsigned int _arch; /* AUDIT_ARCH_* of syscall.  */
        } _sigsys;
    } _sifields;
} siginfo_t;

typedef struct
{
    unsigned long int __val[_SIGSET_NWORDS];
} __sigset_t, sigset_t;

struct sigaction
{
    /* Signal handler.  */
    union
    {
        /* Used if SA_SIGINFO is not set.  */
        sighandler_t sa_handler;
        /* Used if SA_SIGINFO is set.  */
        void (*sa_sigaction) (int, siginfo_t*, void*);
    }__sigaction_handler;

# define sa_handler	__sigaction_handler.sa_handler
# define sa_sigaction	__sigaction_handler.sa_sigaction

    /* Additional set of signals to be blocked.  */
    __sigset_t sa_mask;

    /* Special flags.  */
    int sa_flags;
    int is_inited; // introduced (DK)

    /* Restore handler.  */
    void (*sa_restorer) (void);
};

WLAC4_WLAC4_EXPORT int sigemptyset(sigset_t* set);
WLAC4_WLAC4_EXPORT int sigaddset(sigset_t* set, int signum);
WLAC4_WLAC4_EXPORT int sigaction(int signum, const struct sigaction* act, struct sigaction* oldact);


WLAC4_END_C

#endif  //  #ifndef WLAC4_INCLUDE_WLAC4_OTHER_REDESIGNED_SIGNAL_H
