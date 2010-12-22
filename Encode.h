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
