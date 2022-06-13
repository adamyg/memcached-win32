/*    $Header: /cvs/memcached/libmemcached/memcached-1.6.15/daemon.c,v 1.1 2022/06/12 16:59:23 cvsuser Exp $    */
/*    $NetBSD: daemon.c,v 1.9 2003/08/07 16:42:46 agc Exp $    */
/*-
 * Copyright (c) 1990, 1993
 *    The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#if defined __SUNPRO_C || defined __DECC || defined __HP_cc
# pragma ident "@(#)$Header: /cvs/memcached/libmemcached/memcached-1.6.15/daemon.c,v 1.1 2022/06/12 16:59:23 cvsuser Exp $"
# pragma ident "$NetBSD: daemon.c,v 1.9 2003/08/07 16:42:46 agc Exp $"
#endif

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "memcached.h"

int daemonize(int nochdir, int noclose)
{
    int fd;

    switch (fork()) {
    case -1:
        return (-1);
    case 0:
        break;
    default:
        _exit(EXIT_SUCCESS);
    }

    if (setsid() == -1)
        return (-1);

    if (nochdir == 0) {
        if(chdir("/") != 0) {
            perror("chdir");
            return (-1);
        }
    }

    if (noclose == 0 && (fd = open("/dev/null", O_RDWR, 0)) != -1) {
        if(dup2(fd, STDIN_FILENO) < 0) {
            perror("dup2 stdin");
            goto err_cleanup;
        }
        if(dup2(fd, STDOUT_FILENO) < 0) {
            perror("dup2 stdout");
            goto err_cleanup;
        }
        if(dup2(fd, STDERR_FILENO) < 0) {
            perror("dup2 stderr");
            goto err_cleanup;
        }

        if(close(fd) < 0) {
            perror("close");
            return (-1);
        }
    }
    return (0);

    err_cleanup:
        close(fd);
        return (-1);
}
