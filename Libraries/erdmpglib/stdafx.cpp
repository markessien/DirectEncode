/** This file is part of The Standard Mpeg Encoder.

The Standard Mpeg Encoder is free software: you can redistribute it 
and/or modify it under the terms of the GNU General Public License 
as published by the Free Software Foundation, either version 3 of 
the License, or (at your option) any later version.

The Standard Mpeg Encoder is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with The Standard Mpeg Encoder.  
 
If not, see <http://www.gnu.org/licenses/>.
**/

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