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
#include <initguid.h>

// #include "IEssienMPEGEncoder.h"
#include "mpegfilter.h"
#include "mpeginputpin.h"
#include "MPEGFilterInterface.h"
#include "mpegobj.h"
#include "MpegSeeking.h"
#include "proppage.h"
#include "mpegoutputpin.h"


// We define our input media types. 
const AMOVIESETUP_MEDIATYPE sudPinTypes[] =
{
    { &MEDIATYPE_Video,         // Major CLSID
      &MEDIASUBTYPE_RGB24 },    // Minor type
    
	{ &MEDIATYPE_Audio,         // Major CLSID
      &MEDIASUBTYPE_PCM },       // Minor type

    { &MEDIATYPE_Stream,         // Major CLSID
      &MEDIASUBTYPE_NULL }       // Minor type

};

// Define our pins
const AMOVIESETUP_PIN psudPins[] =
{
    { L"Input 01",             // Pin's string name
      TRUE,                // Is it rendered
      FALSE,                // Is it an output
      FALSE,                // Allowed none
      FALSE,                // Allowed many
      &CLSID_NULL,          // Connects to filter
      L"Output",            // Connects to pin
      1,                    // Number of types
      &sudPinTypes[0] },       // Pin information

     { L"Input 02",             // Pin's string name
      TRUE,                // Is it rendered
      FALSE,                // Is it an output
      FALSE,                // Allowed none
      FALSE,                // Allowed many
      &CLSID_NULL,          // Connects to filter
      L"Output",            // Connects to pin
      1,                    // Number of types
      &sudPinTypes[1] },       // Pin information
	 
	{ L"Output 01",             // Pin's string name
      FALSE,                // Is it rendered
      TRUE,                // Is it an output
      FALSE,                // Allowed none
      TRUE,                // Allowed many
      &CLSID_NULL,          // Connects to filter
      L"Input",            // Connects to pin
      1,                    // Number of types
      &sudPinTypes[2] }       // Pin information
};

const AMOVIESETUP_FILTER sudInfTee =
{
    &CLSID_StandardMpegEncoder,             // CLSID of filter
    L"Standard MPEG Encoder v6",    // Filter's name
    MERIT_DO_NOT_USE,       // Filter merit
    3,                      // Number of pins
    psudPins                // Pin information
};


//
//  Object creation stuff
//
CFactoryTemplate g_Templates [] = 
{
    { L"Standard MPEG Encoder v6"
    , &CLSID_StandardMpegEncoder
    , CMPEGObj::CreateInstance
    , NULL
    , &sudInfTee 
	},

	{ L"Standard MPEG Encoder General Property Page"
	 , &CLSID_StandardMpegEncoderGeneralProps
	 , CMPEGPropsGeneral::CreateInstance
    },


	{ L"Standard MPEG Encoder Video Property Page"
	 , &CLSID_StandardMpegEncoderVideoProps
	 , CMPEGPropsVideo::CreateInstance
    },

	{ L"Standard MPEG Encoder Audio Property Page"
	 , &CLSID_StandardMpegEncoderAudioProps
	 , CMPEGPropsAudio::CreateInstance
    }

};
int g_cTemplates = sizeof(g_Templates) / sizeof(g_Templates[0]);



// DllRegisterSever
//
// Handle the registration of this filter
//
STDAPI DllRegisterServer()
{

    return AMovieDllRegisterServer2( TRUE );

} // DllRegisterServer


//
// DllUnregisterServer
//
STDAPI DllUnregisterServer()
{
    return AMovieDllRegisterServer2( FALSE );

} // DllUnregisterServer


//
// DllEntryPoint
//
extern "C" BOOL WINAPI DllEntryPoint(HINSTANCE, ULONG, LPVOID);


BOOL APIENTRY DllMain(HANDLE hModule, 
                      DWORD  dwReason, 
                      LPVOID lpReserved)
{
	return DllEntryPoint((HINSTANCE)(hModule), dwReason, lpReserved);
}



///////////////////////////////////////////////////////////
// CMPEGFilter Constructor

CMPEGFilter::CMPEGFilter(CMPEGObj *pMPEGObj,
                         LPUNKNOWN pUnk,
                         HRESULT *phr) :

			 CBaseFilter(NAME("CMPEGFilter"),
						 pUnk, &m_Lock,
						 CLSID_StandardMpegEncoder),

						 m_pMPEGObj(pMPEGObj),
						 m_pPosition(NULL)
{
	m_pOutPinVideo = NULL;
	m_pOutPinAudio = NULL;

	m_pMPEGObj->m_pFilter = this;

	m_pPinVideo = new CMPEGInputPin(pMPEGObj, pUnk,
									this,
									m_pLock,
									&m_ReceiveLock,
									Video,
									L"Video Input",
									phr);
    if (m_pPinVideo == NULL) {
        *phr = E_OUTOFMEMORY;
        return;
    }

    m_pPinAudio = new CMPEGInputPin(pMPEGObj, pUnk,
									this,
									m_pLock,
									&m_ReceiveLock,
									Audio,
									L"Audio Input",
									phr);
    if (m_pPinAudio == NULL) {
        *phr = E_OUTOFMEMORY;
        return;
    }

	m_pOutPinSystems = new CMPEGOutputPin("Systems", m_pMPEGObj, phr, L"Systems Output", 0);
    if (m_pPinAudio == NULL) {
        *phr = E_OUTOFMEMORY;
        return;
    }

	m_pOutPinVideo = new CMPEGOutputPin("VideoOut", m_pMPEGObj, phr, L"Video Output", 1);
    if (m_pOutPinVideo == NULL) {
        *phr = E_OUTOFMEMORY;
        return;
    }

	m_pOutPinAudio = new CMPEGOutputPin("AudioOut", m_pMPEGObj, phr, L"Audio Output", 2);
    if (m_pOutPinAudio == NULL) {
        *phr = E_OUTOFMEMORY;
        return;
    }
}

CMPEGFilter::~CMPEGFilter()
{
	SAFE_DELETE( m_pPinVideo );
    SAFE_DELETE( m_pPinAudio );
	SAFE_DELETE( m_pPosition );

	m_pOutPinSystems->Release();
	m_pOutPinVideo->Release();
	m_pOutPinAudio->Release();
}

CBasePin * CMPEGFilter::GetPin(int n)
{
	switch (n)
	{
	case 0:
		return m_pPinVideo;
	case 1:
		return m_pPinAudio;
	case 2:
		if (!m_pMPEGObj->GetShouldMultiplex()) 
		{
			m_pOutPinVideo->SetExposed(true);
			return m_pOutPinVideo;
		}
		else
		{
			m_pOutPinVideo->SetExposed(false);
			m_pOutPinAudio->SetExposed(false);
			m_pOutPinSystems->SetExposed(true);
			return m_pOutPinSystems;
		}
	case 3:
		if (!m_pMPEGObj->GetShouldMultiplex())
		{
			m_pOutPinAudio->SetExposed(true);
			return m_pOutPinAudio;
		}
	}
    
    return NULL;
}

int CMPEGFilter::GetPinCount()
{
	return m_pMPEGObj->GetShouldMultiplex() ? 3 : 4;
}

STDMETHODIMP CMPEGFilter::Stop()
{
	TraceVerbose("Entered CMPEGFilter::Stop\n");
    CAutoLock cObjectLock(m_pLock);
	HRESULT hr = m_pMPEGObj->Stop();
    hr = CBaseFilter::Stop();
	TraceVerbose("Exited CMPEGFilter::Stop\n");
	return hr;
}


// This returns the IMediaPosition and IMediaSeeking interfaces

HRESULT CMPEGFilter::GetMediaPositionInterface(REFIID riid, void **ppv)
{
    CAutoLock cObjectCreationLock(&m_ObjectCreationLock);
	
    if (m_pPosition) {
        return m_pPosition->NonDelegatingQueryInterface(riid,ppv);
    }

    HRESULT hr = NOERROR;

    // Create implementation of this dynamically since sometimes we may
    // never try and do a seek. The helper object implements a position
    // control interface (IMediaPosition) which in fact simply takes the
    // calls normally from the filter graph and passes them upstream

	/*
    m_pPosition = new CRendererPosPassThru(NAME("Renderer CPosPassThru"),
                                           CBaseFilter::GetOwner(),
                                           (HRESULT *) &hr,
                                           GetPin(0));*/
	m_pPosition = new CMPEGSeeking(NAME("Renderer CPosPassThru"),
                                           CBaseFilter::GetOwner(),
                                           (HRESULT *) &hr,
                                           GetPin(0),
										   GetPin(1),
										   m_pMPEGObj);
    if (m_pPosition == NULL) {
        return E_OUTOFMEMORY;
    }

    if (FAILED(hr)) {
        delete m_pPosition;
        m_pPosition = NULL;
        return E_NOINTERFACE;
    }

	m_pPosition->AddRef();
	*ppv = m_pPosition;

    return S_OK;
}


STDMETHODIMP CMPEGFilter::Pause()
{
	TraceVerbose("Entered CMPEGFilter::Pause\n");

	// Lock any other app thread functions from entering
	CAutoLock cObjectLock(m_pLock);

	 // Pause the base filter class
    HRESULT hr = CBaseFilter::Pause();
    if (FAILED(hr)) {
        NOTE("Pause failed");
        return hr;
    }

	m_pMPEGObj->Pause();	

	TraceVerbose("Exiting CMPEGFilter::Pause\n");
    return S_OK;
}

STDMETHODIMP CMPEGFilter::Run(REFERENCE_TIME tStart)
{
	TraceVerbose("Entered CMPEGFilter::Run\n");

	CAutoLock cObjectLock(m_pLock);

	ASSERT(m_State != State_Stopped);
	if (m_State != State_Running)
	{
		HRESULT hr = m_pMPEGObj->Run();
		if (FAILED(hr))
		{
			CBaseFilter::Run(tStart);
			return hr;
		}
	}

	HRESULT hr = CBaseFilter::Run(tStart);
	
	TraceVerbose("Exiting CMPEGFilter::Run\n");
    return hr;
}

STDMETHODIMP CMPEGFilter::GetState(DWORD dwMilliSecsTimeout, FILTER_STATE *State)
{
	HRESULT hr = CBaseFilter::GetState(dwMilliSecsTimeout, State);
	return hr;
}


STDMETHODIMP CMPEGFilter::QueryVendorInfo(LPWSTR *pVendorInfo)
{
    CheckPointer(pVendorInfo, E_POINTER);
    ValidateReadWritePtr(pVendorInfo, sizeof(LPWSTR));

    *pVendorInfo = (LPWSTR)CoTaskMemAlloc(256);
    if(*pVendorInfo==NULL)
    {
        return E_OUTOFMEMORY;
    }

    wcscpy_s(*pVendorInfo, 256, L"Standard MPEG");
    return NOERROR;
}



CCritSec* CMPEGFilter::GetMainLock()
{
	return m_pLock;
}

CMPEGInputPin* CMPEGFilter::GetVideoPin()
{
	return m_pPinVideo;
}
