#include "StdAfx.h"
#include "codec.h"

CCodec::CCodec(void)
{
	m_nIndex = 0;
	m_nComplexity = 0;
	m_nMaxPasses = 0;
	m_strCodecGuid = "";
	m_strCodecName = "";
	m_nPreference = 0;
	m_nIdealCodecFormat = 0;
}

CCodec::~CCodec(void)
{
	ClearFormats();
}

HRESULT CCodec::SupportedVBRModes(BOOL* CBR1Pass, BOOL* CBR2Pass, BOOL* VBR1Pass, BOOL* VBR2Pass, LONG* ConstrainValue)
{
	*CBR1Pass = m_formatSettings.m_bSupportsCBR_1Pass;
	*CBR2Pass = m_formatSettings.m_bSupportsCBR_2Pass;
	*VBR1Pass = m_formatSettings.m_bSupportsVBR_1Pass;
	*VBR2Pass = m_formatSettings.m_bSupportsVBR_2Pass_Constrained;
	*ConstrainValue = 0;
	return NOERROR;
}

HRESULT CCodec::Load(IWMCodecInfo2* pICodecInfo, GUID guidType, int nIndex)
{
	m_nIndex = nIndex;

	// Get codec name
    DWORD dwCount = 0;
    HRESULT hr = pICodecInfo->GetCodecName(guidType, nIndex, NULL, &dwCount);
	if (SUCCEEDED(hr) && dwCount > 0) 
	{
		WCHAR *wszCodecName = new WCHAR[ dwCount + 1 ];
		if (wszCodecName == NULL) return E_POINTER;
		pICodecInfo->GetCodecName(guidType, nIndex, wszCodecName, &dwCount);
		m_strCodecName = wszCodecName;
		delete [] wszCodecName;
	}
	
	m_majorType = guidType;

	// Get props interface of code	
	CComPtr<IWMStreamConfig> pStreamConfigCodec;
    hr = pICodecInfo->GetCodecFormat(guidType, nIndex, 0, &pStreamConfigCodec);
	if (SUCCEEDED(hr) && pStreamConfigCodec)
		LoadMediaProps(pStreamConfigCodec);

	LoadFormats(pICodecInfo, guidType, nIndex);

	/*
	CComQIPtr<IWMCodecInfo3> pICodecInfo3(pICodecInfo);

	m_nComplexityLive = GetDWordProperty(pICodecInfo3, guidType, nIndex, g_wszComplexityLive);
	m_nComplexityMax = GetDWordProperty(pICodecInfo3, guidType, nIndex, g_wszComplexityMax);
	m_nComplexityOffline = GetDWordProperty(pICodecInfo3, guidType, nIndex, g_wszComplexityOffline);
	_ASSERT(m_nComplexityMax == 0);

	LoadPassAndVBRSettings(pICodecInfo3, guidType, nIndex);

	// We have to do a bit of trickery here. Because we limit the format enum
	// settings above, only the first codec lists all format settings. So we cheat
	// and load them individually for each

	// 1-pass cbr
	QueryPropertySupported(pICodecInfo3, guidType, nIndex, WMT_TYPE_DWORD, g_wszNumPasses, 1);
	QueryPropertySupported(pICodecInfo3, guidType, nIndex, WMT_TYPE_BOOL, g_wszVBREnabled, FALSE);
	LoadFormats(pICodecInfo, guidType, nIndex);

	// 1-pass vbr
	QueryPropertySupported(pICodecInfo3, guidType, nIndex, WMT_TYPE_DWORD, g_wszNumPasses, 1);
	QueryPropertySupported(pICodecInfo3, guidType, nIndex, WMT_TYPE_BOOL, g_wszVBREnabled, TRUE);
	LoadFormats(pICodecInfo, guidType, nIndex);

	// 2-pass cbr
	QueryPropertySupported(pICodecInfo3, guidType, nIndex, WMT_TYPE_DWORD, g_wszNumPasses, 2);
	QueryPropertySupported(pICodecInfo3, guidType, nIndex, WMT_TYPE_BOOL, g_wszVBREnabled, FALSE);
	LoadFormats(pICodecInfo, guidType, nIndex);

	// 2-pass vbr
	QueryPropertySupported(pICodecInfo3, guidType, nIndex, WMT_TYPE_DWORD, g_wszNumPasses, 2);
	QueryPropertySupported(pICodecInfo3, guidType, nIndex, WMT_TYPE_BOOL, g_wszVBREnabled, TRUE);
	LoadFormats(pICodecInfo, guidType, nIndex);
*/
	return S_OK;
}

DWORD CCodec::GetDWordProperty(IWMCodecInfo3* pICodecInfo3, GUID guidType, int nIndex, LPCWSTR wszQuery)
{
	DWORD dwSize = 0;
	WMT_ATTR_DATATYPE attrdw = WMT_TYPE_DWORD;

	HRESULT hr = pICodecInfo3->GetCodecEnumerationSetting(guidType, nIndex, wszQuery, &attrdw,
														NULL, &dwSize);

	DWORD dwValue = 0;
	hr = pICodecInfo3->GetCodecEnumerationSetting(guidType, nIndex, wszQuery, &attrdw,
														(BYTE*)&dwValue, &dwSize);

	if (FAILED(hr))
		return 0;

	return dwValue;
}

HRESULT CCodec::QueryPropertySupported(IWMCodecInfo3* pICodecInfo3, GUID guidType, int nIndex, WMT_ATTR_DATATYPE dtype, LPCWSTR wszQuery, DWORD dwValue)
{
	BOOL bSettings = (dwValue != 0);
	DWORD dwSize = dtype == WMT_TYPE_DWORD ? sizeof(DWORD) : sizeof(BOOL); // fix
	WMT_ATTR_DATATYPE typedw = dtype;

	HRESULT hr = S_OK;
	// we set our enum settings to 2 pass, then enum to see who supports it
	if (dtype == WMT_TYPE_DWORD)
		hr = pICodecInfo3->SetCodecEnumerationSetting(guidType, nIndex, wszQuery, typedw,
														(BYTE*)&dwValue, dwSize);
	else
		hr = pICodecInfo3->SetCodecEnumerationSetting(guidType, nIndex, wszQuery, typedw,
														(BYTE*)&bSettings, dwSize);
	if (hr == NS_E_UNSUPPORTED_PROPERTY)
	{
		return S_FALSE;
	}

	// cross check
	DWORD cFormat = 0;
	hr = pICodecInfo3->GetCodecFormatCount(guidType, nIndex, &cFormat);
	if (cFormat == 0)
		return S_FALSE;

	return S_OK;
}

HRESULT CCodec::LoadPassAndVBRSettings(IWMCodecInfo3* pICodecInfo3, GUID guidType, int nIndex)
{
	// get 2 pass encoding stuff
	
	if (pICodecInfo3 == NULL)
	{
		// old or 3rd party codec
		m_nMaxPasses = 1;
		return S_OK;
	}

	if (QueryPropertySupported(pICodecInfo3, guidType, nIndex, WMT_TYPE_DWORD, g_wszNumPasses, 2) == S_OK)
	{
		m_nMaxPasses = 2;
		
		// it supports 2-pass encoding
		if (QueryPropertySupported(pICodecInfo3, guidType, nIndex, WMT_TYPE_BOOL, g_wszVBREnabled, TRUE) == S_OK)
		{
			// it supports 2.Pass VBR
			m_formatSettings.m_bSupportsVBR_2Pass_Constrained = true;
			m_formatSettings.m_bSupportsVBR_2Pass_Unconstrained = true;
		}

		if (QueryPropertySupported(pICodecInfo3, guidType, nIndex, WMT_TYPE_BOOL, g_wszVBREnabled, FALSE) == S_OK)
		{
			// it supports CBR
			m_formatSettings.m_bSupportsCBR_2Pass = true;
		}

		// now we reset it back to one-pass, and see what it supports there
		if (QueryPropertySupported(pICodecInfo3, guidType, nIndex, WMT_TYPE_DWORD, g_wszNumPasses, 1) == S_OK)
		{
			if (QueryPropertySupported(pICodecInfo3, guidType, nIndex, WMT_TYPE_BOOL, g_wszVBREnabled, TRUE) == S_OK)
			{
				// it supports 1-Pass VBR
				m_formatSettings.m_bSupportsVBR_1Pass = true;
			}

			if (QueryPropertySupported(pICodecInfo3, guidType, nIndex, WMT_TYPE_BOOL, g_wszVBREnabled, FALSE) == S_OK)
			{
				// it supports CBR
				m_formatSettings.m_bSupportsCBR_1Pass = true;
			}
		}
	}
	else
	{
		m_nMaxPasses = 1;

		// it supports one-pass encoding only

		if (QueryPropertySupported(pICodecInfo3, guidType, nIndex, WMT_TYPE_BOOL, g_wszVBREnabled, TRUE) == S_OK)
		{
			// it supports VBR
			m_formatSettings.m_bSupportsVBR_1Pass = true;
		}

		if (QueryPropertySupported(pICodecInfo3, guidType, nIndex, WMT_TYPE_BOOL, g_wszVBREnabled, FALSE) == S_OK)
		{
			// it supports CBR
			m_formatSettings.m_bSupportsCBR_1Pass = true;
		}
	}

	return NOERROR;
}

HRESULT CCodec::LoadMediaProps(IWMStreamConfig* pStreamConfig)
{
	CComPtr<IWMMediaProps> pProps;
	HRESULT hr = pStreamConfig->QueryInterface(IID_IWMMediaProps, (void**)&pProps);
	
	// Get media type
	if (SUCCEEDED(hr) && pProps)
	{
		DWORD cbtype = 0;
		hr = pProps->GetMediaType(NULL, &cbtype);

		BYTE *pBuf = new BYTE[cbtype];
		WM_MEDIA_TYPE *pType = (WM_MEDIA_TYPE*) pBuf;
		hr = pProps->GetMediaType(pType, &cbtype);
		
		m_codecGuid = pType->subtype;
		CComBSTR strGuid(pType->subtype);
		m_strCodecGuid = strGuid;
		
		DeterminePreference(pType->subtype);
		delete [] pBuf;
	}

	return hr;
}

GUID CCodec::GetMajorType(void)
{
	return m_majorType;
}

CComBSTR CCodec::GetCodecGuid(void)
{
	return m_strCodecGuid;
}

long CCodec::GetMaxPasses(void)
{
	return m_nMaxPasses;
}

HRESULT CCodec::LoadFormats(IWMCodecInfo2* pICodecInfo, GUID guidType, int nIndex)
{
	HRESULT hr = S_OK;
	DWORD dwFormatCount = 0;
	hr = pICodecInfo->GetCodecFormatCount(guidType, nIndex, &dwFormatCount);
	if (FAILED(hr))
		return hr;

	OutputDebugString("\n\nListing formats for AudioCodec:");
	OutputDebugStringW(m_strCodecName);
	OutputDebugStringW(L"\n\n");

	for (int i=0;i<(long)dwFormatCount;i++)
	{
		DWORD dwCount = 0;
		hr = pICodecInfo->GetCodecFormatDesc(guidType, nIndex, i, NULL, NULL, &dwCount);
		if (SUCCEEDED(hr))
		{
			CComPtr<IWMStreamConfig> pStreamConfig;
			WCHAR *wszDesc = new WCHAR[ dwCount + 1 ];
			hr = pICodecInfo->GetCodecFormatDesc(guidType, nIndex, i, &pStreamConfig, wszDesc, &dwCount);
			if (SUCCEEDED(hr))
			{
				DWORD dwBitrate = 0;
				pStreamConfig->GetBitrate(&dwBitrate);
			
				char sz[128];
				sprintf(sz, "Bitrate=%lu\n", dwBitrate);
				OutputDebugString(sz);

				Format* pFormat = new Format;
				pFormat->strName = wszDesc;
				pFormat->nFormatIndex = i;
				pFormat->dwBitrate = dwBitrate;
				m_arrFormats.Add(pFormat);

				if (m_codecGuid == WMMEDIASUBTYPE_ACELPnet)
				{
					if (dwBitrate >= 16000)
						m_nIdealCodecFormat = i;
				}
				else if (m_codecGuid == WMMEDIASUBTYPE_WMSP1)
				{
					if (dwBitrate >= 20000)
						m_nIdealCodecFormat = i;
				}
				else if (m_codecGuid == WMMEDIASUBTYPE_WMAudioV9 ||
						m_codecGuid == WMMEDIASUBTYPE_WMAudioV8 ||
						m_codecGuid == WMMEDIASUBTYPE_WMAudioV7)
				{
					//if (dwBitrate > 192000  )
					//	m_nIdealCodecFormat = i;
				}
				else
				{
					m_nIdealCodecFormat = i; // last listed format, usually maximum
				}
			}

	
			delete [] wszDesc;
			pStreamConfig = NULL;
		}
	}

	return NOERROR;
}

void CCodec::ClearFormats(void)
{
	while (m_arrFormats.GetCount())
	{
		Format* pFormat = m_arrFormats.GetAt(0);
		delete pFormat;
		m_arrFormats.RemoveAt(0);
	}
	_ASSERT(m_arrFormats.GetCount() == 0);
}

CFormatArray* CCodec::GetFormats(void)
{
	return &m_arrFormats;
}

long CCodec::GetIndex(void)
{
	return m_nIndex;
}

void CCodec::SetPreference(long n)
{
	m_nPreference = n;
}

long CCodec::GetPreference(void)
{
	return m_nPreference;
}

void CCodec::DeterminePreference(GUID g)
{
	// video
	if (g == WMMEDIASUBTYPE_WMV3)
		m_nPreference = 100;
	else if (g == WMMEDIASUBTYPE_WMV2)
		m_nPreference = 90;
	else if (g == WMMEDIASUBTYPE_WMV1)
		m_nPreference = 80;

	if (g == WMMEDIASUBTYPE_WMAudioV9)
		m_nPreference = 100;
	else if (g == WMMEDIASUBTYPE_WMAudioV8)
		m_nPreference = 90;
	else if (g == WMMEDIASUBTYPE_WMAudioV7)
		m_nPreference = 80;
}

long CCodec::GetIdealFormat(void)
{
	return m_nIdealCodecFormat;
}
