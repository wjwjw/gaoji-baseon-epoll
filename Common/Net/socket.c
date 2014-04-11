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

#include <stdbool.h>
#include "socket.h"

VOID socket_init()
{
    m_socket = INVALID_SOCKET;
    memset( &m_socket_addr, 0, sizeof(SOCKADDR_IN) );
    memset( m_host, 0, ip_size);
    m_port = 0;
}

//初始化socket addr, host, port
VOID socket_init_designation(const CHAR* host, UINT port)
{
    strncpy(m_host, host, ip_size - 1);
    m_port = port;
    socket_create();
}

BOOL socket_create()
{
    m_socket = socket_ex( AF_INET, SOCK_STREAM, 0 );
    memset( &m_socket_addr, 0, sizeof(m_socket_addr) );
    m_socket_addr.sin_family = AF_INET;
    if ( socket_isvalid() )
        return true;
    else
        return false;
}

BOOL socket_setreuseaddr()
{
    return reuse_ex(m_socket);
}

BOOL socket_bind()
{
    m_socket_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    m_socket_addr.sin_port = htons(m_port);

    BOOL result = bind_ex( m_socket, (const struct sockaddr *)&m_socket_addr, sizeof(m_socket_addr));

    if( result )
    {
        return true;
    }
    else
    {
        return false;
    }
}

BOOL socket_bind_designation(UINT port)
{
    m_port = port;

    m_socket_addr.sin_addr.s_addr  = htonl(INADDR_ANY);
    m_socket_addr.sin_port         = htons(m_port);

    BOOL result = bind_ex( m_socket, (const struct sockaddr *)&m_socket_addr, sizeof(m_socket_addr));

    if (result)
    {
        return true;
    }
    else
    {
        return false;
    }
}

BOOL socket_listen()
{
    return 1;
}

BOOL socket_isvalid()
{
    return m_socket != INVALID_SOCKET;
}
