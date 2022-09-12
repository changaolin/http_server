使用套接字进行读写：开始交流吧
https://time.geekbang.org/column/article/116043

-MTU： Maximum Transmit Unit，最大传输单元，即物理接口（数据链路层）提供给其上层（通常是IP层）最大一次传输数据的大小；以普遍使用的以太网接口为例，缺省MTU=1500 Byte，这是以太网接口对IP层的约束，如果IP层有<=1500 byte 需要发送，只需要一个IP包就可以完成发送任务；如果IP层有> 1500 byte 数据需要发送，需要分片才能完成发送，这些分片有一个共同点，即IP Header ID相同。
 
-MSS：Maximum Segment Size ，TCP提交给IP层最大分段大小，不包含TCP Header和 TCP Option，只包含TCP Payload ，MSS是TCP用来限制application层最大的发送字节数。如果底层物理接口MTU= 1500 byte，则 MSS = 1500- 20(IP Header) -20 (TCP Header) = 1460 byte，如果application 有2000 byte发送，需要两个segment才可以完成发送，第一个TCP segment = 1460，第二个TCP segment = 540。
 
https://www.jianshu.com/p/3be7582ddf78


- (阻塞IO)read 返回值为0， 表示EOF(end of file),在网络中则表示收到了FIN包。
- (阻塞IO)read 返回值为-1，表示出错

- timeout 单位 ms： 
int poll(struct pollfd *fds, unsigned long nfds, int timeout); 
　　　
返回值：若有就绪描述符则为其数目，若超时则为0，若出错则为-1

struct pollfd {    
	int    fd;       /* file descriptor */    
	short  events;   /* events to look for */    
	short  revents;  /* events returned */
};

POLLIN // 可读
POLLOUT // 可写

POLLERR		/* 一些错误发送 */
POLLHUP    /* 描述符挂起*/
POLLNVAL   /* 请求的事件无效*/

//// IO_BLOCK.png
read 总是在接收缓冲区有数据时就立即返回，不是等到应用程序给定的数据充满才返回。当接收缓冲区为空时，阻塞模式会等待，非阻塞模式立即返回 -1，并有 EWOULDBLOCK 或 EAGAIN 错误。
和 read 不同，阻塞模式下，write 只有在发送缓冲区足以容纳应用程序的输出字节时才返回；而非阻塞模式下，则是能写入多少就写入多少，并返回实际写入的字节数。
阻塞模式下的 write 有个特例, 就是对方主动关闭了套接字，这个时候 write 调用会立即返回，并通过返回值告诉应用程序实际写入的字节数，如果再次对这样的套接字进行 write 操作，就会返回失败。失败是通过返回值 -1 来通知到应用程序的。
当我们调用fcntl将套接字配置为非阻塞后，在该套接字上后续的accept，read，write操作都将变为非阻塞


//epoll

int epoll_create(int size);
int epoll_create1(int flags);
返回值: 若成功返回一个大于0的值，表示epoll实例；若返回-1表示出错

int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
返回值: 若成功返回0；若返回-1表示出错

EPOLL_CTL_ADD： 向 epoll 实例注册文件描述符对应的事件
EPOLL_CTL_DEL：向 epoll 实例删除文件描述符对应的事件；
EPOLL_CTL_MOD： 修改文件描述符对应的事件。

typedef union epoll_data {
     void        *ptr;
     int          fd;
     uint32_t     u32;
     uint64_t     u64;
 } epoll_data_t;

 struct epoll_event {
     uint32_t     events;      /* Epoll events */
     epoll_data_t data;        /* User data variable */
 };
EPOLLIN：表示对应的文件描述字可以读；
EPOLLOUT：表示对应的文件描述字可以写；
EPOLLRDHUP：表示套接字的一端已经关闭，或者半关闭；
EPOLLHUP：表示对应的文件描述字被挂起；
EPOLLET：设置为 edge-triggered，默认为 level-triggered。

int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
返回值: 成功返回的是一个大于0的数，表示事件的个数；返回0表示的是超时时间到；若出错返回-1.

epoll 通过改进的接口设计，避免了用户态 - 内核态频繁的数据拷贝，大大提高了系统性能。在使用 epoll 的时候，我们一定要理解条件触发和边缘触发两种模式。条件触发的意思是只要满足事件的条件，比如有数据需要读，就一直不断地把这个事件传递给用户；而边缘触发的意思是只有第一次满足条件的时候才触发，之后就不会再传递同样的事件了。
