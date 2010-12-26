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


#pragma once

typedef enum _MediaFormat
{
	Audio,
	Video
} MediaFormat;

class CMPEGObj;

class CMPEGInputPin : public CBaseInputPin
{
public:
	CMediaType* GetMediaType();
	HRESULT Run();
	void SetPaused(bool bPaused);

    CMPEGInputPin(CMPEGObj *pMPEG,
                  LPUNKNOWN pUnk,
                  CBaseFilter *pFilter,
                  CCritSec *pLock,
                  CCritSec *pReceiveLock,
				  MediaFormat mediaFormat,
                  LPCWSTR pszPinName,
                  HRESULT *phr);

    // Do something with this media sample
    STDMETHODIMP Receive(IMediaSample *pSample);
    STDMETHODIMP ReceiveCanBlock();
	HRESULT SetMediaType(const CMediaType *pmt);
    HRESULT CheckMediaType(const CMediaType *);
    HRESULT BreakConnect();
    STDMETHODIMP NewSegment(REFERENCE_TIME tStart,
                            REFERENCE_TIME tStop,
                            double dRate);

	HRESULT GetMediaType(int iPosition, CMediaType *pMediaType);
	int GetVideoInfoHeaderLevel();

	VIDEOINFOHEADER2* GetVideoInfoHeader2();
	VIDEOINFOHEADER* GetVideoInfoHeader();
	WAVEFORMATEX* GetWaveFormat();

	    // Override methods to track end of stream state
    STDMETHODIMP EndOfStream();
    STDMETHODIMP EndFlush();

    HRESULT Active();
    HRESULT Run(REFERENCE_TIME tStart);

	void DoCompleteHandling();

private:
	bool m_bPaused;
	CMediaType m_mediaType;
    CMPEGObj * const m_pMPEGObj;        // Main renderer object
    CCritSec m_csReceiveLock;    // Sample critical section
    REFERENCE_TIME   m_tLastSampleTime;             // Last sample receive time
    bool m_bInsideCheckMediaType;		// Re-entrancy control
	MediaFormat  m_mediaFormat;
	int m_nVidInfoHeaderLevel;
	VIDEOINFOHEADER m_videoInfoHeader;
	VIDEOINFOHEADER2 m_videoInfoHeader2;
	WAVEFORMATEX m_audInfo;
	// Member variables to track state
    BOOL m_bAtEndOfStream;      // Set by EndOfStream
    BOOL m_bCompleteNotified;   // Set when we notify for EC_COMPLETE

};

