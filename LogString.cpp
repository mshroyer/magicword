// LogString.cpp
//
// A simple debug string logging facility, utilizing the Windows
// OutputDebugString() function, with zero footprint on non-debug builds of
// the application.

#include "stdafx.h"
#include "LogString.h"

#ifdef _DEBUG

int _logStringCurrentLevel = LOGSTRING_ALL;

const TCHAR* logStringLevelName(LogStringLevel level)
{
	switch ( level ) {
	case LOGSTRING_ALL:
		return _T("ALL");
	case LOGSTRING_TRACE:
		return _T("TRACE");
	case LOGSTRING_DEBUG:
		return _T("DEBUG");
	case LOGSTRING_INFO:
		return _T("INFO");
	case LOGSTRING_WARN:
		return _T("WARN");
	case LOGSTRING_ERROR:
		return _T("ERROR");
	case LOGSTRING_FATAL:
		return _T("FATAL");
	case LOGSTRING_OFF:
		return _T("OFF");
	default:
		return NULL;
	}
}

void _LogStringLevel(LogStringLevel level)
{
	_logStringCurrentLevel = level;
}

void _LogString(const TCHAR* function, LogStringLevel level, const TCHAR* fmt, ...)
{
	va_list vl;
	TCHAR* output = new TCHAR[LOGSTRING_MAX_LENGTH];
	TCHAR* message = new TCHAR[LOGSTRING_MAX_LENGTH];

	if ( level < _logStringCurrentLevel ) return;
	
	va_start(vl, fmt);

	StringCbVPrintf(message,
		LOGSTRING_MAX_LENGTH * sizeof(TCHAR),
		fmt,
		vl);

	// TODO: If message is greater than a certain length, this call will return
	// STRSAFE_E_INSUFFICIENT_BUFFER and the output string won't have a newline
	// at the end, resulting in possible formatting problems when displaying
	// the debug strings. This is not a security issue as StringCbPrintf will
	// prevent a buffer overflow.
	StringCbPrintf(output,
		LOGSTRING_MAX_LENGTH * sizeof(TCHAR),
		_T("[%5s] %s - %s\n"),
		logStringLevelName(level),
		function,
		message);

	OutputDebugString(output);

	va_end(vl);

	delete output;
	delete message;
}

#endif