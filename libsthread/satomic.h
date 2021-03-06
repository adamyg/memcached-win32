#if !defined(SATOMIC_H_INCLUDED)
#define SATOMIC_H_INCLUDED
/*
 *  Simple win32 threads - atomic operations
 *
 *  Copyright (c) 2020, Adam Young.
 *  All rights reserved.
 *
 *  This file is part of memcached-win32.
 *
 *  The applications are free software: you can redistribute it
 *  and/or modify it under the terms of the GNU General Public License as
 *  published by the Free Software Foundation, version 3.
 *
 *  Redistributions of source code must retain the above copyright
 *  notice, and must be distributed with the license document above.
 *
 *  Redistributions in binary form must reproduce the above copyright
 *  notice, and must include the license document above in
 *  the documentation and/or other materials provided with the
 *  distribution.
 *
 *  This project is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *  ==end==
 */

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_MSC_VER)

typedef long satomic_lock_t;
extern long __cdecl _InterlockedExchange(long volatile *, long);
extern void _ReadWriteBarrier();

#pragma intrinsic( _InterlockedExchange )
#pragma intrinsic( _ReadWriteBarrier )

#define SATOMIC_INTERLOCK_EXCHANGE _InterlockedExchange
#define SATOMIC_FENCE _ReadWriteBarrier();
#endif

static __inline int
satomic_try_lock(volatile satomic_lock_t *lock) {
    long r = SATOMIC_INTERLOCK_EXCHANGE(lock, 1);
    SATOMIC_FENCE
    return (r == 0);
}


static __inline void
satomic_lock(volatile satomic_lock_t *lock) {
    unsigned k = 0;
    while (! satomic_try_lock(lock)) {
        if (k < 4) {
        } else if (k < 32) {
            Sleep(0);
        } else {
            Sleep(1);
        }
        ++k;
    }
}


static __inline void
satomic_unlock(volatile satomic_lock_t *lock) {
    SATOMIC_FENCE
    *lock = 0;
}

#ifdef __cplusplus
}
#endif

#endif /*SATOMIC_H_INCLUDED*/

/*end*/
