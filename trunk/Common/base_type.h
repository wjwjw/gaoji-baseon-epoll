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

#ifndef _BASE_TYPE_H
#define _BASE_TYPE_H

#include <string.h>

///////////////////////////////////////////////////////////////////////
//标准数据类型定义
///////////////////////////////////////////////////////////////////////
#define VOID            void            //标准空
typedef unsigned char   UCHAR;          //标准无符号CHAR
typedef char            CHAR;           //标准CHAR
typedef unsigned int    UINT;           //标准无符号INT
typedef int             INT;            //标准INT
typedef unsigned short  USHORT;         //标准无符号short
typedef short           SHORT;          //标准short
typedef unsigned long   ULONG;          //标准无符号LONG(不推荐使用)
typedef long            LONG;           //标准LONG(不推荐使用)
typedef float           FLOAT;          //标准float

typedef UCHAR           uchar;
typedef USHORT          ushort;
typedef UINT            uint;
typedef ULONG           ulong;
typedef ULONG           IP_t;
typedef USHORT          PacketID_t;
typedef INT             BOOL;
typedef UCHAR           BYTE;

//IP地址的字符最大长度
#define ip_size         24

#endif
