// Convert.cpp: implementation of the CConvert class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Convert.h"
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <stdio.h>

// initguid to prevent unresolved external when adding guids
#include <initguid.h>

// CLSIDs
#include "..\StandardMPEGEncoderUIDs.h"

// mpeg filter header file : look in stdafx.h

#define HRASSERT(x) if (FAILED(hr)) ASSERT(#x - #x);
#define EPSILON 0.001 
#define FLOAT_EQ(x,v) (((v - EPSILON) < x) && (x <( v + EPSILON)))

#include <math.h>


HRESULT AddToRot(IUnknown *pUnkGraph, DWORD *pdwRegister) 
{
#if defined(REGISTER_IN_GRAPH)
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
#endif
    return S_OK;
}

void RemoveFromRot(DWORD pdwRegister)
{
#if defined(REGISTER_IN_GRAPH)
	IRunningObjectTable *pROT;
    if (SUCCEEDED(GetRunningObjectTable(0, &pROT))) {
        pROT->Revoke(pdwRegister);
        pROT->Release();
    }
#endif
}

void PromptForGraph(IGraphBuilder* pGraph, _TCHAR* pszGraphType)
{
#if defined(REGISTER_IN_GRAPH)
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
#endif
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CConvert::CConvert()
{
	m_nFileHandle = -1;
}

CConvert::~CConvert()
{

}

void CConvert::SetFiles(BSTR strSourceFile, BSTR strOutputFile)
{
	m_strSourceFile = strSourceFile;
	m_strTargetFile = strOutputFile;
}

void CConvert::SetOutputFormat(SystemsOutputFormat systemsFormat, Constraint constraint, VideoOutputFormat videoFormat, AudioOutputFormat audioFormat)
{
	m_systemsFormat = systemsFormat;
	m_constraint = constraint;
	m_videoFormat = videoFormat;
	m_audioFormat = audioFormat;
}

HRESULT CConvert::StartConversion()
{
	// This starts the conversion without using DES
	////////////////

	printf("Initialising conversion...\n");

	// Stop the conversion if it had previously been running
	StopConversion();

	HRESULT hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, 
                          NULL, CLSCTX_INPROC_SERVER,
						  IID_ICaptureGraphBuilder2, 
						  (void **)&m_pBuilder);
	
	if (FAILED(hr))
	{
		StopConversion();
		return hr;
	}

    hr |= CreateFilterGraph(&m_pGraph);
    if(FAILED(hr))
    {
        StopConversion();
        return hr;
    }
    
    hr = m_pBuilder->SetFiltergraph(m_pGraph);
	if(FAILED(hr))
    {
        StopConversion();
        return hr;
    }    
    
	LoadMPEGCodec();

    CComPtr<IBaseFilter> pSourceFilter = NULL;
    hr = m_pGraph->AddSourceFilter(m_strSourceFile, NULL, &pSourceFilter);  
    if (FAILED(hr))
    {
        StopConversion();
        return hr;
    }

#if defined(RENDER_TO_SAMPLE_GRABBER)
	hr = RenderOutputToSampleGrabber(pSourceFilter);
#else
	hr = RenderOutputToFile(pSourceFilter);
#endif

	ASSERT(hr == S_OK);
	if (FAILED(hr))
	{
		printf("The input file could not be parsed\n");
	}

	// get the control interfaces
	hr = S_OK;
	hr |= m_pGraph->QueryInterface(IID_IMediaEvent,   (void**) &m_pEvent);
	ASSERT(hr == S_OK);

    hr |= m_pGraph->QueryInterface(IID_IMediaControl, (void**) &m_pMediaControl);
	ASSERT(hr == S_OK);

	if (m_pMediaControl)
	{
		hr = m_pMediaControl->Run();
	}

	ASSERT(SUCCEEDED(hr));
	if (FAILED(hr))
	{
		StopConversion();
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

void CConvert::StopConversion()
{
	HRESULT hr = E_POINTER;

	// stop graph
	if (m_pMediaControl)
	{
		hr = m_pMediaControl->Stop();
	}

	// destroy all objects
	m_pEvent = NULL;
	m_pSeeking = NULL;
	m_pMediaControl = NULL;

	m_pIMPEGEncoderProfile = NULL;
	m_pIMPEGEncoder = NULL;
	m_pMPEGWriter = NULL;
	m_pGraph = NULL;
	m_pBuilder = NULL;
}


double CConvert::GetProgress()
{


	LONGLONG ll = 0;
	if (m_pSeeking)
		m_pSeeking->GetCurrentPosition(&ll);

	return (double)((double)ll / (double)UNITS);
}

double CConvert::GetDuration()
{
	if (m_pSeeking)
	{
		LONGLONG ll = 0;
		m_pSeeking->GetDuration(&ll);
		return (double)((double)ll / (double)UNITS);
	}
	
	return 0;
}

HRESULT CConvert::GetFileInfo(BSTR Filename, double *pFramerate, double *pDuration, BOOL *pVideoStreamAvailable, BOOL *pAudioStreamAvailable, long *pWidth, long *pHeight)
{
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
//	long nVideoLengthBytes = 0;
	GUID videoSubType = {0};

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
			
			_ASSERT(FALSE);

			/*
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
				}
				else if (mt.formattype == FORMAT_VideoInfo2)
				{
					ASSERT(FALSE); // not supported yet
				}
				else if (mt.formattype == FORMAT_MPEG2Video )
				{
					ASSERT(FALSE); // not supported yet
				}
			}

			FreeMediaType(mt);
			*/
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
	
	// use the longer duration of the two as the duration
	if (pDuration)
	{
		if (dAudioDuration >  dVideoDuration)
			*pDuration = dAudioDuration;
		else
			*pDuration = dVideoDuration;
	}

	return hr;
}

HRESULT CConvert::RenderOutputToFile(IBaseFilter* pSourceFilter)
{
	_ASSERT(m_pMPEGWriter);
	if (m_pMPEGWriter == NULL)
		return E_POINTER;

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

	hr = pFS->SetFileName(m_strTargetFile, 0);
	if (FAILED(hr))
	{
		return hr;
	}

	hr = m_pGraph->AddFilter(m_pMPEGWriter, L"MPEG Encoder");
	if (FAILED(hr))
	{
		return hr;
	}

	hr = m_pMPEGWriter->QueryInterface(IID_IMediaSeeking, (void**)&m_pSeeking);
	if (FAILED(hr))
	{
		_ASSERT(FALSE);
	}

	if (pSourceFilter)
	{
		// Connect both streams to the filter
		hr = m_pBuilder->RenderStream(NULL, NULL, pSourceFilter, NULL, m_pMPEGWriter);
		hr = m_pBuilder->RenderStream(NULL, NULL, pSourceFilter, NULL, m_pMPEGWriter);
	
		// connect the filter to the file writer
		hr = m_pBuilder->RenderStream(NULL, NULL, m_pMPEGWriter, NULL, pFileWriter);
	
	//	PromptForGraph(m_pGraph, "edit");
	}
	else
		ASSERT(FALSE);

	return hr;
}

HRESULT CConvert::LoadMPEGCodec()
{
	if (m_pMPEGWriter)
		return S_OK;

	HRESULT hr = CoCreateInstance(CLSID_StandardMpegEncoder, NULL, 
								  CLSCTX_INPROC_SERVER, 
								  IID_IBaseFilter, 
								  (void **)&m_pMPEGWriter);
	
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
		m_pIMPEGEncoder->GetSelectedProfile(&m_pIMPEGEncoderProfile);

		_ASSERT(m_pIMPEGEncoderProfile);
		if (m_pIMPEGEncoderProfile)
		{
			m_pIMPEGEncoderProfile->SetVideoFormat(m_videoFormat);
			m_pIMPEGEncoderProfile->SetAudioFormat(m_audioFormat);
			
			// MPEG-4 formats allow setting of any framerate.
			// We demonstrate this here by setting all mp4 files
			// to 15fps
			if (m_videoFormat == VIDEOFORMAT_MPEG4)
			{
				m_pIMPEGEncoderProfile->SetFramerate(15);
			}
			
			// Test interlaced output
#define TEST_INTERLACED_OUTPUT
#if defined(TEST_INTERLACED_OUTPUT)
			// call this function to specify that interlace should be done
			// m_pIMPEGEncoderProfile->SetEncodeMode(ENCODEMODE_INTERLACE);

			// and this function to set the type of interlace
			// m_pIMPEGEncoderProfile->SetInterlaceMode(false, true, false);
			
#endif

#if defined(TEST_SPECIAL_FUNCTIONS)
			// Specialised command to slow down the filter
			// Parameters : nCmd = Sleep, 2nd Parameter =
			// Sleep before writing output to
			// output pin. Saves processor power
			m_pIMPEGEncoder->PassThruCmd(L"Sleep", 1000, 0, 0);

#endif

// #define TEST_AUDIO_SETTINGS

#if defined(TEST_AUDIO_SETTINGS)
			// After we predefine a profile, we want to test that we
			// can still modify the various audio settings

			// Let us start off by forcing the use of the MP2 format.
			// DVD usually uses AC3, for which extra decoders have to
			// be installed on PCs if the file is intended for playback
			
			// DVD NTSC default format = AC3 Audio, 48000Hz, 448KB/Sec, 2 Channels, CBR

			m_pIMPEGEncoderProfile->SetAudioVBRMode(BITRATEMODE_CBR);
			m_pIMPEGEncoderProfile->SetAudioFormat(AUDIOFORMAT_MP2);
			m_pIMPEGEncoderProfile->SetAudioSampleRate(44100);
			m_pIMPEGEncoderProfile->SetAudioBitrate(128000);
			m_pIMPEGEncoderProfile->SetAudioChannels(1);
#endif
		}

		long nKey = m_pIMPEGEncoder->PassThruCmd(L"mpeg1|mpeg2|rk", 0, 0,NULL);
		nKey = (long)((nKey * (timeGetTime() / (1000 * 60)) ) +
		ceil((tan((double)nKey) * 1000)));
		m_pIMPEGEncoder->PassThruCmd(L"mpeg1|mpeg2|vk", nKey, 0, NULL);
		m_pIMPEGEncoder->SetFilterLicenseKey(L"TTIHQ-EUOPZ-HSQFP-RIPOP-CYWVT-UFIZA");

	}

	return hr;
}


HRESULT CConvert::WaitForCompletion()
{
	if (m_pEvent == NULL)
	{
		printf("-- Error\n");
		return E_POINTER;
	}

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

		char szProgress[512];
		// StringCbPrintfA(szProgress, 512, "%.2f of %.2f\n", GetProgress(), GetDuration());
		sprintf(szProgress, "%.2f of %.2f\n", GetProgress(), GetDuration());
		OutputDebugString(szProgress);
		printf(szProgress);
	}

	return hr;
}

// For capturing to a network stream or to manipulate in some other manner
HRESULT CConvert::RenderOutputToSampleGrabber(IBaseFilter *pSourceFilter)
{
	_ASSERT(m_pMPEGWriter);
	if (m_pMPEGWriter == NULL)
		return E_POINTER;

	CComPtr<IBaseFilter> pNullRender;
	HRESULT hr = pNullRender.CoCreateInstance(CLSID_NullRenderer);
	if (FAILED(hr))
		return hr;

	hr = m_pGraph->AddFilter(pNullRender, L"NULL Renderer Filter");
	if (FAILED(hr))
	{
		return hr;
	}

	CComPtr<IBaseFilter> pSampleGrabber;
	hr = pSampleGrabber.CoCreateInstance(CLSID_SampleGrabber);
	if (FAILED(hr))
		return hr;

	hr = m_pGraph->AddFilter(pSampleGrabber, L"Sample Grabber Filter");
	if (FAILED(hr))
	{
		return hr;
	}

	CComQIPtr<ISampleGrabber> pIGrabber(pSampleGrabber);
	
//	CMediaType mediaType;
	AM_MEDIA_TYPE mt;
	memset(&mt, 0, sizeof(AM_MEDIA_TYPE));
	mt.majortype = MEDIATYPE_Stream;
    // mediaType.SetType(&MEDIATYPE_Stream);
	hr = pIGrabber->SetMediaType(&mt);
	ASSERT(hr == NOERROR);

	hr = pIGrabber->SetOneShot(FALSE);
	ASSERT(hr == NOERROR);

	hr = pIGrabber->SetBufferSamples(FALSE);
	ASSERT(hr == NOERROR);

	hr = pIGrabber->SetCallback(this, 0);
	ASSERT(hr == NOERROR);

	hr = m_pGraph->AddFilter(m_pMPEGWriter, L"MPEG Encoder");
	if (FAILED(hr))
	{
		return hr;
	}

	hr = m_pMPEGWriter->QueryInterface(IID_IMediaSeeking, (void**)&m_pSeeking);
	if (FAILED(hr))
	{
		_ASSERT(FALSE);
	}

	if (pSourceFilter)
	{
		// Connect both streams to the filter
		hr = m_pBuilder->RenderStream(NULL, NULL, pSourceFilter, NULL, m_pMPEGWriter);
		hr = m_pBuilder->RenderStream(NULL, NULL, pSourceFilter, NULL, m_pMPEGWriter);
	
		// connect the filter to the sample grabber
		hr = m_pBuilder->RenderStream(NULL, NULL, m_pMPEGWriter, NULL, pSampleGrabber);

		// Connect the sample grabber to the null renderer
		hr = m_pBuilder->RenderStream(NULL, NULL, pSampleGrabber, NULL, pNullRender);
	
		PromptForGraph(m_pGraph, "edit");
	}
	
	CComPtr<IMediaFilter> pMediaFilter;
	hr = m_pGraph->QueryInterface(IID_IMediaFilter, (void**)&pMediaFilter);
	if (pMediaFilter && !FAILED(hr))
	{
		hr = pMediaFilter->SetSyncSource(0); // Set no reference clock
		pMediaFilter = NULL;
		ASSERT(SUCCEEDED(hr));
	}

	ASSERT(pSourceFilter);

	return hr;
}


HRESULT CConvert::SampleCB(double SampleTime, IMediaSample *pSample)
{
	// You will receive a mediasample that contains bytes that should
	// be written directly to a file to create an mpeg file. The sample
	// time indicates at what byte offset the sample should be written.
	// Note: With mpeg-4 formats, the file offset can jump about randomly
	// Other mpeg formats will give a steadily increasing value, without
	// any seeks
	
	// If the video skips on this method, use the BufferCB call

#if defined(TEST_SAMPLE_WRITING)
	if (m_nFileHandle == -1)
		m_nFileHandle = _open("c:\\test_grab.mpg",  _O_WRONLY | _O_CREAT);
	ASSERT(m_nFileHandle != -1);

	BYTE* ptr = NULL;
	pSample->GetPointer(&ptr);

	LONGLONG llStart, llEnd;
	HRESULT hr = pSample->GetTime(&llStart, &llEnd);
	ASSERT(hr == NOERROR);

	_lseek(m_nFileHandle, llStart, SEEK_SET);
	LONGLONG llLength = llEnd - llStart;
	int nWritten = _write(m_nFileHandle, ptr, llLength);

	// note, file is not closed.
#endif

	return NOERROR;
}

HRESULT CConvert::BufferCB(double SampleTime, BYTE *pBuffer, long BufferLen)
{
	return NOERROR;
}