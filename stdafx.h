#pragma once

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include <streams.h>
#include <atlbase.h>
//#include <stdlib.h>
#include <dvdmedia.h>
//#include <ios>


#define _ATL_APARTMENT_THREADED

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>

// #include <atlcom.h>
//#include <stdio.h>
//#include <string>
#undef lstrcpyW

#ifndef __DirectEncode_h_h__
#include "DirectEncode_h.h"
#endif

#define VARFUNCS
// #define DECLARE_OUTPUT_FORMAT
#define DECLARE_FUNC_VARIABLES

#include "libraries\erdmpglib\erdmpglib.h"

// #define wcscpy_s(pszTarget, len, pszSource) wcscpy(pszTarget, pszSource)

/*
#define VS6
*/


#if defined(VS6)
#define wcscat_s(pszTarget, len, pszSource) wcscat(pszTarget, pszSource)
#define strcpy_s(pszTarget, len, pszSource) strcpy(pszTarget, pszSource)
#define _tcscpy_s(pszTarget, len, pszSource) _tcscpy(pszTarget, pszSource)
#define _tcscat_s(pszTarget, len, pszSource) _tcscat(pszTarget, pszSource)
#define _tcsncpy_s(pszTarget, len, pszSource, srclen) _tcsncpy(pszTarget, pszSource, srclen)
#define wcscpy_s(pszTarget, len, pszSource) wcscpy(pszTarget, pszSource)
#endif


/*
#if defined(VS6)
#include <strsafe.h>
#define wcscat_s(pszTarget, len, pszSource) StringCbCatW(pszTarget, len, pszSource)
#define strcpy_s(pszTarget, len, pszSource) StringCbCopyA(pszTarget, len, pszSource)
#define _tcscpy_s(pszTarget, len, pszSource) StringCbCopy(pszTarget, len, pszSource)
#define _tcscat_s(pszTarget, len, pszSource) StringCbCat(pszTarget, len, pszSource)
#define _tcsncpy_s(pszTarget, len, pszSource, srclen) _tcsncpy(pszTarget, pszSource, srclen)
#define sprintf_s
#define wcscpy_s(pszTarget, len, pszSource) StringCbCopyW(pszTarget, len, pszSource)
#endif
*/

/*
#ifndef _tcsncpy_s
#define _tcsncpy_s(pszTarget, len, pszSource, srclen) _tcsncpy(pszTarget, pszSource, srclen)
#undef _tcscat_s
#define _tcscat_s StringCbCat
#endif

#ifndef wcscpy_s

#else
#define wcscpy_s StringCbCopyW
#endif

#endif

// #undef strcpy
// #define strcpy_s StringCbCopy


//#undef _tcscpy_s
//#define _tcscpy_s StringCbCopy
// _tcsncpy_s(&szLoc[15], 128,&pstrLicense[12], 4);

//#undef wcscat_s
//#define wcscat_s StringCbCatW

//#undef sprintf_s
//#define sprintf_s StringCbPrintf
*/

#define EPSILON 0.01
#define FLOAT_EQ(x,v) (((v - EPSILON) < x) && (x <( v + EPSILON)))
#define SAFE_DELETE(x) if (x) delete x; x = NULL

#ifdef _DEBUG
inline void Trace(LPCTSTR pStr, ...)
{
	_TCHAR szBuff[3024];

	va_list va;
	va_start(va, pStr);
	wvsprintf(szBuff, pStr, va);
//	StringCbVPrintf(szBuff, 3024, pStr, va); // use wvsprintf with older psdk
	va_end(va);
	OutputDebugString(szBuff);
}
#else
	#define Trace 
#endif

#undef VERBOSE
#define VERBOSE

#if defined(VERBOSE)
#define TraceVerbose Trace
#else
#define TraceVerbose
#endif