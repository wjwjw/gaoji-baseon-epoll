#include "global.h"

void start_game_server();

/*
注释新的服务进程
*/
int 
main(int argc,char** argv)
{

    pid_t log_pid;
    log_pid = fork();
    //启动日志进程
    if(log_pid == 0){
    }
    //启动服务器进程
    else{
	start_game_server();
    }
    return 0;
}
