set(CMAKE_C_STANDARD 11)
add_executable(poll_server common.c server.c)
add_executable(poll_client common.c client.c)
