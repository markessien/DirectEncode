// ErdBitmap.h: interface for the CStillBitmap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ERDBITMAP_H__1142B7F4_3279_4913_8D46_ACD4420B35D5__INCLUDED_)
#define AFX_ERDBITMAP_H__1142B7F4_3279_4913_8D46_ACD4420B35D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStillBitmap  
{
public:
	long GetBufferLength();
	BYTE* GetBuffer();
	CStillBitmap();
	virtual ~CStillBitmap();

	HRESULT Load(BSTR strPath, int nWidth, int nHeight);

private:
	BYTE*   GetRGB24Bits(HDC hdc, int nWidth, int nHeight);

private:
	HBITMAP m_hBitmap;
	BYTE* m_pBuffer;
	long m_nLength;
};

#endif // !defined(AFX_ERDBITMAP_H__1142B7F4_3279_4913_8D46_ACD4420B35D5__INCLUDED_)
