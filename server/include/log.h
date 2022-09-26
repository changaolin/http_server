#ifndef LOG_H
#define LOG_H
enum log_level {
	LOG_DEBUG,
	LOG_INFO,
	LOG_WARNING,
	LOG_ERROR
};
void write_log(const char* file, const char* func, int line, int level, const char* fmt, ...);
#define DEBUG_LOG(fmt, ...) write_log(__FILE__, __func__, __LINE__, LOG_DEBUG, fmt, ##__VA_ARGS__)
#define INFO_LOG(fmt, ...) write_log(__FILE__, __func__, __LINE__, LOG_INFO, fmt, ##__VA_ARGS__)
#define WARNING_LOG(fmt, ...) write_log(__FILE__, __func__, __LINE__, LOG_WARNING,  fmt, ##__VA_ARGS__)
#define ERROR_LOG(fmt, ...) write_log(__FILE__, __func__, __LINE__, LOG_ERROR, fmt, ##__VA_ARGS__)
#endif // LOG_H
