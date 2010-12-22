
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

