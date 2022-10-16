set(lib
		acceptor.c
		buffer.c
		channel.c
		channel_map.c
		event_loop.c
		event_loop_thread.c
		http_request.c
		http_response.c
		http_server.c
        log.c
		poll_dispatcher.c
		sock.c
		tcp_connection.c
		tcp_server.c
		thread_pool.c
        )
if (EPOLL_EXISTS)
else ()
endif ()


add_library(serverlib ${lib})
target_link_libraries(serverlib pthread)

install(TARGETS serverlib DESTINATION lib)

#file(GLOB HEADERS "*.h")
#install(FILES ${HEADERS} DESTINATION include/)

