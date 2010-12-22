// Convert.cpp: implementation of the CConvert class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Convert.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


// Convert.cpp: implementation of the CConvert class.
//
//////////////////////////////////////////////////////////////////////

#define DIRECTINPUT_VERSION 0x0800
#include "stdafx.h"
#include "Convert.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <basetsd.h>
#include <ddraw.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <dmusici.h>
#include ".\convert.h"
#undef lstrlenW
#undef wsprintfW

#define WM_GRAPHNOTIFY WM_APP + 1
#define WM_MPEGNOTIFY WM_APP + 2
#define HR_ASSERT(x) if (FAILED(hr)) _ASSERT(#x - #x);
#define EPSILON 0.001 
#define FLOAT_EQ(x,v) (((v - EPSILON) < x) && (x <( v + EPSILON)))

#include <initguid.h>
#include <StandardMPEGEncoderUIDs.h>

HRESULT AddToRot(IUnknown *pUnkGraph, DWORD *pdwRegister) 
{
    IMoniker * pMoniker;
    IRunningObjectTable *pROT;
    if (FAILED(GetRunningObjectTable(0, &pROT))) {
        return E_FAIL;
    }
    WCHAR wsz[256];
    wsprintfW(wsz, L"FilterGraph %08p pid %08x", (DWORD_PTR)pUnkGraph, GetCurrentProcessId());
    HRESULT hr = CreateItemMoniker(L"!", wsz, &pMoniker);
    if (SUCCEEDED(hr)) {
        hr = pROT->Register(0, pUnkGraph, pMoniker, pdwRegister);
        pMoniker->Release();
    }
    pROT->Release();
    return hr;
}

void RemoveFromRot(DWORD pdwRegister)
{
	IRunningObjectTable *pROT;
    if (SUCCEEDED(GetRunningObjectTable(0, &pROT))) {
        pROT->Revoke(pdwRegister);
        pROT->Release();
    }
}

void PromptForGraph(IGraphBuilder* pGraph, _TCHAR* pszGraphType)
{

	DWORD dwGraphRegister = 0;
	AddToRot(pGraph, &dwGraphRegister);

	_TCHAR szMsg[1024];
	_tcscpy(szMsg, _T("You can connect to the "));
	_tcscat(szMsg, pszGraphType);
	_tcscat(szMsg, _T(" Graph right now. This is NOT an error."));

	MessageBox(::GetDesktopWindow(), szMsg, 
			   _T("Developer information"),
				MB_ICONINFORMATION|MB_OK|
				MB_SETFOREGROUND|MB_SYSTEMMODAL);

	RemoveFromRot(dwGraphRegister);
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CConvert::CConvert(IConvertCallback* pCallback) : m_pCallback(pCallback)
{
	m_strLicenseKey = L"GJEF-FEFH-IGHJ-RVGQ-ECDF";
	m_bLicensed = false;
	m_tStartTime = 0;
	m_pMPEGProfile = NULL;
	m_hwndPreviewWnd = 0;
	m_pSettings = NULL;
	m_bTiming = false;
	m_nLastEncodedFrameCount = 0;

	CoInitialize(0);
	LoadMPEGCodec();
}

CConvert::~CConvert()
{
	// m_pMPEGWriter = NULL;
}

HRESULT CConvert::StartConversion()
{
	StopConversion();
	
	printf("Initialising conversion...\n");
	
	bool bIsURL = IsURL(m_pSettings->strInputFile);
	if (bIsURL)
		return StartConversionDirect();

	HRESULT hr = MakeNotificationWindow();
	if (FAILED(hr))
		return hr;

	m_pSettings->ApplySettingsToFilter(m_pMPEGWriter);

	m_nLastEncodedFrameCount = 0;

	hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, 
                          NULL, CLSCTX_INPROC_SERVER,
						  IID_ICaptureGraphBuilder2, 
						  (void **)&m_pBuilder);
	
	if (FAILED(hr))
	{
		StopConversion();
		ThrowError(hr, "GraphBuilder could not be created");
		return hr;
	}

	if (wcscmp(m_pSettings->strInputFile, m_pSettings->strOutputFile) == 0)
	{
		StopConversion();
		ThrowError(E_FAIL, "The source and target files are the same.");
		return E_FAIL;
	}

    // make the timeline
    hr = CoCreateInstance(CLSID_AMTimeline, 
                         NULL, 
                         CLSCTX_INPROC_SERVER, 
                         IID_IAMTimeline, 
                         (void**) &m_pTimeline);

    if(FAILED( hr ))
	{
		StopConversion();
		ThrowError(hr, "Timeline could not be created");
        return hr;
	}

	BOOL bOutputHasVideo = TRUE;
	/*
	switch (m_audioFormat)
	{
	case formatMP3:
	case formatWAV:
		bOutputHasVideo = FALSE; 
		break;
	}*/

	double dFramerate = 0;
	BOOL bVideo = FALSE;
	BOOL bAudio = FALSE;
	long nWidth = 0;
	long nHeight = 0;
	
	hr = GetFileInfo(m_pSettings->strInputFile, &dFramerate, &m_dSourceLength, &bVideo, &bAudio, &nWidth, &nHeight, 0, 0);

	if (!bIsURL && FAILED(hr))
	{
		StopConversion();
		ThrowError(E_FAIL, "The source file could not be read. The conversion cannot proceed");
		return E_FAIL;
	}

	/*
	if ((bAudio && !bVideo || !bOutputHasVideo) && m_bLimitAudio)
	{
		SetStopTime(30);
	}
	*/

	/*
	if (m_dSourceLength == 0 && nWidth && nHeight)
	{
		// picture. We will encode as mpeg still image
		m_dSourceLength = 0.429f;
	}
	else */if (m_dSourceLength == 0)
	{
		StopConversion();
		ThrowError(E_FAIL, "The source file had a duration of 0 seconds. The conversion cannot proceed");
		return E_FAIL;
	}

	if (bVideo && (nWidth == 0 || nHeight == 0))
	{
		StopConversion();
		ThrowError(E_FAIL, "The source video could not be read. The conversion cannot proceed");
		return E_FAIL;
	}


	if (bVideo && bOutputHasVideo)
	{
		hr = AddVideoGroup(dFramerate, nWidth, nHeight);
		if (FAILED(hr))
		{
			StopConversion();
			ThrowError(hr, "Video group could not be added to timeline");
			_ASSERT(FALSE);
			return hr;
		}
	}

	if (bAudio)
	{
		hr = AddAudioGroup();
		if (FAILED(hr))
		{
			_ASSERT(FALSE);
			StopConversion();
			ThrowError(hr, "Audio group could not be added to timeline");
			return hr;
		}
	}

	if (bVideo && bOutputHasVideo)
	{
		hr = AddVideoTracks();
		if (FAILED(hr))
		{
			_ASSERT(FALSE);
			StopConversion();
			ThrowError(hr, "Video track could not be added to timeline");
			return hr;
		}
	}

	if (bAudio)
	{
		hr = AddAudioTracks();
		if (FAILED(hr))
		{
			_ASSERT(FALSE);
			StopConversion();
			ThrowError(hr, "Audio track could not be added to timeline");
			return hr;
		}
	}

	if (bVideo && bOutputHasVideo)
	{
		hr = AddVideoSourceFiles();
		if (FAILED(hr))
		{
			_ASSERT(FALSE);
			StopConversion();
			ThrowError(hr, "Video source file could not be added to timeline");
			return hr;
		}
	}
	
	if (bAudio)
	{
		hr = AddAudioSourceFiles();
		if (FAILED(hr))
		{
			_ASSERT(FALSE);
			StopConversion();
			ThrowError(hr, "Audio source file could not be added to timeline");
			
			return hr;
		}
	}

    hr = m_pTimeline->ValidateSourceNames(SFN_VALIDATEF_CHECK|SFN_VALIDATEF_POPUP|SFN_VALIDATEF_REPLACE, NULL, 0);
    _ASSERT(!FAILED(hr));

    hr = CoCreateInstance(CLSID_RenderEngine, NULL, CLSCTX_INPROC_SERVER, IID_IRenderEngine, (void**) &m_pRenderEngine);
    if (FAILED(hr))
	{
		StopConversion();
		ThrowError(hr, "Render engine could not be created");
		return hr;
	}

    hr = m_pRenderEngine->SetTimelineObject( m_pTimeline );
    if (FAILED(hr))
	{
		StopConversion();
		ThrowError(hr, "Timeline object corrupt. Bad timeline!");		
		return hr;
	}

	if (m_pSettings->dStartTime || m_pSettings->dEndTime)
	{
		hr = m_pRenderEngine->SetRenderRange((__int64)(m_pSettings->dStartTime * UNITS), (__int64)(m_pSettings->dEndTime * UNITS));
		if (FAILED(hr))
		{
			_ASSERT(FALSE);
		}
	}

    hr = m_pRenderEngine->ConnectFrontEnd();
	if (FAILED(hr))
	{
		StopConversion();
		ThrowError(hr, "File could not be rendered");
		return hr;
	}

	hr = S_OK;
	hr = m_pRenderEngine->GetFilterGraph( &m_pGraph );
	hr |= m_pBuilder->SetFiltergraph(m_pGraph);
	if (FAILED(hr))
	{
		StopConversion();
		ThrowError(hr, "Filter graph could not be retrieved");
		return hr;
	}


	CComPtr<IPin> pVideoOutPin;
	CComPtr<IPin> pAudioOutPin;

	// if it has an audio stream, but no video stream, or does not need video out
	if (bAudio && (!bVideo || !bOutputHasVideo))
	{
		hr = m_pRenderEngine->GetGroupOutputPin(0, &pAudioOutPin);
	}
	else
	{
		hr = m_pRenderEngine->GetGroupOutputPin(0, &pVideoOutPin);
		hr = m_pRenderEngine->GetGroupOutputPin(1, &pAudioOutPin);
	}

	hr = RenderOutput(m_pBuilder, m_pGraph, m_pRenderEngine, NULL, pVideoOutPin, pAudioOutPin, NULL);
	if (FAILED(hr))
	{
		ThrowError(hr, "The output could not be rendered");
		_ASSERT(FALSE);
		StopConversion();
		return hr;
	}
	
	if (CheckVisibility() == S_OK)
	{
		m_pVideoWindow->put_Owner((OAHWND)m_hwndPreviewWnd);
		Resize(m_rcWin);
		m_pVideoWindow->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	}


	// PromptForGraph(m_pGraph, "edit");

	if (m_pCallback)
		m_pCallback->ConversionAboutToRun();


	hr = Run();
	_ASSERT(SUCCEEDED(hr));
	if (FAILED(hr))
	{
		StopConversion();
		ThrowError(hr, "Everything was initialized okay, but the actual conversion could not start. Please check that you can write to the output file.");
	}

	return hr;
}

void CConvert::StopConversion()
{
	Stop();
	
	if (m_pEvent)
	{
		m_pEvent->SetNotifyFlags(AM_MEDIAEVENT_NONOTIFY);
		m_pEvent->SetNotifyWindow(NULL, WM_GRAPHNOTIFY, 0);
		m_pEvent = NULL;
	}

	m_pSeeking = NULL;
	m_pMediaControl = NULL;

	if (m_pRenderEngine)
		m_pRenderEngine->ScrapIt();

	m_pRenderEngine = NULL;
    m_pTimeline = NULL;
    m_pVideoGroupObj = NULL;
    m_pAudioGroupObj = NULL;
	m_pVideoRender = NULL;
	m_pSmartTee = NULL;
	m_pVideoWindow = NULL;

	if (m_pMPEGWriter && m_pGraph)
	{
		// remove the filter from graph
		m_pGraph->RemoveFilter(m_pMPEGWriter);
	}
	
	m_pGraph = NULL;
/*
#ifdef _USE_NOTIFY_WND
	if (m_wndNotify.IsWindow())
		m_wndNotify.DestroyWindow();
#endif
*/
	if (m_pBuilder)
	{
		m_pBuilder = NULL;
		m_pCallback->ConversionComplete();
	}
}

HRESULT CConvert::MakeNotificationWindow()
{
#ifdef _USE_NOTIFY_WND
	//if (m_wndNotify.IsWindow())
	//	return S_OK;

	if (m_wndNotify.IsWindow())
	{
		// m_wndNotify.SendMessage(WM_CLOSE);
		m_wndNotify.DestroyWindow();
		m_wndNotify.m_hWnd = NULL;
	}
	
	m_wndNotify.SetDrainFunction(NotifyFunc, (LONG_PTR)this);
	RECT rect;
	rect.left = 0; rect.top = 0; rect.right = 5; rect.bottom = 5;
	m_wndNotify.Create(NULL, rect, _T("NotifyWnd"), WS_POPUP);
	_ASSERT(m_wndNotify.IsWindow());
	
	return (m_wndNotify.IsWindow() ? S_OK : E_FAIL);
#else	
	return S_OK;
#endif
}

HRESULT CConvert::AddVideoGroup(double dSourceFramerate, long nSourceWidth, long nSourceHeight)
{

    // make the root group/composition
	HRESULT hr = S_OK;
    hr = m_pTimeline->CreateEmptyNode(&m_pVideoGroupObj, TIMELINE_MAJOR_TYPE_GROUP);
    if(FAILED( hr )) 
    {
        return hr;
    }

	CComQIPtr<IAMTimelineGroup, &IID_IAMTimelineGroup> pVideoGroup(m_pVideoGroupObj);
 
	//// Set Media Type
	CMediaType VideoGroupType;
	VideoGroupType.SetType(&MEDIATYPE_Video);
	VideoGroupType.SetSubtype(&MEDIASUBTYPE_RGB24);
	VideoGroupType.SetFormatType(&FORMAT_VideoInfo);
	
	VIDEOINFOHEADER *pVideoHeader = (VIDEOINFOHEADER*)VideoGroupType.AllocFormatBuffer(sizeof(VIDEOINFOHEADER));
	ZeroMemory(pVideoHeader, sizeof(VIDEOINFOHEADER));
	
	pVideoHeader->bmiHeader.biBitCount = 24;
	pVideoHeader->bmiHeader.biWidth = nSourceWidth;
	pVideoHeader->bmiHeader.biHeight = nSourceHeight;
	pVideoHeader->bmiHeader.biPlanes = 1;
	pVideoHeader->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pVideoHeader->bmiHeader.biSizeImage = DIBSIZE(pVideoHeader->bmiHeader);

	VideoGroupType.SetSampleSize(DIBSIZE(pVideoHeader->bmiHeader));
	
	hr = pVideoGroup->SetMediaType(&VideoGroupType);
    if(FAILED( hr )) 
    {
        return hr;
    }

	
//	double dRequiredInputFramerate = 0;
//	m_pMPEGWriterProps->SetSourceFramerate(dSourceFramerate, &dRequiredInputFramerate);

// 	hr = pVideoGroup->SetOutputFPS(15);


	/*
	if (GetOutputFPS() != 0)
	{
		// the user set a framerate
		hr = pVideoGroup->SetOutputFPS(GetOutputFPS());
		GetMPEGWriterProps()->OverrideSourceFPS(GetOutputFPS());
	}
	else if (IsFrameRateSupported((float)dSourceFramerate))
	{
		// the user did not set a framerate. If the source
		// framerate is supported, we use it.
		hr = pVideoGroup->SetOutputFPS(dSourceFramerate);
		GetMPEGWriterProps()->OverrideSourceFPS((float)dSourceFramerate);
	}
	else
	{
		// the user did not want a framerate, and the framerate
		// of the file is not supported. We use 25fps
		hr = pVideoGroup->SetOutputFPS(25);
		GetMPEGWriterProps()->OverrideSourceFPS(25);
	}
	*/

	hr = m_pTimeline->AddGroup(m_pVideoGroupObj);

	return hr;
}

HRESULT CConvert::AddAudioGroup()
{
	HRESULT hr;
	hr = m_pTimeline->CreateEmptyNode(&m_pAudioGroupObj, TIMELINE_MAJOR_TYPE_GROUP );
    if(FAILED( hr )) 
    {
        return hr;
    }

	CComQIPtr<IAMTimelineGroup, &IID_IAMTimelineGroup> pAudioGroup(m_pAudioGroupObj);
    CMediaType AudioGroupType;

    // all we set is the major type. The group will automatically use other defaults
    AudioGroupType.SetType( &MEDIATYPE_Audio);
    hr = pAudioGroup->SetMediaType( &AudioGroupType );
    if(FAILED( hr )) 
    {
        return hr;
    }
	
	hr = m_pTimeline->AddGroup(m_pAudioGroupObj);
    if(FAILED( hr )) 
    {
        return hr;
    }
	
	return hr;
}

BOOL CConvert::NotifyFunc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LONG_PTR pClass)
{
	CConvert* pThis = (CConvert*)pClass;
	_ASSERT(pThis);

	BOOL bResult = FALSE;
	switch(uMsg)
	{
	case WM_GRAPHNOTIFY:
		pThis->HandleEvent();
		break;
		/*
	case WM_MPEGNOTIFY:
		switch (wParam)
		{
		case EC_STATE_CHANGE: // requires dx8.1 for this declaration
			if (pThis->m_pMPEGWriterProps)
			{
				char* pStatus = NULL; 
//				pThis->m_pMPEGWriterProps->GetStatusStringPtr(&pStatus); // don't delete this string.
				pThis->m_pCallback->ConversionStatusChanged(pStatus);
			}
			break;
		}
		break;*/
	}

	return bResult;
}

HRESULT CConvert::HandleEvent()
{
	if (m_pEvent == NULL)
		return E_FAIL;

	HRESULT hr;
	long evCode, param1, param2;
    
    while (hr = m_pEvent->GetEvent(&evCode, &param1, &param2, 0), SUCCEEDED(hr))
    { 
        hr = m_pEvent->FreeEventParams(evCode, param1, param2);
		
		if ((EC_COMPLETE == evCode) || (EC_USERABORT == evCode))
        {
			StopConversion();
			return S_FALSE; // Stop destroys objects, so return immediately
        }
    } 
	
	return hr;
}

HRESULT CConvert::AddVideoTracks()
{
	HRESULT hr = S_OK;

	CComQIPtr<IAMTimelineComp, &IID_IAMTimelineComp> pRootComp(m_pVideoGroupObj);

	CComPtr<IAMTimelineObj> pTrackVideoObj;
	hr = m_pTimeline->CreateEmptyNode(&pTrackVideoObj, TIMELINE_MAJOR_TYPE_TRACK);
	if(FAILED(hr)) 
	{
		return hr;
	}

	hr = pRootComp->VTrackInsBefore(pTrackVideoObj, -1);
	if(FAILED( hr )) 
	{
		return hr;
	}

	return hr;
}

double CConvert::GetTimeElapsed()
{
	static DWORD dwElapsedMS = 0;
	if (m_bTiming == false)
		return ((double)dwElapsedMS / 1000.0f);

	dwElapsedMS = timeGetTime() - m_tStartTime;
	return ((double)dwElapsedMS / 1000.0f);
}

HRESULT CConvert::AddFilter(CLSID clsid, IBaseFilter** ppFilter, BSTR strName, IPin **ppInputPin)
{
	HRESULT hr = CoCreateInstance(clsid, NULL, 
								  CLSCTX_INPROC_SERVER, 
								  IID_IBaseFilter, 
								  (void**)ppFilter);
	if (FAILED(hr))
		return hr;

	hr = m_pGraph->AddFilter(*ppFilter, strName);
	if (FAILED(hr))
		return hr;
	
	hr = m_pBuilder->FindPin(*ppFilter, PINDIR_INPUT, NULL, NULL, FALSE, 0, ppInputPin);
	return hr;
}


HRESULT CConvert::AddAudioTracks()
{
	HRESULT hr = S_OK;

	CComQIPtr<IAMTimelineComp, &IID_IAMTimelineComp> pRootComp(m_pAudioGroupObj);

	CComPtr<IAMTimelineObj> pTrackAudioObj;
	hr = m_pTimeline->CreateEmptyNode(&pTrackAudioObj, TIMELINE_MAJOR_TYPE_TRACK );
	if(FAILED( hr )) 
	{
		return hr;
	}

	hr = pRootComp->VTrackInsBefore(pTrackAudioObj, -1);
	if(FAILED( hr )) 
	{
		return hr;
	}

	return hr;
}

HRESULT CConvert::AddVideoSourceFiles()
{
	HRESULT hr = S_OK;

	CComPtr<IAMTimelineObj> pSourceVideoObj;	
	hr = m_pTimeline->CreateEmptyNode(&pSourceVideoObj, TIMELINE_MAJOR_TYPE_SOURCE );
	if(FAILED( hr )) 
		return hr;
	
	double dStop = m_pSettings->dEndTime;
	if (m_pSettings->dEndTime == 0.0f)
		dStop = m_dSourceLength;

	hr = S_OK;
	hr |= pSourceVideoObj->SetStartStop2(0, dStop);
	HR_ASSERT(hr);

	CComQIPtr<IAMTimelineSrc, &IID_IAMTimelineSrc> pSourceVideoSrc(pSourceVideoObj);
	hr |= pSourceVideoSrc->SetMediaTimes2(0, dStop);
	HR_ASSERT(hr);

	hr |= pSourceVideoSrc->SetMediaName(m_pSettings->strInputFile);
	HR_ASSERT(hr);

	hr |= pSourceVideoSrc->SetStretchMode(RESIZEF_STRETCH);
	HR_ASSERT(hr);

	if (FAILED( hr )) 
		return hr;
			
	// Get the video root composition
	CComQIPtr<IAMTimelineComp, &IID_IAMTimelineComp> pRootComp(m_pVideoGroupObj);
	
	CComPtr<IAMTimelineObj> pVideoTrackObj;
	pRootComp->GetVTrack(&pVideoTrackObj, 0);

	CComQIPtr<IAMTimelineTrack, &IID_IAMTimelineTrack> pTrackVideo(pVideoTrackObj);
	hr = pTrackVideo->SrcAdd(pSourceVideoObj);
	if (FAILED( hr )) 
		return hr;

	return hr;
}

HRESULT CConvert::AddAudioSourceFiles()
{
	HRESULT hr = S_OK;
	CComPtr<IAMTimelineObj> pSourceAudioObj;	
	hr = m_pTimeline->CreateEmptyNode(&pSourceAudioObj, TIMELINE_MAJOR_TYPE_SOURCE );
	if(FAILED( hr )) 
		return hr;

	double dStop = m_pSettings->dEndTime;
	if (m_pSettings->dEndTime == 0.0f)
		dStop = m_dSourceLength;

	hr = pSourceAudioObj->SetStartStop2(0, dStop);		

	hr = S_OK;
	CComQIPtr<IAMTimelineSrc, &IID_IAMTimelineSrc> pSourceAudioSrc(pSourceAudioObj);
	hr |= pSourceAudioSrc->SetMediaTimes2(0, dStop);
	hr |= pSourceAudioSrc->SetMediaName(m_pSettings->strInputFile);
	
	if(FAILED( hr )) 
		return hr;
	
	// Get the audio root composition
	CComQIPtr<IAMTimelineComp, &IID_IAMTimelineComp> pRootComp(m_pAudioGroupObj);
	
	CComPtr<IAMTimelineObj> pAudioTrackObj;
	pRootComp->GetVTrack(&pAudioTrackObj, 0);

	CComQIPtr<IAMTimelineTrack, &IID_IAMTimelineTrack> pTrackAudio(pAudioTrackObj);
	hr = pTrackAudio->SrcAdd(pSourceAudioObj);
	if (FAILED( hr )) 
		return hr;

	return hr;
}

HRESULT CConvert::Run()
{
	HRESULT hr = E_POINTER;
	if (m_pMediaControl)
	{
		m_tStartTime = timeGetTime();
		m_bTiming = true;
		hr = m_pMediaControl->Run();
	}

	return hr;
}

HRESULT CConvert::Stop()
{
	HRESULT hr = E_POINTER;
	if (m_pMediaControl)
	{
		hr = m_pMediaControl->Stop();
		m_bTiming = false;
	}

	return hr;
}

double CConvert::GetProgress()
{
	if (m_pSeeking)
	{
		LONGLONG ll = 0;
		m_pSeeking->GetCurrentPosition(&ll);
		return (double)((double)ll / (double)UNITS);
    }

	return 0;
}

double CConvert::GetDuration()
{
	if (m_pSeeking)
	{
		LONGLONG ll = 0;
		m_pSeeking->GetDuration(&ll);
		if (ll == 0)
			return m_dSourceLength;
		return (double)((double)ll / (double)UNITS);
	}
	
	return 0;
}

bool CConvert::IsRunning()
{
	if (m_pMediaControl == NULL)
		return false;

	OAFilterState state;
	HRESULT hr = m_pMediaControl->GetState(2000, &state);
	if (hr == S_OK)
	{
		if (state == State_Running)
			return true;
	}

	return false;
}

bool CConvert::IsPaused()
{
	if (m_pMediaControl == NULL)
		return false;

	OAFilterState state;
	HRESULT hr = m_pMediaControl->GetState(2000, &state);
	if (hr == S_OK)
	{
		if (state == State_Paused)
			return true;
	}

	return false;
}

void CConvert::ThrowError(HRESULT hr, char *pstrMsg)
{
	m_pCallback->ConversionError(hr, pstrMsg);
}

HRESULT CConvert::GetFileInfo(BSTR Filename, double *pFramerate, double *pDuration, BOOL *pVideoStreamAvailable, BOOL *pAudioStreamAvailable, long *pWidth, long *pHeight, long *pBitrate, BSTR *pPosterFramePath)
{
	USES_CONVERSION;

	// init all pointers
	if (pFramerate)	*pFramerate = 0;
	if (pVideoStreamAvailable) *pVideoStreamAvailable = FALSE;
	if (pAudioStreamAvailable) *pAudioStreamAvailable = FALSE;
	if (pWidth)	*pWidth = 0;
	if (pHeight) *pHeight = 0;
	if (pDuration) *pDuration = 0;
	
	BOOL bVideoStream = FALSE;
	double dVideoDuration = 0;
	double dAudioDuration = 0;
	long nAudioLengthBytes = 0;
	long nVideoLengthBytes = 0;
	GUID videoSubType = {0};

	long nFileSize = GetFileSize(Filename);
	if (nFileSize == 0)
		return E_FAIL;

	HRESULT hr = S_OK;
	CComPtr<IMediaDet> pDet;
	hr = pDet.CoCreateInstance(__uuidof(MediaDet));
	if (FAILED(hr))
		return hr;

	hr = pDet->put_Filename(Filename);
	if (FAILED(hr))
		return hr;

	long lStreamCount = 0;
	hr = pDet->get_OutputStreams(&lStreamCount);
	for (long i=0; i<lStreamCount;i++)
	{
		GUID major_type;
		hr = pDet->put_CurrentStream(i);
		hr = pDet->get_StreamType(&major_type);

		if (major_type == MEDIATYPE_Video)  // Found a video stream.
		{
			bVideoStream = TRUE;

			// video stream is available
			if (pVideoStreamAvailable) *pVideoStreamAvailable = TRUE;

			// get framerate
			if (pFramerate)	pDet->get_FrameRate(pFramerate);
			
			// get length of video stream
			pDet->get_StreamLength(&dVideoDuration);
			if (pDuration)*pDuration = dVideoDuration;
			
			// get detailed info about video
			AM_MEDIA_TYPE mt;
			hr = pDet->get_StreamMediaType(&mt);
			if (SUCCEEDED(hr))
			{
				videoSubType = mt.subtype;

				// avi, mpeg and so on have this...
				if (mt.formattype == FORMAT_VideoInfo)
				{
					VIDEOINFOHEADER *pVih = (VIDEOINFOHEADER*)(mt.pbFormat);
					
					if (pWidth)	  *pWidth = pVih->bmiHeader.biWidth;
					if (pHeight)  *pHeight = pVih->bmiHeader.biHeight;
					if (pHeight) if (*pHeight < 0) *pHeight *= -1;
					if (pBitrate) *pBitrate = pVih->dwBitRate;
				}
				else if (mt.formattype == FORMAT_VideoInfo2)
				{
					_ASSERT(FALSE); // not supported yet
				}
				else if (mt.formattype == FORMAT_MPEG2Video )
				{
					_ASSERT(FALSE); // not supported yet
				}
			}

			FreeMediaType(mt);
		}
		else if (major_type == MEDIATYPE_Audio)
		{
			// audio stream is available
			if (pAudioStreamAvailable) *pAudioStreamAvailable = TRUE;
			
			// get audio stream length
			pDet->get_StreamLength(&dAudioDuration);
			
			AM_MEDIA_TYPE mt;
			hr = pDet->get_StreamMediaType(&mt);
			if (SUCCEEDED(hr) && mt.formattype == FORMAT_WaveFormatEx)
			{
				WAVEFORMATEX *pWav = (WAVEFORMATEX*)(mt.pbFormat);
				nAudioLengthBytes = (long)(pWav->nAvgBytesPerSec * dAudioDuration);
			}
		}	
	}
	
	// calculate the actual bitrate
	if (nFileSize && pBitrate)
	{
		double d = max(dAudioDuration, dVideoDuration);

		*pBitrate = (long)(float)((float)nFileSize / d);
		*pBitrate *= 8;

		/*
		nVideoLengthBytes = nFileSize - nAudioLengthBytes;
		long nBytesPerSecond = (long)(float)((float)nVideoLengthBytes / dVideoDuration);
		if (nBytesPerSecond == 0 && nAudioLengthBytes && pBitrate)
		{
			if (pBitrate)
			{
				*pBitrate = (long)(float)((float)nFileSize / dAudioDuration);
				*pBitrate *= 8;
			}
		}
		else if (pBitrate && *pBitrate == 0)
			*pBitrate = nBytesPerSecond * 8;
			*/
	}

	// use the longer duration of the two as the duration
	if (pDuration)
	{
		if (dAudioDuration >  dVideoDuration)
			*pDuration = dAudioDuration;
		else
			*pDuration = dVideoDuration;
	}
	
	// save poster frame if required
	if (pPosterFramePath && bVideoStream == TRUE)
	{
		// get path in tmp dir
		TCHAR szTmp[MAX_PATH];
		GetTempPath(MAX_PATH, szTmp);
		_tcscat(szTmp, _T("erdposter.bmp"));
		
		// copy the file to the buffer
		CComBSTR str = szTmp;
		str.CopyTo(pPosterFramePath);
		
		// make sure no such file
		DeleteFile(szTmp);

		// get the filename in ansi
		char* pstrFile = W2A(Filename);
		_strlwr(pstrFile); // make lower

		// if the file has asf or wmv, in it, don't seek, else
		// it will freeze. So write at pos 0, while for others
		// we write at 1sec
		if (videoSubType == MEDIASUBTYPE_Asf ||
			strstr(pstrFile, "asf") || 
			strstr(pstrFile, "wmv"))
		{
			pDet->WriteBitmapBits(0, 163, 112, str);
		}
		else
			pDet->WriteBitmapBits(1, 163, 112, str);
	}
	

	return hr;
}

HRESULT CConvert::RenderOutput(ICaptureGraphBuilder2 *pBuilder, IGraphBuilder *pGraph, IRenderEngine* pEngine, IBaseFilter* pVideoGrabber, IPin *pVideoPin, IPin *pAudioPin, IBaseFilter* pSourceFilter)
{
	if (m_pMPEGWriter == NULL)
	{
		return E_POINTER;
	}

	CComPtr<IBaseFilter> pFileWriter;
	HRESULT hr = pFileWriter.CoCreateInstance(CLSID_FileWriter);
	if (FAILED(hr))
		return hr;

	hr = m_pGraph->AddFilter(pFileWriter, L"File Writer Filter");
	if (FAILED(hr))
	{
		return hr;
	}

	CComPtr <IFileSinkFilter> pFS;
	hr = pFileWriter->QueryInterface(IID_IFileSinkFilter, (void **) &pFS);
	if (FAILED(hr) || pFS == NULL)
	{
		return hr;
	}

	hr = pFS->SetFileName(m_pSettings->strOutputFile, 0);
	if (FAILED(hr))
	{
		return hr;
	}

	hr = pGraph->AddFilter(m_pMPEGWriter, L"MPEG Mux Filter");
	if (FAILED(hr))
	{
		return hr;
	}

	hr = m_pMPEGWriter->QueryInterface(IID_IMediaSeeking, (void**)&m_pSeeking);
	if (FAILED(hr))
	{
		return hr;
	}


	if (pAudioPin && pVideoPin == NULL)
	{
		// audio only needs special attention.
		CComPtr<IPin> pAudioInPin;
		hr = pBuilder->FindPin(m_pMPEGWriter, PINDIR_INPUT, NULL, NULL, FALSE, 1, &pAudioInPin);
		_ASSERT(pAudioInPin);

		hr = pGraph->Connect(pAudioPin, pAudioInPin);
	}
	else
	{
		// both video and audio pin
		if (pVideoPin)
		{
			if (m_pSettings->bShowPreview)
			{
				CComPtr<IPin> pVideoRenderInPin;
				AddFilter(CLSID_VideoRenderer, &m_pVideoRender, L"Video Renderer", &pVideoRenderInPin);
				
				CComPtr<IPin> pTeeInPin;
				AddFilter(CLSID_SmartTee, &m_pSmartTee, L"Smart Tee Filter", &pTeeInPin);

				hr = pBuilder->RenderStream(NULL, NULL, pVideoPin, m_pSmartTee, m_pMPEGWriter);
				hr = pBuilder->RenderStream(NULL, NULL, m_pSmartTee, NULL, m_pVideoRender);
		
				hr = m_pVideoRender->QueryInterface(IID_IVideoWindow, (void **)&m_pVideoWindow);
			}
			else
				hr = pBuilder->RenderStream(NULL,	NULL, pVideoPin, NULL, m_pMPEGWriter);
		}

		if (pAudioPin)
			hr = pBuilder->RenderStream(NULL, &MEDIATYPE_Audio, pAudioPin, NULL, m_pMPEGWriter);
	}


	hr = pBuilder->RenderStream(NULL, NULL, m_pMPEGWriter, NULL, pFileWriter);


	hr = S_OK;
	hr |= m_pGraph->QueryInterface(IID_IMediaEvent,   (void**) &m_pEvent);
	_ASSERT(hr == S_OK);

    hr |= m_pGraph->QueryInterface(IID_IMediaControl, (void**) &m_pMediaControl);
	_ASSERT(hr == S_OK);

	if (m_pEvent)
		hr = m_pEvent->SetNotifyWindow((OAHWND)m_wndNotify.m_hWnd, WM_GRAPHNOTIFY, 0);
	
	DWORD dwCaps = AM_SEEKING_CanSeekAbsolute;
	if (m_pSeeking && m_pSeeking->CheckCapabilities(&dwCaps) == S_OK)
	{
		m_bCanSeek = true;
	}
	else
		m_bCanSeek = false;

#if 1
//	PromptForGraph(m_pGraph, _T("edit"));
#endif
	
	return hr;
}

HRESULT CConvert::Resize(RECT rc)
{
	m_rcWin = rc;

	HRESULT hr = E_POINTER;
    if (m_pVideoWindow)
    {
		hr = m_pVideoWindow->SetWindowPosition(rc.left, rc.top, 
											   (rc.right - rc.left) - 30, 
											   rc.bottom - rc.top);	
	}

	return hr;
}

HRESULT CConvert::CheckVisibility()
{
	HRESULT hr;

    if ((!m_pVideoWindow) )
    {
		return S_FALSE;
    }
	
	long lVisible;
    hr = m_pVideoWindow->get_Visible(&lVisible);
    if (FAILED(hr))
    {
        // If this is an audio-only clip, get_Visible() won't work.
        //
        // Also, if this video is encoded with an unsupported codec,
        // we won't see any video, although the audio will work if it is
        // of a supported format.
        //
        if (hr == E_NOINTERFACE)
        {
            return S_FALSE;
        }
    }

	return S_OK;
}

unsigned long CConvert::GetFileSize(TCHAR* strPath)
{
	unsigned long fileSize;

	HANDLE hFile; 
	hFile = CreateFile( strPath,
						GENERIC_READ,
						FILE_SHARE_READ | FILE_SHARE_WRITE,
						NULL,
						OPEN_EXISTING,
						FILE_ATTRIBUTE_NORMAL,
						NULL); 

	if (hFile == INVALID_HANDLE_VALUE)
		return 0;
	// get the size of file
	fileSize = ::GetFileSize( hFile, NULL );
	CloseHandle(hFile);

	return fileSize;
}

bool CConvert::IsFrameRateSupported(float fps)
{
	if (FLOAT_EQ(fps, 24) || FLOAT_EQ(fps, 25) || 
		FLOAT_EQ(fps, 30) || FLOAT_EQ(fps, 50) || 
		FLOAT_EQ(fps, 60) || FLOAT_EQ(fps, 23.976) ||
		FLOAT_EQ(fps, 29.97) || FLOAT_EQ(fps, 59.94))
	{
		return true;
	}

	return false;
}

HRESULT CConvert::LoadMPEGCodec()
{
	HRESULT hr = CoCreateInstance(CLSID_StandardMpegEncoder, NULL, 
								  CLSCTX_INPROC_SERVER, 
								  IID_IBaseFilter, 
								  (void **)&m_pMPEGWriter);
	
	if (FAILED(hr))
	{
		return hr;
	}

	hr = m_pMPEGWriter->QueryInterface(__uuidof(IStandardMpegEncoder), (void**)&m_pMPEGWriterProps);
	_ASSERT(m_pMPEGWriterProps);
	if (FAILED(hr))
	{
		return hr;
	}

	if (SUCCEEDED(hr))
	{
		m_pMPEGWriterProps->GetSelectedProfile(&m_pMPEGProfile);
	}


	m_pMPEGWriter->QueryInterface(__uuidof(IStandardMpegEncoderStats), (void**) &m_pMPEGStats);

	return hr;
}

HRESULT CConvert::AddNullRenderer(IPin **ppInputPin)
{
	HRESULT hr = CoCreateInstance(CLSID_NullRenderer, NULL, 
								  CLSCTX_INPROC_SERVER, 
								  IID_IBaseFilter, 
								  (void **)&m_pNullRender);
	if (FAILED(hr))
		return hr;

	hr = m_pGraph->AddFilter(m_pNullRender, L"Null Renderer");
	if (FAILED(hr))
		return hr;
	
	hr = m_pBuilder->FindPin(m_pNullRender, PINDIR_INPUT, NULL, NULL, FALSE, 0, ppInputPin);
	return hr;
}

HRESULT CConvert::WaitForCompletion()
{
	long evCode = 0;
	HRESULT hr = m_pEvent->WaitForCompletion(1000, &evCode);
	while (hr == E_ABORT)
	{
		hr = m_pEvent->WaitForCompletion(1000, &evCode);

		if (evCode == EC_COMPLETE ||
			evCode == EC_ERRORABORT  ||
			evCode == EC_USERABORT)
		{
			break;
		}

		TCHAR szProgress[512];
		_stprintf(szProgress, _T("%.2f of %.2f\n"), GetProgress(), GetDuration());
		OutputDebugString(szProgress);
		_tprintf(szProgress);
	}

	return hr;
}


HRESULT CConvert::CreateStill(BSTR strLowRes, BSTR strHighRes, BSTR OutputPath)
{
	/*
	if (m_pMPEGWriterProps == NULL)
		return E_POINTER;

	// get the desktop dc
	HDC hdc = ::GetDC(NULL);

	// create out own dc
	HDC hMemDC = CreateCompatibleDC(hdc);
	
	int nLowWidth = 352;
	int nLowHeight = 288;
	int nHiWidth = 704;
	int nHiHeight = 576;
	switch (m_videoFormat)
	{
	case formatVCD_PAL:	{
			nLowWidth = 352;
			nLowHeight = 288;
		} break;
	case formatVCD_NTSC: {
			nLowWidth = 352;
			nLowHeight = 240;
			nHiHeight = 480;
		} break;
	case formatSVCD_PAL: {
			nLowWidth = 480;
			nLowHeight = 576;
		} break;
	case formatSVCD_NTSC: {
			nLowWidth = 480;
			nLowHeight = 480;
			nHiHeight = 480;
		} break;
	}

	// create two bitmaps, both at the correct sizes
	HBITMAP hbmLowRes = NULL; 
	HBITMAP hbmHiRes  = NULL;

	// try to load the low res picture
	CComPtr<IPicture> pPicture;
	HRESULT hr = ::OleLoadPicturePath(CComBSTR(strLowRes), NULL, 0, 0, IID_IPicture, (void**)&pPicture);
	if (SUCCEEDED(hr))
	{
		// if it succeeds, create an empty bitmap for it
		hbmLowRes = ::CreateCompatibleBitmap(hdc, nLowWidth, nLowHeight);

		// select the bitmap into the mem dc for drawing
		HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hMemDC, hbmLowRes);

		// draw the loaded image on the bitmap, stretching it if neccesary
		// if you wish, you can maintain aspect ratio by making the bitmap
		// black, and then doing some simply arithmetic. Mail me if you need
		// the formula
		OLE_XSIZE_HIMETRIC cy;
		OLE_XSIZE_HIMETRIC cx;
		pPicture->get_Height(&cy);
		pPicture->get_Width(&cx);
		pPicture->Render(hMemDC, 0, nLowHeight, nLowWidth, -nLowHeight, 0, 0, cx, cy, NULL);
		pPicture = NULL;

		::SelectObject(hMemDC, hOldBitmap);
	}

	// try to load the hi res picture
	hr = ::OleLoadPicturePath(CComBSTR(strHighRes), NULL, 0, 0, IID_IPicture, (void**)&pPicture);
	if (SUCCEEDED(hr))
	{
		// if it succeeds, create an empty bitmap for it
		hbmHiRes = ::CreateCompatibleBitmap(hdc, nHiWidth, nHiHeight);

		// select the bitmap into the mem dc for drawing
		HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hMemDC, hbmHiRes);

		// draw the loaded image on the bitmap, stretching it if neccesary
		// if you wish, you can maintain aspect ratio by making the bitmap
		// black, and then doing some simply arithmetic. Mail me if you need
		// the formula
		OLE_XSIZE_HIMETRIC cy;
		OLE_XSIZE_HIMETRIC cx;
		pPicture->get_Height(&cy);
		pPicture->get_Width(&cx);
		pPicture->Render(hMemDC, 0, nHiHeight, nHiWidth, -nHiHeight, 0, 0, cx, cy, NULL);

		pPicture = NULL;
		::SelectObject(hMemDC, hOldBitmap);
	}

	// encode still. This function will block till it is complete. Should take
	// less than 10 seconds, even on the slowest pc
//	hr = m_pMPEGWriterProps->EncodeStillImage(hbmLowRes, hbmHiRes, OutputPath, TRUE, m_videoFormat);
	
//	hr = m_pMPEGWriterProps->EncodeStillImage(NULL, hbmHiRes, OutputPath, TRUE, m_videoFormat);


	// release desktop dc
	ReleaseDC(NULL, hdc);

	return hr;
	*/
	return S_OK;
}

HRESULT CConvert::PauseConversion()
{
	HRESULT hr = E_POINTER;
	if (m_pMediaControl)
	{
		hr = m_pMediaControl->Pause();
		m_bTiming = false;
	}

	return hr;
}

HRESULT CConvert::ResumeConversion()
{
	return Run();
}

bool CConvert::IsURL(BSTR strPath)
{
	if (wcsncmp(strPath, L"mms://", 3) == 0)
		return true;

	if (wcsstr(strPath, L"/") != NULL)
		return true;

	return false;
}


HRESULT CConvert::StartConversionDirect()
{
	StopConversion();
	printf("Initialising conversion...\n");
	m_tStartTime = timeGetTime();

	HRESULT hr = MakeNotificationWindow();
	if (FAILED(hr))
		return hr;

	hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, 
                          NULL, CLSCTX_INPROC_SERVER,
						  IID_ICaptureGraphBuilder2, 
						  (void **)&m_pBuilder);
	
	if (FAILED(hr))
	{
		StopConversion();
		ThrowError(hr, "GraphBuilder could not be created");
		return hr;
	}

	if (wcscmp(m_pSettings->strOutputFile, m_pSettings->strOutputFile) == 0)
	{
		StopConversion();
		ThrowError(E_FAIL, "The source and target files are the same.");
		return E_FAIL;
	}

    hr |= CreateFilterGraph(&m_pGraph);
    if(FAILED(hr))
    {
        StopConversion();
        ThrowError(hr, "Couldn't create filter graph! Please check that DirectX 8 (or higher) is installed");
        return hr;
    }
    
    hr = m_pBuilder->SetFiltergraph(m_pGraph);
	if(FAILED(hr))
    {
        StopConversion();
        ThrowError(hr, "Couldn't create filter graph! Please check that DirectX 8 (or higher) is installed");
        return hr;
    }    
    
	m_pCallback->ConversionConnecting();

    CComPtr<IBaseFilter> pSourceFilter = NULL;
    hr = m_pGraph->AddSourceFilter(m_pSettings->strInputFile, NULL, &pSourceFilter);  
    if (FAILED(hr))
    {
        StopConversion();
        ThrowError(hr, "Failed to render source UROL!");
        return hr;
    }

	if (m_pCallback)
		m_pCallback->ConversionStreaming();

	hr = RenderOutput(m_pBuilder, m_pGraph, NULL, NULL, NULL, NULL, pSourceFilter);


//	PromptForGraph(m_pGraph, "stream");

	if (m_pCallback)
		m_pCallback->ConversionAboutToRun();


	hr = Run();
	
	if(FAILED(hr))
	{
        StopConversion();
		ThrowError(hr, "Could not start streaming!");
		return hr;
	}


    return hr;
}

HRESULT CConvert::SetNoClock(IFilterGraph *graph)
{
    // Keep a useless clock from being instantiated....
    IMediaFilter *graphF;
    HRESULT hr = graph->QueryInterface(IID_IMediaFilter, (void **) &graphF);

    if(SUCCEEDED(hr))
    {
        hr = graphF->SetSyncSource(NULL);
        if (FAILED(hr))
            printf("SetNoClock: Failed to set sync source!  hr=0x%x\n", hr);

        graphF->Release();
    }
    else
    {
        printf("SetNoClock: Failed to QI for media filter!  hr=0x%x\n", hr);
    }

    return hr;
}


HRESULT CConvert::CreateFilterGraph(IGraphBuilder **pGraph)
{
    HRESULT hr;

    hr = CoCreateInstance(CLSID_FilterGraph, // get the graph object
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_IGraphBuilder,
        (void **) pGraph);

    if(FAILED(hr))
    {
        printf("CreateFilterGraph: Failed to create graph!  hr=0x%x\n", hr);
        *pGraph = NULL;
        return hr;
    }

    return S_OK;
}

HRESULT CConvert::FindPinOnFilter( IBaseFilter * pFilter, PIN_DIRECTION PinDir,
						DWORD dwPin, BOOL fConnected, IPin ** ppPin )
{
	HRESULT			hr = S_OK;
	IEnumPins *		pEnumPin = NULL;
	IPin *			pConnectedPin = NULL;
	PIN_DIRECTION	PinDirection;
	ULONG			ulFetched;
	DWORD			nFound = 0;

	_ASSERT( pFilter != NULL );
	*ppPin = NULL;

	hr = pFilter->EnumPins( &pEnumPin );
	if(SUCCEEDED(hr))
	{
		while ( S_OK == ( hr = pEnumPin->Next( 1L, ppPin, &ulFetched ) ) )
		{
			hr = (*ppPin)->ConnectedTo( &pConnectedPin );
			if (pConnectedPin)
			{
				pConnectedPin->Release();
				pConnectedPin = NULL;
			}
			if ( ( ( VFW_E_NOT_CONNECTED == hr ) && !fConnected ) ||
				 ( ( S_OK                == hr ) &&  fConnected ) )
			{
				hr = (*ppPin)->QueryDirection( &PinDirection );
				if ( ( S_OK == hr ) && ( PinDirection == PinDir ) )
				{
					if ( nFound == dwPin ) break;
					nFound++;
				}
			}
			(*ppPin)->Release();
		}
	}
	pEnumPin->Release();
	return hr;
} // FindPinOnFilter



void CConvert::SetLicensed(bool bLicensed)
{
	m_bLicensed = bLicensed;
}

void CConvert::SetSettings(CMPEGSettings* pSettings)
{
	m_pSettings = pSettings;
	m_pSettings->LoadSettingsFromFilter(m_pMPEGWriter);
}

void CConvert::SelectFormat(SystemsOutputFormat sys, Constraint c)
{
	// first, we make the mpeg writer switch the profile it is currently
	// addressing. 
	m_pMPEGWriterProps->SelectFormat(sys, c);

	// then we set the profile we are addressing to the same one
	m_pMPEGProfile = NULL;
	m_pMPEGWriterProps->GetSelectedProfile(&m_pMPEGProfile);

	// in case we had previously set any settings on that profile
	// we reset it back to the default settings
	m_pMPEGProfile->ConfigureForSystemsFormat(sys, c);

	// then we set the writer settings to the same thing
	m_pSettings->LoadSettingsFromFilter(m_pMPEGWriter);
}

long CConvert::GetFramesEncoded(void)
{
	long nFrames = 0;
	m_pMPEGStats->GetFramesEncoded(&nFrames);
	return nFrames;
}

long CConvert::GetWrittenBytes(void)
{
	long nBytes = 0;
	m_pMPEGStats->GetWrittenBytes(&nBytes);
	return nBytes;
}

long CConvert::GetEncodeFramerate(void)
{
	// simplistic fps formula. A more accurate one will
	// be built into the encoder soon

	if (m_pGraph == NULL)
	{
		// if the mpegstats is gone, then we return the average fps
		return (long)((double)GetFramesEncoded() / (double)GetTimeElapsed());
	}
	else
	{
		long n = GetFramesEncoded();
		long fps =  n - m_nLastEncodedFrameCount;
		m_nLastEncodedFrameCount = n;
		return fps;
	}
}

void CConvert::SetShowPreview(bool b)
{
	if (m_pVideoWindow)
	{
		m_pVideoWindow->put_Visible(b?OATRUE:OAFALSE);
	}
}



typedef HRESULT(WINAPI * DIRECTDRAWCREATE)( GUID*, LPDIRECTDRAW*, IUnknown* );
typedef HRESULT(WINAPI * DIRECTDRAWCREATEEX)( GUID*, VOID**, REFIID, IUnknown* );
typedef HRESULT(WINAPI * DIRECTINPUTCREATE)( HINSTANCE, DWORD, LPDIRECTINPUT*,
                                             IUnknown* );




//-----------------------------------------------------------------------------
// Name: GetDXVersion()
// Desc: This function returns the DirectX version number as follows:
//          0x0000 = No DirectX installed
//          0x0100 = DirectX version 1 installed
//          0x0200 = DirectX 2 installed
//          0x0300 = DirectX 3 installed
//          0x0500 = At least DirectX 5 installed.
//          0x0600 = At least DirectX 6 installed.
//          0x0601 = At least DirectX 6.1 installed.
//          0x0700 = At least DirectX 7 installed.
//          0x0800 = At least DirectX 8 installed.
// 
//       Please note that this code is intended as a general guideline. Your
//       app will probably be able to simply query for functionality (via
//       QueryInterface) for one or two components.
//
//       Please also note:
//          "if( dwDXVersion != 0x500 ) return FALSE;" is VERY BAD. 
//          "if( dwDXVersion <  0x500 ) return FALSE;" is MUCH BETTER.
//       to ensure your app will run on future releases of DirectX.
//-----------------------------------------------------------------------------
DWORD GetDXVersion()
{
	/*
    DIRECTDRAWCREATE     DirectDrawCreate   = NULL;
    DIRECTDRAWCREATEEX   DirectDrawCreateEx = NULL;
    DIRECTINPUTCREATE    DirectInputCreate  = NULL;
    HINSTANCE            hDDrawDLL          = NULL;
    HINSTANCE            hDInputDLL         = NULL;
    HINSTANCE            hD3D8DLL           = NULL;
    HINSTANCE            hDPNHPASTDLL       = NULL;
    LPDIRECTDRAW         pDDraw             = NULL;
    LPDIRECTDRAW2        pDDraw2            = NULL;
    LPDIRECTDRAWSURFACE  pSurf              = NULL;
    LPDIRECTDRAWSURFACE3 pSurf3             = NULL;
    LPDIRECTDRAWSURFACE4 pSurf4             = NULL;
    DWORD                dwDXVersion        = 0;
    HRESULT              hr;

    // First see if DDRAW.DLL even exists.
    hDDrawDLL = LoadLibrary( "DDRAW.DLL" );
    if( hDDrawDLL == NULL )
    {
        dwDXVersion = 0;
        OutputDebugString( "Couldn't LoadLibrary DDraw\r\n" );
        return dwDXVersion;
    }

    // See if we can create the DirectDraw object.
    DirectDrawCreate = (DIRECTDRAWCREATE)GetProcAddress( hDDrawDLL, "DirectDrawCreate" );
    if( DirectDrawCreate == NULL )
    {
        dwDXVersion = 0;
        FreeLibrary( hDDrawDLL );
        OutputDebugString( "Couldn't GetProcAddress DirectDrawCreate\r\n" );
        return dwDXVersion;
    }

    hr = DirectDrawCreate( NULL, &pDDraw, NULL );
    if( FAILED(hr) )
    {
        dwDXVersion = 0;
        FreeLibrary( hDDrawDLL );
        OutputDebugString( "Couldn't create DDraw\r\n" );
        return dwDXVersion;
    }

    // So DirectDraw exists.  We are at least DX1.
    dwDXVersion = 10;

    // Let's see if IID_IDirectDraw2 exists.
    hr = pDDraw->QueryInterface( IID_IDirectDraw2, (VOID**)&pDDraw2 );
    if( FAILED(hr) )
    {
        // No IDirectDraw2 exists... must be DX1
        pDDraw->Release();
        FreeLibrary( hDDrawDLL );
        OutputDebugString( "Couldn't QI DDraw2\r\n" );
        return dwDXVersion;
    }

    // IDirectDraw2 exists. We must be at least DX2
    pDDraw2->Release();
    dwDXVersion = 20;


	//-------------------------------------------------------------------------
    // DirectX 3.0 Checks
	//-------------------------------------------------------------------------

    // DirectInput was added for DX3
    hDInputDLL = LoadLibrary( "DINPUT.DLL" );
    if( hDInputDLL == NULL )
    {
        // No DInput... must not be DX3
        pDDraw->Release();
        FreeLibrary( hDDrawDLL );
        OutputDebugString( "Couldn't LoadLibrary DInput\r\n" );
        return dwDXVersion;
    }

    DirectInputCreate = (DIRECTINPUTCREATE)GetProcAddress( hDInputDLL,
                                                        "DirectInputCreateA" );
    if( DirectInputCreate == NULL )
    {
        // No DInput... must be DX2
        FreeLibrary( hDInputDLL );
        pDDraw->Release();
        FreeLibrary( hDDrawDLL );
        OutputDebugString( "Couldn't GetProcAddress DInputCreate\r\n" );
        return dwDXVersion;
    }

    // DirectInputCreate exists. We are at least DX3
    dwDXVersion = 30;
    FreeLibrary( hDInputDLL );

    // Can do checks for 3a vs 3b here


	//-------------------------------------------------------------------------
    // DirectX 5.0 Checks
	//-------------------------------------------------------------------------

    // We can tell if DX5 is present by checking for the existence of
    // IDirectDrawSurface3. First, we need a surface to QI off of.
    DDSURFACEDESC ddsd;
    ZeroMemory( &ddsd, sizeof(ddsd) );
    ddsd.dwSize         = sizeof(ddsd);
    ddsd.dwFlags        = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

    hr = pDDraw->SetCooperativeLevel( NULL, DDSCL_NORMAL );
    if( FAILED(hr) )
    {
        // Failure. This means DDraw isn't properly installed.
        pDDraw->Release();
        FreeLibrary( hDDrawDLL );
        dwDXVersion = 0;
        OutputDebugString( "Couldn't Set coop level\r\n" );
        return dwDXVersion;
    }

    hr = pDDraw->CreateSurface( &ddsd, &pSurf, NULL );
    if( FAILED(hr) )
    {
        // Failure. This means DDraw isn't properly installed.
        pDDraw->Release();
        FreeLibrary( hDDrawDLL );
        dwDXVersion = 0;
        OutputDebugString( "Couldn't CreateSurface\r\n" );
        return dwDXVersion;
    }

    // Query for the IDirectDrawSurface3 interface
    if( FAILED( pSurf->QueryInterface( IID_IDirectDrawSurface3,
                                       (VOID**)&pSurf3 ) ) )
    {
        pSurf->Release();
        pDDraw->Release();
        FreeLibrary( hDDrawDLL );
        OutputDebugString( "Couldn't QI DDS3\r\n" );
        return dwDXVersion;
    }

    // QI for IDirectDrawSurface3 succeeded. We must be at least DX5
    dwDXVersion = 50;
    pSurf3->Release();


	//-------------------------------------------------------------------------
    // DirectX 6.0 Checks
	//-------------------------------------------------------------------------

    // The IDirectDrawSurface4 interface was introduced with DX 6.0
    if( FAILED( pSurf->QueryInterface( IID_IDirectDrawSurface4,
                                       (VOID**)&pSurf4 ) ) )
    {
        pSurf->Release();
        pDDraw->Release();
        FreeLibrary( hDDrawDLL );
        OutputDebugString( "Couldn't QI DDS4\r\n" );
        return dwDXVersion;
    }

    // IDirectDrawSurface4 was create successfully. We must be at least DX6
    dwDXVersion = 60;
    pSurf4->Release();
    pSurf->Release();
    pDDraw->Release();


	//-------------------------------------------------------------------------
    // DirectX 6.1 Checks
	//-------------------------------------------------------------------------

    // Check for DMusic, which was introduced with DX6.1
    LPDIRECTMUSIC pDMusic = NULL;
    CoInitialize( NULL );
    hr = CoCreateInstance( CLSID_DirectMusic, NULL, CLSCTX_INPROC_SERVER,
                           IID_IDirectMusic, (VOID**)&pDMusic );
    if( FAILED(hr) )
    {
        FreeLibrary( hDDrawDLL );
        OutputDebugString( "Couldn't create CLSID_DirectMusic\r\n" );
        return dwDXVersion;
    }

    // DirectMusic was created successfully. We must be at least DX6.1
    dwDXVersion = 61;
    pDMusic->Release();
    CoUninitialize();
    

	//-------------------------------------------------------------------------
    // DirectX 7.0 Checks
	//-------------------------------------------------------------------------

    // Check for DirectX 7 by creating a DDraw7 object
    LPDIRECTDRAW7 pDD7;
    DirectDrawCreateEx = (DIRECTDRAWCREATEEX)GetProcAddress( hDDrawDLL,
                                                       "DirectDrawCreateEx" );
    if( NULL == DirectDrawCreateEx )
    {
        FreeLibrary( hDDrawDLL );
        OutputDebugString( "Couldn't GetProcAddress DirectDrawCreateEx\r\n" );
        return dwDXVersion;
    }

    if( FAILED( DirectDrawCreateEx( NULL, (VOID**)&pDD7, IID_IDirectDraw7,
                                    NULL ) ) )
    {
        FreeLibrary( hDDrawDLL );
        OutputDebugString( "Couldn't DirectDrawCreateEx\r\n" );
        return dwDXVersion;
    }

    // DDraw7 was created successfully. We must be at least DX7.0
    dwDXVersion = 70;
    pDD7->Release();


	//-------------------------------------------------------------------------
    // DirectX 8.0 Checks
	//-------------------------------------------------------------------------

    // Simply see if D3D8.dll exists.
    hD3D8DLL = LoadLibrary( "D3D8.DLL" );
    if( hD3D8DLL == NULL )
    {
	    FreeLibrary( hDDrawDLL );
        OutputDebugString( "Couldn't LoadLibrary D3D8.DLL\r\n" );
        return dwDXVersion;
    }

    // D3D8.dll exists. We must be at least DX8.0
    dwDXVersion = 80;


	//-------------------------------------------------------------------------
    // DirectX 8.1 Checks
	//-------------------------------------------------------------------------

    // Simply see if dpnhpast.dll exists.
    hDPNHPASTDLL = LoadLibrary( "dpnhpast.dll" );
    if( hDPNHPASTDLL == NULL )
    {
	    FreeLibrary( hDPNHPASTDLL );
        OutputDebugString( "Couldn't LoadLibrary dpnhpast.dll\r\n" );
        return dwDXVersion;
    }

    // dpnhpast.dll exists. We must be at least DX8.1
    dwDXVersion = 81;


	//-------------------------------------------------------------------------
    // End of checking for versions of DirectX 
	//-------------------------------------------------------------------------

    // Close open libraries and return
    FreeLibrary( hDDrawDLL );
    FreeLibrary( hD3D8DLL );
    
    return dwDXVersion;
	*/
	return 9;
}

