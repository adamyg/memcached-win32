#ifndef LIBW32_SYS_RWLOCK_H_INCLUDED
#define LIBW32_SYS_RWLOCK_H_INCLUDED
#include <edidentifier.h>
__CIDENT_RCSID(gr_libw32_sys_rwlock_h,"$Id: rwlock.h,v 1.1 2022/06/12 16:08:46 cvsuser Exp $")
__CPRAGMA_ONCE

/* -*- mode: c; indent-width: 4; -*- */
/*
 * win32 <rwlock.h> implementation
 *
 * Copyright (c) 1998 - 2022, Adam Young.
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

#include <sys/cdefs.h>

typedef struct rwlock {
    unsigned int        opaque[16];
} rwlock_t;

#define RWLOCK_INITIALIZER      {0xffff}

__BEGIN_DECLS

LIBW32_API void         rwlock_init(struct rwlock *rw);
LIBW32_API void         rwlock_destroy(struct rwlock *rw);
LIBW32_API void         rwlock_rdlock(struct rwlock *rw);
LIBW32_API void         rwlock_wrlock(struct rwlock *rw);
LIBW32_API void         rwlock_rdunlock(struct rwlock *rw);
LIBW32_API void         rwlock_wrunlock(struct rwlock *rw);
LIBW32_API void         rwlock_unlock(struct rwlock *rw);
LIBW32_API int          rwlock_status(struct rwlock *rw);

__END_DECLS

#endif /*LIBW32_SYS_RWLOCK_H_INCLUDED*/

