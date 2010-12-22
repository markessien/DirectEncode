// ErdBitmap.cpp: implementation of the CStillBitmap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StillBitmap.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CStillBitmap::CStillBitmap() : m_hBitmap(0), m_pBuffer(NULL), m_nLength(0)
{
}

CStillBitmap::~CStillBitmap()
{
	delete [] m_pBuffer;
}

BYTE* CStillBitmap::GetRGB24Bits(HDC hdc, int nWidth, int nHeight)
{
	// Returns a byte buffer with the bitmaps of a hdc in
	// the rgb32 format. This function is VERY slow!

	BYTE* pBuffer = new BYTE[nWidth*nHeight*3];
	BYTE* p = pBuffer;

	for (int i=(nHeight-1);i>=0;i--) // each line
	{
		// each pixel in the line
		for (int k=0;k<nWidth;k++)
		{
			COLORREF rcPixel = GetPixel(hdc, k, i);

			// 1 pixel = 3 bytes = 24 bits = RGB
			pBuffer[0] = GetBValue(rcPixel);
			pBuffer[1] = GetGValue(rcPixel);
			pBuffer[2] = GetRValue(rcPixel);
			pBuffer += 3;
		}
	}

	return p;
}

HRESULT CStillBitmap::Load(BSTR strPath, int nWidth, int nHeight)
{
	// get the desktop dc
	HDC hdc = ::GetDC(NULL);

	// create out own dc
	HDC hMemDC = CreateCompatibleDC(hdc);
	
	// try to load the picture
	CComPtr<IPicture> pPicture;
	HRESULT hr = ::OleLoadPicturePath(strPath, NULL, 0, 0, IID_IPicture, (void**)&pPicture);
	if (SUCCEEDED(hr))
	{
		// if it succeeds, create an empty bitmap for it
		m_hBitmap = ::CreateCompatibleBitmap(hdc, nWidth, nHeight);

		// select the bitmap into the mem dc for drawing
		HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hMemDC, m_hBitmap);

		// draw the loaded image on the bitmap, stretching it if neccesary
		OLE_XSIZE_HIMETRIC cy;
		OLE_XSIZE_HIMETRIC cx;
		pPicture->get_Height(&cy);
		pPicture->get_Width(&cx);
		pPicture->Render(hMemDC, 0, nHeight, nWidth, -nHeight, 0, 0, cx, cy, NULL);
		pPicture = NULL;

		m_pBuffer = GetRGB24Bits(hMemDC, nWidth, nHeight);
		m_nLength = nWidth * nHeight * 3;

		::SelectObject(hMemDC, hOldBitmap);
	}

	return hr;
}

BYTE* CStillBitmap::GetBuffer()
{
	return m_pBuffer;
}

long CStillBitmap::GetBufferLength()
{
	return m_nLength;
}
