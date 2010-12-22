// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__5A80F56C_1516_4464_B8CD_97A228B78E3C__INCLUDED_)
#define AFX_STDAFX_H__5A80F56C_1516_4464_B8CD_97A228B78E3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

// Include the path of this file (DirectEncode.tlb) into your development enviroment include
// list. This file comes with the DirectEncode SDK, and will be in a location similar to
// C:\Program Files\Standard Mpeg Encoder\Include
// All Automatically Exluding warnings are perfectly normal
#pragma warning(disable : 4192)
#import "DirectEncode.tlb" no_namespace, raw_interfaces_only exclude("UINT_PTR") 


#include <stdio.h>
#include <windows.h>

// For CComPtr
#include <atlbase.h>

// dshow includes
#include <qedit.h>
#include <streams.h>


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__5A80F56C_1516_4464_B8CD_97A228B78E3C__INCLUDED_)
