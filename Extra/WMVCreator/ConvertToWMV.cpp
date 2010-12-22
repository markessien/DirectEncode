#include "StdAfx.h"
#include <dshowasf.h>
#include "converttowmv.h"
#include "profile.h"

CConvertToWMV::CConvertToWMV(void) : CUnknown("ConvertToWMV", NULL, NULL),
									 m_llStart(0), 
									 m_llEnd(0), 
									 m_pCurProfile(NULL),
									 m_pCallback(NULL)
{
	m_Graph.m_pGraphEvents = this;
	m_nBestVideoCodec = 0;
	m_nBestAudioCodec = 0;
	m_bLicensed = false;

	m_logoOverlay.CreateLogo();
}

CConvertToWMV::~CConvertToWMV(void)
{
}

void CConvertToWMV::SetCallback(IGraphEvents* pCallback)
{
	m_pCallback = pCallback;
}

CProfileArray* CConvertToWMV::GetProfiles(void)
{
	// make sure codecs are loaded
	LoadSystemCodecs();

	if (m_arrProfiles.GetCount() == 0)
	{
		AddCustomProfile("mobile-phones");
		AddCustomProfile("small-screen");
		AddCustomProfile("website-lo");
		AddCustomProfile("website-hi");
		AddCustomProfile("desktop");
	}

	return &m_arrProfiles;
}

CProfileArray* CConvertToWMV::GetSystemProfiles(void)
{
	// This function will load all system profiles
	// into profile objects. It will also add a single
	// custom profile that can be freely configured

	// we should not need to load the system profiles
	// more than once
	if (m_arrSysProfiles.GetCount() > 0) return &m_arrSysProfiles;

	LoadSystemCodecs();

	// create profile manager that contains the profiles
    CComPtr <IWMProfileManager> pIWMProfileManager;
    HRESULT hr = WMCreateProfileManager(&pIWMProfileManager);
    if(FAILED(hr))
    {
        ThrowError(hr, "ListProfiles: Failed to create profile manager!");
        return NULL; // error
    }

	// retrieve the interface. Highest supported by wmv 9
    CComQIPtr<IWMProfileManager2, &IID_IWMProfileManager2> pIPM2(pIWMProfileManager);
    if (pIPM2 == NULL) 
    {
        ThrowError(hr, "ListProfiles: Failed to QI IWMProfileManager2!");
        return NULL;
    }

	// m_CustomProfile.SetCodecArray(&m_arrSysCodecs);

	// loop twice to get the wmv8 and wmv7 profiles
	int c = 2;
	while (c)
	{
		// set the profile version. wmv9 does not have system profiles
		hr = pIPM2->SetSystemProfileVersion( c == 2 ? WMT_VER_7_0 : WMT_VER_8_0);
		if(FAILED(hr)) 
		{
			ThrowError(hr, "ListProfiles: Failed to set system profile version!");
			continue;
		}
		
		// get number of system profiles
		DWORD cProfiles = 0;
		hr = pIWMProfileManager->GetSystemProfileCount(&cProfiles);
		if(FAILED(hr))
		{
			ThrowError(hr, "ListProfiles: Failed to get system profile count!");
			continue;
		}
    
		// Load the profile strings
		for(int i = 0; i < (int)cProfiles; ++i)
		{
			// load system profile. IWMProfileManager::LoadSystemProfile creates a 
			// profile object populated with data from a system profile.

			CComPtr<IWMProfile> pIWMProfile;
			hr = pIWMProfileManager->LoadSystemProfile(i, &pIWMProfile);
			if(FAILED(hr))
			{
				continue;
			}
			
			// create new profile object
			CProfile* pProfile = new CProfile;
			pProfile->SetCodecArray(&m_arrVideoCodecs, &m_arrAudioCodecs, m_nBestVideoCodec, m_nBestAudioCodec);

			// load the settings from the wmv profile struct to our own object
			pProfile->Load(pIWMProfile);

			// add the loaded profile to the list
			m_arrSysProfiles.Add(pProfile);
		}

		c--;
	}

//	m_CustomProfile.CreateNew();

	return &m_arrSysProfiles;
}

void CConvertToWMV::ThrowError(HRESULT hr, char* pstrMsg)
{
	if (m_pCallback)
		m_pCallback->OnGraphEvent(NULL, EC_ERRORABORT, hr, (LONG_PTR)pstrMsg);
}

CProfile* CConvertToWMV::GetProfile(unsigned int nIndex)
{
	if (nIndex < m_arrProfiles.GetCount() && 
		nIndex >= 0)
		return m_arrProfiles.GetAt(nIndex);

	return NULL;
}

HRESULT STDMETHODCALLTYPE CConvertToWMV::Notify(INSSBuffer3 *pNSSBuffer3, IPin *pPin, REFERENCE_TIME *prtStart, REFERENCE_TIME *prtEnd)
{
	m_Graph.Notify(pNSSBuffer3, pPin, prtStart, prtEnd);

	/*
	BYTE* pBuffer = NULL;
	DWORD dwLength = 0;
	if (pNSSBuffer3)
	{
		pNSSBuffer3->GetBufferAndLength(&pBuffer, &dwLength);
		m_logoOverlay.OverlayLogo(pBuffer, m_Graph.m_nVideoWidth, m_Graph.m_nVideoHeight);
	}
*/
	return S_OK;
};


CProfile* CConvertToWMV::GetSystemProfile(unsigned int nIndex)
{
	if (nIndex < m_arrSysProfiles.GetCount() && 
		nIndex >= 0)
		return m_arrSysProfiles.GetAt(nIndex);

	return NULL;
}

void CConvertToWMV::LoadSystemCodecs(void)
{
	if (m_arrVideoCodecs.GetCount() > 0 ||
		m_arrAudioCodecs.GetCount() > 0) return;

    HRESULT hr = S_OK;
    CComPtr <IWMProfileManager> pIWMProfileManager;
    hr = WMCreateProfileManager(&pIWMProfileManager);
    if(FAILED(hr))
    {
        ThrowError(hr, "ListProfiles: Failed to create profile manager!");
		return;
    }
    
	CComPtr<IWMCodecInfo2> pICodecInfo;
    if (pICodecInfo == NULL)
    {
        hr = pIWMProfileManager->QueryInterface(IID_IWMCodecInfo2, (void**)&pICodecInfo);
        if(!pICodecInfo || FAILED(hr))
			return;
    }
  
	long nBestCodec = 0;
	long nCurBestPreference = 0;

	// Load the video codecs
    DWORD dwCodecCount = 0;
    pICodecInfo->GetCodecInfoCount(WMMEDIATYPE_Video, &dwCodecCount);
    for (int i=0;i<(long)dwCodecCount;i++)
    {   
		CCodec* pCodec = new CCodec;
		pCodec->Load(pICodecInfo, WMMEDIATYPE_Video, i);

		if (pCodec->GetPreference() >= nCurBestPreference)
		{
			nCurBestPreference = pCodec->GetPreference();
			nBestCodec = i;
		}

		m_arrVideoCodecs.Add(pCodec);
    }

	m_nBestVideoCodec = nBestCodec;

	nBestCodec = 0;
	nCurBestPreference = 0;

	// load the audio codecs
	dwCodecCount = 0;
    pICodecInfo->GetCodecInfoCount(WMMEDIATYPE_Audio, &dwCodecCount);
    for (int i=0;i<(long)dwCodecCount;i++)
    {   
		CCodec* pCodec = new CCodec;
		pCodec->Load(pICodecInfo, WMMEDIATYPE_Audio, i);

		if (pCodec->GetPreference() >= nCurBestPreference)
		{
			nCurBestPreference = pCodec->GetPreference();
			nBestCodec = i;
		}

		m_arrAudioCodecs.Add(pCodec);
    }

	m_nBestAudioCodec = nBestCodec;
}


HRESULT CConvertToWMV::StartConversion(void)
{
	m_Graph.SetInputFile(m_strInputFile);
	m_Graph.SetOutputFile(m_strOutputFile);

	HRESULT hr = m_Graph.CreateCaptureGraphBuilder();
	if (FAILED(hr)) return hr;

	hr = m_Graph.CreateGraphBuilder();
	if (FAILED(hr)) return hr;

	hr = m_Graph.m_pBuilder->SetFiltergraph(m_Graph.m_pGraph);
	if (FAILED(hr)) return hr;

	m_Graph.PreLoadFileInformation();

	hr = m_Graph.AddSourceFilter();
	if (FAILED(hr)) return hr;

	hr = m_Graph.AddWMVFileWriter();
	if (FAILED(hr)) return hr;

	if (m_pCurProfile)
	{
		m_pCurProfile->SetSourceInfo(m_Graph.m_dFramerate, 
									m_Graph.m_nVideoWidth, 
									m_Graph.m_nVideoHeight,
									m_Graph.m_nVideoBitrate,
									0);

		hr = m_Graph.ConfigureWMVWriterWithProfile(m_pCurProfile->GetWMProfile());
		if (FAILED(hr)) return hr;
	}


	if (m_bLicensed == false)
	{
		hr = m_Graph.AddOverlayFilter();
		if (FAILED(hr))
		{
			ThrowError(hr, "A processing filter is not available");
			StopConversion();
			return hr;
		}
	}

	m_Graph.SetWMWriterCallback(this);

	if (m_bLicensed == true)
	{
		hr = m_Graph.RenderStream(NULL, NULL, 
								m_Graph.m_pSourceFilter,
								NULL,
								m_Graph.m_pWMVWriter);
	}
	else
	{
		hr = m_Graph.RenderStream(NULL, NULL, 
								m_Graph.m_pSourceFilter,
								NULL,
								m_Graph.m_pOverlay);
		if (FAILED(hr))
			return hr;

		hr = m_Graph.RenderStream(NULL, NULL,
								m_Graph.m_pOverlay, NULL, m_Graph.m_pWMVWriter);
	}

	if (FAILED(hr))
	{
		HRASSERT(hr);
		ThrowError(hr, "The stream could not be rendered");
		StopConversion();
		return hr;
	}

	if (m_Graph.m_pOverlay != NULL)
	{
		hr = m_Graph.ConnectFilters(m_Graph.m_pGraph, m_Graph.m_pOverlay, m_Graph.m_pWMVWriter);
	}
	
	hr = m_Graph.RenderStream(NULL, NULL, 
						m_Graph.m_pSourceFilter,
						NULL,
						m_Graph.m_pWMVWriter);

	// m_Graph.PromptForGraph(m_Graph.m_pGraph, "Edit");

	// retrieve all supported interfaces
	hr = m_Graph.GetInterfaces();
	if (m_Graph.m_pControl == NULL) return E_FAIL;

	// get all relevant info, like video widht
	hr = m_Graph.GetInformation();

	// create notification window and specify to graph
	hr = m_Graph.SetNotifications();

	if (m_pCallback)
		m_pCallback->OnGraphEvent(NULL, EC_SEGMENT_STARTED, 0, 0);

	if (m_bLicensed == false)
		m_Graph.WriteTextOnOverlay("Demo");

	m_Graph.Run(m_llStart, m_llEnd);

	return hr;
}

HRESULT CConvertToWMV::StopConversion(void)
{
	// m_Graph.Stop();
	m_Graph.Destroy();
	m_pCurProfile->DestroyObjects();

	if (m_pCallback)
		m_pCallback->OnGraphEvent(NULL, EC_COMPLETE, 0, 0);

	return NOERROR;
}

void CConvertToWMV::SetInputFile(BSTR str)
{
	m_strInputFile = str;
}

void CConvertToWMV::SetOutputFile(BSTR str)
{
	m_strOutputFile = str;
}

HRESULT CConvertToWMV::Pause(void)
{
	return m_Graph.Pause();
}

/*
HRESULT CConvertToWMV::Notify(INSSBuffer3*  pNSSBuffer3, IPin*  pPin, REFERENCE_TIME*  prtStart, REFERENCE_TIME*  prtEnd)
{
	return E_NOTIMPL;
}*/

double CConvertToWMV::GetDuration(void)
{
	return m_Graph.GetDuration();
}

double CConvertToWMV::GetProgress(void)
{
	return m_Graph.GetProgress();
}

CComBSTR CConvertToWMV::GetInputFile(void)
{
	return m_strInputFile;
}

HRESULT CConvertToWMV::OnGraphEvent(CGraph* pGraph, long lEventCode, LONG_PTR lParam1, LONG_PTR lParam2)
{
	switch (lEventCode)
	{
	case EC_COMPLETE:
		StopConversion();
	}

	return S_OK;
}

CComBSTR CConvertToWMV::GetOutputFile(void)
{
	return m_strOutputFile;
}

HRESULT CConvertToWMV::Seek(double d)
{
	return E_NOTIMPL;
}

CProfile* CConvertToWMV::GetConversionProfile(void)
{
	return m_pCurProfile;
}

void CConvertToWMV::SetConversionProfile(CProfile* pProfile)
{
	m_pCurProfile = pProfile;
}

void CConvertToWMV::AddCustomProfile(char* pstrID)
{
	CProfile* pProfile = new CProfile();
	pProfile->SetCodecArray(&m_arrVideoCodecs, &m_arrAudioCodecs, m_nBestVideoCodec, m_nBestAudioCodec);
	pProfile->ConfigureProfileFromSystemID(CComBSTR(pstrID), false);
	m_arrProfiles.Add(pProfile);
}

CCodecArray* CConvertToWMV::GetVideoCodecs(void)
{
	LoadSystemCodecs();

	return &m_arrVideoCodecs;
}

CCodecArray* CConvertToWMV::GetAudioCodecs(void)
{
	LoadSystemCodecs();

	return &m_arrAudioCodecs;
}

CCodec* CConvertToWMV::GetVideoCodec(unsigned int nIndex)
{
	if (nIndex < 0 || nIndex >= m_arrVideoCodecs.GetCount()) return NULL;

	return m_arrVideoCodecs.GetAt(nIndex);
}

CCodec* CConvertToWMV::GetAudioCodec(unsigned int nIndex)
{
	if (nIndex < 0 || nIndex >= m_arrAudioCodecs.GetCount()) return NULL;

	return m_arrAudioCodecs.GetAt(nIndex);
}

long CConvertToWMV::GetEncodeFramerate(void)
{
	return m_Graph.GetEncodeFramerate();
}

void CConvertToWMV::SetLicensed(bool bVal)
{
	m_bLicensed = bVal;
}
