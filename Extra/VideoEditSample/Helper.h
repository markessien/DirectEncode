//#define Trace CHelper::Trace
#include <stdio.h>

#define LOGFILE "c:\\videoedit.log"

class CHelper  
{
public:
	
	static void LogTimeStamp(BOOL bTimeStamp)
	{
//		m_bTimeStamp = bTimeStamp;
	}

	static void Trace(LPCTSTR pStr, ...)
	{
		_TCHAR szBuff[1024];

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
			if (true)
			{
				_ftprintf(pFile, TEXT("%04u/%02u/%02u %02u:%02u:%02u-%03u\t%s"), 
						  time.wYear, time.wMonth, time.wDay, time.wHour,
						  time.wMinute, time.wSecond, time.wMilliseconds, 
						  szBuff);
			}
			else
			{
				_ftprintf(pFile, TEXT("%s"), szBuff);
			}
			
			fflush(pFile);
		}
#endif

		OutputDebugString(szBuff);
	}

	static FILE* CHelper::GetLogStream() 
	{ 
		// Author: Mark A. Essien
		// Date: 12.02.2002
		// Description: Returns a pointer to log file, and opens the file if not already open

		static FILE *streamLog = NULL;

		if( streamLog != NULL || (streamLog = _tfopen( _T(LOGFILE), _T("w+") )) != NULL )
		{
			return streamLog;
		}

		return NULL;
	}
};
