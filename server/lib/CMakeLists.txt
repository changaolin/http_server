set(lib
		acceptor.c
		buffer.c
		channel.c
		channel_map.c
		event_loop.c
        log.c
		poll_dispatcher.c
		sock.c
        )
if (EPOLL_EXISTS)
else ()
endif ()


add_library(serverlib ${lib})
target_link_libraries(serverlib pthread)

install(TARGETS serverlib DESTINATION lib)

#file(GLOB HEADERS "*.h")
#install(FILES ${HEADERS} DESTINATION include/)

