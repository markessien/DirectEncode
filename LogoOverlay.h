#pragma once

class CLogoOverlay
{
public:
	CLogoOverlay(void);
	~CLogoOverlay(void);

	HRESULT CreateLogo();
	void OverlayLogo(BYTE *pstrBuffer, long nInputWidth, long nInputHeight);
	BYTE* GetRGB24Bits(HDC hdc, int nWidth, int nHeight);

private:
	BYTE* m_pBrandBits;
	long  m_nBrandWidth;
	long  m_nBrandHeight;
};
