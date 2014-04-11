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

#include <stdio.h>

#include "thread_manager.h"
#include "server_thread.h"

bool thread_manager_init()
{
    m_nthreads ++;
    return true;
}

bool thread_manager_start()
{
    pthread_create(&tid, NULL, server_thread_run, NULL);
    return true;
}

bool thread_manager_stop()
{
    void* tret;
    pthread_cancel(tid);
    pthread_join(tid, &tret);
    printf("server thread run stop exit code=%d\n", (int)tret);
    return false;
}
