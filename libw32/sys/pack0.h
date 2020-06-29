/* -*- mode: c; indent-width: 4; -*-
 * $Id: pack0.h,v 1.2 2020/06/28 23:57:48 cvsuser Exp $
 * ==noguard==
 *
 * win32 declaration helpers
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
 *
 * Usage:
 *
 *      #include <sys/cdefs.h>
 *
 *      #include <sys/pack1.h>
 *      struct __packed_pre__ mypackedstruct {
 *              :
 *      } __packed_post__;
 *      #include <sys/pack0.h>
 *
 */


#if !defined(__SYS_PACK1_H_INCLUDED__)
#error bad usage <sys/pack1.h> required
#endif

#if !(defined(lint) || defined(_lint))
#   if defined(_MSC_VER) && (_MSC_VER >= 800)
#       pragma pack()
#   elif defined(__WATCOMC__) || defined(__BORLANDC__) || defined(__PARADIGM__)
#       pragma pack()
#   endif
#endif
