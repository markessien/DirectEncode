// WMVCreatorObj.cpp : Implementation of CWMVCreatorObjObj
#include "stdafx.h"
#include "WMVCreatorObj.h"
#include "..\..\erdlib\erdlicense.h"

// CWMVCreatorObjObj

// CWMVCreatorObj

STDMETHODIMP CWMVCreatorObj::StartConversion(void)
{
	Validate();

	m_Convert.StartConversion();

	return S_OK;
}

STDMETHODIMP CWMVCreatorObj::StopConversion(void)
{
	m_Convert.StopConversion();

	return S_OK;
}

STDMETHODIMP CWMVCreatorObj::get_Duration(DOUBLE* pVal)
{
	*pVal = m_Convert.GetDuration();

	return S_OK;
}

STDMETHODIMP CWMVCreatorObj::get_Progress(DOUBLE* pVal)
{
	*pVal = m_Convert.GetProgress();

	return S_OK;
}

STDMETHODIMP CWMVCreatorObj::put_Progress(DOUBLE newVal)
{
	// this is not a good thing to do
	m_Convert.Seek(newVal);

	return S_OK;
}

STDMETHODIMP CWMVCreatorObj::LoadSystemProfiles(void)
{
	m_Convert.GetSystemProfiles();

	return S_OK;
}

STDMETHODIMP CWMVCreatorObj::get_SystemProfileCount(long* pVal)
{
	if (pVal == NULL) return E_POINTER;

	*pVal = (long)m_Convert.GetSystemProfiles()->GetCount();

	return S_OK;
}

STDMETHODIMP CWMVCreatorObj::get_SystemProfile(LONG Index, IWMVProfile** pVal)
{
	CProfile* pp = m_Convert.GetSystemProfile(Index);
	if (pp == NULL)
	{
		*pVal = NULL;
		return S_OK;
	}

	// create profile object here
	CComPtr<IWMVProfile> pProfile;
	HRESULT hr = pProfile.CoCreateInstance(CLSID_WMVProfile);
	if (FAILED(hr)) return E_POINTER;

	// attach our internal profile class to the profile object

	// first, cast the interface to a C++ class
	CWMVProfile* p = (CWMVProfile*)pProfile.p;

	// then set the pointer to the class to the appropriate class
	p->m_pProfile = m_Convert.GetSystemProfile(Index);

	// addref it
	pProfile.CopyTo(pVal);


	return S_OK;
}

STDMETHODIMP CWMVCreatorObj::LoadSystemCodecs(void)
{
	m_Convert.LoadSystemCodecs();

	return S_OK;
}

STDMETHODIMP CWMVCreatorObj::get_VideoCodecCount(long* pVal)
{
	if (pVal)
		*pVal = (long)m_Convert.GetVideoCodecs()->GetCount();

	return S_OK;
}

STDMETHODIMP CWMVCreatorObj::get_VideoCodec(LONG Index, IWMVCodec** pVal)
{
	if (m_Convert.GetVideoCodec(Index) == NULL)
		return S_OK;

	// create profile object here
	CComPtr<IWMVCodec> pCodec;
	HRESULT hr = pCodec.CoCreateInstance(CLSID_WMVCodec);
	if (FAILED(hr)) return E_POINTER;

	// attach our internal profile class to the profile object

	// first, cast the interface to a C++ class
	CWMVCodec* p = (CWMVCodec*)pCodec.p;

	// then set the pointer to the class to the appropriate class
	p->m_pCodec = m_Convert.GetVideoCodec(Index);

	// addref it
	pCodec.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CWMVCreatorObj::get_InputFile(BSTR* pVal)
{
	m_Convert.GetInputFile().CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CWMVCreatorObj::put_InputFile(BSTR newVal)
{
	m_Convert.SetInputFile(newVal);

	return S_OK;
}

STDMETHODIMP CWMVCreatorObj::get_OutputFile(BSTR* pVal)
{
	m_Convert.GetOutputFile().CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CWMVCreatorObj::put_OutputFile(BSTR newVal)
{
	m_Convert.SetOutputFile(newVal);

	return S_OK;
}

STDMETHODIMP CWMVCreatorObj::get_ConversionProfile(IWMVProfile** pVal)
{
	// create profile object here
	CComPtr<IWMVProfile> pProfile;
	HRESULT hr = pProfile.CoCreateInstance(CLSID_WMVProfile);
	if (FAILED(hr)) return E_POINTER;

	// attach our internal profile class to the profile object

	// first, cast the interface to a C++ class
	CWMVProfile* p = (CWMVProfile*)pProfile.p;

	// then set the pointer to the class to the appropriate class
	p->m_pProfile = m_Convert.GetConversionProfile();

	// addref it
	pProfile.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CWMVCreatorObj::putref_ConversionProfile(IWMVProfile* newVal)
{
	if (newVal == NULL)
		return E_POINTER;

	CWMVProfile* p = (CWMVProfile*)newVal;
	m_Convert.SetConversionProfile(p->m_pProfile);

//	_ASSERT(!"Do not change the profile. Copy a new profile into it!");
//	return E_NOTIMPL;

	return S_OK;
}

STDMETHODIMP CWMVCreatorObj::get_ProfileCount(LONG* pVal)
{
//	this->OnComplete();

	*pVal = (LONG)m_Convert.GetProfiles()->GetCount();

	return S_OK;
}

STDMETHODIMP CWMVCreatorObj::get_Profile(long Index, IWMVProfile** pVal)
{
	CProfile* pp = m_Convert.GetProfile(Index);
	if (pp == NULL)
	{
		*pVal = NULL;
		return S_OK;
	}

	// create profile object here
	CComPtr<IWMVProfile> pProfile;
	HRESULT hr = pProfile.CoCreateInstance(CLSID_WMVProfile);
	if (FAILED(hr)) return E_POINTER;

	// attach our internal profile class to the profile object

	// first, cast the interface to a C++ class
	CWMVProfile* p = (CWMVProfile*)pProfile.p;

	// then set the pointer to the class to the appropriate class
	p->m_pProfile = m_Convert.GetProfile(Index);

	// addref it
	pProfile.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CWMVCreatorObj::putref_Profile(long Index, IWMVProfile* newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVCreatorObj::get_AudioCodec(long Index, IWMVCodec** pVal)
{
	if (m_Convert.GetAudioCodec(Index) == NULL)
		return S_OK;

	// create profile object here
	CComPtr<IWMVCodec> pCodec;
	HRESULT hr = pCodec.CoCreateInstance(CLSID_WMVCodec);
	if (FAILED(hr)) return E_POINTER;

	// attach our internal profile class to the profile object

	// first, cast the interface to a C++ class
	CWMVCodec* p = (CWMVCodec*)pCodec.p;

	// then set the pointer to the class to the appropriate class
	p->m_pCodec = m_Convert.GetAudioCodec(Index);

	// addref it
	pCodec.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CWMVCreatorObj::get_AudioCodecCount(long* pVal)
{
	if (pVal)
		*pVal = (long)m_Convert.GetAudioCodecs()->GetCount();

	return S_OK;
}

STDMETHODIMP CWMVCreatorObj::get_EncodeFramerate(long* pVal)
{
	if (pVal)
		*pVal = (long)m_Convert.GetEncodeFramerate();

	return S_OK;
}

void CWMVCreatorObj::CreateLicense()
{
#ifdef _DEBUG
	srand( (unsigned int )timeGetTime( ) );
	
	// generate 4 random letters
	char sz[128];
	for (int i=0;i<4;i++)
	{
		int n = rand() % 25;
		char c = (char)(int)(65 + n);
		sz[i] = c;
	}

	// tranform next 4 to match
	for (int i=4;i<8;i++)
	{
		sz[i] = NMBR_TRANSFORM(sz[i-4], 8356 + (i - 4));
	}

	for (int i=8;i<12;i++)
	{
		int n = rand() % 25;
		char c = (char)(int)(65 + n);
		sz[i] = c;
	}

	for (int i=12;i<16;i++)
	{
		sz[i] = COS_TRANSFORM(NMBR_TRANSFORM(sz[i-4], 2386 + ((i+1) * 4)), 864);
	}

	sz[16] = 0;

	OutputDebugString(sz);
	OutputDebugString("\n");
#endif
}

bool CWMVCreatorObj::Validate()
{
	// simple key validation. If you have this code you
	// have the key anyways.
	
	if (wcslen(m_strLicenseKey) > 16 || wcslen(m_strLicenseKey) < 16)
		return false;

	// Essien Simple Time Variant License Key Scheme
	m_Convert.SetLicensed(true);

	int v = 0;
	while (v < 2)
	{
		long nHour = (timeGetTime() / (1000 * 60 * 60));

		// verify first part of license. First half is function/time based
		// second half is function based
		for (int i=0;i<4;i++)
		{
			char c = NMBR_TRANSFORM(m_strLicenseKey[i], 8356 + i);
			if (m_strLicenseKey[i+4] != c)
			{
				m_Convert.SetLicensed(false);
			}
		}

		for (int i=8;i<12;i++)
		{
			char c = NMBR_TRANSFORM(m_strLicenseKey[i], 2386 + ((i+5) * 4));
			c = COS_TRANSFORM(c, 864);
			if (m_strLicenseKey[i+4] != c)
			{
				m_Convert.SetLicensed(false);
			}
		}

		v++;
	}

	return true;
}

STDMETHODIMP CWMVCreatorObj::put_LicenseKey(BSTR newVal)
{
	if (wcslen(newVal) < 100)
		wcscpy(m_strLicenseKey, newVal);

	return S_OK;
}
