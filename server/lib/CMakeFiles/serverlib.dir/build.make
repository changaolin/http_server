# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cal/code/socket_p/server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cal/code/socket_p/server

# Include any dependencies generated for this target.
include lib/CMakeFiles/serverlib.dir/depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/serverlib.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/serverlib.dir/flags.make

lib/CMakeFiles/serverlib.dir/acceptor.c.o: lib/CMakeFiles/serverlib.dir/flags.make
lib/CMakeFiles/serverlib.dir/acceptor.c.o: lib/acceptor.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cal/code/socket_p/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object lib/CMakeFiles/serverlib.dir/acceptor.c.o"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/serverlib.dir/acceptor.c.o   -c /home/cal/code/socket_p/server/lib/acceptor.c

lib/CMakeFiles/serverlib.dir/acceptor.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/serverlib.dir/acceptor.c.i"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cal/code/socket_p/server/lib/acceptor.c > CMakeFiles/serverlib.dir/acceptor.c.i

lib/CMakeFiles/serverlib.dir/acceptor.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/serverlib.dir/acceptor.c.s"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cal/code/socket_p/server/lib/acceptor.c -o CMakeFiles/serverlib.dir/acceptor.c.s

lib/CMakeFiles/serverlib.dir/buffer.c.o: lib/CMakeFiles/serverlib.dir/flags.make
lib/CMakeFiles/serverlib.dir/buffer.c.o: lib/buffer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cal/code/socket_p/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object lib/CMakeFiles/serverlib.dir/buffer.c.o"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/serverlib.dir/buffer.c.o   -c /home/cal/code/socket_p/server/lib/buffer.c

lib/CMakeFiles/serverlib.dir/buffer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/serverlib.dir/buffer.c.i"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cal/code/socket_p/server/lib/buffer.c > CMakeFiles/serverlib.dir/buffer.c.i

lib/CMakeFiles/serverlib.dir/buffer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/serverlib.dir/buffer.c.s"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cal/code/socket_p/server/lib/buffer.c -o CMakeFiles/serverlib.dir/buffer.c.s

lib/CMakeFiles/serverlib.dir/channel.c.o: lib/CMakeFiles/serverlib.dir/flags.make
lib/CMakeFiles/serverlib.dir/channel.c.o: lib/channel.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cal/code/socket_p/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object lib/CMakeFiles/serverlib.dir/channel.c.o"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/serverlib.dir/channel.c.o   -c /home/cal/code/socket_p/server/lib/channel.c

lib/CMakeFiles/serverlib.dir/channel.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/serverlib.dir/channel.c.i"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cal/code/socket_p/server/lib/channel.c > CMakeFiles/serverlib.dir/channel.c.i

lib/CMakeFiles/serverlib.dir/channel.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/serverlib.dir/channel.c.s"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cal/code/socket_p/server/lib/channel.c -o CMakeFiles/serverlib.dir/channel.c.s

lib/CMakeFiles/serverlib.dir/channel_map.c.o: lib/CMakeFiles/serverlib.dir/flags.make
lib/CMakeFiles/serverlib.dir/channel_map.c.o: lib/channel_map.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cal/code/socket_p/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object lib/CMakeFiles/serverlib.dir/channel_map.c.o"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/serverlib.dir/channel_map.c.o   -c /home/cal/code/socket_p/server/lib/channel_map.c

lib/CMakeFiles/serverlib.dir/channel_map.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/serverlib.dir/channel_map.c.i"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cal/code/socket_p/server/lib/channel_map.c > CMakeFiles/serverlib.dir/channel_map.c.i

lib/CMakeFiles/serverlib.dir/channel_map.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/serverlib.dir/channel_map.c.s"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cal/code/socket_p/server/lib/channel_map.c -o CMakeFiles/serverlib.dir/channel_map.c.s

lib/CMakeFiles/serverlib.dir/event_loop.c.o: lib/CMakeFiles/serverlib.dir/flags.make
lib/CMakeFiles/serverlib.dir/event_loop.c.o: lib/event_loop.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cal/code/socket_p/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object lib/CMakeFiles/serverlib.dir/event_loop.c.o"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/serverlib.dir/event_loop.c.o   -c /home/cal/code/socket_p/server/lib/event_loop.c

lib/CMakeFiles/serverlib.dir/event_loop.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/serverlib.dir/event_loop.c.i"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cal/code/socket_p/server/lib/event_loop.c > CMakeFiles/serverlib.dir/event_loop.c.i

lib/CMakeFiles/serverlib.dir/event_loop.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/serverlib.dir/event_loop.c.s"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cal/code/socket_p/server/lib/event_loop.c -o CMakeFiles/serverlib.dir/event_loop.c.s

lib/CMakeFiles/serverlib.dir/event_loop_thread.c.o: lib/CMakeFiles/serverlib.dir/flags.make
lib/CMakeFiles/serverlib.dir/event_loop_thread.c.o: lib/event_loop_thread.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cal/code/socket_p/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object lib/CMakeFiles/serverlib.dir/event_loop_thread.c.o"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/serverlib.dir/event_loop_thread.c.o   -c /home/cal/code/socket_p/server/lib/event_loop_thread.c

lib/CMakeFiles/serverlib.dir/event_loop_thread.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/serverlib.dir/event_loop_thread.c.i"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cal/code/socket_p/server/lib/event_loop_thread.c > CMakeFiles/serverlib.dir/event_loop_thread.c.i

lib/CMakeFiles/serverlib.dir/event_loop_thread.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/serverlib.dir/event_loop_thread.c.s"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cal/code/socket_p/server/lib/event_loop_thread.c -o CMakeFiles/serverlib.dir/event_loop_thread.c.s

lib/CMakeFiles/serverlib.dir/http_request.c.o: lib/CMakeFiles/serverlib.dir/flags.make
lib/CMakeFiles/serverlib.dir/http_request.c.o: lib/http_request.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cal/code/socket_p/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object lib/CMakeFiles/serverlib.dir/http_request.c.o"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/serverlib.dir/http_request.c.o   -c /home/cal/code/socket_p/server/lib/http_request.c

lib/CMakeFiles/serverlib.dir/http_request.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/serverlib.dir/http_request.c.i"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cal/code/socket_p/server/lib/http_request.c > CMakeFiles/serverlib.dir/http_request.c.i

lib/CMakeFiles/serverlib.dir/http_request.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/serverlib.dir/http_request.c.s"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cal/code/socket_p/server/lib/http_request.c -o CMakeFiles/serverlib.dir/http_request.c.s

lib/CMakeFiles/serverlib.dir/http_response.c.o: lib/CMakeFiles/serverlib.dir/flags.make
lib/CMakeFiles/serverlib.dir/http_response.c.o: lib/http_response.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cal/code/socket_p/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object lib/CMakeFiles/serverlib.dir/http_response.c.o"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/serverlib.dir/http_response.c.o   -c /home/cal/code/socket_p/server/lib/http_response.c

lib/CMakeFiles/serverlib.dir/http_response.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/serverlib.dir/http_response.c.i"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cal/code/socket_p/server/lib/http_response.c > CMakeFiles/serverlib.dir/http_response.c.i

lib/CMakeFiles/serverlib.dir/http_response.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/serverlib.dir/http_response.c.s"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cal/code/socket_p/server/lib/http_response.c -o CMakeFiles/serverlib.dir/http_response.c.s

lib/CMakeFiles/serverlib.dir/http_server.c.o: lib/CMakeFiles/serverlib.dir/flags.make
lib/CMakeFiles/serverlib.dir/http_server.c.o: lib/http_server.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cal/code/socket_p/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object lib/CMakeFiles/serverlib.dir/http_server.c.o"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/serverlib.dir/http_server.c.o   -c /home/cal/code/socket_p/server/lib/http_server.c

lib/CMakeFiles/serverlib.dir/http_server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/serverlib.dir/http_server.c.i"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cal/code/socket_p/server/lib/http_server.c > CMakeFiles/serverlib.dir/http_server.c.i

lib/CMakeFiles/serverlib.dir/http_server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/serverlib.dir/http_server.c.s"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cal/code/socket_p/server/lib/http_server.c -o CMakeFiles/serverlib.dir/http_server.c.s

lib/CMakeFiles/serverlib.dir/log.c.o: lib/CMakeFiles/serverlib.dir/flags.make
lib/CMakeFiles/serverlib.dir/log.c.o: lib/log.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cal/code/socket_p/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object lib/CMakeFiles/serverlib.dir/log.c.o"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/serverlib.dir/log.c.o   -c /home/cal/code/socket_p/server/lib/log.c

lib/CMakeFiles/serverlib.dir/log.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/serverlib.dir/log.c.i"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cal/code/socket_p/server/lib/log.c > CMakeFiles/serverlib.dir/log.c.i

lib/CMakeFiles/serverlib.dir/log.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/serverlib.dir/log.c.s"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cal/code/socket_p/server/lib/log.c -o CMakeFiles/serverlib.dir/log.c.s

lib/CMakeFiles/serverlib.dir/poll_dispatcher.c.o: lib/CMakeFiles/serverlib.dir/flags.make
lib/CMakeFiles/serverlib.dir/poll_dispatcher.c.o: lib/poll_dispatcher.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cal/code/socket_p/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object lib/CMakeFiles/serverlib.dir/poll_dispatcher.c.o"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/serverlib.dir/poll_dispatcher.c.o   -c /home/cal/code/socket_p/server/lib/poll_dispatcher.c

lib/CMakeFiles/serverlib.dir/poll_dispatcher.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/serverlib.dir/poll_dispatcher.c.i"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cal/code/socket_p/server/lib/poll_dispatcher.c > CMakeFiles/serverlib.dir/poll_dispatcher.c.i

lib/CMakeFiles/serverlib.dir/poll_dispatcher.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/serverlib.dir/poll_dispatcher.c.s"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cal/code/socket_p/server/lib/poll_dispatcher.c -o CMakeFiles/serverlib.dir/poll_dispatcher.c.s

lib/CMakeFiles/serverlib.dir/sock.c.o: lib/CMakeFiles/serverlib.dir/flags.make
lib/CMakeFiles/serverlib.dir/sock.c.o: lib/sock.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cal/code/socket_p/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object lib/CMakeFiles/serverlib.dir/sock.c.o"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/serverlib.dir/sock.c.o   -c /home/cal/code/socket_p/server/lib/sock.c

lib/CMakeFiles/serverlib.dir/sock.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/serverlib.dir/sock.c.i"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cal/code/socket_p/server/lib/sock.c > CMakeFiles/serverlib.dir/sock.c.i

lib/CMakeFiles/serverlib.dir/sock.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/serverlib.dir/sock.c.s"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cal/code/socket_p/server/lib/sock.c -o CMakeFiles/serverlib.dir/sock.c.s

lib/CMakeFiles/serverlib.dir/tcp_connection.c.o: lib/CMakeFiles/serverlib.dir/flags.make
lib/CMakeFiles/serverlib.dir/tcp_connection.c.o: lib/tcp_connection.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cal/code/socket_p/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object lib/CMakeFiles/serverlib.dir/tcp_connection.c.o"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/serverlib.dir/tcp_connection.c.o   -c /home/cal/code/socket_p/server/lib/tcp_connection.c

lib/CMakeFiles/serverlib.dir/tcp_connection.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/serverlib.dir/tcp_connection.c.i"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cal/code/socket_p/server/lib/tcp_connection.c > CMakeFiles/serverlib.dir/tcp_connection.c.i

lib/CMakeFiles/serverlib.dir/tcp_connection.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/serverlib.dir/tcp_connection.c.s"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cal/code/socket_p/server/lib/tcp_connection.c -o CMakeFiles/serverlib.dir/tcp_connection.c.s

lib/CMakeFiles/serverlib.dir/tcp_server.c.o: lib/CMakeFiles/serverlib.dir/flags.make
lib/CMakeFiles/serverlib.dir/tcp_server.c.o: lib/tcp_server.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cal/code/socket_p/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building C object lib/CMakeFiles/serverlib.dir/tcp_server.c.o"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/serverlib.dir/tcp_server.c.o   -c /home/cal/code/socket_p/server/lib/tcp_server.c

lib/CMakeFiles/serverlib.dir/tcp_server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/serverlib.dir/tcp_server.c.i"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cal/code/socket_p/server/lib/tcp_server.c > CMakeFiles/serverlib.dir/tcp_server.c.i

lib/CMakeFiles/serverlib.dir/tcp_server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/serverlib.dir/tcp_server.c.s"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cal/code/socket_p/server/lib/tcp_server.c -o CMakeFiles/serverlib.dir/tcp_server.c.s

lib/CMakeFiles/serverlib.dir/thread_pool.c.o: lib/CMakeFiles/serverlib.dir/flags.make
lib/CMakeFiles/serverlib.dir/thread_pool.c.o: lib/thread_pool.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cal/code/socket_p/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building C object lib/CMakeFiles/serverlib.dir/thread_pool.c.o"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/serverlib.dir/thread_pool.c.o   -c /home/cal/code/socket_p/server/lib/thread_pool.c

lib/CMakeFiles/serverlib.dir/thread_pool.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/serverlib.dir/thread_pool.c.i"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cal/code/socket_p/server/lib/thread_pool.c > CMakeFiles/serverlib.dir/thread_pool.c.i

lib/CMakeFiles/serverlib.dir/thread_pool.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/serverlib.dir/thread_pool.c.s"
	cd /home/cal/code/socket_p/server/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cal/code/socket_p/server/lib/thread_pool.c -o CMakeFiles/serverlib.dir/thread_pool.c.s

# Object files for target serverlib
serverlib_OBJECTS = \
"CMakeFiles/serverlib.dir/acceptor.c.o" \
"CMakeFiles/serverlib.dir/buffer.c.o" \
"CMakeFiles/serverlib.dir/channel.c.o" \
"CMakeFiles/serverlib.dir/channel_map.c.o" \
"CMakeFiles/serverlib.dir/event_loop.c.o" \
"CMakeFiles/serverlib.dir/event_loop_thread.c.o" \
"CMakeFiles/serverlib.dir/http_request.c.o" \
"CMakeFiles/serverlib.dir/http_response.c.o" \
"CMakeFiles/serverlib.dir/http_server.c.o" \
"CMakeFiles/serverlib.dir/log.c.o" \
"CMakeFiles/serverlib.dir/poll_dispatcher.c.o" \
"CMakeFiles/serverlib.dir/sock.c.o" \
"CMakeFiles/serverlib.dir/tcp_connection.c.o" \
"CMakeFiles/serverlib.dir/tcp_server.c.o" \
"CMakeFiles/serverlib.dir/thread_pool.c.o"

# External object files for target serverlib
serverlib_EXTERNAL_OBJECTS =

lib/libserverlib.a: lib/CMakeFiles/serverlib.dir/acceptor.c.o
lib/libserverlib.a: lib/CMakeFiles/serverlib.dir/buffer.c.o
lib/libserverlib.a: lib/CMakeFiles/serverlib.dir/channel.c.o
lib/libserverlib.a: lib/CMakeFiles/serverlib.dir/channel_map.c.o
lib/libserverlib.a: lib/CMakeFiles/serverlib.dir/event_loop.c.o
lib/libserverlib.a: lib/CMakeFiles/serverlib.dir/event_loop_thread.c.o
lib/libserverlib.a: lib/CMakeFiles/serverlib.dir/http_request.c.o
lib/libserverlib.a: lib/CMakeFiles/serverlib.dir/http_response.c.o
lib/libserverlib.a: lib/CMakeFiles/serverlib.dir/http_server.c.o
lib/libserverlib.a: lib/CMakeFiles/serverlib.dir/log.c.o
lib/libserverlib.a: lib/CMakeFiles/serverlib.dir/poll_dispatcher.c.o
lib/libserverlib.a: lib/CMakeFiles/serverlib.dir/sock.c.o
lib/libserverlib.a: lib/CMakeFiles/serverlib.dir/tcp_connection.c.o
lib/libserverlib.a: lib/CMakeFiles/serverlib.dir/tcp_server.c.o
lib/libserverlib.a: lib/CMakeFiles/serverlib.dir/thread_pool.c.o
lib/libserverlib.a: lib/CMakeFiles/serverlib.dir/build.make
lib/libserverlib.a: lib/CMakeFiles/serverlib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cal/code/socket_p/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Linking C static library libserverlib.a"
	cd /home/cal/code/socket_p/server/lib && $(CMAKE_COMMAND) -P CMakeFiles/serverlib.dir/cmake_clean_target.cmake
	cd /home/cal/code/socket_p/server/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/serverlib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/CMakeFiles/serverlib.dir/build: lib/libserverlib.a

.PHONY : lib/CMakeFiles/serverlib.dir/build

lib/CMakeFiles/serverlib.dir/clean:
	cd /home/cal/code/socket_p/server/lib && $(CMAKE_COMMAND) -P CMakeFiles/serverlib.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/serverlib.dir/clean

lib/CMakeFiles/serverlib.dir/depend:
	cd /home/cal/code/socket_p/server && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cal/code/socket_p/server /home/cal/code/socket_p/server/lib /home/cal/code/socket_p/server /home/cal/code/socket_p/server/lib /home/cal/code/socket_p/server/lib/CMakeFiles/serverlib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/CMakeFiles/serverlib.dir/depend

