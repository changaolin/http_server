#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "log.h"
/*
格式: 
\033[ 开头
属性码 ; 分号分割
m 结尾
\033[41;33mhelloworld\033[0m
属性码
0:重置所有属性，1高亮/加粗 2 暗淡 4 下划线 5 闪烁 7 反转 8 隐藏
40 ~ 47 背景颜色， 30 ～ 37 字颜色
nA 光标上移n行
nB 光标下移n行
nC 光标右移n行
nD 光标左移n行

30｜40 黑色
31｜41 红色
32｜42 绿色
33｜43 黄色
34｜44 蓝色
35｜45 紫色
36｜46 深绿
37｜47 白色
*/
#define ERROR_COLOR "\033[31;5m"
#define WARNING_COLOR "\033[33;5m"
#define INFO_COLOR "\033[30;47m"
#define DEBUG_COLOR "\033[32m"
#define COLOR_CLEAR "\033[m"
static char* level_2_str[]  = {
	DEBUG_COLOR"DEBUG"COLOR_CLEAR,
	INFO_COLOR"INFO"COLOR_CLEAR,
	WARNING_COLOR"WARNING"COLOR_CLEAR,
	ERROR_COLOR"ERROR"COLOR_CLEAR
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
