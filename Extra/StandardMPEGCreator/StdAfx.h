// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__7C561AD1_60C5_4CBC_8797_AECBDB96D0CC__INCLUDED_)
#define AFX_STDAFX_H__7C561AD1_60C5_4CBC_8797_AECBDB96D0CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
#define _ATL_APARTMENT_THREADED

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
#include <atlctl.h>

// dshow includes
#include <qedit.h>
#include <streams.h>

// Add the path to these files to your development enviroment include files
// The path will look something like: "C:\Program Files\Standard MPEG Encoders\Include"

#import  <DirectEncode.tlb> no_namespace raw_interfaces_only exclude("UINT_PTR", \
							"_VideoOutputFormat", \
							"_AudioOutputFormat", \
							"_SystemsOutputFormat", \
							"_Constraint", \
							"_EncodeMode", \
							"_AspectRatio", \
							"_BitrateMode") 

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__7C561AD1_60C5_4CBC_8797_AECBDB96D0CC__INCLUDED)
