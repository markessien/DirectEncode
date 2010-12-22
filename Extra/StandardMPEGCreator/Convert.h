// Convert.h: interface for the CConvert class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONVERT_H__AFFFCB84_FBF2_4A93_AED9_99412936DBC7__INCLUDED_)
#define AFX_CONVERT_H__AFFFCB84_FBF2_4A93_AED9_99412936DBC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define _USE_NOTIFY_WND

#include "mpegsettings.h"
#include "notifywindow.h"

class IConvertCallback
{
public:
	virtual void ConversionComplete() {;}
	virtual void ConversionError(HRESULT hr, char* pstrMessage) {;}
	virtual void ConversionStatusChanged(char* pstrNewStatus) {;}
	virtual void ConversionAboutToRun() {;}
	virtual void ConversionConnecting() {;}
	virtual void ConversionStreaming() {;}
};

class CConvert  
{
public:
	CConvert(IConvertCallback* pCallback);
	virtual ~CConvert();

	
	HRESULT ResumeConversion();
	HRESULT PauseConversion();
	HRESULT CreateStill(BSTR strLowRes, BSTR strHighRes, BSTR OutputPath);
	HRESULT WaitForCompletion();
	HRESULT StartConversion();
	HRESULT StartConversionDirect();
	HRESULT CreateFilterGraph(IGraphBuilder **pGraph);
	HRESULT SetNoClock(IFilterGraph *graph);
	HRESULT Resize(RECT rc);
	HRESULT FindPinOnFilter( IBaseFilter * pFilter, PIN_DIRECTION PinDir, DWORD dwPin, BOOL fConnected, IPin ** ppPin );
	HRESULT GetFileInfo(BSTR Filename, double *pFramerate, double *pDuration, BOOL *pVideoStreamAvailable, BOOL *pAudioStreamAvailable, long *pWidth, long *pHeight, long *pBitrate, BSTR *pPosterFramePath);


	void   StopConversion();
	bool   IsURL(BSTR strPath);
	void   SetSettings(CMPEGSettings* pSettings);
	long   GetFramesEncoded();
	bool   IsPaused();
	void   SetLicensed(bool bLicensed);
	void   SelectFormat(SystemsOutputFormat sys, Constraint c);
	long   GetWrittenBytes(void);
	long   GetEncodeFramerate(void);
	void   SetShowPreview(bool b);
	double GetDuration();
	double GetProgress();
	double GetTimeElapsed();

	void SetParentWindow(HWND hwndAx)
	{
		m_hwndPreviewWnd = hwndAx;
	}
	


private:
	virtual CComPtr<IBaseFilter> GetMPEGWriter() { return m_pMPEGWriter; }
	virtual CComPtr<IStandardMpegEncoder> GetMPEGWriterProps() { return m_pMPEGWriterProps; }
	virtual CComPtr<IStandardMpegEncoderProfile> GetMPEGProfile(){ return m_pMPEGProfile; }
	virtual void SetMPEGProfile(CComPtr<IStandardMpegEncoderProfile> pProfile) { m_pMPEGProfile = NULL; pProfile.CopyTo(&m_pMPEGProfile); }

	bool IsRunning();
	bool IsFrameRateSupported(float fps);

	HRESULT AddFilter(CLSID clsid, IBaseFilter** ppFilter, BSTR strName, IPin **ppInputPin);
	HRESULT CheckVisibility();
	HRESULT Stop();
	HRESULT Run();
	HRESULT AddVideoSourceFiles();
	HRESULT AddAudioSourceFiles();
	HRESULT AddAudioTracks();
	HRESULT AddVideoTracks();
	HRESULT HandleEvent();
	HRESULT AddNullRenderer(IPin ** ppInputPin);
	HRESULT AddVideoGroup(double dSourceFramerate, long nSourceWidth, long nSourceHeight);
	HRESULT MakeNotificationWindow();
	HRESULT AddAudioGroup();
	HRESULT RenderOutput(ICaptureGraphBuilder2 *pBuilder, IGraphBuilder *pGraph, IRenderEngine* pEngine, IBaseFilter* pVideoGrabber, IPin *pVideoPin, IPin *pAudioPin, IBaseFilter* pSourceFilter);
	HRESULT LoadMPEGCodec();
	
	unsigned long GetFileSize(TCHAR* strPath);
	void ThrowError(HRESULT hr, char* pstrMsg);
	static BOOL NotifyFunc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, long pClass);


private:
	IConvertCallback* m_pCallback;
#ifdef _USE_NOTIFY_WND
	CNotifyWindow  m_wndNotify;
#endif
	long m_nLastEncodedFrameCount;
	bool m_bTiming;
	bool m_bLicensed;
	bool  m_bCanSeek;
	double m_dSourceLength;
	DWORD m_tStartTime;
	HWND m_hwndPreviewWnd;

	CMPEGSettings* m_pSettings;

	RECT m_rcWin;

	CComBSTR m_strLicenseKey;

	// dshow filters
	CComPtr<IGraphBuilder> m_pGraph;
	CComPtr<IMediaEventEx> m_pEvent;
	CComPtr<IMediaSeeking> m_pSeeking;
	CComPtr<IMediaControl> m_pMediaControl;
	CComPtr<ICaptureGraphBuilder2> m_pBuilder;
	CComPtr<IBaseFilter> m_pNullRender;
	CComPtr<IBaseFilter> m_pVideoRender;
	CComPtr<IBaseFilter> m_pSmartTee;
	CComPtr<IVideoWindow>  m_pVideoWindow;

	// DES filters
	CComPtr<IRenderEngine> m_pRenderEngine;
    CComPtr<IAMTimeline> m_pTimeline;
	CComPtr<IAMTimelineObj> m_pVideoGroupObj;
    CComPtr<IAMTimelineObj> m_pAudioGroupObj;

	// mpeg objects
	CComPtr<IBaseFilter> m_pMPEGWriter;
	CComPtr<IStandardMpegEncoder> m_pMPEGWriterProps;
	CComPtr<IStandardMpegEncoderProfile> m_pMPEGProfile;	
	CComPtr<IStandardMpegEncoderStats> m_pMPEGStats;

};

#endif // !defined(AFX_CONVERT_H__AFFFCB84_FBF2_4A93_AED9_99412936DBC7__INCLUDED_)
