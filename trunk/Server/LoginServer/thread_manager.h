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

/*
线程管理器
*/
#ifndef _THREAD_MANAGER_H
#define _THREAD_MANAGER_H

#include <stdbool.h>
#include <pthread.h>

//初始化
bool    thread_manager_init();
//启动所有线程
bool    thread_manager_start();
//停止所有线程
bool    thread_manager_stop();

int    m_nthreads;
pthread_t   tid;

#endif
