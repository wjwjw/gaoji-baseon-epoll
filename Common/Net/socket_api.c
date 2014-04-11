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
#include "socket_api.h"

SOCKET socket_ex(INT domain, INT type, INT protocol)
{
    SOCKET s = socket(domain, type, protocol);

    if (s == INVALID_SOCKET)
    {
#if __linux__
        switch( errno )
        {
            //错误原因是参数中的错误,表示申请的服务或指定的协议无效
            case EPROTONOSUPPORT:
            //错误的原因是应用程序的描述符已满
            case EMFILE:
            //错误的原因是应用程序内部的系统文件表已满
            case ENFILE:
            case EACCES:
            //错误的原因是系统没有可用的缓冲空间
            case ENOBUFS:
            default:
                {
                    break;
                }
        }
#elif _WIN32
#endif
    }
    return s;
}

BOOL reuse_ex(SOCKET s)
{
    INT result = evutil_make_listen_socket_reuseable(s);
    if(result == -1)
    {
#if __linux__
        switch( errno )
        {
            //错误原因是第一个参数没有指定合法的描述符
            case EBADF:
            //错误原因是第一个参数没有指定一个套接字描述符
            case ENOTSOCK:
            //错误原因是opt 不正确
            case ENOPROTOOPT:
            //错误原因是参数buffer 不正确
            case EFAULT:
            default:
                {
                    break;
                }
        }
    return false;
#elif _WIN32
#endif  
    }
    return true;
}

BOOL bind_ex(SOCKET s , const struct sockaddr * addr , UINT addrlen)
{
    if ( bind (s, addr, addrlen) == SOCKET_ERROR )
    {
#if __linux__
        switch ( errno ) 
        {
        case EADDRINUSE :
        case EINVAL : 
        case EACCES : 
        case ENOTSOCK : 
        case EBADF : 
        case EROFS : 
        case EFAULT : 
        case ENAMETOOLONG : 
        case ENOENT : 
        case ENOMEM : 
        case ENOTDIR : 
        case ELOOP : 
        default :
            {
                break;
            }
        }//end of switch
#elif _WIN32
#endif
        return false;
    }
    return true;
}
