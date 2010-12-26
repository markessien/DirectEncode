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

#include "StdAfx.h"
#include "logooverlay.h"

CLogoOverlay::CLogoOverlay(void)
{
	m_nBrandWidth = 0;
	m_nBrandHeight = 0;
	m_pBrandBits = NULL;
}

CLogoOverlay::~CLogoOverlay(void)
{
	if (m_pBrandBits)
		delete [] m_pBrandBits;
	m_pBrandBits = NULL;
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
	
	HFONT dcFont = CreateFont(12,0,0,0,0,0,0,0,0,0,0,0,0, "Arial"); 
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
	DrawText(hMemDC, "Standard MPEG Demo\nwww.standardmpeg.com", -1, &rcText, DT_CENTER);

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


