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
