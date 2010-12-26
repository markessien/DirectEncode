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

// Encode.h: Schnittstelle für die Klasse CEncode.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENCODE_H__2CDE1989_78CB_4FD4_9244_0ADA74FC5DE5__INCLUDED_)
#define AFX_ENCODE_H__2CDE1989_78CB_4FD4_9244_0ADA74FC5DE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// #include "IEssienMPEGEncoder.h"
#include "profile.h"

class CMPEGProfile;

class CEncode  
{
public:
	
	typedef struct EnumSourceInfo
	{
		double dSourceFPS;
		WAVEFORMATEX wfexSrc;
		long nSourceWidth;
		long nSourceHeight;
		bool bHasVideo;
		bool bHasAudio;
		// VIDEOINFOHEADER* pVidInfoSrc;
	} SourceInfo;

	CEncode();
	virtual ~CEncode();
	
	virtual HRESULT StopConversion();
	virtual HRESULT StartConversion() = 0;
	virtual HRESULT EncodeAudioSample(IMediaSample *pSample);
	virtual HRESULT EncodeVideoSample(IMediaSample *pSample);
	virtual HRESULT SetInputFormats(WAVEFORMATEX* pwfex, BITMAPINFOHEADER *pbminfo);
	virtual void SetOutputFile(wchar_t* pstrOutputFile);
	SourceInfo& GetSourceInfo() {return m_SourceSettings; }
	void SetEncodeProfile(CMPEGProfile* pEncodeProfile);
	bool GetWritingAudio() {return m_bWritingAudio;}
	bool GetWritingVideo() {return m_bWritingVideo;}

protected:
	// HRESULT GetAVFiles(TCHAR *pstrOutputFile);
	DWORD GetFileLength(TCHAR* pstrPath);
	void Error(TCHAR* pstrMsg);
	virtual HRESULT Flip(BYTE *pBuffer, long nActualLength);
	
protected:
	bool m_bWritingAudio;
	bool m_bWritingVideo;
	SourceInfo m_SourceSettings;
	BYTE* m_pBuffer;
	bool m_bDisplayErrors;
	CMPEGProfile* m_pEncodeProfile;
	wchar_t m_szOutputFile[1024];
};

#endif // !defined(AFX_ENCODE_H__2CDE1989_78CB_4FD4_9244_0ADA74FC5DE5__INCLUDED_)
