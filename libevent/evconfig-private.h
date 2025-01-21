#if !defined(EVENT_EVCONFIG__PRIVATE_H_)
#define EVENT_EVCONFIG__PRIVATE_H_

/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
#undef _GNU_SOURCE
#endif

/* Compiler tweaks */
#if defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
#pragma GCC diagnostic ignored "-Wcast-function-type"
#pragma GCC diagnostic ignored "-Wshadow"
#endif

#endif
