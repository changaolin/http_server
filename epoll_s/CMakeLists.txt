set(CMAKE_C_STANDARD 11)
add_executable(epoll_server common.c server.c)
add_executable(epoll_client common.c client.c)
