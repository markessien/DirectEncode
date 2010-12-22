// AudioResample.h: Schnittstelle für die Klasse CAudioResample.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUDIORESAMPLE_H__4F8FA23E_41AC_4D20_9075_E661D6F039B7__INCLUDED_)
#define AFX_AUDIORESAMPLE_H__4F8FA23E_41AC_4D20_9075_E661D6F039B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <mmsystem.h>
#include "mmreg.h"
#include "msacm.h"

class CAudioResample  
{
public:
	CAudioResample();
	virtual ~CAudioResample();
	
	HRESULT SpecifyFormats(WAVEFORMATEX &wfxSrc, WAVEFORMATEX &wfxDst);
	HRESULT Resample(BYTE* pBuffer, long nBufferLen, BYTE** pResult, long  & nResultLen);
	void Close();

private:
	long m_nSrcBufLen;
	long m_nDstBufLen;
	BYTE* m_pbDstBuffer;
	BYTE* m_pbSrcBuffer;
	HACMSTREAM m_hAcmStream;
	WAVEFORMATEX m_wfxSrc;
	WAVEFORMATEX m_wfxDst;
	ACMSTREAMHEADER m_streamheader;
};

#endif // !defined(AFX_AUDIORESAMPLE_H__4F8FA23E_41AC_4D20_9075_E661D6F039B7__INCLUDED_)
