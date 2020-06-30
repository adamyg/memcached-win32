/*
 * memcache service ...
 *
 * Copyright (c) 2020, Adam Young.
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
 * The WinRSH/WinSSH project is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * ==end==
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/resource.h>
#include <unistd.h>
#include <assert.h>


int
daemonize(int nochdir, int noclose)
{
    (void) nochdir;
    (void) noclose;
    return 0;
}


int
setgid(int groupid)
{
    assert(0);
    return -1;
}


int
setuid(int uid)
{
    assert(0);
    return -1;
}

/*end*/
