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

// MPEGObj.cpp: Implementierung der Klasse CMPEGObj.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
// #include "IStandardMPEGEncoder.h"
#include "mpegseeking.h"
#include "mpeginputpin.h"
#include "MPEGFilterInterface.h"
#include "MPEGObj.h"
#include <time.h>
#include "resource.h"
#include "mpegfilter.h"
#include <math.h>
#undef lstrcpyW

#include "MPEGOutputPin.h"


#define WRITEOUT(var)  hr = pStream->Write(&var, sizeof(var), NULL); \
               if (FAILED(hr)) return hr;

#define READIN(var)    hr = pStream->Read(&var, sizeof(var), NULL); \
               if (FAILED(hr)) return hr;

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CMPEGObj::CMPEGObj(LPUNKNOWN pUnk, HRESULT *phr) :
				   CUnknown(NAME("CMPEGObj"), pUnk),
				   m_pFilter(NULL),
				   m_pInterface(NULL),
				   m_eventIsPrimed(TRUE),
				   CPersistStream(pUnk, phr)
{
	m_bAudioLocked = false;
	HRESULT hr = m_pDirectEncodeVB.CoCreateInstance(__uuidof(DirectEncodeVB));

	_ASSERT(m_pInterface == NULL);
	m_pInterface = new CMPEGFilterInterface;
	m_pInterface->AddRef();
	m_pInterface->m_pObj = this;
	
	m_bMultiplex = true;
	m_bStopped = true;

#if defined(COMPILE_AS_REGISTERED)
	m_bLicensedMP4 = true;
#else
	m_bLicensedMP4 = false;
#endif

	m_pLicense = NULL;
	m_pEncode = new CEncodeErdLib();
	m_pEncode->SetDeliverCallback(this);

	m_pCurrentProfile = &m_prMPEG1;

#if defined(SPECIAL_BUILD_SMARTCAST)
	m_pCurrentProfile = &m_prMPEG2;
#else
	m_pCurrentProfile = &m_prMPEG1;
#endif

	memset(m_szOutputFile, 0, 1024 * sizeof(wchar_t));
	memset(m_szEncodeLibrary, 0, 1024 * sizeof(wchar_t));
	memset(m_szLicense, 0, 25);
	
	wcscpy_s(m_szEncodeLibrary, 25, L"erdmpg-6.dll");

	m_bHasAudio = false;
	m_bHasVideo = false;
#if defined(COMPILE_AS_REGISTERED)
	m_bAuthenticated = true;
#else
	m_bAuthenticated = false;
#endif

	m_nVideoFramesReceived = 0;
	m_nAudioSamplesReceived = 0;
	m_nVideoFramesReceivedSincePause = 0;
	m_nAudioSamplesReceivedSincePause = 0;
	m_bLicensed = false;
	m_bPrimed = false;
	m_rtCurrentVideo = 0;
	m_rtCurrentAudio = 0;
	m_iStreamsStopped = 0;
	m_iStreamCount = 0;
	m_dwSleep = 0;

	/* NEW_FORMAT CHANGE POINT */
	m_prVCDPal.AddRef();
	m_prVCDNtsc.AddRef();
	m_prMPEG1.AddRef();
	m_prMPEG2.AddRef();
	m_prDVDPal.AddRef();
	m_prDVDNtsc.AddRef();
	m_prSVCDNtsc.AddRef();
	m_prSVCDPal.AddRef();
	m_prMP4.AddRef();
	m_prMP4IPod.AddRef();
	m_prMP4QT.AddRef();
	m_prMP4AVI.AddRef();
	m_pr3GP.AddRef();
	m_pr3G2.AddRef();
	m_prPSP.AddRef();
	m_prFLV.AddRef();
	m_prElementary.AddRef();
		
	m_prDVB.AddRef();
	m_prRM.AddRef();
	m_prMPEG2_HD.AddRef();
	m_prMP4IPod_Nano.AddRef();
	m_prMP4IPhone.AddRef();
	m_prMP4H264.AddRef();

	m_prSVCDNtsc_Still.AddRef();
	m_prSVCDPal_Still.AddRef();
	m_prVCDNtsc_Still.AddRef();
	m_prVCDPal_Still.AddRef();

	// to add a new format
	// 1. Add new profile
	// 2. Add the auto format conf in profile class
	// 3. AddRef above for this profile
	// 4. Make sure when system format is called, the profile is selected

	/* NEW_FORMAT CHANGE POINT */
	m_prElementary.ConfigureForSystemsFormat(SYSTEMSFORMAT_NONE, CONSTRAINT_NONE);
	m_prMPEG1.ConfigureForSystemsFormat(SYSTEMSFORMAT_MPEG1, CONSTRAINT_NONE);
	m_prVCDPal.ConfigureForSystemsFormat(SYSTEMSFORMAT_VCD, CONSTRAINT_PAL);
	m_prVCDNtsc.ConfigureForSystemsFormat(SYSTEMSFORMAT_VCD, CONSTRAINT_NTSC);
	m_prMPEG2.ConfigureForSystemsFormat(SYSTEMSFORMAT_MPEG2, CONSTRAINT_NONE);
	m_prDVDPal.ConfigureForSystemsFormat(SYSTEMSFORMAT_DVD, CONSTRAINT_PAL);
	m_prDVDNtsc.ConfigureForSystemsFormat(SYSTEMSFORMAT_DVD, CONSTRAINT_NTSC);
	m_prSVCDPal.ConfigureForSystemsFormat(SYSTEMSFORMAT_SVCD, CONSTRAINT_PAL);
	m_prSVCDNtsc.ConfigureForSystemsFormat(SYSTEMSFORMAT_SVCD, CONSTRAINT_NTSC);
	m_prMP4.ConfigureForSystemsFormat(SYSTEMSFORMAT_MP4, CONSTRAINT_NONE);
	m_prMP4IPod.ConfigureForSystemsFormat(SYSTEMSFORMAT_MP4, CONSTRAINT_IPOD);
	m_prMP4QT.ConfigureForSystemsFormat(SYSTEMSFORMAT_MOV, CONSTRAINT_NONE);
	m_prMP4AVI.ConfigureForSystemsFormat(SYSTEMSFORMAT_AVI, CONSTRAINT_NONE);
	
	m_prDVB.ConfigureForSystemsFormat(SYSTEMSFORMAT_DVB, CONSTRAINT_NONE);
	m_prRM.ConfigureForSystemsFormat(SYSTEMSFORMAT_RM, CONSTRAINT_NONE);
	m_prMPEG2_HD.ConfigureForSystemsFormat(SYSTEMSFORMAT_MPEG2, CONSTRAINT_HD);
	m_prMP4IPod_Nano.ConfigureForSystemsFormat(SYSTEMSFORMAT_MP4, CONSTRAINT_IPOD_NANO);
	m_prMP4IPhone.ConfigureForSystemsFormat(SYSTEMSFORMAT_MP4, CONSTRAINT_IPHONE);
	m_prMP4H264.ConfigureForSystemsFormat(SYSTEMSFORMAT_MP4, CONSTRAINT_H264);

	m_pr3GP.ConfigureForSystemsFormat(SYSTEMSFORMAT_3GP, CONSTRAINT_NONE);
	m_pr3G2.ConfigureForSystemsFormat(SYSTEMSFORMAT_3G2, CONSTRAINT_NONE);
	m_prPSP.ConfigureForSystemsFormat(SYSTEMSFORMAT_PSP, CONSTRAINT_NONE);
	m_prFLV.ConfigureForSystemsFormat(SYSTEMSFORMAT_FLV, CONSTRAINT_NONE);

	m_prSVCDNtsc_Still.ConfigureForSystemsFormat(SYSTEMSFORMAT_SVCD_STILL, CONSTRAINT_NTSC);
	m_prSVCDPal_Still.ConfigureForSystemsFormat(SYSTEMSFORMAT_SVCD_STILL, CONSTRAINT_PAL);
	m_prVCDNtsc_Still.ConfigureForSystemsFormat(SYSTEMSFORMAT_VCD_STILL, CONSTRAINT_NTSC);
	m_prVCDPal_Still.ConfigureForSystemsFormat(SYSTEMSFORMAT_VCD_STILL, CONSTRAINT_PAL);

	m_LogoOverlay.CreateLogo();

    m_pFilter = new CMPEGFilter(this, GetOwner(), phr);
    if (m_pFilter == NULL) 
	{
        *phr = E_OUTOFMEMORY;
        return;
    }
}

STDMETHODIMP CMPEGObj::GetPages(CAUUID *pPages)
{
	pPages->cElems = 3;
	pPages->pElems = reinterpret_cast<GUID*>(CoTaskMemAlloc(3 * sizeof(GUID)));
	if (pPages->pElems == NULL) 
	{
		return E_OUTOFMEMORY;
	}

	pPages->pElems[0] = CLSID_StandardMpegEncoderGeneralProps; 
	pPages->pElems[1] = CLSID_StandardMpegEncoderVideoProps; 
	pPages->pElems[2] = CLSID_StandardMpegEncoderAudioProps; 

	return S_OK;
} 

STDMETHODIMP CMPEGObj::SetFileName(LPCOLESTR pszFileName, const AM_MEDIA_TYPE *pmt)
{
    // Is this a valid filename supplied

    CheckPointer(pszFileName, E_POINTER);
    if (pszFileName && wcslen(pszFileName) > MAX_PATH)
        return ERROR_FILENAME_EXCED_RANGE;

    // Take a copy of the filename
	
	USES_CONVERSION;

	//char* pstrFileName = W2T(pszFileName);
	if (m_bPrimed && wcscmp(m_szOutputFile, pszFileName) != 0)
	{
		// in this case, the filename is being changed, but the
		// stream has not stopped. All other settings are the same
		// We mux the files, and continue with the new file

		StopConversion();

		if (wcslen(pszFileName) > 0)
			Run();
	}

    wcscpy_s(m_szOutputFile, 1024, pszFileName);
	
    // Create the file then close it
	
    HANDLE hFile = CreateFileW(m_szOutputFile,   // The filename
							 GENERIC_WRITE,         // File access
							 (DWORD) 0,             // Share access
							 NULL,                  // Security
							 CREATE_ALWAYS,         // Open flags
							 (DWORD) 0,             // More flags
							 NULL);                 // Template

    if (hFile == INVALID_HANDLE_VALUE) {
        DWORD dwErr = GetLastError();
        return HRESULT_FROM_WIN32(dwErr);
    }
	
	CloseHandle(hFile);

    return NOERROR;

} // SetFileName


STDMETHODIMP CMPEGObj::GetCurFile(LPOLESTR * ppszFileName,AM_MEDIA_TYPE *pmt)
{
    CheckPointer(ppszFileName, E_POINTER);
    *ppszFileName = NULL;
    
	if (m_szOutputFile != NULL && wcslen(m_szOutputFile) != 0) 
	{
        *ppszFileName = (LPOLESTR)
        QzTaskMemAlloc(sizeof(WCHAR) * (1+wcslen(m_szOutputFile)));
        if (*ppszFileName != NULL) {
            lstrcpyW(*ppszFileName, m_szOutputFile);
        }
    }

    if(pmt) {
        ZeroMemory(pmt, sizeof(*pmt));
        pmt->majortype = MEDIATYPE_NULL;
        pmt->subtype = MEDIASUBTYPE_NULL;
    }
    return S_OK;

}

CMPEGObj::~CMPEGObj()
{
    SAFE_DELETE( m_pFilter );
	SAFE_DELETE( m_pInterface );
	SAFE_DELETE( m_pLicense );
}

// Provide the way for COM to create this filter
CUnknown * WINAPI CMPEGObj::CreateInstance(LPUNKNOWN punk, HRESULT *phr)
{
	DbgInitialise(g_hInst);
	DbgSetModuleLevel(LOG_LOCKING, 3);

    CMPEGObj *pNewObject = new CMPEGObj(punk, phr);
    if (pNewObject == NULL) {
        *phr = E_OUTOFMEMORY;
    }
    return pNewObject;

} 

HRESULT CMPEGObj::PassThruCmd(BSTR strCmd, long nCmd, double dCmd, BYTE* pCmd)
{
	static int nValidate = 0;
	if (_wcsicmp(strCmd, L"TestVB") == 0)
	{
		MessageBox(0, "VB Was able to successfully access the filter", 0, 0);
		return S_OK;
	}
	else if (_wcsicmp(strCmd, L"IsConnected") == 0)
	{
		if (m_pFilter->GetPin(1)->IsConnected() ||
			m_pFilter->GetPin(0)->IsConnected())
			return S_OK;
		else
			return S_FALSE;
	}
	else if (_wcsicmp(strCmd, L"Unpause") == 0)
	{
		Run();
	}
	else if (_wcsicmp(strCmd, L"Pause") == 0)
	{
		Pause();
	}
	else if (wcscmp(strCmd, L"mpeg1|mpeg2|rkb") == 0)
	{
		srand( (unsigned int )timeGetTime( ) );
		nValidate = (rand() % 230) + 1;
		if (pCmd)
			*pCmd = (BYTE)nValidate;
		return S_OK;
	}
	else if (wcscmp(strCmd, L"mpeg1|mpeg2|vkb") == 0)
	{
		int i = 0;
		while (i<2)
		{
			long nMinNow = (timeGetTime() / (1000 * 60)) + i;
			if (nMinNow > 256) nMinNow = nMinNow % 256;

			if (nCmd == nMinNow)
				m_bAuthenticated = true;

			i++;
		}
		return S_OK;
	}
	else if (wcscmp(strCmd, L"mpeg1|mpeg2|rk") == 0)
	{
		long nMax = 1288579;
		
		// here we send back a random large number
		m_bAuthenticated = false;
		srand( (unsigned int )timeGetTime( ) );
		nValidate = (rand() % nMax) + 1;

		return nValidate;
	}
	else if (wcscmp(strCmd, L"mpeg1|mpeg2|vk") == 0)
	{
		// the client performs a time and pi transformation on
		// it, and we validate the results.
		
		int i = 0;
		while (i<2)
		{
			long nMinNow = (timeGetTime() / (1000 * 60)) + i;
			long nKey = (nValidate * nMinNow) + (long)ceil((tan((double)nValidate) * 1000));

			if (nCmd == nKey)
				m_bAuthenticated = true;
			
			i++;
		}

		return S_OK;
	}
	else if (_wcsicmp(strCmd, L"Sleep") == 0)
	{
		m_dwSleep = nCmd;
		return S_OK;
	}
	else if (nCmd == 14496)
	{
		CLicense* pLicense = new CLicense();
		if (pLicense->IsShortLicenseValid(strCmd) == true)
			m_bLicensedMP4 = true;
		delete pLicense;
		return S_OK;
	}

	return E_NOTIMPL;
}

STDMETHODIMP CMPEGObj::NonDelegatingQueryInterface(REFIID riid, void ** ppv)
{
	if (m_pFilter == NULL)
		return E_POINTER;
	
    CheckPointer(ppv, E_POINTER);
    
	CAutoLock lock(m_pFilter->GetMainLock());

    if (riid == IID_IBaseFilter || riid == IID_IMediaFilter || riid == IID_IPersist) 
	{
	    return m_pFilter->NonDelegatingQueryInterface(riid, ppv);
    }
    else if (riid == IID_IMediaPosition || riid == IID_IMediaSeeking) 
	{
		return m_pFilter->GetMediaPositionInterface(riid,ppv);
    }
	else if (riid == IID_ISpecifyPropertyPages) {
		return GetInterface((ISpecifyPropertyPages *) this, ppv);
	}
	else if (riid == IID_IPersistStream) {
		return GetInterface((IPersistStream *) this, ppv);
	}
	else if (riid == IID_IStandardMpegEncoder) {
		return GetInterface((IStandardMpegEncoder *) m_pInterface, ppv);
	}
	else if (riid == IID_IStandardMpegEncoderProfile) {
		return GetInterface((IStandardMpegEncoderProfile *) &GetCurrentSettingsProfile(), ppv);
	}
	else if (riid == IID_IStandardMpegEncoderStats) {
		return GetInterface((IStandardMpegEncoderStats *) m_pInterface, ppv);
	}

	return CUnknown::NonDelegatingQueryInterface(riid, ppv);

} // NonDelegatingQueryInterface

HRESULT CMPEGObj::Run()
{
	return S_OK;
}

HRESULT CMPEGObj::Stop()
{
	Trace("Stop entered\n");
	StopConversion();

	return NOERROR;
}

HRESULT CMPEGObj::EndOfStream(MediaFormat mediaFormat)
{
	Trace(_T("End of stream. Type=%lu\n"), mediaFormat);
	m_iStreamsStopped++;

	if (!m_bMultiplex)
	{
		if (mediaFormat == Video)
			m_pFilter->m_pOutPinVideo->DeliverEndOfStream();
		else
			m_pFilter->m_pOutPinAudio->DeliverEndOfStream();
	}

	if (m_iStreamsStopped == m_iStreamCount)
	{
		m_pEncode->EndOfStream();
		m_pFilter->m_pOutPinSystems->DeliverEndOfStream();

		return NOERROR;
	}

	return S_FALSE;
}

STDMETHODIMP CMPEGObj::SelectFormat(SystemsOutputFormat systemsFormat, Constraint constraint)
{
	/* NEW_FORMAT CHANGE POINT */

	switch (systemsFormat)
	{
	case SYSTEMSFORMAT_NONE:
		m_pCurrentProfile = &m_prElementary; break;
	case SYSTEMSFORMAT_MPEG1:
		m_pCurrentProfile = &m_prMPEG1; break;
	case SYSTEMSFORMAT_VCD:
		m_pCurrentProfile = constraint == CONSTRAINT_PAL ? &m_prVCDPal : &m_prVCDNtsc; break;
	case SYSTEMSFORMAT_MPEG2:
		m_pCurrentProfile = constraint == CONSTRAINT_HD ? &m_prMPEG2_HD : &m_prMPEG2; break;
	case SYSTEMSFORMAT_DVD:
		m_pCurrentProfile = constraint == CONSTRAINT_PAL ? &m_prDVDPal : &m_prDVDNtsc; break;
	case SYSTEMSFORMAT_SVCD:
		m_pCurrentProfile = constraint == CONSTRAINT_PAL ? &m_prSVCDPal : &m_prSVCDNtsc; break;
	case SYSTEMSFORMAT_MP4:
		{
			if (constraint == CONSTRAINT_IPOD)
				m_pCurrentProfile = &m_prMP4IPod;
			else if (constraint == CONSTRAINT_IPOD_NANO)
				m_pCurrentProfile = &m_prMP4IPod_Nano;
			else if (constraint == CONSTRAINT_IPHONE)
				m_pCurrentProfile = &m_prMP4IPhone;
			else if (constraint == CONSTRAINT_H264)
				m_pCurrentProfile = &m_prMP4H264;
			else
				m_pCurrentProfile = &m_prMP4;
		}
		break;
	case SYSTEMSFORMAT_MOV:
		m_pCurrentProfile = &m_prMP4QT; break;
	case SYSTEMSFORMAT_AVI:
		m_pCurrentProfile = &m_prMP4AVI; break;
	case SYSTEMSFORMAT_VCD_STILL:
		m_pCurrentProfile = constraint == CONSTRAINT_PAL ? &m_prVCDPal_Still : &m_prVCDNtsc_Still; break;
	case SYSTEMSFORMAT_SVCD_STILL:
		m_pCurrentProfile = constraint == CONSTRAINT_PAL ? &m_prSVCDPal_Still : &m_prSVCDNtsc_Still; break;
	case SYSTEMSFORMAT_FLV:
		m_pCurrentProfile = &m_prFLV; break;
	case SYSTEMSFORMAT_DVB:
		m_pCurrentProfile = &m_prDVB; break;
	case SYSTEMSFORMAT_RM:
		m_pCurrentProfile = &m_prRM; break;
	default:
		return S_FALSE;
	}


	return S_OK;
}

HRESULT CMPEGObj::ReceiveAudio(IMediaSample *pSample)
{
	m_bAudioLocked = true;
	DWORD dwTimeRequired = timeGetTime();

	TraceVerbose("#### Entering ReceiveAudio\n");

	m_eventIsPrimed.Wait(INFINITE);
	if (m_bPrimed == false || m_bStopped == true) 
	{
		TraceVerbose("~~~~~~~DISCARDING SAMPLES Audio Receive Exit 1\n");
		return S_FALSE;
	}

	
	CAutoLock lock(&m_ReceiveLock);
	if (m_bPrimed == false || m_bStopped == true) 
	{
		TraceVerbose("~~~~~~~DISCARDING SAMPLES Audio Receive Exit 2\n");
		m_bAudioLocked = false;
		return S_FALSE;
	}

	TraceVerbose("++     Audio: %I64d\n", m_nAudioSamplesReceived + 1);

	m_nAudioSamplesReceivedSincePause++;
	m_nAudioSamplesReceived++;

	REFERENCE_TIME rtStart = 0;
	pSample->GetTime(&rtStart, &m_rtCurrentAudio);
	if (m_rtCurrentAudio == 0) m_rtCurrentAudio = rtStart;

//	ASSERT(pSample->IsSyncPoint() == S_OK);
//	ASSERT(pSample->IsPreroll() == S_FALSE);

	HRESULT hr = m_pEncode->EncodeAudioSample(pSample);
	if (FAILED(hr))	{

		TraceVerbose("~~~~~~~ Audio Receive Exit 3\n");
		m_bAudioLocked = false;
		return hr;
	}

//	TraceVerbose("++     Audio Exit: %I64d. Time=%lu\n", m_nAudioSamplesReceived, timeGetTime() - dwTimeRequired);

	TraceVerbose("~~~~~~~ Audio Receive Exit 4\n");
	m_bAudioLocked = false;
	return hr;
}

HRESULT CMPEGObj::ReceiveVideo(IMediaSample *pSample)
{
	// we don't need a lock here because the pins are going to make sure
	// that they only call themselves once. So theoretically, this functions
	// could be called twice, but the compare statement below is multithread safe

	TraceVerbose("#### Entering ReceiveVideo\n");

	m_eventIsPrimed.Wait(INFINITE);
	if (m_bPrimed == false || m_bStopped == true)
	{
		TraceVerbose("~~~~~~~DISCARDING SAMPLES Video Receive Exit 1\n");
		return S_FALSE;
	}

	CAutoLock lock(&m_ReceiveLock);
	if (m_bPrimed == false || m_bStopped == true)	
	{
		TraceVerbose("~~~~~~~DISCARDING SAMPLES Video Receive Exit 2\n");
		return S_FALSE;
	}

	m_nVideoFramesReceivedSincePause++;
	m_nVideoFramesReceived++;

	REFERENCE_TIME rtStart = 0;
	pSample->GetTime(&rtStart, &m_rtCurrentVideo);

	TraceVerbose("++     Video: %I64d ! %I64d - %I64d\n", m_nVideoFramesReceived + 1, rtStart, m_rtCurrentVideo);

	if (m_rtCurrentVideo == 0) // may not have stop time
		m_rtCurrentVideo = rtStart;

	BYTE* pBuffer = 0;
	HRESULT hr = pSample->GetPointer(&pBuffer);
	ASSERT(hr == S_OK);

	if (m_bLicensed == false) 
	{
		m_LogoOverlay.OverlayLogo(pBuffer, 
			m_pEncode->GetSourceInfo().nSourceWidth,
			m_pEncode->GetSourceInfo().nSourceHeight);
	}

//	ASSERT(pSample->IsSyncPoint() == S_OK);
	ASSERT(pSample->IsPreroll() == S_FALSE);

	hr = m_pEncode->EncodeVideoSample(pSample);
	if (FAILED(hr)) {
		TraceVerbose("~~~~~~~ Video Receive Exit 3\n");
		return hr;
	}

//	TraceVerbose("++     Video Exit: %I64d. Time=%lu\n", m_nVideoFramesReceived, timeGetTime() - dwTimeRequired);

	TraceVerbose("~~~~~~~ Video Receive Exit 4\n");
	return NOERROR;
}



REFERENCE_TIME CMPEGObj::GetCurrentTime()
{
	if (m_pEncode->GetWritingAudio() == false)
		return m_rtCurrentVideo;

	if (m_pEncode->GetWritingVideo() == false)
		return m_rtCurrentAudio;

	if (m_iStreamCount <= 1)
		return max(m_rtCurrentVideo, m_rtCurrentAudio);

	return min(m_rtCurrentVideo, m_rtCurrentAudio);
}

void CMPEGObj::StopConversion()
{
	CAutoLock lock(m_pFilter->GetMainLock());

	if (m_bPrimed)
	{
		// inform receive threads that we are going to stop
		// We will probably have one receive event waiting for
		// the other receive event to clear up. We then wait to
		// make sure that both get cleared
		// If we do not do so, we would be calling the encode func
		// twice from different threads
		m_bStopped = true;
		CAutoLock lock(&m_ReceiveLock); // deadlock possibility
		m_pEncode->StopConversion();
	}

	m_bPrimed = false;
	m_eventIsPrimed.Set();
	// m_eventIsPrimed.Reset();
	// TODO, CAREFUL
}

CMPEGProfile& CMPEGObj::GetCurrentSettingsProfile()
{
	_ASSERT(m_pCurrentProfile);
	return (*m_pCurrentProfile);
}

CMPEGProfile& CMPEGObj::GetSettingsProfile(SystemsOutputFormat systemsFormat, Constraint constraint)
{
	/* NEW_FORMAT CHANGE POINT */

	switch (systemsFormat)
	{
	case SYSTEMSFORMAT_MPEG1: 
		return m_prMPEG1; 
		break;
	case SYSTEMSFORMAT_VCD:
		switch (constraint)	{
			case CONSTRAINT_NTSC: return m_prVCDNtsc;
			case CONSTRAINT_FILM: return m_prVCDNtsc;
			case CONSTRAINT_PAL: return m_prVCDPal;
		}
		break;
	case SYSTEMSFORMAT_MPEG2: 
		if (constraint == CONSTRAINT_HD)
			return m_prMPEG2_HD;

		return m_prMPEG2; 
		break;
	case SYSTEMSFORMAT_SVCD:
		switch (constraint) 	{
			case CONSTRAINT_NTSC: return m_prSVCDNtsc;
			case CONSTRAINT_FILM: return m_prSVCDNtsc;
			case CONSTRAINT_PAL: return m_prSVCDPal;
		}
		break;
	case SYSTEMSFORMAT_DVD:
		switch (constraint)	{
			case CONSTRAINT_NTSC: return m_prDVDNtsc;
			case CONSTRAINT_FILM: return m_prDVDNtsc;
			case CONSTRAINT_PAL: return m_prDVDPal;
		}
	case SYSTEMSFORMAT_MP4:
		{
			switch (constraint)	{
				case CONSTRAINT_IPOD: return m_prMP4IPod;
				case CONSTRAINT_IPHONE: return m_prMP4IPhone;
				case CONSTRAINT_IPOD_NANO: return m_prMP4IPod_Nano;
			}

			return m_prMP4;
		}
	case SYSTEMSFORMAT_MOV:
		{
			return m_prMP4QT;
		}
	case SYSTEMSFORMAT_AVI:
		{
			return m_prMP4AVI;
		}
	case SYSTEMSFORMAT_3GP:
		{
			return m_pr3GP;
		}
	case SYSTEMSFORMAT_3G2:
		{
			return m_pr3G2;
		}
	case SYSTEMSFORMAT_PSP:
		{
			return m_prPSP;
		}
	case SYSTEMSFORMAT_FLV:
		{
			return m_prFLV;
		}
	case SYSTEMSFORMAT_DVB:
		{
			return m_prDVB;
		}
	case SYSTEMSFORMAT_RM:
		{
			return m_prRM;
		}

	}

	return m_prMPEG1;
}

HRESULT CMPEGObj::SaveSettings(BSTR strKey)
{
	HRESULT hr = S_OK;

	USES_CONVERSION;

	CRegKey regKey;
	regKey.Create(HKEY_CURRENT_USER, W2T(strKey));

	wchar_t szSubKey[1024];
	wcscpy_s(szSubKey, 1024, strKey);
	wcscat_s(szSubKey, 1024, L"\\DirectEncode_MPEG1");
	m_prMPEG1.SaveProfile(szSubKey);

	wcscpy_s(szSubKey, 1024, strKey);
	wcscat_s(szSubKey, 1024, L"\\DirectEncode_MPEG2");
	m_prMPEG2.SaveProfile(szSubKey);

	wcscpy_s(szSubKey, 1024, strKey);
	wcscat_s(szSubKey, 1024, L"\\DirectEncode_DVDPal");
	m_prDVDPal.SaveProfile(szSubKey);

	wcscpy_s(szSubKey, 1024, strKey);
	wcscat_s(szSubKey, 1024, L"\\DirectEncode_DVDNtsc");
	m_prDVDNtsc.SaveProfile(szSubKey);

	wcscpy_s(szSubKey, 1024, strKey);
	wcscat_s(szSubKey, 1024, L"\\DirectEncode_VCDPal");
	m_prVCDPal.SaveProfile(szSubKey);

	wcscpy_s(szSubKey, 1024, strKey);
	wcscat_s(szSubKey, 1024, L"\\DirectEncode_VCDNtsc");
	m_prVCDNtsc.SaveProfile(szSubKey);

	wcscpy_s(szSubKey, 1024, strKey);
	wcscat_s(szSubKey, 1024, L"\\DirectEncode_SVDPal");
	m_prSVCDPal.SaveProfile(szSubKey);

	wcscpy_s(szSubKey, 1024, strKey);
	wcscat_s(szSubKey, 1024, L"\\DirectEncode_SVDNtsc");
	m_prSVCDNtsc.SaveProfile(szSubKey);

	return hr;
}

//
// GetClassID
//
// This is the only method of IPersist
//
STDMETHODIMP CMPEGObj::GetClassID(CLSID *pClsid)
{
    return m_pFilter->GetClassID(pClsid);

} // GetClassID


//
// ScribbleToStream
//
// Overriden to write our state into a stream
//
HRESULT CMPEGObj::WriteToStream(IStream *pStream)
{
    HRESULT hr;

    WRITEOUT(m_bMultiplex);
 
    return NOERROR;

} // ScribbleToStream


//
// ReadFromStream
//
// Likewise overriden to restore our state from a stream
//
HRESULT CMPEGObj::ReadFromStream(IStream *pStream)
{
    HRESULT hr;

    READIN(m_bMultiplex);
   
    return NOERROR;

} // ReadFromStream


HRESULT CMPEGObj::LoadSettings(BSTR strKey)
{
	
	HRESULT hr = S_OK;

	USES_CONVERSION;

	MessageBox(0, W2A(strKey), 0, 0);

	CRegKey regKey;
	regKey.Open(HKEY_CURRENT_USER, W2T(strKey));
	
	DWORD dwVal = FALSE;

	wchar_t szSubKey[1024];
	wcscpy_s(szSubKey, 1024, strKey);
	wcscat_s(szSubKey, 1024, L"\\DirectEncode_MPEG1");
	m_prMPEG1.LoadProfile(szSubKey);

	wcscpy_s(szSubKey, 1024, strKey);
	wcscat_s(szSubKey, 1024, L"\\DirectEncode_MPEG2");
	m_prMPEG2.LoadProfile(szSubKey);

	wcscpy_s(szSubKey, 1024, strKey);
	wcscat_s(szSubKey, 1024, L"\\DirectEncode_DVDPal");
	m_prDVDPal.LoadProfile(szSubKey);

	wcscpy_s(szSubKey, 1024, strKey);
	wcscat_s(szSubKey, 1024, L"\\DirectEncode_DVDNtsc");
	m_prDVDNtsc.LoadProfile(szSubKey);

	wcscpy_s(szSubKey, 1024, strKey);
	wcscat_s(szSubKey, 1024, L"\\DirectEncode_VCDPal");
	m_prVCDPal.LoadProfile(szSubKey);

	wcscpy_s(szSubKey, 1024, strKey);
	wcscat_s(szSubKey, 1024, L"\\DirectEncode_VCDNtsc");
	m_prVCDNtsc.LoadProfile(szSubKey);

	wcscpy_s(szSubKey, 1024, strKey);
	wcscat_s(szSubKey, 1024, L"\\DirectEncode_SVDPal");
	m_prSVCDPal.LoadProfile(szSubKey);

	wcscpy_s(szSubKey, 1024, strKey);
	wcscat_s(szSubKey, 1024, L"\\DirectEncode_SVDNtsc");
	m_prSVCDNtsc.LoadProfile(szSubKey);
	return hr;
}


HRESULT CMPEGObj::PrimeForEncode()
{
	if (IsPrimed())
	{
		Trace("Prime called, but was not gone through because it has already been called\n");
		return S_FALSE;
	}

	CAutoLock lock(m_pFilter->GetMainLock());

	Trace("Prime Entered!\n");
	
	m_nVideoFramesReceived = 0;
	m_nAudioSamplesReceived = 0;
	m_nVideoFramesReceivedSincePause = 0; 
	m_nAudioSamplesReceivedSincePause = 0;

	m_rtCurrentAudio = 0;
	m_rtCurrentVideo = 0;

	HRESULT hr = S_OK;

	m_pEncode->SetVideoEncoder("erdmpg-6.dll");

	bool bEnableNewFormats = false;
	m_bLicensed = false;
	if (m_bAuthenticated)
	{
		if (m_pLicense == NULL)	m_pLicense = new CLicense();
		m_bLicensed = m_pLicense->IsLicenseValid(m_szLicense, bEnableNewFormats);
		m_bLicensedMP4 = m_bLicensed;
	}

	VideoOutputFormat vFormat;
	AudioOutputFormat aFormat;
	SystemsOutputFormat sFormat;
	Constraint sConstraint;

	m_pCurrentProfile->GetVideoFormat(&vFormat);
	m_pCurrentProfile->GetAudioFormat(&aFormat);
	m_pCurrentProfile->GetSystemsFormat(&sFormat);
	m_pCurrentProfile->GetConstraint(&sConstraint);

	if (vFormat == 	VIDEOFORMAT_MPEG4 ||
		vFormat == 	VIDEOFORMAT_H263 ||
		vFormat == VIDEOFORMAT_H264 ||
		aFormat == AUDIOFORMAT_AAC ||
		sFormat == SYSTEMSFORMAT_MP4 ||
		sFormat == SYSTEMSFORMAT_3GP ||
		sFormat == SYSTEMSFORMAT_MOV ||
		sFormat == SYSTEMSFORMAT_3G2 ||
		sFormat == SYSTEMSFORMAT_PSP ||
		sFormat == SYSTEMSFORMAT_AVI
		)
	{
		if (m_bLicensed == true && m_bLicensedMP4 == false)
		{
			m_bLicensed = false;
			MessageBox(0, "MPEG-4 Encoding has to be separately licensed. Visit www.standardmpeg.com for more information.", "Not licensed", 0);
		}

	}

	if (sFormat == SYSTEMSFORMAT_FLV ||
		sFormat == SYSTEMSFORMAT_RM ||
		sFormat == SYSTEMSFORMAT_DVB ||
		sConstraint == CONSTRAINT_IPHONE ||
		sConstraint == CONSTRAINT_HD ||
		sConstraint == CONSTRAINT_IPOD_NANO ||
		vFormat == VIDEOFORMAT_FLV )
	{
		if (m_bLicensed == true && bEnableNewFormats == false)
		{
			m_bLicensed = false;
			MessageBox(0, "The selected format requires Standard MPEG Encoder v6.0 with an appropriate license. Visit www.standardmpeg.com for more information.", "Not licensed", 0);
		}
	}

	m_iStreamCount = 0;
	m_rtCurrentVideo = 0;
	m_rtCurrentAudio = 0;
	m_iStreamsStopped = 0;
	
	WAVEFORMATEX* pwfxSrc = NULL;
	if (m_pFilter->GetPin(1)->IsConnected())
	{
		CMPEGInputPin* pAudioInPin = (CMPEGInputPin*)m_pFilter->GetPin(1);
		pwfxSrc = pAudioInPin->GetWaveFormat();
		m_iStreamCount++;
		m_bHasAudio = true;
	}


	VIDEOINFOHEADER* pvidInfo1 = NULL;
	VIDEOINFOHEADER2* pvidInfo2 = NULL;

	if (m_pFilter->GetPin(0)->IsConnected())
	{
		CMPEGInputPin* pVideoInPin = (CMPEGInputPin*)m_pFilter->GetPin(0);
		if (pVideoInPin->GetVideoInfoHeaderLevel() == 1)
			pvidInfo1 = pVideoInPin->GetVideoInfoHeader();
		else
			pvidInfo2 = pVideoInPin->GetVideoInfoHeader2();
		m_iStreamCount++;
		m_bHasVideo = true;
	}
	
	ASSERT(m_iStreamCount);
	if (m_iStreamCount == 0)
		return E_FAIL;

	BITMAPINFOHEADER * pbmHeader = NULL;
	if (pvidInfo1 || pvidInfo2)
	{
		VIDEOINFOHEADER vidInfo;
		
		if (pvidInfo1)
		{
			vidInfo.AvgTimePerFrame = pvidInfo1->AvgTimePerFrame;
			vidInfo.bmiHeader = pvidInfo1->bmiHeader;
		}
		else
		{
			vidInfo.AvgTimePerFrame = pvidInfo2->AvgTimePerFrame;
			vidInfo.bmiHeader = pvidInfo2->bmiHeader;
		}

		pbmHeader = pvidInfo1 ? &(pvidInfo1->bmiHeader) : &(pvidInfo2->bmiHeader);

		long nInputWidth = pbmHeader->biWidth;
		long nInputHeight = pbmHeader->biHeight;
		
		if (nInputWidth < 0)  nInputWidth = -nInputWidth;
		if (nInputHeight < 0) nInputHeight = -nInputHeight;
	
		ASSERT(nInputWidth);
		ASSERT(nInputHeight);

		if (nInputWidth == 0 || nInputHeight == 0)
		{
			m_bPrimed = false;
			return VFW_E_INVALID_RECT;
		}

		if (m_pEncode->GetSourceInfo().dSourceFPS == 0.0f)
		{
			if (vidInfo.AvgTimePerFrame == 0)
				m_pEncode->GetSourceInfo().dSourceFPS = 0; // will cause out of sync
			else
				m_pEncode->GetSourceInfo().dSourceFPS = 10000000.0  / vidInfo.AvgTimePerFrame;
		}
	}
	
	if (m_bMultiplex == false)
	{
		m_pCurrentProfile->GetMuxProfile()->SetMultiplexStreams(FALSE);
	}

	m_pEncode->SetEncodeProfile(m_pCurrentProfile);
	m_pEncode->SetInputFormats(pwfxSrc, pbmHeader);
	m_pEncode->SetOutputFile(m_szOutputFile);

	hr = m_pEncode->StartConversion();
	
	Trace("Prime Exited!\n");

	m_bPrimed = true;

	return hr;
}

signed __int64 CMPEGObj::SeekOutput(signed __int64 newPos, int nID)
{
	CMPEGOutputPin* pOutputPin = NULL;
	if (nID == 0 || m_bMultiplex == true)
		pOutputPin = m_pFilter->m_pOutPinSystems;
	else if (nID == 1)
		pOutputPin = m_pFilter->m_pOutPinVideo;
	else if (nID == 2)
		pOutputPin = m_pFilter->m_pOutPinAudio;

	return pOutputPin->Seek(newPos);
}

HRESULT CMPEGObj::Deliver(unsigned char* pBuf, int nBufLen, int nID)
{
	TraceVerbose("CMPEGObj::Deliver entered\n");

	if (m_dwSleep)
	{
		TraceVerbose("Sleeping!!!\n");
		Sleep(m_dwSleep);
	}

	CMPEGOutputPin* pOutputPin = NULL;
	if (nID == 0 || m_bMultiplex == true)
		pOutputPin = m_pFilter->m_pOutPinSystems;
	else if (nID == 1)
		pOutputPin = m_pFilter->m_pOutPinVideo;
	else if (nID == 2)
		pOutputPin = m_pFilter->m_pOutPinAudio;

	return pOutputPin->SendSample(pBuf, nBufLen);
}

bool CMPEGObj::IsPrimed()
{
	return m_bPrimed;
}

void CMPEGObj::Pause()
{	
	if (m_bPrimed == false)
	{
		m_eventIsPrimed.Reset(); // set the wait
		PrimeForEncode();
		m_bStopped = false;
		m_eventIsPrimed.Set(); // release the wait
	}
	/*
	else if (m_bPrimed)
	{
		// m_pEncode->EndOfStream();
		StopConversion();
		OutputDebugString("STOPPING AT PAUSE!!");
	}
	*/
}

void CMPEGObj::SetShouldMultiplex(bool b)
{
	m_bMultiplex = b;
	m_pFilter->IncrementPinVersion();
}

bool CMPEGObj::GetShouldMultiplex()
{
	return m_bMultiplex;
}
