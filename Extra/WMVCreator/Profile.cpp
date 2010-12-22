#include "StdAfx.h"
#include "profile.h"
#include <dshowasf.h>

CProfile::CProfile(void)
{
	m_nBestVideoCodec = 0;
	m_nBestAudioCodec = 0;
	m_nBestAudioFormat = 0;
	m_nVideoCodecCount = 0;
}

CProfile::~CProfile(void)
{
}

HRESULT CProfile::Load(IWMProfile* pWMProfile)
{
	HRESULT hr = NOERROR;

	// This function retrieves an existing WMProfile object
	// usually got from a listing of the system profiles,
	// and populates this object from that WMProfile. After
	// that, it takes over control of the WMProfile object

	m_pIWMProfile = pWMProfile;

	// Get if audio and video are supported
	hr |= GetSupportedStreams();

	// get name and profile description
	hr |= GetNameAndDescription();
	ASSERT(SUCCEEDED(hr));

	m_VideoStream.SetCodecArray(m_pVideoCodecArray);
	m_AudioStream.SetCodecArray(m_pAudioCodecArray);

	// Load the video stream parameters from the profile
	// information. The codec info is got from the stream
	hr = m_VideoStream.Load(m_pIWMProfile);
	if (m_bHasVideo) ASSERT(hr == S_OK);

	// same for audio
	hr = m_AudioStream.Load(m_pIWMProfile);
	if (m_bHasAudio) ASSERT(hr == S_OK);

	return NOERROR;
}

HRESULT CProfile::GetSupportedStreams()
{
	// check if profile has audio and video
	m_bHasAudio = false;
	m_bHasVideo = false;

	unsigned long nCount = 0;
	m_pIWMProfile->GetStreamCount(&nCount);
	for (int k=0;k<(int)nCount;k++)
	{
		CComPtr<IWMStreamConfig> pStreamConfig;
		m_pIWMProfile->GetStream(k, &pStreamConfig);
		if (pStreamConfig)	
		{
			GUID gType;
			pStreamConfig->GetStreamType(&gType);

			if (gType == WMMEDIATYPE_Audio)
			{
				m_bHasAudio = true;
			}

			if (gType == WMMEDIATYPE_Video)
			{
				m_bHasVideo = true;
			}

			if (m_bHasVideo && m_bHasAudio)
			{
				// if wé have got both already, no need
				// to continue looking
				return S_OK;
			}
		}
		else
			continue;
	}

	return S_FALSE; // we do not have both streams
}

HRESULT CProfile::GetNameAndDescription()
{
	// How large is the profile name?
	HRESULT hr = S_OK;
	DWORD cchName = 0;
	hr = m_pIWMProfile->GetName(NULL, &cchName);
	if(SUCCEEDED(hr))
	{
		WCHAR *wszName = new WCHAR[ cchName + 1 ];
		if(NULL == wszName) return E_POINTER;
		hr = m_pIWMProfile->GetName(wszName, &cchName);
		if(SUCCEEDED(hr))
		{
			m_strName = wszName;
		}
		delete [] wszName;
	}

	DWORD cchDescription = 0;
	hr = m_pIWMProfile->GetDescription(NULL, &cchDescription);
	if(SUCCEEDED(hr))
	{
		WCHAR *wszDescription = new WCHAR[ cchDescription + 1 ];
		if(NULL == wszDescription) return E_POINTER;
		hr = m_pIWMProfile->GetDescription(wszDescription, &cchDescription);
		if(SUCCEEDED(hr))
		{
			m_strDescription = wszDescription;
		}
		delete[] wszDescription;
	}

	return S_OK;
}

IWMProfile* CProfile::GetWMProfile(void)
{
	// Get windows media profile. This function is called
	// when the stream is to be encoded. If we do not have
	// the object yet, we create it using the settings we currently
	// have on the thingy

	DestroyObjects();

	if (m_pIWMProfile == NULL)
		CreateNew();
	else
		_ASSERT(FALSE);

	return m_pIWMProfile;
}

bool CProfile::GetHasVideo(void)
{
	return m_bHasVideo;
}

bool CProfile::GetHasAudio(void)
{
	return m_bHasAudio;
}

CVideoStream* CProfile::GetVideoStream(void)
{
	return &m_VideoStream;
}

CAudioStream* CProfile::GetAudioStream(void)
{
	return &m_AudioStream;
}

void CProfile::SetCodecArray(CCodecArray* pVideoCodecArray, CCodecArray* pAudioCodecArray, long nBestVideo, long nBestAudio)
{
	m_nBestVideoCodec = nBestVideo;
	m_nBestAudioCodec = nBestAudio;
	m_pVideoCodecArray = pVideoCodecArray;
	m_pAudioCodecArray = pAudioCodecArray;
	m_VideoStream.SetCodecArray(m_pVideoCodecArray);
	m_AudioStream.SetCodecArray(m_pAudioCodecArray);
}

HRESULT CProfile::CreateNew(void)
{
    HRESULT hr = S_OK;
    CComPtr <IWMProfileManager> pIWMProfileManager;
    hr = WMCreateProfileManager(&pIWMProfileManager);
    if(FAILED(hr) || pIWMProfileManager == NULL) return hr;

	// create empty profile with current version
    hr = pIWMProfileManager->CreateEmptyProfile(WMT_VER_9_0, &m_pIWMProfile);
    if (FAILED(hr)) 
	{
		hr = pIWMProfileManager->CreateEmptyProfile(WMT_VER_8_0, &m_pIWMProfile);
		if (FAILED(hr))
		{
			hr = pIWMProfileManager->CreateEmptyProfile(WMT_VER_7_0, &m_pIWMProfile);
			if (FAILED(hr))
				return hr;
		}
	}

	// set name and description
    hr = m_pIWMProfile->SetName(m_strName);
	_ASSERT(!FAILED(hr));

    hr = m_pIWMProfile->SetDescription(m_strDescription);
    _ASSERT(!FAILED(hr));

	if (m_bHasAudio)
	{
 		hr = m_AudioStream.CreateNew(m_pIWMProfile);
		if (FAILED(hr)) return hr;
	}

	if (m_bHasVideo)
	{
		m_VideoStream.SetBestVideoCodec(m_nBestVideoCodec);
		hr = m_VideoStream.CreateNew(m_pIWMProfile);
		if (FAILED(hr)) return hr;
	}

	return S_OK;
}

void CProfile::SetSourceInfo(double fps, long cx, long cy, long vbitrate, long abitrate)
{
	// call this with the params of the source to allow the profile to
	// reconfigure itself to make the best possible source file. For example
	// if a video is 20x20, why increase the size to 160x120? The rescaling
	// can be done during playback. If any of the values above is 0, the def
	// profile value will be used
	m_VideoStream.SetSourceInfo(fps, cx, cy);
}

void CProfile::ConfigureProfileFromSystemID(BSTR strID, bool bUpdate)
{
	// this will load settings that correspond to the system ID.
	// the Smart settings should be turned on, and the things specified
	// here may change

	if (strID == NULL)
		strID = m_strSystemID;

	m_strSystemID = strID;
	if (wcscmp(strID, L"mobile-phones") == 0)
	{
		m_strName = "Mobile Phones";
		m_strDescription = "For use with mobile/smart phones";

		// set video settings
		m_VideoStream.SetVideoCodec(m_nBestVideoCodec); // best codec currently on system. If fails, no fallback

		if (bUpdate)
		{
			if (m_VideoStream.GetAutoDimensions() == true)
				m_VideoStream.SetVideoDimensions(160, 120); // if source is smaller, it does not increase size
		}
		else
		{
			m_VideoStream.SetVideoDimensions(160, 120); // if source is smaller, it does not increase size
			m_VideoStream.SetAutoDimensions(true);
			m_VideoStream.SetVBR(true); // if vbr available, will use, else cbr
			m_VideoStream.SetQuality(75);
			m_VideoStream.SetBitrate(186152); // 225kbs. If vbr does not work, it falls back on this
			m_VideoStream.SetFramerate(15); // if src fps lower, uses src fps. if does not work, goes back to this
			m_VideoStream.SetKeyFramerate(3); // TODO: Always make keyframe rate LOWER thatn length of fiel
			m_VideoStream.SetPasses(2); // if not possible, will silently ignore and do one-pass
		}

		// set audio
		m_AudioStream.SetAudioCodec(m_nBestAudioCodec);
		m_AudioStream.SelectNearestFormat(true, 32048, 2); // bitrate, vbr, passes. If vbr don't work, uses cbr with val there.
	}
	else if (wcscmp(strID, L"small-screen") == 0)
	{
		m_strName = "PDAs, Portable Media Center and other small screen devices";
		m_strDescription = "For use with small screen devices";

		// set video settings
		if (bUpdate)
		{
			if (m_VideoStream.GetAutoDimensions() == true)
				m_VideoStream.SetVideoDimensions(320, 240); // if source is smaller, it does not increase size
		}
		else
		{
			m_VideoStream.SetVideoCodec(m_nBestVideoCodec); // best codec currently on system. If fails, no fallback
			m_VideoStream.SetVideoDimensions(320, 240); // if source is smaller, it does not increase size
			m_VideoStream.SetAutoDimensions(true);
			m_VideoStream.SetVBR(true); // if vbr available, will use, else cbr
			m_VideoStream.SetQuality(90);
			m_VideoStream.SetBitrate(186152); // 225kbs. If vbr does not work, it falls back on this
			m_VideoStream.SetFramerate(24); // if src fps lower, uses src fps. if does not work, goes back to this
			m_VideoStream.SetKeyFramerate(1); // TODO: Always make keyframe rate LOWER thatn length of fiel
			m_VideoStream.SetPasses(2); // if not possible, will silently ignore and do one-pass
		}

		// set audio
		m_AudioStream.SetAudioCodec(m_nBestAudioCodec);
		m_AudioStream.SelectNearestFormat(true, 32048, 2); // bitrate, vbr, passes. If vbr don't work, uses cbr with val there.

	}
	else if (wcscmp(strID, L"website-lo") == 0)
	{
		m_strName = "Putting on a website for download or streaming (Low quality)";
		m_strDescription = "For download";

		// set video settings
		if (bUpdate)
		{
			if (m_VideoStream.GetAutoDimensions() == true)
				m_VideoStream.SetVideoDimensions(240, 180); // if source is smaller, it does not increase size
		}
		else
		{
			m_VideoStream.SetVideoCodec(m_nBestVideoCodec); // best codec currently on system. If fails, no fallback
			m_VideoStream.SetVideoDimensions(240, 180); // if source is smaller, it does not increase size
			m_VideoStream.SetAutoDimensions(true);
			m_VideoStream.SetVBR(true); // if vbr available, will use, else cbr
			m_VideoStream.SetQuality(90);
			m_VideoStream.SetBitrate(189000); // 225kbs. If vbr does not work, it falls back on this
			m_VideoStream.SetFramerate(24); // if src fps lower, uses src fps. if does not work, goes back to this
			m_VideoStream.SetKeyFramerate(1); // TODO: Always make keyframe rate LOWER thatn length of fiel
			m_VideoStream.SetPasses(2); // if not possible, will silently ignore and do one-pass
		}

		// set audio
		m_AudioStream.SetAudioCodec(m_nBestAudioCodec);
		m_AudioStream.SelectNearestFormat(true, 32000, 2); // bitrate, vbr, passes. If vbr don't work, uses cbr with val there.

	}
	else if (wcscmp(strID, L"website-hi") == 0)
	{
		m_strName = "Putting on a website for download or streaming (High quality)";
		m_strDescription = "For use with mobile/smart phones";

		// set video settings
		if (bUpdate)
		{
			if (m_VideoStream.GetAutoDimensions() == true)
				m_VideoStream.SetVideoDimensions(320, 240); // if source is smaller, it does not increase size
		}
		else
		{
			m_VideoStream.SetVideoCodec(m_nBestVideoCodec); // best codec currently on system. If fails, no fallback
			m_VideoStream.SetVideoDimensions(320, 240); // if source is smaller, it does not increase size
			m_VideoStream.SetAutoDimensions(true);
			m_VideoStream.SetVBR(true); // if vbr available, will use, else cbr
			m_VideoStream.SetQuality(90);
			m_VideoStream.SetBitrate(632000); // 225kbs. If vbr does not work, it falls back on this
			m_VideoStream.SetFramerate(24); // if src fps lower, uses src fps. if does not work, goes back to this
			m_VideoStream.SetKeyFramerate(1); // TODO: Always make keyframe rate LOWER thatn length of fiel
			m_VideoStream.SetPasses(2); // if not possible, will silently ignore and do one-pass
		}

		// set audio
		m_AudioStream.SetAudioCodec(m_nBestAudioCodec);
		m_AudioStream.SelectNearestFormat(true, 64040, 2); // bitrate, vbr, passes. If vbr don't work, uses cbr with val there.
	}
	else if (wcscmp(strID, L"desktop") == 0)
	{
		m_strName = "Viewing/Listening from your Desktop or a CD";
		m_strDescription = "Viewing from your desktop";

		// set video settings
		if (bUpdate)
		{
			if (m_VideoStream.GetAutoDimensions() == true)
				m_VideoStream.SetVideoDimensions(640, 480); // if source is smaller, it does not increase size
		}
		else
		{
			m_VideoStream.SetVideoCodec(m_nBestVideoCodec); // best codec currently on system. If fails, no fallback
			m_VideoStream.SetVideoDimensions(640, 480); // if source is smaller, it does not increase size
			m_VideoStream.SetAutoDimensions(true);
			m_VideoStream.SetVBR(true); // if vbr available, will use, else cbr
			m_VideoStream.SetQuality(95);
			m_VideoStream.SetBitrate(1868000); // 225kbs. If vbr does not work, it falls back on this
			m_VideoStream.SetFramerate(30); // if src fps lower, uses src fps. if does not work, goes back to this
			m_VideoStream.SetKeyFramerate(1); // TODO: Always make keyframe rate LOWER thatn length of fiel
			m_VideoStream.SetPasses(2); // if not possible, will silently ignore and do one-pass
		}

		// set audio
		m_AudioStream.SetAudioCodec(m_nBestAudioCodec);
		m_AudioStream.SelectNearestFormat(true, 128040, 2); // bitrate, vbr, passes. If vbr don't work, uses cbr with val there.

	}
	else
	{
		m_strName = "User defined profile";
		m_strDescription = "User specified settings";
		_ASSERT(FALSE);
	}
}
void CProfile::SetSupportedStreams(bool bVideo, bool bAudio)
{
}

void CProfile::DestroyObjects(void)
{
	// remove all profile objects. LEaves the settings as they are
	m_AudioStream.DestroyObjects();
	m_VideoStream.DestroyObjects();
	m_pIWMProfile = NULL;
}
