/*
 * Copyright (c) 2020 - 2025, Adam Young.
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

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/resource.h>
#include <unistd.h>
#include <assert.h>

extern int daemonize(int nochdir, int noclose);
extern int setgid(int groupid);
extern int setuid(int uid);

int
daemonize(int nochdir, int noclose)
{
    HWND console = GetConsoleWindow();
    if (console) {
        ShowWindow(console, SW_HIDE /*SW_MINIMIZE*/);
    }
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
