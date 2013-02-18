/*	$Id$	*/

/*
 * Currently only supports console applications.
 */

#if defined(MSLINKER)
/* requires microsoft toolkit headers and linker, and pcc-libs */
#define	CPPADD { "-DWIN32", "-D_WIN32", NULL }
#define DEFLIBS { "/subsystem:console", "msvcrt.lib", "libpcc.a", NULL }
#else
/* common cpp predefines */
#define	CPPADD { "-DWIN32", "-D_WIN32", "-D__MSVCRT__", "-D__MINGW32__", NULL }

/* host-dependent */
/* requires w32api-3.2.tar.gz and mingw-runtime-3.14.tar.gz */
#define CRT0		"crt2.o"
#define STARTLABEL	"_mainCRTStartup"
#define CRT0_S		"dllcrt2.o"
#define STARTLABEL_S	"_DllMainCRTStartup@12"
#define GCRT0		"gcrt2.o"	/* in _addition_ to either crt2.o or dllcrt2.o */
#define	CRTBEGIN	0
#define	CRTBEGIN_S	0
#define	CRTBEGIN_T	0
#define	CRTEND		0
#define	CRTEND_S	0
#define	CRTEND_T	0
#define CRTI		((char*)0)
#define CRTN		((char*)0)
/* MingW cannot do -static linking */

#define WIN32_LIBC	"-lmsvcrt"
#define MINGW_RTLIBS	"-lmoldname", "-lmingwex", "-lmingw32"
#define MINGW_SYSLIBS	"-luser32", "-lkernel32" /* ,"-ladvapi32", "-lshell32" */
#define	DEFLIBS		{ MINGW_RTLIBS, "-lpcc", WIN32_LIBC, MINGW_SYSLIBS, MINGW_RTLIBS, WIN32_LIBC, 0 }
#define	DEFPROFLIBS	{ MINGW_RTLIBS, "-lpcc", WIN32_LIBC, "-lgmon", MINGW_SYSLIBS, MINGW_RTLIBS, WIN32_LIBC, 0 }
#define	DEFCXXLIBS	{ "-lp++", MINGW_RTLIBS, "-lpcc", WIN32_LIBC, MINGW_SYSLIBS, MINGW_RTLIBS, WIN32_LIBC, 0 }

#endif

#define CPPMDADD { "-D__i386__", NULL }
