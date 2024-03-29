#pragma once
/*
 *  timespec.h
 *
 *  Copyright (c) 2020 - 2022, Adam Young.
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

#if !defined(HAVE_TIMESPEC_GET)
#if defined(_MSC_VER) && (_MSC_VER >= 1900)
#define HAVE_TIMESPEC_GET
#endif
#endif //HAVE_TIMESPEC_GET

#include <time.h>

#if defined(_MSC_VER)
#if !defined(_TIMESPEC_DEFINED) && !defined(HAVE_TIMESPEC_GET)
#define _TIMESPEC_DEFINED /* 2013 < */
struct timespec {
        time_t tv_sec;
        long tv_nsec;
};
#endif /*TIMESPEC_STRUCT_T*/

#elif defined(__WATCOMC__)
#if !defined(_TIMESPEC_DEFINED) && (__WATCOMC__ < 1300)
#define _TIMESPEC_DEFINED /* OWC1.9=1290, OWC2.0=1300 */
struct timespec {
        time_t tv_sec;
        long tv_nsec;
};
#else
#include <signal.h>
#endif /*TIMESPEC_STRUCT_T*/
#endif /*WATCOMC*/

#if !defined(HAVE_TIMESPEC)
#define HAVE_TIMESPEC
#endif

#if !defined(TIMEVAL_TO_TIMESPEC)
#define TIMEVAL_TO_TIMESPEC(tv, ts) {           \
        (ts)->tv_sec = (tv)->tv_sec;            \
        (ts)->tv_nsec = (tv)->tv_usec * 1000;   \
}
#define TIMESPEC_TO_TIMEVAL(tv, ts) {           \
        (tv)->tv_sec = (ts)->tv_sec;            \
        (tv)->tv_usec = (ts)->tv_nsec / 1000;   \
}
#endif

/*end*/
