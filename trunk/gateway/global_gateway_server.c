#include "server.h"

struct sockaddr_in serveraddr;

void 
setnonblocking(int sock)
{
    int opts;
    opts=fcntl(sock,F_GETFL);
    if(opts<0){
	   perror("fcntl(sock,GETFL)");
    }
   	opts = opts|O_NONBLOCK;
    if(fcntl(sock,F_SETFL,opts)<0){
	   perror("fcntl(sock,SETFL,opts)");
    }
}

void
init_game_server(){
	char *local_addr = "127.0.0.1";
	int game_port = 12345;
	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	inet_aton(local_addr,&(serveraddr.sin_addr));
	serveraddr.sin_port = htons(game_port);
}


void
start_game_sever(){
	//声明epoll_event结构体的变量,ev用于注册事件,数组用于回传要处理的事件
	struct epoll_event ev,events[20];
	int i;
	int epfd,nfds;
	int listenfd,connfd,sockfd;
	socklen_t clilen;
	struct sockaddr_in serveraddr;
	struct sockaddr_in clientaddr;
	ssize_t n = 0;
	char line[MAXLINE];

	init_game_server();
	epfd = epoll_create(256);
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	setnonblocking(listenfd);
	ev.data.fd = listenfd;
	ev.events = EPOLLIN | EPOLLET;
	epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);
	bind(listenfd, (const struct sockaddr *)&serveraddr, sizeof(serveraddr));
	listen(listenfd, LISTENQ);
	for (; ; ){
		nfds = epoll_wait(epfd, events, 20, 500);
		for(i = 0; i < nfds; ++i){
            //如果新监测到一个SOCKET用户连接到了绑定的SOCKET端口，建立新的连接。
			if(events[i].data.fd == listenfd){
           		connfd = accept(listenfd,(struct sockaddr *)&clientaddr, &clilen);
                if(connfd<0){
                    perror("connfd<0");
                }
                //setnonblocking(connfd);

                char *str = inet_ntoa(clientaddr.sin_addr);
                //设置用于读操作的文件描述符
                printf("%s",str);

                ev.data.fd=connfd;
                //设置用于注测的读操作事件

                ev.events=EPOLLIN|EPOLLET;
                //ev.events=EPOLLIN;

                //注册ev

                epoll_ctl(epfd,EPOLL_CTL_ADD,connfd,&ev);
            }
            //如果是已经连接的用户，并且收到数据，那么进行读入。
            else if(events[i].events&EPOLLIN){
            	if ( (sockfd = events[i].data.fd) < 0)
                    continue;
                if ( (n = read(sockfd, line, MAXLINE)) < 0){
                    if (errno == ECONNRESET){
                        close(sockfd);
                        events[i].data.fd = -1;
                    } 
                    else{}
                } 
                else if (n == 0){
                    close(sockfd);
                    events[i].data.fd = -1;
                }
                line[n] = '\0';
                //设置用于写操作的文件描述符

                ev.data.fd=sockfd;
                //设置用于注测的写操作事件

                ev.events=EPOLLOUT|EPOLLET;
                //修改sockfd上要处理的事件为EPOLLOUT

                //epoll_ctl(epfd,EPOLL_CTL_MOD,sockfd,&ev);

            }
            // 如果有数据发送
            else if(events[i].events&EPOLLOUT){
                sockfd = events[i].data.fd;
                write(sockfd, line, n);
                //设置用于读操作的文件描述符

                ev.data.fd=sockfd;
                //设置用于注测的读操作事件

                ev.events=EPOLLIN|EPOLLET;
                //修改sockfd上要处理的事件为EPOLIN

                epoll_ctl(epfd,EPOLL_CTL_MOD,sockfd,&ev);
            }
        }
	}
}
