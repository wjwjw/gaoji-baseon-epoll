#include "global.h"
#define MAX_EVENTS 500

/**
struct epoll_event
{
  uint32_t events;   //事件
  epoll_data_t data;    
} __attribute__ ((__packed__));

typedef union epoll_data
{
  void *ptr; //用户指针
  int fd;  //描述符
  uint32_t u32;
  uint64_t u64;
} epoll_data_t;
EPOLLIN ：表示对应的文件描述符可以读（包括对端SOCKET正常关闭）；
EPOLLOUT：表示对应的文件描述符可以写；
EPOLLPRI：表示对应的文件描述符有紧急的数据可读（这里应该表示有带外数据到来）；
EPOLLERR：表示对应的文件描述符发生错误；
EPOLLHUP：表示对应的文件描述符被挂断；
EPOLLET： 将EPOLL设为边缘触发(Edge Triggered)模式，这是相对于水平触发(Level Triggered)来说的。
EPOLLONESHOT：只监听一次事件，当监听完这次事件之后，如果还需要继续监听这个socket的话，需要再次把这个socket加入到EPOLL队列里
*/

struct myevent_s  
{  
    int fd;  
    void (*call_back)(int fd, int events, void *arg);  
    int events;  
    void *arg;  
    int status; // 1: in epoll wait list, 0 not in  
    char buff[128]; // recv data buffer  
    int len;  
    long last_active; // last active time  
}; 

int e_pollFd;  
struct myevent_s g_Events[MAX_EVENTS+1];

void RecvData(int fd, int events, void *arg);  
void SendData(int fd, int events, void *arg);

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

// set event  
void 
EventSet(struct myevent_s *ev, int fd, void (*call_back)(int, int, void*), void *arg)  
{  
    ev->fd = fd;  
    ev->call_back = call_back;  
    ev->events = 0;  
    ev->arg = arg;  
    ev->status = 0;  
    ev->last_active = time(NULL);  
}  

// add/mod an event to epoll  
//myevent_s用户空间的指针,给描述符增加事件监听
void 
EventAdd(int epollFd, int events, struct myevent_s *ev)  
{  
    struct epoll_event epv = {0, {0}};  //内核epoll事件结构体
    int op;  
    epv.data.ptr = ev;  
    epv.events = ev->events = events;  
    if(ev->status == 1){  
        op = EPOLL_CTL_MOD;  
    }  
    else{  
        op = EPOLL_CTL_ADD;  
        ev->status = 1;  
    }  
    if(epoll_ctl(epollFd, op, ev->fd, &epv) < 0)  
        printf("Event Add failed[fd=%d]/n", ev->fd);  
    else  
        printf("Event Add OK[fd=%d]/n", ev->fd);  
}  

// delete an event from epoll  
void 
EventDel(int epollFd, struct myevent_s *ev)  
{  
    struct epoll_event epv = {0, {0}};  
    if(ev->status != 1) return;  
    epv.data.ptr = ev;  
    ev->status = 0;  
    epoll_ctl(epollFd, EPOLL_CTL_DEL, ev->fd, &epv);  
}

void 
AcceptConn(int fd, int events, void *arg)  
{  
    struct sockaddr_in sin;  
    socklen_t len = sizeof(struct sockaddr_in);  
    int nfd, i;  
    // accept  
    if((nfd = accept(fd, (struct sockaddr*)&sin, &len)) == -1)  
    {  
        if(errno != EAGAIN && errno != EINTR)  
        {  
            printf("%s: bad accept", __func__);  
        }  
        return;  
    }  
    do  
    {  
        for(i = 0; i < MAX_EVENTS; i++)  
        {  
            if(g_Events[i].status == 0)  
            {  
                break;  
            }  
        }  
        if(i == MAX_EVENTS)  
        {  
            printf("%s:max connection limit[%d].", __func__, MAX_EVENTS);  
            break;  
        }  
        // set nonblocking  
        if(fcntl(nfd, F_SETFL, O_NONBLOCK) < 0) break;  
        // add a read event for receive data  
        EventSet(&g_Events[i], nfd, RecvData, &g_Events[i]);  
        EventAdd(e_pollFd, EPOLLIN|EPOLLET, &g_Events[i]);  
        printf("new conn[%s:%d][time:%ld]/n", inet_ntoa(sin.sin_addr), ntohs(sin.sin_port), g_Events[i].last_active);  
    }while(0);  
}  

// receive data  
void 
RecvData(int fd, int events, void *arg)  
{  
    struct myevent_s *ev = (struct myevent_s*)arg;  
    int len;  
    // receive data  
    len = recv(fd, ev->buff, sizeof(ev->buff)-1, 0);    
    EventDel(e_pollFd, ev);  
    if(len > 0)  
    {  
        ev->len = len;  
        ev->buff[len] = '\0';  
        printf("C[%d]:%s/n", fd, ev->buff);  
        // change to send event  
        EventSet(ev, fd, SendData, ev);  
        EventAdd(e_pollFd, EPOLLOUT|EPOLLET, ev);  
    }  
    else if(len == 0)  
    {  
        close(ev->fd);  
        printf("[fd=%d] closed gracefully./n", fd);  
    }  
    else  
    {  
        close(ev->fd);  
        printf("recv[fd=%d] error[%d]:%s/n", fd, errno, strerror(errno));  
    }  
} 

// send data  
void 
SendData(int fd, int events, void *arg)  
{  
    struct myevent_s *ev = (struct myevent_s*)arg;  
    int len;  
    // send data  
    len = send(fd, ev->buff, ev->len, 0);  
    ev->len = 0;  
    EventDel(e_pollFd, ev);  
    if(len > 0)  
    {  
        // change to receive event  
        EventSet(ev, fd, RecvData, ev);  
        EventAdd(e_pollFd, EPOLLIN|EPOLLET, ev);  
    }  
    else  
    {  
        close(ev->fd);  
        printf("recv[fd=%d] error[%d]/n", fd, errno);  
    }  
}

void
InitListenSocket(int e_pollFd, short port){
    int listenFd = socket(AF_INET, SOCK_STREAM, 0);
    setnonblocking(listenFd); //设置为非阻塞
    EventSet(&g_Events[MAX_EVENTS], listenFd, AcceptConn, &g_Events[MAX_EVENTS]);
    EventAdd(e_pollFd, EPOLLIN|EPOLLET, &g_Events[MAX_EVENTS]);  //给listenfd注册时间
	struct sockaddr_in sin;  
    bzero(&sin, sizeof(sin));  
    sin.sin_family = AF_INET;  
    sin.sin_addr.s_addr = INADDR_ANY;  
    sin.sin_port = htons(port);  
    bind(listenFd, (const struct sockaddr*)&sin, sizeof(sin));  
    listen(listenFd, 5);
}


int
start_game_server(){
    short port = 12345;
    e_pollFd = epoll_create(256);
    if(e_pollFd <= 0){
        perror("e_pollFd < 0");
    }

	InitListenSocket(e_pollFd, port); //初始化服务器配置
    printf("server running:port[%d]/n", port);  

	struct epoll_event events[MAX_EVENTS];
    int checkPos = 0;  
    while(1){  
        // a simple timeout check here, every time 100, better to use a mini-heap, and add timer event  
        long now = time(NULL);  
        int i;
        for(i = 0; i < 100; i++, checkPos++) // doesn't check listen fd  
        {  
            if(checkPos == MAX_EVENTS) checkPos = 0; // recycle  
            if(g_Events[checkPos].status != 1) continue;  
            long duration = now - g_Events[checkPos].last_active;  
            if(duration >= 60) // 60s timeout  
            {  
                close(g_Events[checkPos].fd);  
                printf("[fd=%d] timeout[%ld--%ld]./n", g_Events[checkPos].fd, g_Events[checkPos].last_active, now);  
                EventDel(e_pollFd, &g_Events[checkPos]);  
            }  
        }  
        // wait for events to happen  
        int fds = epoll_wait(e_pollFd, events, MAX_EVENTS, 1000);  
        if(fds < 0){  
            printf("epoll_wait error, exit/n");  
            break;  
        }  
        for(i = 0; i < fds; i++){  
            struct myevent_s *ev = (struct myevent_s*)events[i].data.ptr;  
            if((events[i].events & EPOLLIN) && (ev->events & EPOLLIN)) // read event  
            {  
                ev->call_back(ev->fd, events[i].events, ev->arg);  
            }  
            if((events[i].events & EPOLLOUT)&&(ev->events & EPOLLOUT)) // write event  
            {  
                ev->call_back(ev->fd, events[i].events, ev->arg);  
            }  
        }  
    }  
    // free resource  
    return 0;  
}
