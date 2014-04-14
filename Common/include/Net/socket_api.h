/*  
    Copyright (C) <2014>  <jjchen.lian@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _SOCKET_API_H
#define _SOCKET_API_H


#if _WIN32
#elif __linux__
#include <sys/types.h>          // for accept()
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>          // for inet_xxx()
#include <netinet/in.h>
#include <errno.h>              // for errno
#include <stdbool.h>
#endif

#include <event.h>
#include <event2/bufferevent.h>

#include "base_type.h"

typedef     evutil_socket_t  SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;

#define     INVALID_SOCKET   -1
#define     SOCKET_ERROR     -1

SOCKET    socket_ex(INT domain, INT type, INT protocol);
BOOL    reuse_ex(SOCKET s);
BOOL    bind_ex(SOCKET s , const struct sockaddr * addr , UINT addrlen);
VOID    connect_ex();
BOOL    listen_ex();
VOID    accept_ex();
BOOL    setsocketnoblocking_ex(SOCKET s);

// SOCKET listener;
#endif
