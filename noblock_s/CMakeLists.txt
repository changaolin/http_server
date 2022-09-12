set(CMAKE_C_STANDARD 11)
add_executable(noblock_server common.c server.c)
add_executable(noblock_client common.c client.c)
