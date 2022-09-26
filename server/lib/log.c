#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "log.h"

static char* level_2_str[]  = {
	"DEBUG",
	"INFO",
	"WARNING",
	"ERROR"
}; 

void write_log(const char* file, const char* func, int line, int level, const char* fmt, ...)
{
	va_list arg;
	char buf[1024] = {0};
	const char* pos = strrchr(file, '/');
	if (pos != NULL) {
		pos += 1;
	} else {
		pos = file;
	}
	if (level > LOG_ERROR || level < LOG_DEBUG) {
		level = LOG_ERROR;
	}
	int len = sprintf(buf, "%s:%d:%s():%s -- ", pos, line, func, level_2_str[level]);
	va_start(arg, fmt);
	vsnprintf(buf + len, 1024 - len, fmt, arg);
	va_end(arg);
	fprintf(stdout, "%s\n", buf);
}
