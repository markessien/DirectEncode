// WMVProfile.cpp : Implementation of CWMVProfile

#include "stdafx.h"
#include "WMVProfile.h"


// CWMVProfile



STDMETHODIMP CWMVProfile::get_ProfileName(BSTR* pVal)
{
	CComBSTR str = m_pProfile->m_strName;
	str.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CWMVProfile::put_ProfileName(BSTR newVal)
{
	m_pProfile->m_strName = newVal;

	return S_OK;
}

STDMETHODIMP CWMVProfile::get_ProfileDescription(BSTR* pVal)
{
	CComBSTR str = m_pProfile->m_strDescription;
	str.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CWMVProfile::put_ProfileDescription(BSTR newVal)
{
	m_pProfile->m_strDescription = newVal;

	return S_OK;
}

STDMETHODIMP CWMVProfile::get_HasVideoStream(VARIANT_BOOL* pVal)
{
	*pVal = m_pProfile->GetHasVideo() ? VARIANT_TRUE : VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CWMVProfile::put_HasVideoStream(VARIANT_BOOL newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVProfile::get_HasAudioStream(VARIANT_BOOL* pVal)
{
	*pVal = m_pProfile->GetHasAudio() ? VARIANT_TRUE : VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CWMVProfile::put_HasAudioStream(VARIANT_BOOL newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVProfile::get_Bitrate(LONG* pVal)
{
	*pVal = m_pProfile->GetVideoStream()->GetBitrate() + m_pProfile->GetAudioStream()->GetBitrate();

	return S_OK;
}

STDMETHODIMP CWMVProfile::put_Bitrate(LONG newVal)
{
	// You cannot set profile bitrate, you need to set stream bitrates
	return E_NOTIMPL;
}

STDMETHODIMP CWMVProfile::get_StringEquivalent(BSTR Param, BSTR* pVal)
{
	CComBSTR str = L"Undefined";
	str.CopyTo(pVal);

	if (_wcsnicmp(Param, L"dimensions", 10) == 0)
	{
		LONG cx, cy;
		get_VideoWidth(&cx);
		get_VideoHeight(&cy);

		wchar_t* pstrParam2 = wcsstr(Param, L";");

		char sz[128];
		CComBSTR str;
		if (m_pProfile->GetVideoStream()->GetAutoDimensions())
		{
			if (pstrParam2)
			{
				// special case. We want the value, not the text.
				// Read this code and WEEEEP!
				long x = _wtol(pstrParam2 + 1);
				long y = _wtol(wcsstr(pstrParam2 + 1, L"x") + 1); // DANGEROUS. If wrongly parsed, will crash
				sprintf(sz, "%lu x %lu", x < cx && y < cy ? x : cx, x < cx && y < cy ? y : cy);
				str = sz;
			}
			else
				str = "Automatically select";
		}
		else if (m_pProfile->GetVideoStream()->GetDimensionsFromSrc())
		{
			if (pstrParam2)
			{
				// special case. We want the value, not the text
				long x = _wtol(pstrParam2 + 1);
				long y = _wtol(wcsstr(pstrParam2 + 1, L"x") + 1); // DANGEROUS. If wrongly parsed, will crash
				sprintf(sz, "%lu x %lu", x, y);
				str = sz;
			}
			else
				str = "Same as source";
		}
		else
		{
			sprintf(sz, "%lu x %lu", cx, cy);
			str = sz;
		}
		
		str.CopyTo(pVal);
	}
	else if (wcscmp(Param, L"bitrate") == 0)
	{
		long l = 0;
		get_Bitrate(&l);

		if (m_pProfile->GetVideoStream()->GetAutoBitrate())
		{
			CComBSTR str = "Automatically select based on system";
			str.CopyTo(pVal);
		}
		else
		{
			char sz[128];
			sprintf(sz, "%lu Kbs", l);

			CComBSTR str = sz;
			str.CopyTo(pVal);
		}
	}
	else if (wcscmp(Param, L"streams") == 0)
	{
		VARIANT_BOOL bVideo, bAudio;
		get_HasVideoStream(&bVideo);
		get_HasAudioStream(&bAudio);
		
		CComBSTR str;
		if (bVideo == VARIANT_TRUE && bAudio == VARIANT_FALSE)
		{
			str = L"Video Only";
		}
		else if (bVideo == VARIANT_FALSE && bAudio == VARIANT_TRUE)
		{
			str = L"Audio Only";
		}
		else
		{
			str = "Audio and Video";
		}

		str.CopyTo(pVal);
	}
	else if (_wcsnicmp(Param, L"framerate", 9) == 0)
	{
		wchar_t* pstrParam2 = wcsstr(Param, L";");

		double dFPS = 0;
		get_Framerate(&dFPS);

		char sz[128];
		CComBSTR str;
		if (m_pProfile->GetVideoStream()->GetAutomaticFramerate())
		{
			if (pstrParam2)
			{
				// special case. We want the value, not the text
				double dSrcFPS = _wtof(pstrParam2 + 1);
				sprintf(sz, "%.2f", dSrcFPS < dFPS ? dSrcFPS : dFPS);
				str = sz;
			}
			else
				str = "Automatically select";
		}
		else if (m_pProfile->GetVideoStream()->GetFramerateFromSrc())
		{
			if (pstrParam2)
			{
				// special case. We want the value, not the text
				double dSrcFPS = _wtof(pstrParam2 + 1);
				sprintf(sz, "%.2f", dSrcFPS);
				str = sz;
			}
			else
				str = "Same as source";
		}
		else
		{			
			sprintf(sz, "%.2f", dFPS);
			str = sz;
		}

		str.CopyTo(pVal);
	}

	return S_OK;
}

STDMETHODIMP CWMVProfile::put_StringEquivalent(BSTR Param, BSTR newVal)
{
	if (wcscmp(Param, L"dimensions") == 0)
	{
		CComBSTR str = newVal;
		long x = _wtol(str);
		long y =  0;

		wchar_t* pstrY = wcsstr(newVal, L"x");
		if (pstrY)
		{
			y = _wtol(pstrY + 1);
		}

		if (_wcsnicmp(newVal, L"same", 4) == 0)
		{
			// same as source file
			m_pProfile->GetVideoStream()->SetAutoDimensions(false);
			m_pProfile->GetVideoStream()->SetDimensionsFromSrc(true);
		}
		else if (_wcsnicmp(newVal, L"auto", 4) == 0)
		{
			m_pProfile->GetVideoStream()->SetAutoDimensions(true);
			m_pProfile->GetVideoStream()->SetDimensionsFromSrc(false);
			m_pProfile->ConfigureProfileFromSystemID(NULL, true);
		}
		else if (x > 0 && y > 0)
		{
			m_pProfile->GetVideoStream()->SetAutoDimensions(false);
			m_pProfile->GetVideoStream()->SetDimensionsFromSrc(false);
			m_pProfile->GetVideoStream()->SetVideoDimensions(x, y);
		}
	}
	else if (wcscmp(Param, L"bitrate") == 0)
	{
		if (_wcsnicmp(newVal, L"auto", 4) == 0)
		{
			m_pProfile->GetVideoStream()->SetAutoBitrate(true);
			m_pProfile->ConfigureProfileFromSystemID(NULL, true);
		}
		else
		{
			long bitrate = _wtol(newVal);
			if (bitrate > 0)
			{
				bitrate *= 1024;
				m_pProfile->GetVideoStream()->SetBitrate(bitrate);
				m_pProfile->GetVideoStream()->SetAutoBitrate(false);
			}
		}
	}
	else if (wcscmp(Param, L"framerate") == 0)
	{
		double fps = _wtof(newVal);
		if (_wcsnicmp(newVal, L"same", 4) == 0)
		{
			// same as source file
			m_pProfile->GetVideoStream()->SetAutoFramerate(false);
			m_pProfile->GetVideoStream()->SetFramerateFromSrc(true);
		}
		else if (_wcsnicmp(newVal, L"auto", 4) == 0)
		{
			m_pProfile->GetVideoStream()->SetAutoFramerate(true);
			m_pProfile->GetVideoStream()->SetFramerateFromSrc(false);
			m_pProfile->ConfigureProfileFromSystemID(NULL, true);
		}
		else if (fps > 0 && fps < 500)
		{
			m_pProfile->GetVideoStream()->SetFramerateFromSrc(false);
			m_pProfile->GetVideoStream()->SetAutoFramerate(false);
			m_pProfile->GetVideoStream()->SetFramerate(fps);
		}
	}
	else if (wcscmp(Param, L"streams") == 0)
	{
		if (_wcsicmp(newVal, L"audio and video") == 0)
		{
			m_pProfile->SetSupportedStreams(true, true);
		}
		else if (_wcsicmp(newVal, L"audio only") == 0)
		{
			m_pProfile->SetSupportedStreams(false, true);
		}
		else if (_wcsicmp(newVal, L"video only") == 0)
		{
			m_pProfile->SetSupportedStreams(true, false);
		}
	}

	return S_OK;
}

STDMETHODIMP CWMVProfile::get_VideoWidth(LONG* pVal)
{
	*pVal = m_pProfile->GetVideoStream()->GetVideoWidth();

	return S_OK;
}

STDMETHODIMP CWMVProfile::put_VideoWidth(LONG newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVProfile::get_VideoHeight(LONG* pVal)
{
	*pVal = m_pProfile->GetVideoStream()->GetVideoHeight();

	return S_OK;
}

STDMETHODIMP CWMVProfile::put_VideoHeight(LONG newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVProfile::get_VideoCodec(IWMVCodec** pVal)
{
	CCodec* pCodec = m_pProfile->GetVideoStream()->GetCodec();
	if (pCodec == NULL)
	{
		*pVal = NULL;
		return S_OK;
	}

	// create profile object here
	CComPtr<IWMVCodec> pWMVCodec;
	HRESULT hr = pWMVCodec.CoCreateInstance(CLSID_WMVCodec);
	if (FAILED(hr)) return E_POINTER;

	// attach our internal profile class to the profile object

	// first, cast the interface to a C++ class
	CWMVCodec* p = (CWMVCodec*)pWMVCodec.p;

	// then set the pointer to the class to the appropriate class
	p->m_pCodec = pCodec;

	// addref it
	pWMVCodec.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CWMVProfile::put_VideoCodec(IWMVCodec* newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVProfile::get_AudioCodec(IWMVCodec** pVal)
{
	CCodec* pCodec = m_pProfile->GetAudioStream()->GetCodec();
	if (pCodec == NULL)
	{
		*pVal = NULL;
		return S_OK;
	}

	// create profile object here
	CComPtr<IWMVCodec> pWMVCodec;
	HRESULT hr = pWMVCodec.CoCreateInstance(CLSID_WMVCodec);
	if (FAILED(hr)) return E_POINTER;

	// attach our internal profile class to the profile object

	// first, cast the interface to a C++ class
	CWMVCodec* p = (CWMVCodec*)pWMVCodec.p;

	// then set the pointer to the class to the appropriate class
	p->m_pCodec = pCodec;

	// addref it
	pWMVCodec.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CWMVProfile::put_AudioCodec(IWMVCodec* newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVProfile::get_KeyFrameSpacing(long* pVal)
{
	*pVal = m_pProfile->GetVideoStream()->GetKeyFrameFreq();

	return S_OK;
}

STDMETHODIMP CWMVProfile::put_KeyFrameSpacing(long newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVProfile::get_Framerate(DOUBLE* pVal)
{
	*pVal = m_pProfile->GetVideoStream()->GetFramerate();

	return S_OK;
}

STDMETHODIMP CWMVProfile::put_Framerate(DOUBLE newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVProfile::get_Quality(long* pVal)
{
	*pVal = m_pProfile->GetVideoStream()->GetQuality();

	return S_OK;
}

STDMETHODIMP CWMVProfile::put_Quality(long newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVProfile::get_VideoBitrate(long* pVal)
{
	*pVal = m_pProfile->GetVideoStream()->GetBitrate();

	return S_OK;
}

STDMETHODIMP CWMVProfile::put_VideoBitrate(long newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVProfile::get_AudioBitrate(long* pVal)
{
	*pVal = m_pProfile->GetAudioStream()->GetBitrate();

	return S_OK;
}

STDMETHODIMP CWMVProfile::put_AudioBitrate(long newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVProfile::CopyProfile(IWMVProfile* ProfileToCopy)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVProfile::get_Seekable(VARIANT_BOOL* pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVProfile::put_Seekable(VARIANT_BOOL newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}
