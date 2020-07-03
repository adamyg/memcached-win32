/*
 *  config.h.in.  Generated from configure.ac by autoheader.
 */

#if defined(_WIN32)
#if defined(NDEBUG)                             // non-assert
#if defined(_DEBUG)
#error NDEBUG and _DEBUG are mutually exclusive
#endif
#else
#if !defined(_DEBUG)
#error NDEBUG and _DEBUG are mutually exclusive
#endif
#endif //NDEBUG
#if !defined(WIN32PORT)
#define WIN32PORT 1                             // enable windows tweaks
#endif
#endif //_WIN32

#if defined(_WIN32)
#include <w32config.h>
#include <libcompat.h>
#endif

#if !defined(_CRT_NO_POSIX_ERROR_CODES)
#define _CRT_NO_POSIX_ERROR_CODES
#endif

#if defined(_MSC_VER) || defined(__WATCOMC__)
#if !defined(LIBW32_SOCKET_MAP_NATIVE)
#define LIBW32_SOCKET_MAP_NATIVE 1              /* enable socket function mapping */
#endif
#if !defined(LIBW32_UNISTD_MAP)
#define LIBW32_UNISTD_MAP 1                     /* enable unistd function mapping */
#endif
#endif

#if defined(_MSC_VER)
#pragma warning(disable:4018) // '<': signed/unsigned mismatch
#pragma warning(disable:4028) // formal parameter 2 different from declaration
#pragma warning(disable:4101) // 'x': unreferenced local variable 'xxx'
#pragma warning(disable:4114) // same type qualifier used more than once (logger.h)
#pragma warning(disable:4146) // unary minus operator applied to unsigned type, result still unsigned
#pragma warning(disable:4244) // '=': conversion from 'xxx' to 'xxx', possible loss of data
#pragma warning(disable:4267) // 'function': conversion from 'size_t' to 'const uint8_t', possible loss of data
#endif

/* Define if building universal (internal helper macro) */
#undef  AC_APPLE_UNIVERSAL_BUILD

/* Set to nonzero if you want to enable ARMv8 crc32 */
#undef  ARM_CRC32

/* Set to nonzero if you want to compile using ASAN */
#undef  ASAN

/* Set to nonzero if you want to disable unix domain socket */
#define DISABLE_UNIX_SOCKET 1

/* Set to nonzero if you want to include DTRACE */
#undef  ENABLE_DTRACE

/* Set to nonzero if you want to include SASL */
#undef  ENABLE_SASL

/* Set to nonzero if you want to enable a SASL pwdb */
#undef  ENABLE_SASL_PWDB

/* machine is bigendian */
#undef  ENDIAN_BIG

/* machine is littleendian */
#define ENDIAN_LITTLE 1

/* Set to nonzero if you want to enable extstore */
#define EXTSTORE 1

/* Define to 1 if support accept4 */
#undef  HAVE_ACCEPT4

/* Define to 1 if you have the `cap_enter' function. */
#undef  HAVE_CAP_ENTER

/* Define to 1 if you have the `clock_gettime' function. */
#undef  HAVE_CLOCK_GETTIME

/* Define this if you have an implementation of drop_privileges() */
#undef  HAVE_DROP_PRIVILEGES

/* Define this if you have an implementation of drop_worker_privileges() */
#undef  HAVE_DROP_WORKER_PRIVILEGES

/* GCC 64bit Atomics available */
#undef  HAVE_GCC_64ATOMICS

/* GCC Atomics available */
#undef  HAVE_GCC_ATOMICS

/* Define to 1 if support getopt_long */
#if !defined(HAVE_GETOPT_LONG)
#if defined(_MSC_VER) || defined(__WATCOMC__)
#define HAVE_GETOPT_LONG 1
#endif
#endif
/*#undef  HAVE_GETOPT_LONG*/

/* Define to 1 if you have the `getpagesizes' function. */
#undef  HAVE_GETPAGESIZES

/* Have ntohll */
#if (defined(_MSC_VER) && (_WIN32_WINNT >= 0x602))
#define HAVE_HTONLL 1
#endif

/* Define to 1 if you have the <inttypes.h> header file. */
#undef  HAVE_INTTYPES_H

/* Define to 1 if you have the `memcntl' function. */
#undef  HAVE_MEMCNTL

/* Define to 1 if you have the <memory.h> header file. */
#undef  HAVE_MEMORY_H

/* Define to 1 if you have the `mlockall' function. */
#undef  HAVE_MLOCKALL

/* Define to 1 if you have the `pledge' function. */
#undef  HAVE_PLEDGE

/* Define to 1 if you have the `pread' function. */
#undef  HAVE_PREAD

/* Define to 1 if you have the `preadv' function. */
#undef  HAVE_PREADV

/* we have sasl_callback_ft */
#undef  HAVE_SASL_CALLBACK_FT

/* Set to nonzero if your SASL implementation supports SASL_CB_GETCONF */
#undef  HAVE_SASL_CB_GETCONF

/* Set to nonzero if your SASL implementation supports SASL_CB_GETCONFPATH */
#undef  HAVE_SASL_CB_GETCONFPATH

/* Define to 1 if you have the <sasl/sasl.h> header file. */
#undef  HAVE_SASL_SASL_H

/* Define to 1 if you have the `setppriv' function. */
#undef  HAVE_SETPPRIV

/* Define to 1 if you have the `sigignore' function. */
#undef  HAVE_SIGIGNORE

/* Define to 1 if stdbool.h conforms to C99. */
#undef  HAVE_STDBOOL_H

/* Define to 1 if you have the <stdint.h> header file. */
#undef  HAVE_STDINT_H

/* Define to 1 if you have the <stdlib.h> header file. */
#undef  HAVE_STDLIB_H

/* Define to 1 if you have the <strings.h> header file. */
#undef  HAVE_STRINGS_H

/* Define to 1 if you have the <string.h> header file. */
#undef  HAVE_STRING_H

/* Define to 1 if you have the `sysconf' function. */
#undef  HAVE_SYSCONF

/* Define to 1 if you have the <sys/stat.h> header file. */
#undef  HAVE_SYS_STAT_H

/* Define to 1 if you have the <sys/types.h> header file. */
#undef  HAVE_SYS_TYPES_H

/* Define to 1 if you have the <unistd.h> header file. */
#undef  HAVE_UNISTD_H

/* Define to 1 if the system has the type `_Bool'. */
#undef  HAVE__BOOL

/* Machine need alignment */
#undef  NEED_ALIGN

/* Name of package */
#define PACKAGE             "memcached"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT   ""

/* Define to the full name of this package. */
#define PACKAGE_NAME        "memmached"

/* Define to the version of this package. */
#define PACKAGE_VERSION     "1.6.6"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING      PACKAGE_NAME " - " PACKAGE_VERSION

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME     ""

/* Define to the home page for this package. */
#define PACKAGE_URL         ""

/* The size of `void *', as computed by sizeof. */
#undef  SIZEOF_VOID_P

/* Set to nonzero if you want to compile a statically linked binary */
#undef  STATIC

/* Define to 1 if you have the ANSI C header files. */
#if !defined(STDC_HEADERS)
#define STDC_HEADERS
#endif

/* Set to nonzero if you want to enable TLS */
#undef  TLS

/* Version number of package */
#define VERSION             PACKAGE_VERSION

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
#  undef WORDS_BIGENDIAN
# endif
#endif

/* find sigignore on Linux */
#undef _GNU_SOURCE

/* Define to empty if `const' does not conform to ANSI C. */
#undef  const

/* define to int if socklen_t not available */
#undef  socklen_t

#if defined(HAVE_STDBOOL_H)
#include <stdbool.h>
#else
#if !defined(bool)
#define bool char
#endif
#if !defined(false)
#define false 0
#define true 1
#endif
#endif

#if !defined(__attribute__)
#if defined(_MSC_VER) || defined(__WATCOMC__)
#define __attribute__(__x)
#endif
#endif

#if defined(HAVE_INTTYPES_H)
#include <inttypes.h>
#endif

#include <sys/socket.h>
#include <unistd.h>

extern int setgid(int groupid);
extern int setuid(int uid);

/*end*/
