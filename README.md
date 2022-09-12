- TIME_WAIT
- close(int sock)(关闭读写两个方向)
- shutdown(int sock, int howto) // SHUT_RD(1) | SHUT_WR(1) | SHUT_RDWR(2)
- TCP Keep-Alive | Ping-Pong
- TCP 拥塞 ｜ 用户缓冲区，系统缓冲区 ｜ 大报文 ｜ 小报文
- 在程序设计层面，不要多次频繁地发送小报文，如果有，可以使用 writev 批量发送。
- UDP 可以做connect，主要是为了应用可以处理 异步错误消息。 一般在Client端进行Connect。
- 性能有一定的优化，因为它简化了系统每次发送报文之后的断开socket的过程。
- 如果是UDP 的server端进行Connect，那将导致它只能和一个Client进行通信。
- TCP服务端程序应该都设置REUSEADDR，设置重用: 使用一个TIME_WAIT状态的端口 ｜ 可以为多网卡提供服务
int on = 1;
setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
- UDP 设置重用一般为组播场景：如我们在接收组播流的时候，比如用ffmpeg拉取了一个组播流，但是还想用ffmpeg拉取相同的组播流，这个时候就需要地址重用了
- TCP故障总结： https://time.geekbang.org/column/article/132639
- 连接是双向的，收到对方的 FIN 包只意味着对方不会再发送任何消息
- 设置超时
struct timeval tv;
tv.tv_sec = 5;
tv.tv_usec = 0;
setsockopt(connfd, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof tv);
