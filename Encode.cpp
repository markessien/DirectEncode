// Encode.cpp: Implementierung der Klasse CEncode.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Encode.h"
#define EPSILON 0.01   // Define your own tolerance
#define FLOAT_EQ(x,v) (((v - EPSILON) < x) && (x <( v + EPSILON)))


//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CEncode::CEncode() : m_pBuffer(NULL), m_pEncodeProfile(NULL)
{
#ifdef _DEBUG
	m_bDisplayErrors = true;
#else
	m_bDisplayErrors = false;
#endif

	m_bWritingAudio = false;
	m_bWritingVideo = false;

	memset(&m_SourceSettings, 0, sizeof(SourceInfo));
}

CEncode::~CEncode()
{
	_ASSERT(m_pBuffer == NULL);
}

HRESULT CEncode::SetInputFormats(WAVEFORMATEX *pwfex, BITMAPINFOHEADER *pbminfo)
{
	if (pbminfo)
	{
		m_SourceSettings.bHasVideo = true;
		m_SourceSettings.nSourceHeight = pbminfo->biHeight;
		m_SourceSettings.nSourceWidth = pbminfo->biWidth;
	}
	else
	{
		m_SourceSettings.nSourceHeight = 0;
		m_SourceSettings.nSourceWidth = 0;
	}

	if (pwfex)
	{
		m_SourceSettings.bHasAudio = true;
		memcpy(&m_SourceSettings.wfexSrc, pwfex, sizeof(WAVEFORMATEX));
	}

	return S_OK;
}

HRESULT CEncode::EncodeVideoSample(IMediaSample *pSample)
{
	return E_NOTIMPL;
}

HRESULT CEncode::EncodeAudioSample(IMediaSample *pSample)
{
	return E_NOTIMPL;
}

HRESULT CEncode::StopConversion()
{
	return E_NOTIMPL;
}

DWORD CEncode::GetFileLength(TCHAR* pstrPath)
{
	HANDLE hFile = ::CreateFile(pstrPath, GENERIC_READ,
								FILE_SHARE_READ|FILE_SHARE_WRITE,
								0, 
								OPEN_EXISTING,
								0,
								0);

	if (hFile == INVALID_HANDLE_VALUE)
		return 0;

	DWORD dwSize = ::GetFileSize(hFile, 0);
	CloseHandle(hFile);
	return dwSize;
}

void CEncode::SetEncodeProfile(CMPEGProfile* pEncodeProfile)
{
	m_pEncodeProfile = pEncodeProfile;
}

void CEncode::SetOutputFile(wchar_t *pstrOutputFile)
{
	wcscpy_s(m_szOutputFile, 1024, pstrOutputFile);
}

void CEncode::Error(TCHAR *pstrMsg)
{
	if (m_bDisplayErrors)
		MessageBox(NULL, pstrMsg, _T("Error!"), 0);
	else
		Trace(_T("ERROR! %s\n"), pstrMsg);
}


HRESULT CEncode::Flip(BYTE *pBuffer, long nActualLength)
{
	// get the pixel length. 3 bytes for 24 bits
	int nPixelLen = 3;

	// get the pointer. This points at the top of the buffer,
	// which is actually the bottom of the image
	BYTE* pTop = pBuffer;
//	pSample->GetPointer(&pTop);
	
	// make sure it is a sync point. This should not assert

	if (m_pBuffer == NULL)
		return E_FAIL;

	long nSourceHeight = m_SourceSettings.nSourceHeight;
	long nSourceWidth = m_SourceSettings.nSourceWidth;

	// get the width in bytes. Each pixel is 3 bytes, so if it
	// has 10 pixels, then it has 30 bytes.
	long nWidthBytes = nSourceWidth * nPixelLen;

	// get the length of the entire buffer in bytes
	// long nLenBytes = nActualLength; //pSample->GetActualDataLength();
	
	long nLenBytes = nWidthBytes * nSourceHeight; 

	/*
	if (nLenBytes != nWidthBytes * nSourceHeight)
	{
		// this is strange, but this actually happens. We
		// stop encoding video if this happens
		_ASSERT(FALSE);
		return E_FAIL;
	}

	// make sure it is the same as what we think it is
	ASSERT(nLenBytes == nWidthBytes * nSourceHeight);
*/

	// make sure it is not 0, and not negative
	ASSERT(nSourceHeight > 0);

	// get the middle of the picture. Example, 200 pixels
	// will give us 100pixels as the middle
//	long nMiddle = m_nHeight/2;

	// make sure it was positive
//	ASSERT(nMiddle);

	// walk from 0 to the middle
	for (int i=0;i<(nSourceHeight);i++)
	{
		// get the byte offset of the current buffer.
		// if nPosBytes is addressed after this operation
		// it will point at the first address of the current
		// line. We are working from the bottom of the image
		// to the top, but working the buffer downwards
		// For example, at line 5, we are at byte offset
		// 5 * (480  * 3)
		long nPosTopBytes = i * nWidthBytes;
		long nPosBotBytes = (nLenBytes - nPosTopBytes) - nWidthBytes;

		// We get the equivalent line from the BOTTOM.
		// If for example, we are at line 5 (i=5), then
		// pBottom should be equal to (height - 5). The buffer
		// will point at the first pixel of the line

		memcpy(&m_pBuffer[nPosBotBytes], &pTop[nPosTopBytes], nWidthBytes);
		
		// copy line from the bottom to the top
		memcpy(&m_pBuffer[nPosTopBytes], &pTop[nPosBotBytes], nWidthBytes);

		// copy the former top from the temporary buffer
		// to the bottom
		//memcpy(&m_pBuffer[nPosBotBytes], &pTop[nPosBytes], nWidthBytes);

		//m_pBuffer += 
	}

	return S_OK;
}