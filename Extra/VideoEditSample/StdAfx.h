// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__E15B8541_AED6_4E21_9424_EB7FD82BA0D1__INCLUDED_)
#define AFX_STDAFX_H__E15B8541_AED6_4E21_9424_EB7FD82BA0D1__INCLUDED_

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

// dshow includes. Install the Platform SDK and add the "Include" directory
#include <qedit.h>
#include <streams.h>

#import "msxml.dll" named_guids raw_interfaces_only

// Include the path of this file (DirectEncode.tlb) into your development enviroment include
// list. This file comes with the DirectEncode SDK, and will be in a location similar to
// C:\Program Files\Essien DirectEncode\MPEGFilter
#import "DirectEncode.tlb" no_namespace, raw_interfaces_only exclude("UINT_PTR") 



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_STDAFX_H__E15B8541_AED6_4E21_9424_EB7FD82BA0D1__INCLUDED)
