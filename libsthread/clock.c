/*
 *  Simple win32 threads - conditions.
 *
 *  Copyright (c) 2020, Adam Young.
 *  All rights reserved.
 *
 *  This file is part of memcached-win32.
 *
 *  The applications are free software: you can redistribute it
 *  and/or modify it under the terms of the GNU General Public License as
 *  published by the Free Software Foundation, either version 3 of the License,
 *  or (at your option) any later version.
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

#include "sthread.h"

#include <sys/socket.h>
#if defined(_MSC_VER) || defined(__WATCOMC__)
#include <sys/timeb.h>
#endif
#include <time.h>
#include <assert.h>
#include <unistd.h>

#include "timespec.h"


int
clock_gettime(int clockid, struct timespec *time_spec)
{
#if defined(HAVE_TIMESPEC_GET)
    timespec_get(time_spec, TIME_UTC);

#elif defined(_MSC_VER) || defined(__WATCOMC__)
    struct __timeb64 ftime;

    _ftime64(&ftime);
    time_spec->tv_sec = ftime.time + lt.timezone;
    time_spec->tv_usec = ftime.millitm * 1000000;

#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    TIMEVAL_TO_TIMESPEC(&tv, timespec);
#endif

    assert(CLOCK_REALTIME == clockid);
    (void)clockid;

    return 0;
}


int
usleep(useconds_t useconds)
{
    if (useconds >= 1000000) return EINVAL;
    Sleep((DWORD)(useconds / 1000));
    return 0;
}


unsigned
sleep(unsigned secs)
{
    Sleep((DWORD)secs * 1000);
    return 0;
}

/*end*/
