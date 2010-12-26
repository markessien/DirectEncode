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


#include "stdafx.h"
#include "mpeginputpin.h"
#include "MPEGFilterInterface.h"
#include "mpegobj.h"

//////////////////////////////////////////////////////
// Input pin

CMPEGInputPin::CMPEGInputPin(CMPEGObj *pMPEGObj,
                             LPUNKNOWN pUnk,
                             CBaseFilter *pFilter,
                             CCritSec *pLock,
                             CCritSec *pReceiveLock,
                             MediaFormat mediaFormat,
                             LPCWSTR pszPinName,
                             HRESULT *phr) :

				CBaseInputPin(NAME("MPEGInPin"),
							 pFilter,                   // Filter
							 pLock,                     // Locking
							 phr,                       // Return code
							 pszPinName),                 // Pin name

							 m_pMPEGObj(pMPEGObj),
							 m_tLastSampleTime(0),
							 m_mediaFormat(mediaFormat),
							 m_bAtEndOfStream(FALSE),
						     m_bCompleteNotified(FALSE)
{
	m_bPaused = false;
	m_nVidInfoHeaderLevel = 1;
	m_mediaType.InitMediaType();

	if (m_mediaFormat == Audio)
    {
		m_mediaType.SetType(&MEDIATYPE_Audio);
        m_mediaType.SetSubtype(&MEDIASUBTYPE_PCM);
		m_mediaType.SetFormatType(&FORMAT_WaveFormatEx);
	}
    else if (m_mediaFormat == Video)
    {
		m_mediaType.SetType(&MEDIATYPE_Video);
        m_mediaType.SetSubtype(&MEDIASUBTYPE_RGB24);
		m_mediaType.SetFormatType(&FORMAT_VideoInfo);
    }
}

HRESULT CMPEGInputPin::CheckMediaType(const CMediaType *pmt)
{
    CAutoLock lock(&m_csReceiveLock);

    if (m_bInsideCheckMediaType == TRUE)
        return NOERROR;

    m_bInsideCheckMediaType = TRUE;

    HRESULT hr = VFW_E_TYPE_NOT_ACCEPTED;

    if (m_mediaFormat == Audio)
    {
        if (*(pmt->Type()) == MEDIATYPE_Audio)
        {
            if (*(pmt->Subtype()) == MEDIASUBTYPE_PCM)
			{
				if (*(pmt->FormatType()) == FORMAT_WaveFormatEx)
				{
					hr = NOERROR;
				}
			}
        }
    }
    else if (m_mediaFormat == Video)
    {
        if (*pmt->Type() == MEDIATYPE_Video)
        {
            if (*(pmt->Subtype()) == MEDIASUBTYPE_RGB24)
			{
				if (*(pmt->FormatType()) == FORMAT_VideoInfo)
				{
					hr = NOERROR;
				}
				
				if (*(pmt->FormatType()) == FORMAT_VideoInfo2)
				{
					hr = NOERROR;
				}
			}
        }
    }

    m_bInsideCheckMediaType = FALSE;
    return hr;

}

HRESULT CMPEGInputPin::BreakConnect()
{
	m_bPaused = false;
    return CBaseInputPin::BreakConnect();
}

STDMETHODIMP CMPEGInputPin::ReceiveCanBlock()
{
    return S_OK;
}

STDMETHODIMP CMPEGInputPin::Receive(IMediaSample *pSample)
{
 //   CAutoLock lock(&m_csReceiveLock);

	TraceVerbose("CMPEGInputPin::Receive: Type=%lu\n", m_mediaFormat);

	HRESULT hr = CBaseInputPin::Receive(pSample);
	if (FAILED(hr))
	{
		Trace("CBaseInputPin rejected our sample\n");
		return hr;
	}

	REFERENCE_TIME tStart, tStop;
    hr = pSample->GetTime(&tStart, &tStop);

	if (m_mediaFormat == Audio)
		hr = m_pMPEGObj->ReceiveAudio(pSample);
	else
		hr = m_pMPEGObj->ReceiveVideo(pSample);

	if (FAILED(hr))
	{
		Trace("Receive failed\n");
	    m_bRunTimeError = TRUE;
	    EndOfStream();
		return hr;
	}

    m_tLastSampleTime = tStart;
    
    return NOERROR;
}


HRESULT CMPEGInputPin::SetMediaType(const CMediaType *pmt)
{
     CAutoLock lock(&m_csReceiveLock);

	if (pmt->formattype == FORMAT_VideoInfo)
	{
		m_nVidInfoHeaderLevel = 1;
		m_videoInfoHeader =	*(reinterpret_cast<VIDEOINFOHEADER*>(pmt->pbFormat));
	}
	if (pmt->formattype == FORMAT_VideoInfo2)
	{
		m_nVidInfoHeaderLevel = 2;
		m_videoInfoHeader2 = *(reinterpret_cast<VIDEOINFOHEADER2*>(pmt->pbFormat));
	}
	else if (pmt->formattype == FORMAT_WaveFormatEx)
	{
		m_audInfo = *(reinterpret_cast<WAVEFORMATEX*>(pmt->pbFormat));
	}

	return NOERROR;
};

//
// NewSegment
//
// Called when we are seeked
//
STDMETHODIMP CMPEGInputPin::NewSegment(REFERENCE_TIME tStart,
                                       REFERENCE_TIME tStop,
                                       double dRate)
{
    m_tLastSampleTime = 0;
    return S_OK;

}

WAVEFORMATEX* CMPEGInputPin::GetWaveFormat()
{	
	return &m_audInfo;
}

int CMPEGInputPin::GetVideoInfoHeaderLevel()
{
	return m_nVidInfoHeaderLevel;
}

VIDEOINFOHEADER2* CMPEGInputPin::GetVideoInfoHeader2()
{
	return &m_videoInfoHeader2;
}


VIDEOINFOHEADER* CMPEGInputPin::GetVideoInfoHeader()
{
	return &m_videoInfoHeader;
}

HRESULT CMPEGInputPin::GetMediaType(int iPosition, CMediaType *pMediaType)
{
	return E_NOTIMPL;
#if 0
	if (iPosition > 0)
	{
		return S_FALSE;
	}

	if (pMediaType)
		*pMediaType = m_mediaType; // copy operator

	return S_OK;
#endif
}

void CMPEGInputPin::SetPaused(bool bPaused)
{
//	m_bPaused = bPaused;
}

HRESULT CMPEGInputPin::Run()
{
	HRESULT hr = S_OK;
	return hr;
}



// Flush end of stream condition - caller should do any
// necessary stream level locking before calling this

STDMETHODIMP CMPEGInputPin::EndOfStream()
{
    CAutoLock lock(&m_csReceiveLock);

	// CAutoLock lock(m_pReceiveLock);
	// Do not return endofstream here to prevent the stream
	// from being stopped when the audio is finished, but
	// beofore the video is done

	Trace("End of stream\n");

	m_bPaused = false;

	HRESULT hr = m_pMPEGObj->EndOfStream(m_mediaFormat);
	if (hr == S_FALSE)
	{
		Trace("Ended stream was not last stream\n");
		return hr;
	}
	
	if (hr == NOERROR)
	{
		Trace("End of all streams\n");
	}

    hr = CheckStreaming();

    //  Do EC_COMPLETE handling for rendered pins
    if (S_OK == hr  && !m_bAtEndOfStream) {
        m_bAtEndOfStream = TRUE;
        FILTER_STATE fs;
        EXECUTE_ASSERT(SUCCEEDED(m_pFilter->GetState(0, &fs)));
        if (fs == State_Running) {
            DoCompleteHandling();
        }
    }
    return hr;
}


// Called to complete the flush

STDMETHODIMP CMPEGInputPin::EndFlush()
{
    CAutoLock lck(m_pLock);

    // Clean up renderer state
    m_bAtEndOfStream = FALSE;
    m_bCompleteNotified = FALSE;

    return CBaseInputPin::EndFlush();
}


// Notify of Run() from filter

HRESULT CMPEGInputPin::Run(REFERENCE_TIME tStart)
{
    UNREFERENCED_PARAMETER(tStart);
    m_bCompleteNotified = FALSE;
    if (m_bAtEndOfStream) {
        DoCompleteHandling();
    }
    return S_OK;
}


//  Clear status on going into paused state

HRESULT CMPEGInputPin::Active()
{
    m_bAtEndOfStream = FALSE;
    m_bCompleteNotified = FALSE;
    return CBaseInputPin::Active();
}


//  Do stuff to deliver end of stream

void CMPEGInputPin::DoCompleteHandling()
{
    ASSERT(m_bAtEndOfStream);
    if (!m_bCompleteNotified) {
        m_bCompleteNotified = TRUE;
        m_pFilter->NotifyEvent(EC_COMPLETE, S_OK, (LONG_PTR)(IBaseFilter *)m_pFilter);
    }
}


CMediaType* CMPEGInputPin::GetMediaType()
{
	return &m_mediaType;
}
