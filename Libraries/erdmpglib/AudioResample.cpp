// AudioResample.cpp: Implementierung der Klasse CAudioResample.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AudioResample.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CAudioResample::CAudioResample()
{
	m_hAcmStream = NULL;
	m_pbDstBuffer = NULL;
	m_pbSrcBuffer = NULL;
}

CAudioResample::~CAudioResample()
{
	Close();
}

HRESULT CAudioResample::Resample(BYTE *pBuffer, long nBufferLen, BYTE **pResult, long &nResultLen)
{
	MMRESULT result;
	
	memcpy(m_pbSrcBuffer, pBuffer, nBufferLen);

	m_streamheader.cbSrcLength = nBufferLen;
	result = acmStreamConvert(m_hAcmStream, &m_streamheader, ACM_STREAMCONVERTF_BLOCKALIGN);
	
	if (MMSYSERR_NOERROR != result)
	{
		_ASSERT(FALSE);
		return E_FAIL;
	}

	_ASSERT((long)m_streamheader.cbSrcLengthUsed == nBufferLen);
	nResultLen = m_streamheader.cbDstLengthUsed;
	_ASSERT(nResultLen);

	*pResult = m_pbDstBuffer;

	return S_OK;
}

HRESULT CAudioResample::SpecifyFormats(WAVEFORMATEX &wfxSrc, WAVEFORMATEX &wfxDst)
{
	m_nSrcBufLen = 1024 * 1024;
	m_nDstBufLen = 1024 * 1024;
	
	_ASSERT(m_pbSrcBuffer == NULL);
	_ASSERT(m_pbDstBuffer == NULL);

	m_pbSrcBuffer = new BYTE[m_nSrcBufLen];
	m_pbDstBuffer = new BYTE[m_nDstBufLen]; // 1meg? 
	
	_ASSERT(m_pbDstBuffer);
	_ASSERT(m_pbSrcBuffer);

	m_streamheader.cbStruct = sizeof(ACMSTREAMHEADER); 
	m_streamheader.fdwStatus = 0L;
	m_streamheader.dwUser = 0L;
	m_streamheader.pbSrc = m_pbSrcBuffer;
	m_streamheader.cbSrcLength = m_nSrcBufLen;
	m_streamheader.cbSrcLengthUsed = 0;
	m_streamheader.dwSrcUser = 0;
	m_streamheader.pbDst = m_pbDstBuffer;
	m_streamheader.cbDstLength = m_nDstBufLen;
	m_streamheader.cbDstLengthUsed = 0;
	m_streamheader.dwDstUser = 0;

	// Call this function before calling the resample function
	m_wfxSrc = wfxSrc;
	m_wfxDst = wfxDst;
	
	// Open the acmstream, which is used to convert from one format to another

	MMRESULT result;
	result = acmStreamOpen(&m_hAcmStream, NULL, 
						   &m_wfxSrc, &m_wfxDst, 
						   0L, 0L, 0L, 
						   ACM_STREAMOPENF_NONREALTIME);
	
	if (MMSYSERR_NOERROR != result)
	{
		Close();
		_ASSERT(FALSE);
		return E_FAIL;
	}
	
	
	result = acmStreamPrepareHeader(m_hAcmStream, &m_streamheader, 0);
	if (MMSYSERR_NOERROR != result)
	{
		Close();
		_ASSERT(FALSE);
		return E_FAIL;
	}

	return S_OK;
}

void CAudioResample::Close()
{
	if (m_hAcmStream != NULL)
	{
		MMRESULT result;
		
		m_streamheader.cbDstLength = m_nDstBufLen;
		m_streamheader.cbSrcLength = m_nSrcBufLen;
		result = acmStreamUnprepareHeader(m_hAcmStream, &m_streamheader, 0);
		_ASSERT(result == MMSYSERR_NOERROR);
		
		result = acmStreamClose(m_hAcmStream, 0);
		_ASSERT(result == MMSYSERR_NOERROR);

		m_hAcmStream = NULL;
	}

	if (m_pbDstBuffer)
		delete [] m_pbDstBuffer;
	m_pbDstBuffer = NULL;

	if (m_pbSrcBuffer)
		delete [] m_pbSrcBuffer;
	m_pbSrcBuffer = NULL;
}
