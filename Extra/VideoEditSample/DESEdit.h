// DESEdit.h: Schnittstelle für die Klasse CDESEdit.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DESEDIT_H__06DD2D4C_714C_4722_9BDF_07FB9E06FD4A__INCLUDED_)
#define AFX_DESEDIT_H__06DD2D4C_714C_4722_9BDF_07FB9E06FD4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "notifywindow.h"
#include "helper.h"

class CMediaFileList;
class CVideoEditObj;

class CDESEdit  
{
public:
	CDESEdit(CVideoEditObj* pCallback);
	virtual ~CDESEdit();
	
	HRESULT Preview(long ParentHwnd, long x, long y, long width, long height);
	HRESULT ConstructGraph(CMediaFileList* pMediaList, long format);
	HRESULT OutputToFile(BSTR strFilePath);

	double GetDuration();
	double GetProgress();
	void Stop();
	void DestroyGraph();

private:
	HRESULT InsertAudioClips(CMediaFileList *pMediaList, IAMTimelineObj* pTrackAudioObj);
	
	HRESULT InsertVideoClips(CMediaFileList *pMediaList, IAMTimelineComp * pRootComp);
	HRESULT HandleEvent();
	static BOOL NotifyFunc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, long pClass);

	HRESULT InsertMPEGCodec(BSTR strTargetFile);
	HRESULT ApplyMPEGProperties();
	void ApplyVideoFormatSettings();
	HRESULT AddLongParam(IPropertySetter* pProp, PWSTR pParam, long lValue);
	HRESULT AddFadeTrack(IAMTimelineComp* pCompVideo, bool bFadeIn, bool bFadeOut, REFERENCE_TIME rtStart, REFERENCE_TIME rtStop);
	HRESULT SetColorOnSourceObject(IAMTimelineObj* pObject, DWORD dwColor);
	HRESULT SaveGraphFile(IGraphBuilder *pGraph, WCHAR *wszPath);

private:
	double m_dFadeOutLength;
	double m_dFadeInLength;
	float m_fOutputFPS;
	long  m_nOutputWidth;
	long  m_nOutputHeight;

	SystemsOutputFormat m_systemsFormat;
	Constraint m_constraint;
	VideoOutputFormat m_videoFormat;
	AudioOutputFormat m_audioFormat;


	CNotifyWindow  m_wndNotify;
	CVideoEditObj* m_pCallback;

	// Plaback filters
	CComPtr<IGraphBuilder> m_pGraph;
	CComPtr<IMediaEventEx> m_pEvent;
	CComPtr<IMediaSeeking> m_pSeeking;
	CComPtr<IMediaControl> m_pMediaControl;
	CComPtr<IBaseFilter>   m_pSrcFilter;
	CComPtr<ICaptureGraphBuilder> m_pBuilder;

	CComPtr<IVideoWindow>  m_pVideoWindow;

	CComPtr< IRenderEngine > m_pRenderEngine;
    CComPtr< IAMTimeline > m_pTimeline;
    CComPtr< IAMTimelineObj > m_pVideoGroupObj;
    CComPtr< IAMTimelineObj > m_pAudioGroupObj;

	CComPtr<IBaseFilter> m_pFileWriter;

	// mpeg objects
	CComPtr<IBaseFilter> m_pMPEGWriter;
	CComPtr<IStandardMpegEncoder> m_pIMPEGEncoder;
	CComPtr<IStandardMpegEncoderProfile> m_pIMPEGEncoderProfile;
};

#endif // !defined(AFX_DESEDIT_H__06DD2D4C_714C_4722_9BDF_07FB9E06FD4A__INCLUDED_)
