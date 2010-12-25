#pragma once

#include "stdafx.h"
#include <stdarg.h>

#define LOGSTRING_MAX_LENGTH 1024

enum LogStringLevel
{
	LOGSTRING_ALL   = 0,
	LOGSTRING_TRACE = 1,
	LOGSTRING_DEBUG = 2,
	LOGSTRING_INFO  = 3,
	LOGSTRING_WARN  = 4,
	LOGSTRING_ERROR = 5,
	LOGSTRING_FATAL = 6,
	LOGSTRING_OFF   = 7,
};

#ifdef _DEBUG

void _LogStringLevel(int level);
void _LogString(const TCHAR* function, LogStringLevel level, const TCHAR* fmt, ...);

#define LogStringLevel(level) _LogStringLevel(level)
#define LogString(level, fmt, ...) _LogString(_T(__FUNCTION__), LOGSTRING_ ## level, fmt, __VA_ARGS__)

#else

#define LogStringLevel(level) 
#define LogString(level, fmt, ...) 

#endif