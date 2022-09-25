add_executable(http_server http_server.c)
target_link_libraries(http_server yolanda)

add_executable(http_server_test http_server_test.c)
target_link_libraries(http_server_test yolanda)
