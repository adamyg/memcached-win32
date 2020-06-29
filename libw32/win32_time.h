#ifndef LIBW32_WIN32_TIME_H_INCLUDED
#define LIBW32_WIN32_TIME_H_INCLUDED
#include <edidentifier.h>
__CIDENT_RCSID(gr_libw32_time_h,"$Id: win32_time.h,v 1.2 2020/06/28 23:57:48 cvsuser Exp $")
__CPRAGMA_ONCE

/* -*- mode: c; indent-width: 4; -*- */
/*
 * win32 time functionality.
 *
 * Copyright (c) 1998 - 2020, Adam Young.
 * All rights reserved.
 *
 * This file is part of memcached-win32.
 *
 * The applications are free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * Redistributions of source code must retain the above copyright
 * notice, and must be distributed with the license document above.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, and must include the license document above in
 * the documentation and/or other materials provided with the
 * distribution.
 *
 * This project is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * ==end==
 */

#include <sys/cdefs.h>

__BEGIN_DECLS

LIBW32_API unsigned int sleep(unsigned int);

struct timeval;
struct timezone;

LIBW32_API int          w32_gettimeofday(struct timeval *tv, void /*struct timezone*/ *tz);

struct utimbuf;

LIBW32_API int          w32_utime(const char *path, const struct utimbuf *times);

#if defined(_MSC_VER) || defined(__WATCOMC__)
LIBW32_API time_t       timegm(struct tm *tm);
#endif

__END_DECLS

#endif /*LIBW32_WIN32_TIME_H_INCLUDED*/
