//
// Created by changaolin on 2022/9/10.
//

#include "common.h"

#define MAX_LOG_LINE_SIZE 4096

void write_log(const char *file, const char *function,
               int line, const char *fmt, ...) {
    char buf[MAX_LOG_LINE_SIZE + 1];
    char *file_name = strrchr(file, '/') + 1;
    int len = sprintf(buf, "[%s::%s:%d]", file_name, function, line);
    va_list arg;
    va_start(arg, fmt);
    len += vsnprintf(buf + len, MAX_LOG_LINE_SIZE - len, fmt, arg);
    va_end(arg);
    fprintf(stderr, "%s\n", buf);
}

int read_n(int fd, void *buffer, int buffer_size, int read_size) {
    if (buffer_size < read_size) {
        return -1;
    }
    char *read_p = (char *) buffer;
    int len = read_size;
    int result;
    while (len > 0) {
        result = read(fd, read_p, len);
        if (result == 0) break; // EOF, 收到 FIN包
        if (result < 0) {
            // 非阻塞io的情况下，没有数据可读
            if (errno == EINTR) continue;
            else return -1;
        }
        len -= result;
        read_p += result;
    }
    return read_size - len; // 返回实际读取的字符数
}