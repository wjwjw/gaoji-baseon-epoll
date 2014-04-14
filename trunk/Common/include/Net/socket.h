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

#ifndef _SOCKET_H
#define _SOCKET_H


#include "socket_api.h"

VOID    socket_init();
VOID    socket_init_designation(const CHAR* host, UINT port);
BOOL    socket_create();
BOOL    socket_setreuseaddr();
BOOL    socket_bind();
BOOL    socket_bind_designation(UINT port);
BOOL    socket_listen(INT backlog);
BOOL    socket_isvalid();
BOOL    socket_setnoblocking(SOCKET s);

SOCKET m_socket;
SOCKADDR_IN m_socket_addr;
int m_port;
char m_host[ip_size];

#endif
