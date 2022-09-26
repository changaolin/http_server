if (EPOLL_EXISTS)
    set(lib
            log.c
            # sock_ntop.c
            # read.c
            # tcp_server.c
            # tcp_client.c
            # event_loop.c
            # channel.c
            # acceptor.c
            # channel_map.c
            # poll_dispatcher.c
            # thread_pool.c
            # event_loop_thread.c
            # utils.c
            # epoll_dispatcher.c
            # buffer.c
            # tcp_connection.c
            # http_server.c
            # http_request.c
            # http_response.c
            )
else ()
    set(lib
            log.c
            # sock_ntop.c
            # read.c
            # tcp_server.c
            # tcp_client.c
            # event_loop.c
            # channel.c
            # acceptor.c
            # channel_map.c
            # poll_dispatcher.c
            # thread_pool.c
            # event_loop_thread.c
            # utils.c
            # buffer.c
            # tcp_connection.c
            # http_server.c
            # http_request.c
            # http_response.c
            )
endif ()


add_library(serverlib ${lib})
target_link_libraries(serverlib pthread)

install(TARGETS serverlib DESTINATION lib)

#file(GLOB HEADERS "*.h")
#install(FILES ${HEADERS} DESTINATION include/)

