// DESEdit.cpp: Implementierung der Klasse CDESEdit.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VideoEdit.h"
#include "videoeditobj.h"
#include "mediafile.h"
#include "MediaFileList.h"
#include "DESEdit.h"

#define WM_GRAPHNOTIFY WM_APP + 13
#define WM_MPEGNOTIFY WM_APP + 20

// initguid to prevent unresolved external when adding guids
#include <initguid.h>

// CLSIDs
#include "..\StandardMPEGEncoderUIDs.h"


//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CDESEdit::CDESEdit(CVideoEditObj* pCallback) : m_pCallback(pCallback)
{
	
	m_systemsFormat = SYSTEMSFORMAT_MPEG1;
	m_constraint = CONSTRAINT_NONE;
	m_videoFormat = VIDEOFORMAT_MPEG1;
	m_audioFormat = AUDIOFORMAT_MP2;
	
	m_fOutputFPS = 0;
	m_nOutputWidth = 320;
	m_nOutputHeight = 240;
	m_dFadeInLength = 2;
	m_dFadeOutLength = 2;
	
	_ASSERT(m_wndNotify.IsWindow() == FALSE);
	m_wndNotify.SetDrainFunction(NotifyFunc, (long)this);
	RECT rect;
	rect.left = 0; rect.top = 0; rect.right = 5; rect.bottom = 5;
	m_wndNotify.Create(NULL, rect, _T("NotifyWnd"), WS_POPUP);
	_ASSERT(m_wndNotify.IsWindow());

}

CDESEdit::~CDESEdit()
{
	if (m_wndNotify.IsWindow())
		m_wndNotify.DestroyWindow();
}

BOOL CDESEdit::NotifyFunc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, long pClass)
{
	CDESEdit* pThis = (CDESEdit*)pClass;
	_ASSERT(pThis);

	BOOL bResult = FALSE;
	switch(uMsg)
	{
	case WM_GRAPHNOTIFY:
		pThis->HandleEvent();
		CHelper::Trace("pThis->HandleEvent() called\n");
		return FALSE;
		break;
	case WM_APP + 30:
		CHelper::Trace("WM_APP + 30\n");
		switch (wParam)
		{
		case EC_COMPLETE:
			pThis->Stop();
			break;
		}
		break;
	}

	return bResult;
}

HRESULT CDESEdit::HandleEvent()
{
	HRESULT hr;
	long evCode, param1, param2;
    
    while (m_pEvent && (hr = m_pEvent->GetEvent(&evCode, &param1, &param2, 0)), SUCCEEDED(hr))
    { 
		if (m_pEvent == NULL)
			return E_POINTER;

        hr = m_pEvent->FreeEventParams(evCode, param1, param2);
		
		if ((EC_COMPLETE == evCode) || (EC_USERABORT == evCode))
        {
			Stop();
			CHelper::Trace("CDESEdit::HandleEvent\n");
			return S_FALSE; // Stop destroys objects, so return immediately
        }
    } 
	
	return hr;
}


HRESULT CDESEdit::ConstructGraph(CMediaFileList *pMediaList, long format)
{
	HRESULT hr;
	
	CHelper::Trace("ConstructGraph\n");

	DestroyGraph();
	
//	m_videoFormat = format;
	ApplyVideoFormatSettings();

	pMediaList->VerifyVisualMediaOffsets();

	
	double dDuration = pMediaList->GetCurrentAudioLength();

	hr = CoCreateInstance(CLSID_CaptureGraphBuilder, 
                          NULL, CLSCTX_INPROC_SERVER,
						  IID_ICaptureGraphBuilder, 
						  (void **)&m_pBuilder);
	
	if (FAILED(hr))
	{
		DestroyGraph();
		return hr;
	}

    // make the timeline
    hr = CoCreateInstance(CLSID_AMTimeline, 
                         NULL, 
                         CLSCTX_INPROC_SERVER, 
                         IID_IAMTimeline, 
                         (void**) &m_pTimeline);

    if(FAILED( hr )) {
		DestroyGraph();
        return hr;
    }

    // make the root group/composition
    hr = m_pTimeline->CreateEmptyNode( &m_pVideoGroupObj, TIMELINE_MAJOR_TYPE_GROUP );
    if(FAILED( hr )) 
    {
        DestroyGraph();
        return hr;
    }
	
	hr = m_pTimeline->CreateEmptyNode( &m_pAudioGroupObj, TIMELINE_MAJOR_TYPE_GROUP );
    if(FAILED( hr )) 
    {
        DestroyGraph();
        return hr;
    }

	CComQIPtr< IAMTimelineGroup, &IID_IAMTimelineGroup > pVideoGroup( m_pVideoGroupObj );
    
	CMediaType VideoGroupType;
	VideoGroupType.SetType( &MEDIATYPE_Video);
	VideoGroupType.SetSubtype(&MEDIASUBTYPE_RGB32);
	VideoGroupType.SetFormatType(&FORMAT_VideoInfo);
	
	VIDEOINFOHEADER *pVideoHeader = (VIDEOINFOHEADER*)VideoGroupType.AllocFormatBuffer(sizeof(VIDEOINFOHEADER));
	ZeroMemory(pVideoHeader, sizeof(VIDEOINFOHEADER));
	
	pVideoHeader->bmiHeader.biWidth = m_nOutputWidth;
	pVideoHeader->bmiHeader.biHeight = m_nOutputHeight;

	pVideoHeader->bmiHeader.biBitCount = 32;
	pVideoHeader->bmiHeader.biPlanes = 1;
	pVideoHeader->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pVideoHeader->bmiHeader.biSizeImage = DIBSIZE(pVideoHeader->bmiHeader);

	VideoGroupType.SetSampleSize(DIBSIZE(pVideoHeader->bmiHeader));

    // all we set is the major type. The group will automatically use other defaults
    
    hr = pVideoGroup->SetMediaType( &VideoGroupType );
    if(FAILED( hr )) 
    {
        DestroyGraph();
        return hr;
    }
		
	CComQIPtr< IAMTimelineGroup, &IID_IAMTimelineGroup > pAudioGroup( m_pAudioGroupObj );
    CMediaType AudioGroupType;

    // all we set is the major type. The group will automatically use other defaults
    AudioGroupType.SetType( &MEDIATYPE_Audio);
    hr = pAudioGroup->SetMediaType( &AudioGroupType );
    if(FAILED( hr )) 
    {
        DestroyGraph();
        return hr;
    }
	
	pVideoGroup->SetOutputFPS(m_fOutputFPS);

	//--------------------------------------------
    // add the group to the timeline
    //--------------------------------------------

    hr = m_pTimeline->AddGroup( m_pVideoGroupObj );
	hr = m_pTimeline->AddGroup( m_pAudioGroupObj );
    if(FAILED( hr )) 
    {
        DestroyGraph();
        return hr;
    }
//---------------------------------------------------------------------------		
	// Commented by FHI
	// This portion is not needed here because in order to render two
	// effects and one transition at the same time, we need to wrap each
	// track into its own composite, which would further be enclosed into 
	// the main video group
/*
    // make a track. A track contains a uniform meduia type

    CComPtr< IAMTimelineObj > pTrackVideoObj;
    hr = m_pTimeline->CreateEmptyNode( &pTrackVideoObj, TIMELINE_MAJOR_TYPE_TRACK );
    if(FAILED( hr )) 
    {
        DestroyGraph();
        return hr;
    }
	
	CComPtr< IAMTimelineObj > pTrackVideoObjAlt;
    hr = m_pTimeline->CreateEmptyNode( &pTrackVideoObjAlt, TIMELINE_MAJOR_TYPE_TRACK );
    if(FAILED( hr )) 
    {
        DestroyGraph();
        return hr;
    }


    // tell the composition about the track

    CComQIPtr< IAMTimelineComp, &IID_IAMTimelineComp > pRootComp( m_pVideoGroupObj );
    hr = pRootComp->VTrackInsBefore( pTrackVideoObj, 0 );
    if(FAILED( hr )) 
    {
        DestroyGraph();
        return hr;
    }
	
	// insert second video track with lower priority
	hr = pRootComp->VTrackInsBefore(pTrackVideoObjAlt, 1 );
    if(FAILED( hr )) 
    {
        DestroyGraph();
        return hr;
    }
//*/
//---------------------------------------------------------------------------		
	CComPtr< IAMTimelineObj > pTrackAudioObj;
    hr = m_pTimeline->CreateEmptyNode( &pTrackAudioObj, TIMELINE_MAJOR_TYPE_TRACK );
    if(FAILED( hr )) 
    {
        DestroyGraph();
        return hr;
    }

	CComQIPtr< IAMTimelineComp, &IID_IAMTimelineComp > pAudioComp( m_pAudioGroupObj );
    hr = pAudioComp->VTrackInsBefore( pTrackAudioObj, -1 );
    if(FAILED( hr )) 
    {
        DestroyGraph();
        return hr;
    }

//---------------------------------------------------------------------------		
	// Modified by FHI
	// Since each track is wrapped in its own composite, we only need to provide
	// a pointer to the main video group to the InsertVideoClips function and 
	// the rest will be done by the function itself
/*
	hr = InsertVideoClips(pMediaList, pTrackVideoObj, pTrackVideoObjAlt);
//*/
  CComQIPtr< IAMTimelineComp, &IID_IAMTimelineComp > pRootComp( m_pVideoGroupObj );
	hr = InsertVideoClips(pMediaList, pRootComp);
//*/
//---------------------------------------------------------------------------		
	ASSERT(!FAILED(hr));

	hr = InsertAudioClips(pMediaList, pTrackAudioObj);
	ASSERT(!FAILED(hr));

	   //----------------------------------------------
    // make sure files are in their correct location
    //----------------------------------------------
    
    hr = m_pTimeline->ValidateSourceNames( 
        SFN_VALIDATEF_CHECK | SFN_VALIDATEF_POPUP | SFN_VALIDATEF_REPLACE, 
        NULL, 
        0 );
    ASSERT( !FAILED( hr ) );

    //--------------------------------------------
    // create the render engine
    //--------------------------------------------

    hr = CoCreateInstance(
                         CLSID_RenderEngine,
                         NULL,
                         CLSCTX_INPROC_SERVER,
                         IID_IRenderEngine,
                         (void**) &m_pRenderEngine );
    ASSERT( !FAILED( hr ) );

    // tell the render engine about the timeline it should look at
    //
    hr = m_pRenderEngine->SetTimelineObject( m_pTimeline );
    ASSERT( !FAILED( hr ) );

    //--------------------------------------------
    // connect up the front end, then the back end
    //--------------------------------------------

    hr = m_pRenderEngine->ConnectFrontEnd( );
	hr = m_pRenderEngine->GetFilterGraph( &m_pGraph );
	hr = m_pBuilder->SetFiltergraph(m_pGraph);

    return hr;
}

HRESULT CDESEdit::SaveGraphFile(IGraphBuilder *pGraph, WCHAR *wszPath) 
{
    const WCHAR wszStreamName[] = L"ActiveMovieGraph"; 
    HRESULT hr;
    
    IStorage *pStorage = NULL;
    hr = StgCreateDocfile(
        wszPath,
        STGM_CREATE | STGM_TRANSACTED | STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
        0, &pStorage);
    if(FAILED(hr)) 
    {
        return hr;
    }

    IStream *pStream;
    hr = pStorage->CreateStream(
        wszStreamName,
        STGM_WRITE | STGM_CREATE | STGM_SHARE_EXCLUSIVE,
        0, 0, &pStream);
    if (FAILED(hr)) 
    {
        pStorage->Release();    
        return hr;
    }

    IPersistStream *pPersist = NULL;
    pGraph->QueryInterface(IID_IPersistStream, reinterpret_cast<void**>(&pPersist));
    hr = pPersist->Save(pStream, TRUE);
    pStream->Release();
    pPersist->Release();
    if (SUCCEEDED(hr)) 
    {
        hr = pStorage->Commit(STGC_DEFAULT);
    }
    pStorage->Release();
    return hr;
}


HRESULT CDESEdit::Preview(long ParentHwnd, long x, long y, long width, long height)
{
	CHelper::Trace("PreviewEntered. About to call stop\n");

	Stop();

	CHelper::Trace("Stop called. About to render preview pins\n");

	HRESULT hr = 0;
	hr = m_pRenderEngine->RenderOutputPins();

	CHelper::Trace("RenderOutputPins. Hr=%lu\n", hr);

	hr |= m_pGraph->QueryInterface( IID_IMediaEvent,   (void**) &m_pEvent );
    hr |= m_pGraph->QueryInterface( IID_IMediaControl, (void**) &m_pMediaControl );
	hr |= m_pGraph->QueryInterface( IID_IMediaSeeking, (void**) &m_pSeeking );
    hr |= m_pGraph->QueryInterface( IID_IVideoWindow,  (void**) &m_pVideoWindow);

	if (m_pEvent)
		hr = m_pEvent->SetNotifyWindow((OAHWND)m_wndNotify.m_hWnd, WM_GRAPHNOTIFY, 0);

	if (m_pVideoWindow)
	{
		m_pVideoWindow->put_Owner(ParentHwnd);
		m_pVideoWindow->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
		m_pVideoWindow->SetWindowPosition(x, y, width, height);
	}
	
	//SaveGraphFile(m_pGraph, L"c:\\videdit_debug.grf");

	CHelper::Trace("About to run. hr=%lu\n", hr);

	m_pCallback->Fire_AboutToRun();
	hr = m_pMediaControl->Run();

	CHelper::Trace("Run. hr=%lu\n", hr);

	return hr;
}

void CDESEdit::DestroyGraph()
{
	Stop();

	if (m_pRenderEngine)
		m_pRenderEngine->ScrapIt();

	m_pRenderEngine = NULL;
    m_pTimeline = NULL;
    m_pVideoGroupObj = NULL;
    m_pAudioGroupObj = NULL;
	m_pSrcFilter = NULL;
	m_pGraph = NULL;
	m_pFileWriter = NULL;
	m_pBuilder = NULL;
	
	CHelper::Trace("DestroyGraph()\n");
}


//---------------------------------------------------------------------------		
// Modified by FHI - October 24, 
// the funcction need only one pRootComp group, see the comment written 
// with the use of this function for more details.

HRESULT CDESEdit::InsertVideoClips(CMediaFileList *pMediaList, IAMTimelineComp * pRootComp)
{
	HRESULT hr = S_OK;

	double dStartOffset = 0;
	for (int i=0;i<pMediaList->GetVideoFileCount();i++)
	{
		// overlay text, generate multiple bitmaps
		((CMediaFile*)(pMediaList->GetVideoItem(i)))->SetCallback(m_pCallback);

		double dEndTransition = 0;
		double dStartTransition = 0;
		double dDuration = 0;

		pMediaList->GetVideoItem(i)->get_Duration(&dDuration);
	
		CComBSTR strStartTransition = "";
		CComBSTR strEndTransition = "";

		if (i == 0) // first item, no transition
		{			
			pMediaList->GetVideoItem(i)->get_TransitionLength(&dStartTransition);
			pMediaList->GetVideoItem(i)->get_Transition(&strStartTransition);
			
			//dStartOffset = 2;
		}
		else
		{	
			pMediaList->GetVideoItem(i-1)->get_TransitionLength(&dEndTransition);
			pMediaList->GetVideoItem(i-1)->get_Transition(&strEndTransition);
		
			pMediaList->GetVideoItem(i)->get_TransitionLength(&dStartTransition);
			pMediaList->GetVideoItem(i)->get_Transition(&strStartTransition);
			
			dStartOffset -= dEndTransition;
		}

		REFERENCE_TIME rtStart = (REFERENCE_TIME)(dStartOffset * UNITS);
		REFERENCE_TIME rtStop = (REFERENCE_TIME)((dStartOffset + dDuration) * UNITS);
		
		// set the start offset for the next image. The offset is never used again
		// till the next iteration.
		dStartOffset += dDuration;
		
		//----------------------------------------------------------------------
		// Modified by FHI - October 24, 
		// Here we create a composite for each video track so that one composite
		// contains only one track and that track contains only one source

		// Create a new composition. There will be several compositions, one for
		// each source file
		CComPtr<IAMTimelineObj> pComp; 
		hr = m_pTimeline->CreateEmptyNode(&pComp, TIMELINE_MAJOR_TYPE_COMPOSITE);
		if(FAILED( hr )) 
		{
			DestroyGraph();
			return hr;
		}

		// add the composition to the root composition. Each following
		// composition is one higher in the priority scale than the others
		hr = pRootComp->VTrackInsBefore(pComp, i);
		if(FAILED( hr )) 
		{
			DestroyGraph();
			return hr;
		}

		// retrieve the interface from the comp
		CComQIPtr<IAMTimelineComp, &IID_IAMTimelineComp> pCompVideo(pComp);
		
		// create source object
		CComPtr<IAMTimelineObj> pSourceVideoObj;	
		hr = m_pTimeline->CreateEmptyNode(&pSourceVideoObj, TIMELINE_MAJOR_TYPE_SOURCE );
		if(FAILED( hr )) 
		{
			break;
		}

		// get source path of this file
		CComBSTR strSourceFile;
		pMediaList->GetVideoItem(i)->get_FilePath(&strSourceFile);
		
		// set the start time and stop time of this source object,
		// relative to the entire timeline
		hr = pSourceVideoObj->SetStartStop( rtStart, rtStop);
		CComQIPtr< IAMTimelineSrc, &IID_IAMTimelineSrc > pSourceVideoSrc( pSourceVideoObj );
		
		// set the media time, which is just the length relative to its 'real' length
		hr |= pSourceVideoSrc->SetMediaTimes( 0, (REFERENCE_TIME)(dDuration * UNITS) );
		hr |= pSourceVideoSrc->SetMediaName( strSourceFile );
		hr |= pSourceVideoSrc->SetStretchMode( RESIZEF_STRETCH );
		if(FAILED( hr )) 
		{
			return hr;
		}

		//---------------------------------------------------------------------------		
		// Added by FHI - October 24, 
		// Here we create a track, insert it into its composite and then insert the 
		// source into it.
		
		// Insert a track into the composition. Each composition has a single track
		CComPtr<IAMTimelineObj> pTrackVideoObj;
		hr = m_pTimeline->CreateEmptyNode( &pTrackVideoObj, TIMELINE_MAJOR_TYPE_TRACK );
		CComQIPtr< IAMTimelineTrack, &IID_IAMTimelineTrack > pTrackVideo(pTrackVideoObj);
		pCompVideo->VTrackInsBefore(pTrackVideoObj, 0);
		

		// add the source to the track
		hr = pTrackVideo->SrcAdd( pSourceVideoObj );
		if(FAILED( hr )) 
		{
			return hr;
		}
		
		// add a track with a fixed color
		int nLast = pMediaList->GetVideoFileCount() - 1;
		if (i == 0 || i == nLast)
		{
			AddFadeTrack(pCompVideo, i == 0, i == nLast, rtStart, rtStop);
		}


		// Apply efffect
		CMediaFile::MotionInfo& motionInfo = ((CMediaFile*)pMediaList->GetVideoItem(i))->GetMotionInfo(m_nOutputWidth, m_nOutputHeight);
		if (motionInfo.bPerformMotion)
		{
			// make sure you use the latest compile of motion.dll in which the 
			// issue of data sharing of static variables among all instances is
			// resolved
			// FHI - October 24, 
			CComBSTR strEffect = L"{4AE66E7E-A9FB-4EB3-B173-9F7E86CE6841}";
			GUID guidEffect;
			hr = CLSIDFromString(strEffect, &guidEffect);

			CComPtr<IPropertySetter> pProp;
			pProp.CoCreateInstance(CLSID_PropertySetter);

			AddLongParam(pProp, L"StartLeft", motionInfo.rcStart.left);
			AddLongParam(pProp, L"StartTop", motionInfo.rcStart.top);
			AddLongParam(pProp, L"StartWidth", motionInfo.rcStart.right - motionInfo.rcStart.left);
			AddLongParam(pProp, L"StartHeight", motionInfo.rcStart.bottom - motionInfo.rcStart.top);
			AddLongParam(pProp, L"EndLeft", motionInfo.rcEnd.left);
			AddLongParam(pProp, L"EndTop", motionInfo.rcEnd.top);
			AddLongParam(pProp, L"EndWidth", motionInfo.rcEnd.right - motionInfo.rcEnd.left);
			AddLongParam(pProp, L"EndHeight", motionInfo.rcEnd.bottom - motionInfo.rcEnd.top);

			CComPtr<IAMTimelineObj> pEffectObj;
			hr = m_pTimeline->CreateEmptyNode(&pEffectObj, TIMELINE_MAJOR_TYPE_EFFECT);
			if (SUCCEEDED(hr))
			{
				hr = S_OK;
				hr |= pEffectObj->SetSubObjectGUID(guidEffect);

				//---------------------------------------------------------------------------		
				// Modified by FHI - October 24, 
				// We should not use (rStart + (dStartTransition * UNITS)) otherwise
				// the second effect will start only after the transition is complete

				hr |= pEffectObj->SetStartStop(rtStart, rtStop);
				//---------------------------------------------------------------------------		
				
				hr |= pEffectObj->SetPropertySetter(pProp);

				if (SUCCEEDED(hr))
				{
					CComPtr<IAMTimelineEffectable> pEffectable  = NULL;
					hr = pTrackVideo->QueryInterface(IID_IAMTimelineEffectable, (void **)&pEffectable);
					hr = pEffectable->EffectInsBefore(pEffectObj, -1);
				}
			}
		}

		// apply transition after all bitmaps added
		//---------------------------------------------------------------------------		
		// Modified by FHI - October 24, 
		// Here I have made a little change in the structure of the DES timeline
		// I have eliminated the end transition. Rather the end transition of any
		// given composite is the START transition of the next composite. The old method
		// is useful if we are to alternate between two tracks only. But now we are 
		// applying transition to as many composites as there are sources.

		if (wcscmp(strStartTransition, L"") != 0 && i != 0 && pMediaList->GetVideoFileCount() > 1)
		{
			// create a transition guid from the transition string
			GUID guidStartTransition;
			hr = CLSIDFromString(strStartTransition, &guidStartTransition);

			if (SUCCEEDED(hr))
			{
				// create a transition object
				CComPtr<IAMTimelineObj> pTransObjStart;
				hr = m_pTimeline->CreateEmptyNode(&pTransObjStart, TIMELINE_MAJOR_TYPE_TRANSITION);
				if (SUCCEEDED(hr))
				{
					hr = S_OK;

					// set the object guid
					hr |= pTransObjStart->SetSubObjectGUID(guidStartTransition);
					
					// set the time at which the transition starts, and when it ends
					// the transition always has to overlap with an object.
					hr |= pTransObjStart->SetStartStop(rtStart, rtStart + (REFERENCE_TIME)(dStartTransition * UNITS));
					
					//CComPtr<IAMTimelineTrans> pTrans;
					//hr = pTransObjStart->QueryInterface(IID_IAMTimelineTrans, (void **)&pTrans);
					//pTrans->SetSwapInputs(FALSE);

					
					if (SUCCEEDED(hr))
					{
						CComPtr<IAMTimelineTransable> pTransable = NULL;
						
						//---------------------------------------------------------------------------		
						// Modified by FHI - October 24, 
						// The most important point - we apply a transition to the composite and 
						// not the track

						hr = pCompVideo->QueryInterface(IID_IAMTimelineTransable, (void **)&pTransable);

						//---------------------------------------------------------------------------		
						hr = pTransable->TransAdd(pTransObjStart);

					} // if
				} // if (SUCCEEDED(hr))
			} // if (SUCCEEDED(hr))
		} // if (wcscmp(
	} // for

	return S_OK;
}

HRESULT CDESEdit::InsertAudioClips(CMediaFileList *pMediaList, IAMTimelineObj* pTrackAudioObj)
{
	for (int i=0;i<pMediaList->GetAudioFileCount();i++)
	{
		CComPtr<IAMTimelineObj> pSourceAudioObj;
		HRESULT hr = m_pTimeline->CreateEmptyNode( &pSourceAudioObj, TIMELINE_MAJOR_TYPE_SOURCE );
		if(FAILED( hr )) 
		{
			return hr;
		}
		
		CComBSTR strSourceFile;
		pMediaList->GetAudioItem(i)->get_FilePath(&strSourceFile);
		
		double dDuration = 0;
		double dStart = 0;
		pMediaList->GetAudioItem(i)->get_StartOffset(&dStart);
		pMediaList->GetAudioItem(i)->get_Duration(&dDuration);

		REFERENCE_TIME rtStart = (REFERENCE_TIME)(dStart * UNITS);
		REFERENCE_TIME rtStop = (REFERENCE_TIME)((dStart + dDuration) * UNITS);

		hr = pSourceAudioObj->SetStartStop( rtStart, rtStop );
		CComQIPtr< IAMTimelineSrc, &IID_IAMTimelineSrc > pSourceAudioSrc( pSourceAudioObj );
		hr |= pSourceAudioSrc->SetMediaTimes( 0, (REFERENCE_TIME)(dDuration * UNITS) );
		hr |= pSourceAudioSrc->SetMediaName( strSourceFile );
		if(FAILED( hr )) 
		{
			return hr;
		}

		CComQIPtr< IAMTimelineTrack, &IID_IAMTimelineTrack > pTrackAudio( pTrackAudioObj );
		hr = pTrackAudio->SrcAdd( pSourceAudioObj );
		if(FAILED( hr )) 
		{
			return hr;
		}
	}

	return S_OK;
}

void CDESEdit::Stop()
{
	CHelper::Trace("Stop\n");

	if (m_pMediaControl)
		m_pMediaControl->Stop();

	if (m_pEvent)
	{
		m_pEvent->SetNotifyFlags(AM_MEDIAEVENT_NONOTIFY);
		m_pEvent->SetNotifyWindow(NULL, WM_GRAPHNOTIFY, 0);
		m_pEvent = NULL;
	}

	m_pSeeking = NULL;
	m_pMediaControl = NULL;
	m_pMPEGWriter = NULL;
	m_pIMPEGEncoder = NULL;
	m_pIMPEGEncoderProfile = NULL;

	if (m_pVideoWindow)
    {
        m_pVideoWindow->put_Visible(OAFALSE);
        m_pVideoWindow->put_Owner(NULL);
		m_pVideoWindow = NULL;

		m_pCallback->Fire_Complete();
    }

	CHelper::Trace("Stop complete\n");
}

double CDESEdit::GetProgress()
{
	if (m_pSeeking)
	{
		LONGLONG ll = 0;
		m_pSeeking->GetCurrentPosition(&ll);
		return (double)((double)ll / (double)UNITS);
    }

	return 0;
}

double CDESEdit::GetDuration()
{
	if (m_pSeeking)
	{
		LONGLONG ll = 0;
		m_pSeeking->GetDuration(&ll);
		return (double)(ll / UNITS);
	}
	
	return 0;
}

HRESULT CDESEdit::OutputToFile(BSTR strFilePath)
{
	Stop();

//	USES_CONVERSION;
	DeleteFileW(strFilePath);

	HRESULT hr;
	hr |= m_pGraph->QueryInterface( IID_IMediaEvent,   (void**) &m_pEvent );
    hr |= m_pGraph->QueryInterface( IID_IMediaControl, (void**) &m_pMediaControl );
    hr |= m_pGraph->QueryInterface( IID_IVideoWindow,  (void**) &m_pVideoWindow);

	if (m_pEvent)
		hr = m_pEvent->SetNotifyWindow((OAHWND)m_wndNotify.m_hWnd, WM_GRAPHNOTIFY, 0);

	hr = InsertMPEGCodec(strFilePath);
	
//	hr |= m_pGraph->QueryInterface( IID_IMediaSeeking, (void**) &m_pSeeking );

	CComPtr<IPin> pVideoOutPin;
	CComPtr<IPin> pAudioOutPin;
	
	hr = m_pRenderEngine->GetGroupOutputPin(0, &pVideoOutPin);
	hr = m_pRenderEngine->GetGroupOutputPin(1, &pAudioOutPin);

	try	{
		hr = m_pBuilder->RenderStream(NULL, pVideoOutPin,	NULL, m_pMPEGWriter);
	}
	catch(...) {
	}

	if (FAILED(hr))
	{
		DestroyGraph();
		return hr;
	}
	
	try	{
		hr = m_pBuilder->RenderStream(NULL, pAudioOutPin, NULL, m_pMPEGWriter);
	}
	catch(...) {
	}

	try	{
		hr = m_pBuilder->RenderStream(NULL, m_pMPEGWriter, NULL, m_pFileWriter);
	}
	catch(...) {
	}
	
	ASSERT( !FAILED( hr ) );
//	ASSERT(m_pMPEGWriterProps);

//	m_pMPEGWriterProps->OverrideSourceFPS(m_fOutputFPS);
	
	m_pCallback->Fire_AboutToRun();
    hr = m_pMediaControl->Run( );
    ASSERT( !FAILED( hr ) );
	if (FAILED(hr))
		Stop();

	return S_OK;
}

HRESULT CDESEdit::ApplyMPEGProperties()
{
	return E_NOTIMPL;
}


HRESULT CDESEdit::InsertMPEGCodec(BSTR strTargetFile)
{
	HRESULT hr = CoCreateInstance(CLSID_StandardMpegEncoder, NULL, 
								  CLSCTX_INPROC_SERVER, 
								  IID_IBaseFilter, 
								  (void **)&m_pMPEGWriter);
	
	if (FAILED(hr))
	{
		return hr;
	}

	
	hr = m_pFileWriter.CoCreateInstance(CLSID_FileWriter);
	if (FAILED(hr))
		return hr;

	hr = m_pGraph->AddFilter(m_pFileWriter, L"File Writer Filter");
	if (FAILED(hr))
	{
		return hr;
	}

	CComPtr <IFileSinkFilter> pFS;
	hr = m_pFileWriter->QueryInterface(IID_IFileSinkFilter, (void **) &pFS);
	if (FAILED(hr) || pFS == NULL)
	{
		return hr;
	}

	hr = pFS->SetFileName(strTargetFile, 0);
	if (FAILED(hr))
	{
		return hr;
	}

	hr = m_pGraph->AddFilter(m_pMPEGWriter, L"Standard MPEG Encoder Filter");
	if (FAILED(hr))
	{
		return hr;
	}

	hr = m_pMPEGWriter->QueryInterface(IID_IMediaSeeking, (void**)&m_pSeeking);
	if (FAILED(hr))
	{
		return hr;
	}

	hr = m_pMPEGWriter->QueryInterface(__uuidof(IStandardMpegEncoder), (void**)&m_pIMPEGEncoder);
	ASSERT(m_pIMPEGEncoder);
	
	if (SUCCEEDED(hr))
	{
		// make the mpeg encoder select one of the pre-defined
		// profile objects that it stores internally. For audio
		// you will need to create your own profile.
		m_pIMPEGEncoder->SelectFormat(m_systemsFormat, m_constraint);
	}

	return hr;

	/*
	HRESULT hr = CoCreateInstance(CLSID_EssienMpegEncoder, NULL, 
								  CLSCTX_INPROC_SERVER, 
								  IID_IBaseFilter, 
								  (void **)&m_pMPEGWriter);
	if (FAILED(hr))
	{
		return hr;
	}
	


	hr = m_pMPEGWriter->QueryInterface(__uuidof(IEssienMpegEncoder), (void**)&m_pIMPEGEncoder);
	ASSERT(m_pIMPEGEncoder);
	
	if (SUCCEEDED(hr))
	{
		// make the mpeg encoder select one of the pre-defined
		// profile objects that it stores internally. For audio
		// you will need to create your own profile.
		m_pIMPEGEncoder->SelectFormat(m_systemsFormat, m_constraint);
		m_pIMPEGEncoder->GetSelectedProfile(&m_pIMPEGEncoderProfile);

		_ASSERT(m_pIMPEGEncoderProfile);
		if (m_pIMPEGEncoderProfile)
		{
			m_pIMPEGEncoderProfile->SetVideoFormat(m_videoFormat);
			m_pIMPEGEncoderProfile->SetAudioFormat(m_audioFormat);

			// If you want the filter to deinterlace, call this
			// m_pIMPEGEncoderProfile->SetInterlaceMode(true, false, false);
		}
	}

	return hr;
	*/
	return E_NOTIMPL;
}

void CDESEdit::ApplyVideoFormatSettings()
{
	/*
	if (m_videoFormat == formatVCD_PAL)
	{
		m_fOutputFPS = 25;
		m_nOutputWidth = 352;
		m_nOutputHeight = 288;
	}
	else if (m_videoFormat == formatVCD_NTSC)
	{
		m_fOutputFPS = (30.0f*1000)/1001;
		m_nOutputWidth = 352;
		m_nOutputHeight = 240;
	}
	else if (m_videoFormat == formatSVCD_PAL)
	{
		m_nOutputWidth = 480; // 720
		m_nOutputHeight = 576; // 576
		m_fOutputFPS = 25;
	}
	else if (m_videoFormat == formatSVCD_NTSC)
	{
		m_nOutputWidth = 480; // 720
		m_nOutputHeight = 480; // 480
		m_fOutputFPS = 30000.0f/1001.0f;
	}
	else if (m_videoFormat == formatDVD_PAL)
	{
		m_nOutputWidth = 720;
		m_nOutputHeight = 576;
		m_fOutputFPS = 25;
	}
	else if (m_videoFormat == formatDVD_NTSC)
	{
		m_nOutputWidth = 720;
		m_nOutputHeight = 480;
		m_fOutputFPS = 30000.0f/1001.0f;
	}
	*/
}

HRESULT CDESEdit::AddLongParam(IPropertySetter* pProp, PWSTR pParam, long lValue)
{
	USES_CONVERSION;

	DEXTER_PARAM pDexParam;
	DEXTER_VALUE *pDexValue = (DEXTER_VALUE *)CoTaskMemAlloc(sizeof(DEXTER_VALUE));

	// Initialize the parameter. 
	pDexParam.Name = SysAllocString(pParam);
	pDexParam.dispID = 0;
	pDexParam.nValues = 1;

	// Initialize the value.
	pDexValue->v.vt = VT_I4;
	pDexValue->v.lVal = lValue;
	pDexValue->rt = 0;
	pDexValue->dwInterp = DEXTERF_JUMP;

	pProp->AddProp(pDexParam, pDexValue);

	// Free allocated resources.
	SysFreeString(pDexParam.Name);
	VariantClear(&(pDexValue->v));
	CoTaskMemFree(pDexValue);
	return S_OK;
}

HRESULT CDESEdit::SetColorOnSourceObject(IAMTimelineObj *pObject, DWORD dwColor)
{
	IPropertySetter *pProp = NULL;
	// Create a property setter.
	HRESULT hr = CoCreateInstance(CLSID_PropertySetter, 
								  NULL, CLSCTX_INPROC_SERVER, 
									IID_IPropertySetter, (void**) &pProp);
	
	if (FAILED(hr))
		return hr;

	//DWORD dwYellow = 0xFFFF00;

	// Set the color.
	DEXTER_PARAM param;
	DEXTER_VALUE val;

	param.Name = SysAllocString(L"Color");
	param.dispID = 0;
	param.nValues = 1;

	val.v.vt = VT_I4;
	val.v.lVal = dwColor;
	val.rt = 0;  // Time must be zero.
	val.dwInterp = DEXTERF_JUMP;

	pProp->AddProp(param, &val);
	pObject->SetPropertySetter(pProp);

	// Clean up.
	SysFreeString(param.Name);
	VariantClear(&val.v);
	pProp->Release();
	
	return hr;
}

HRESULT CDESEdit::AddFadeTrack(IAMTimelineComp* pCompVideo, bool bFadeIn, bool bFadeOut, REFERENCE_TIME rtStart, REFERENCE_TIME rtStop)
{
	// add new track with a lower priority
	CComPtr<IAMTimelineObj> pTrackVideoObj;
	HRESULT hr = m_pTimeline->CreateEmptyNode( &pTrackVideoObj, TIMELINE_MAJOR_TYPE_TRACK );
	CComQIPtr< IAMTimelineTrack, &IID_IAMTimelineTrack > pTrackVideo(pTrackVideoObj);
	pCompVideo->VTrackInsBefore(pTrackVideoObj, 1);

	// create plain color source


	// create transition guid
	GUID guidTransition;
	hr = CLSIDFromString(L"{16B280C5-EE70-11D1-9066-00C04FD9189D}", &guidTransition);

	CComPtr<IAMTimelineTransable> pTransable = NULL;
	CComPtr<IAMTimelineObj> pTransObj;

	// create fade in transition object
	if (bFadeIn)
	{
		CComPtr<IAMTimelineObj> pSourceVideoObj;	
		hr = m_pTimeline->CreateEmptyNode(&pSourceVideoObj, TIMELINE_MAJOR_TYPE_SOURCE );
		if(FAILED( hr )) 
		{
			return hr;
		}
			
		// set the source to be as long as the source file
		hr |= pSourceVideoObj->SetSubObjectGUID( CLSID_ColorSource );
		if(FAILED( hr )) 
		{
			return hr;
		}
		
		// set it black
		SetColorOnSourceObject(pSourceVideoObj, 0);

		// add the source to the track
		hr = pTrackVideo->SrcAdd( pSourceVideoObj );
		if(FAILED( hr )) 
		{
			return hr;
		}

		hr |= pSourceVideoObj->SetStartStop(rtStart, rtStart + (m_dFadeInLength * UNITS));

		hr = m_pTimeline->CreateEmptyNode(&pTransObj, TIMELINE_MAJOR_TYPE_TRANSITION);
		hr = pTransObj->SetSubObjectGUID(guidTransition);
		hr = pTransObj->SetStartStop(rtStart, rtStart + (m_dFadeInLength * UNITS));

		CComPtr<IAMTimelineTrans> pTrans;
		hr = pTransObj->QueryInterface(IID_IAMTimelineTrans, (void **)&pTrans);
		pTrans->SetSwapInputs(TRUE);

		hr = pTrackVideo->QueryInterface(IID_IAMTimelineTransable, (void **)&pTransable);
		hr = pTransable->TransAdd(pTransObj);
	}

	if (bFadeOut)
	{
		CComPtr<IAMTimelineObj> pSourceVideoObj;	
		hr = m_pTimeline->CreateEmptyNode(&pSourceVideoObj, TIMELINE_MAJOR_TYPE_SOURCE );
		if(FAILED( hr )) 
		{
			return hr;
		}
			
		// set the source to be as long as the source file
		hr |= pSourceVideoObj->SetSubObjectGUID( CLSID_ColorSource );
		if(FAILED( hr )) 
		{
			return hr;
		}
		
		// set it black
		SetColorOnSourceObject(pSourceVideoObj, 0);

		// add the source to the track
		hr = pTrackVideo->SrcAdd( pSourceVideoObj );
		if(FAILED( hr )) 
		{
			return hr;
		}

		hr |= pSourceVideoObj->SetStartStop(rtStop - (m_dFadeOutLength * UNITS), rtStop);

		pTransObj = NULL;
		pTransObj = NULL;
		pTransable = NULL;

		hr = m_pTimeline->CreateEmptyNode(&pTransObj, TIMELINE_MAJOR_TYPE_TRANSITION);
		hr = pTransObj->SetSubObjectGUID(guidTransition);
		hr = pTransObj->SetStartStop(rtStop - (m_dFadeOutLength * UNITS), rtStop);

		CComPtr<IAMTimelineTrans> pTrans;
		hr = pTransObj->QueryInterface(IID_IAMTimelineTrans, (void **)&pTrans);
		pTrans->SetSwapInputs(FALSE);

		hr = pTrackVideo->QueryInterface(IID_IAMTimelineTransable, (void **)&pTransable);
		hr = pTransable->TransAdd(pTransObj);
	}

	return hr;
}