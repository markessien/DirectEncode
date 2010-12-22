// stdafx.cpp : source file that includes just the standard includes
// fflib.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

#if defined(DEBUG)
void Trace(LPCTSTR pStr, ...)
{
	char szBuff[1024];

	va_list va;
	va_start(va, pStr);
	wvsprintf (szBuff, pStr, va);
	va_end(va);
	
#if 0 // change to 0, not to log to a file
    SYSTEMTIME time;
	GetLocalTime(&time); 

	FILE* pFile = GetLogStream();
	if (pFile)
	{
		_ftprintf(pFile, TEXT("%04u/%02u/%02u %02u:%02u:%02u-%03u\t%s\n"), 
				  time.wYear, time.wMonth, time.wDay, time.wHour,
				  time.wMinute, time.wSecond, time.wMilliseconds, 
				  szBuff);
		
		fflush(pFile);
	}
#endif

	OutputDebugString(szBuff);
}
#endif

char* WideCharToChar(wchar_t* pstr)
{
	int n = wcslen(pstr) + 1;
	char *ansistr = new char[n];
	::WideCharToMultiByte(CP_ACP, 
							0, 
							pstr, 
							-1, 
							ansistr, 
							n, 
							NULL, 
							NULL);

	return ansistr;
}