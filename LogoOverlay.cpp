#include "StdAfx.h"
#include "logooverlay.h"

CLogoOverlay::CLogoOverlay(void)
{
	m_nBrandWidth = 0;
	m_nBrandHeight = 0;
}

CLogoOverlay::~CLogoOverlay(void)
{
}


void CLogoOverlay::OverlayLogo(BYTE *pstrBuffer, long nInputWidth, long nInputHeight)
{
	// I assume this is an rgb32 buffer

	if (m_nBrandHeight > nInputHeight)
		m_nBrandHeight = nInputHeight;

	if (m_nBrandWidth > nInputWidth)
		m_nBrandWidth = nInputWidth;

	int nBytesPerPixel = 3;

	// get wisdth and height in bytes
	long nInputWidthBytes = nInputWidth * nBytesPerPixel;
	long nBrandWidthBytes = m_nBrandWidth * nBytesPerPixel;

	long nInputMiddle = (nInputWidthBytes / 2) - (nBrandWidthBytes / 2);

	//long nInputMiddle = m_nInputWidth * 2;
	//nInputMiddle = nInputMiddle - ((m_nBrandWidth * nBytesPerPixel) / 2);

	long nTop = (long)((float)nInputHeight * 20.0/100.0);
	pstrBuffer += nInputMiddle;
	pstrBuffer += (nInputWidthBytes * nTop);

	BYTE* pBrand = m_pBrandBits;
	for (int i=0;i<m_nBrandHeight;i++)
	{
		memcpy(pstrBuffer, pBrand, nBrandWidthBytes);
		pstrBuffer += nInputWidthBytes;
		pBrand += nBrandWidthBytes;
	}
}

BYTE* CLogoOverlay::GetRGB24Bits(HDC hdc, int nWidth, int nHeight)
{
	// Returns a byte buffer with the bitmaps of a hdc in
	// the rgb32 format

	BYTE* pBuffer = new BYTE[nWidth*nHeight*3];
	BYTE* p = pBuffer;

	for (int i=(nHeight-1);i>=0;i--) // each line
	{
		// each pixel in the line
		for (int k=0;k<nWidth;k++)
		{
			COLORREF rcPixel = GetPixel(hdc, k, i);

			// 1 pixel = 3 bytes = 24 bits = RGB
			pBuffer[0] = GetRValue(rcPixel);
			pBuffer[1] = GetBValue(rcPixel);
			pBuffer[2] = GetGValue(rcPixel);
			pBuffer += 3;
		}
	}

	return p;
}

HRESULT CLogoOverlay::CreateLogo()
{
	HDC hDC = ::GetDC(::GetDesktopWindow());
	HDC hMemDC = ::CreateCompatibleDC(hDC);
	
	if (hDC == NULL || hMemDC == NULL)
		return E_POINTER;

	m_nBrandWidth = 100;
	m_nBrandHeight = 26;

	long nWidth = m_nBrandWidth;
	long nHeight = m_nBrandHeight;

	HBITMAP hbmBrand = ::CreateCompatibleBitmap(hDC, nWidth, nHeight);
	if (hbmBrand == NULL)
		return E_POINTER;

	::ReleaseDC(::GetDesktopWindow(), hDC);

	HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hMemDC, hbmBrand);
	
	HFONT dcFont = CreateFont(12,0,0,0,0,0,0,0,0,0,0,0,0, _T("Arial")); 
	SelectObject(hMemDC, dcFont);
	
	SetBkColor(hMemDC, RGB(45, 45, 45));
	SetBkMode(hMemDC, TRANSPARENT);

	SelectObject(hMemDC, (HPEN)::GetStockObject(BLACK_PEN));
	SelectObject(hMemDC, (HBRUSH)::GetStockObject(WHITE_BRUSH));

	::Rectangle(hMemDC, 1, 1, nWidth - 1, nHeight - 1);

	RECT rcText;
	rcText.left = 0;
	rcText.right = nWidth;
	rcText.top = 2;
	rcText.bottom = nHeight;
	DrawText(hMemDC, _T("Standard MPEG Demo\nStandardMpeg.com"), -1, &rcText, DT_CENTER);

	BITMAPINFO info;
	memset(&info, 0, sizeof(info));
	info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);

	GetDIBits(hMemDC, hbmBrand, 0, nHeight, 
			  NULL, &info, DIB_RGB_COLORS);

	// int nSize = nWidth*nHeight*4;
	m_pBrandBits = GetRGB24Bits(hMemDC, nWidth, nHeight);

	::SelectObject(hMemDC, hOldBitmap);

	DeleteObject(dcFont);
	DeleteObject(hbmBrand);
	DeleteDC(hMemDC);
	
	return S_OK;
}


