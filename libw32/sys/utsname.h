#ifndef LIBW32_SYS_UTSNAME_H_INCLUDED
#define LIBW32_SYS_UTSNAME_H_INCLUDED
#include <edidentifier.h>
__CIDENT_RCSID(gr_libw32_sys_utsname_h,"$Id: utsname.h,v 1.2 2025/01/20 19:13:51 cvsuser Exp $")
__CPRAGMA_ONCE

/* -*- mode: c; indent-width: 4; -*- */
/*
 * Copyright (c) 2012 - 2025, Adam Young.
 * All rights reserved.
 *
 * This file is part of memcached-win32.
 *
 * The applications are free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, version 3.
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
 * license for more details.
 * ==end==
 */

#define _UTSNAME_LENGTH 64

struct utsname {
    char sysname[_UTSNAME_LENGTH];
    char nodename[_UTSNAME_LENGTH];
    char release[_UTSNAME_LENGTH];
    char version[_UTSNAME_LENGTH];
    char machine[_UTSNAME_LENGTH];
};

#include <sys/cdefs.h>                          /* __BEGIN_DECLS, __PDECL */

__BEGIN_DECLS
LIBW32_API int          uname(struct utsname *buf);
__END_DECLS

#endif  /*LIBW32_SYS_UTSNAME_H_INCLUDED*/

