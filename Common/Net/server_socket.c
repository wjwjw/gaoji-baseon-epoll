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

#include "Net/server_socket.h"

VOID server_socket_init(INT LoginPort)
{
    printf("out out out");
    BOOL ret = false;
    socket_init();
    ret = socket_create();
    assert(ret);
    ret = socket_setreuseaddr();
    assert(ret);
    socket_bind_designation(LoginPort);
    ret = socket_listen(5);
    assert(ret);

}

VOID server_socket_close()
{

}

VOID server_socket_accept()
{

}

VOID server_socket_set_nonblocking()
{

}

