// Profile.cpp: implementation of the CMPEGProfile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Profile.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMPEGProfile::CMPEGProfile() : CUnknown(NAME("CMPEGProfile"), NULL), m_pObj(NULL)
{
	m_strProfileName = L"Not Named";
	m_bFixed = false;

	memset(&m_EncodeParameters, 0, sizeof(m_EncodeParameters));

	m_pMuxProfile = new CMPEGMultiplexProfile();
	m_pMuxProfile->m_pEncodeParameters = &m_EncodeParameters;
	m_pMuxProfile->AddRef();

	m_EncodeParameters.bMultiplex = true;
	m_EncodeParameters.bDirectMultiplexing = true;
	m_EncodeParameters.bUseVideoBitrates = true;
	m_EncodeParameters.bUseAudioBitrates = true;
	m_EncodeParameters.bWriteSystemsFile = true;
	m_EncodeParameters.bWriteAudioStream = true;
	m_EncodeParameters.bWriteVideoStream = true;
	m_EncodeParameters.nOutputAudioChannels = 2;
	m_EncodeParameters.fPixelAspectRatio = (float)1.3333f;
	m_EncodeParameters.fMuxMaxDelay = 0.7f;
	m_EncodeParameters.fMuxPreload = 0.5f;
	m_EncodeParameters.bAutoSelectBitrate = true;
	m_EncodeParameters.bDeInterlace = false;
	m_EncodeParameters.bForceInterlaceDCT = false;
	m_EncodeParameters.bForceInterlaceME = false;
	m_EncodeParameters.nQualityMin = 2;
	m_EncodeParameters.nQualityMax = 31;
	m_EncodeParameters.nProfile = -1;
	m_EncodeParameters.nLevel = -1;

	ConfigureForSystemsFormat(SYSTEMSFORMAT_MPEG1, CONSTRAINT_NONE);
}

CMPEGProfile::~CMPEGProfile()
{
	SAFE_DELETE(m_pMuxProfile);
}

STDMETHODIMP CMPEGProfile::ConfigureForSystemsFormat(SystemsOutputFormat systemsFormat, Constraint constraint)
{
	/* NEW_FORMAT CHANGE POINT */
	switch (systemsFormat)
	{
	case SYSTEMSFORMAT_NONE:
		{
			SetSystemsFormat(SYSTEMSFORMAT_NONE);
			SetAudioFormat(AUDIOFORMAT_NONE);
			SetVideoFormat(VIDEOFORMAT_NONE);
			SetFramerate(0);
			SetWidth(0);
			SetHeight(0);
			SetProfileName(L"Elementary Stream Profile");
			m_pMuxProfile->SetMultiplexFormat(SYSTEMSFORMAT_NONE);
			SetAudioChannels(2);
			SetAudioBitrate(64 * 1000);
			SetVideoBitrate(350 * 1000);
			SetVideoBitrateMin(0);
			SetVideoBitrateMax(750 * 1000);
			SetAudioSampleRate(32000);
			SetVideoVBRMode(BITRATEMODE_MVBR);
			m_EncodeParameters.nQualityMin = 3; // qmin
			m_EncodeParameters.nQualityMax = 5; // qmax min video quantiser scale (VBR)
			m_EncodeParameters.nOutputVideoBufferSize = 4096 * 1000; //bufsize
			m_EncodeParameters.nOutputAudioBitrate = 92000;
			m_pMuxProfile->SetMultiplexStreams(FALSE);
			m_pMuxProfile->SetOnFlyMultiplex(FALSE);
			m_pMuxProfile->SetMultiplexOnStop(FALSE);
			m_pMuxProfile->SetDeleteElementaryStreams(FALSE);
		}
		break;
	case SYSTEMSFORMAT_FLV:
		{
			SetSystemsFormat(SYSTEMSFORMAT_FLV);
			SetAudioFormat(AUDIOFORMAT_MP3);
			SetVideoFormat(VIDEOFORMAT_FLV);
			SetFramerate(0);
			SetWidth(0);
			SetHeight(0);
			SetProfileName(L"Flash Video");
			m_pMuxProfile->SetMultiplexFormat(SYSTEMSFORMAT_FLV);
			SetAudioChannels(2);
			SetAudioBitrate(64 * 1000);
			SetVideoBitrate(350 * 1000);
			SetVideoBitrateMin(0);
			SetVideoBitrateMax(750 * 1000);
			SetAudioSampleRate(22050); // allowed = 11025, 22050, 44100
			SetVideoVBRMode(BITRATEMODE_MVBR);
		}
		break;
	case SYSTEMSFORMAT_MP4:
		{
			SetSystemsFormat(SYSTEMSFORMAT_MP4);
			SetAudioFormat(AUDIOFORMAT_AAC);
			SetVideoFormat(VIDEOFORMAT_MPEG4);
			SetFramerate(0);
			SetWidth(0);
			SetHeight(0);
			SetProfileName(L"Standard MPEG4");
			m_pMuxProfile->SetMultiplexFormat(SYSTEMSFORMAT_MP4);
			SetAudioChannels(2);
			SetAudioBitrate(64 * 1000);
			SetVideoBitrate(350 * 1000);
			SetVideoBitrateMin(0);
			SetVideoBitrateMax(750 * 1000);
			SetAudioSampleRate(32000);
			SetVideoVBRMode(BITRATEMODE_MVBR);

			if (constraint == CONSTRAINT_IPOD )
			{
				SetProfileName(L"Standard MPEG4 iPod Constrained");
				SetConstraint(CONSTRAINT_IPOD);
				SetWidth(320);
				SetHeight(240);
				SetGOPSize(300);
				SetVideoBitrateMin(750 * 1000);
				SetVideoBitrateMax(750 * 1000);

				SetVideoBitrate(750 * 1000);
				m_EncodeParameters.nQualityMin = 3; // qmin
				m_EncodeParameters.nQualityMax = 5; // qmax min video quantiser scale (VBR)
				m_EncodeParameters.nOutputVideoBufferSize = 4096 * 1000; //bufsize
				m_EncodeParameters.nOutputAudioBitrate = 92000;
			}
			else if (constraint == CONSTRAINT_IPOD_NANO)
			{
				SetProfileName(L"Standard MPEG4 iPod Nano");
				SetConstraint(CONSTRAINT_IPOD_NANO);
				SetWidth(176);
				SetHeight(128);
				SetGOPSize(300);
				SetVideoBitrateMin(256 * 1000);
				SetVideoBitrateMax(256 * 1000);

				SetVideoBitrate(256 * 1000);
				m_EncodeParameters.nQualityMin = 3; // qmin
				m_EncodeParameters.nQualityMax = 5; // qmax min video quantiser scale (VBR)
				m_EncodeParameters.nOutputVideoBufferSize = 4096 * 1000; //bufsize
				m_EncodeParameters.nOutputAudioBitrate = 92000;
			}
			else if (constraint == CONSTRAINT_IPHONE)
			{
				SetProfileName(L"Standard MPEG4 iPhone");
				SetConstraint(CONSTRAINT_IPHONE);
				SetWidth(320);
				SetHeight(240);
				SetGOPSize(300);
				SetVideoBitrateMin(750 * 1000);
				SetVideoBitrateMax(750 * 1000);

				SetVideoBitrate(750 * 1000);
				m_EncodeParameters.nQualityMin = 3; // qmin
				m_EncodeParameters.nQualityMax = 5; // qmax min video quantiser scale (VBR)
				m_EncodeParameters.nOutputVideoBufferSize = 4096 * 1000; //bufsize
				m_EncodeParameters.nOutputAudioBitrate = 92000;
			}
			else if (constraint == CONSTRAINT_H264)
			{
				SetVideoFormat(VIDEOFORMAT_H264);
			}

		}
		break;
	case SYSTEMSFORMAT_3GP:
		{
			SetSystemsFormat(SYSTEMSFORMAT_3GP);
			SetAudioFormat(AUDIOFORMAT_AAC);
			SetVideoFormat(VIDEOFORMAT_MPEG4);
			SetFramerate(0);
			SetWidth(0);
			SetHeight(0);
			SetProfileName(L"3GP");
			m_pMuxProfile->SetMultiplexFormat(SYSTEMSFORMAT_MP4);
			SetAudioChannels(2);
			SetAudioBitrate(64 * 1000);
			SetVideoBitrate(350 * 1000);
			SetVideoBitrateMin(0);
			SetVideoBitrateMax(750 * 1000);
			SetAudioSampleRate(32000);
			SetVideoVBRMode(BITRATEMODE_MVBR);
		}
		break;
	case SYSTEMSFORMAT_3G2:
		{
			SetSystemsFormat(SYSTEMSFORMAT_3G2);
			SetAudioFormat(AUDIOFORMAT_AAC);
			SetVideoFormat(VIDEOFORMAT_MPEG4);
			SetFramerate(0);
			SetWidth(0);
			SetHeight(0);
			SetProfileName(L"3G2");
			m_pMuxProfile->SetMultiplexFormat(SYSTEMSFORMAT_MP4);
			SetAudioChannels(2);
			SetAudioBitrate(64 * 1000);
			SetVideoBitrate(350 * 1000);
			SetVideoBitrateMin(0);
			SetVideoBitrateMax(750 * 1000);
			SetAudioSampleRate(32000);
			SetVideoVBRMode(BITRATEMODE_MVBR);
		}
		break;
	case SYSTEMSFORMAT_PSP:
		{
			SetSystemsFormat(SYSTEMSFORMAT_PSP);
			SetAudioFormat(AUDIOFORMAT_AAC);
			SetVideoFormat(VIDEOFORMAT_MPEG4);
			SetFramerate(29.97);
			SetWidth(0);
			SetHeight(0);
			SetProfileName(L"PSP");
			m_pMuxProfile->SetMultiplexFormat(SYSTEMSFORMAT_MP4);
			SetAudioChannels(2);
			SetAudioBitrate(64 * 1000);
			SetVideoBitrate(512 * 1000);
			SetVideoBitrateMin(0);
			SetVideoBitrateMax(512 * 1000);
			SetAudioSampleRate(24000);
			SetVideoVBRMode(BITRATEMODE_MVBR);

			SetWidth(320);
			SetHeight(240);
			SetGOPSize(300);

			m_EncodeParameters.nQualityMin = 3; // qmin
			m_EncodeParameters.nQualityMax = 5; // qmax min video quantiser scale (VBR)
			m_EncodeParameters.nOutputVideoBufferSize = 4096 * 1000; //bufsize
		}
		break;
	case SYSTEMSFORMAT_MOV:
		{
			SetSystemsFormat(SYSTEMSFORMAT_MOV);
			SetAudioFormat(AUDIOFORMAT_AAC);
			SetVideoFormat(VIDEOFORMAT_MPEG4);
			SetFramerate(0);
			SetWidth(0);
			SetHeight(0);
			SetProfileName(L"MPEG4 in Quicktime container");
			m_pMuxProfile->SetMultiplexFormat(SYSTEMSFORMAT_MOV);
			SetAudioChannels(2);
			SetAudioBitrate(64 * 1000);
			SetVideoBitrate(350 * 1000);
			SetVideoBitrateMin(0);
			SetVideoBitrateMax(750 * 1000);
			SetAudioSampleRate(32000);
			SetVideoVBRMode(BITRATEMODE_MVBR);

			if (constraint == CONSTRAINT_IPOD)
			{
				SetProfileName(L"Standard MPEG4 iPod Constrained");
				SetConstraint(CONSTRAINT_IPOD);
				SetWidth(320);
				SetHeight(240);
				SetGOPSize(300);
				SetVideoBitrateMin(0);
				SetVideoBitrateMax(1000 * 1000);

				SetVideoBitrate(750 * 1000);
				m_EncodeParameters.nQualityMin = 3; // qmin
				m_EncodeParameters.nQualityMax = 5; // qmax min video quantiser scale (VBR)
				m_EncodeParameters.nOutputVideoBufferSize = 4096 * 1000; //bufsize
				m_EncodeParameters.nOutputAudioBitrate = 92000;
			}
		}
		break;
	case SYSTEMSFORMAT_AVI:
		{
			SetSystemsFormat(SYSTEMSFORMAT_AVI);
			SetAudioFormat(AUDIOFORMAT_AAC);
			SetVideoFormat(VIDEOFORMAT_MPEG4);
			SetFramerate(0);
			SetWidth(0);
			SetHeight(0);
			SetProfileName(L"MPEG4 in AVI container");
			m_pMuxProfile->SetMultiplexFormat(SYSTEMSFORMAT_AVI);
			SetAudioChannels(2);
			SetAudioBitrate(64 * 1000);
			SetVideoBitrate(350 * 1000);
			SetVideoBitrateMin(0);
			SetVideoBitrateMax(750 * 1000);
			SetAudioSampleRate(32000);
			SetVideoVBRMode(BITRATEMODE_MVBR);
		}
		break;
	case SYSTEMSFORMAT_MPEG1:
		SetSystemsFormat(SYSTEMSFORMAT_MPEG1);
		SetAudioFormat(AUDIOFORMAT_MP2);
		SetVideoFormat(VIDEOFORMAT_MPEG1);
		SetVideoVBRMode(BITRATEMODE_MVBR);
		SetAspectRatio(ASPECTRATIO_4TO3);
		m_pMuxProfile->SetMultiplexFormat(SYSTEMSFORMAT_MPEG1);
		SetAudioChannels(2);
		SetAudioBitrate(128 * 1000);
		SetFramerate(0);
		SetWidth(320);
		SetHeight(240);
		SetVideoBitrate(1140 * 1000);
		SetVideoBitrateMin(0);
		SetVideoBitrateMax(1150 * 1000);
		SetProfileName(L"Standard MPEG1");
		SetAudioSampleRate(32000);
		break;
	case SYSTEMSFORMAT_VCD_STILL:
		{
			SetVideoFormat(VIDEOFORMAT_MPEG1);
			SetAudioFormat(AUDIOFORMAT_NONE);
			SetSystemsFormat(SYSTEMSFORMAT_VCD_STILL);
			m_pMuxProfile->SetMultiplexFormat(SYSTEMSFORMAT_VCD);
			SetVideoVBRMode(BITRATEMODE_CBR);
			SetAspectRatio(ASPECTRATIO_4TO3);
			SetVideoVBVBufferSize(40*1024*8);
			SetWidth(352);
			SetVideoBitrate(62 * 1000);
			SetVideoBitrateMin(62 * 1000);
			SetVideoBitrateMax(62 * 1000);

			switch (constraint)
			{
				case CONSTRAINT_PAL:
					SetHeight(288);
					SetFramerate(25);
					SetGOPSize(15);
					SetConstraint(CONSTRAINT_PAL);
					SetProfileName(L"VCD Still (PAL)");
					break;
				case CONSTRAINT_NTSC:
					SetHeight(240);
					SetFramerate(29.97);
					SetGOPSize(18);
					SetConstraint(CONSTRAINT_NTSC);
					SetProfileName(L"VCD Still (NTSC)");
					break;
			}
		}
		break;
	case SYSTEMSFORMAT_VCD:
		SetVideoFormat(VIDEOFORMAT_MPEG1);
		SetAudioFormat(AUDIOFORMAT_MP2);
		SetSystemsFormat(SYSTEMSFORMAT_VCD);
		m_pMuxProfile->SetMultiplexFormat(SYSTEMSFORMAT_VCD);
		SetVideoVBRMode(BITRATEMODE_CBR);
		SetAspectRatio(ASPECTRATIO_4TO3);
		SetVideoVBVBufferSize(40*1024*8);
		SetAudioBitrate(224 * 1000);
		SetWidth(352);
		SetAudioChannels(2);
		SetVideoBitrate(1150 * 1000);
		SetVideoBitrateMin(1150 * 1000);
		SetVideoBitrateMax(1150 * 1000);
		SetAudioSampleRate(32000);

		switch (constraint)
		{
			case CONSTRAINT_PAL:
				SetHeight(288);
				SetFramerate(25);
				SetGOPSize(15);
				SetConstraint(CONSTRAINT_PAL);
				SetProfileName(L"MPEG1 with VCD Extensions (PAL)");
				break;
			case CONSTRAINT_NTSC:
				SetHeight(240);
				SetFramerate(29.97);
				SetGOPSize(18);
				SetConstraint(CONSTRAINT_NTSC);
				SetProfileName(L"MPEG1 with VCD Extensions (NTSC)");
				break;
		}
		break;
	case SYSTEMSFORMAT_RM:
		{
			SetSystemsFormat(SYSTEMSFORMAT_RM);
			SetAudioFormat(AUDIOFORMAT_AAC);
			SetVideoFormat(VIDEOFORMAT_MPEG4);
			SetFramerate(0);
			SetWidth(0);
			SetHeight(0);
			SetProfileName(L"Real Media");
			m_pMuxProfile->SetMultiplexFormat(SYSTEMSFORMAT_RM);
			SetAudioChannels(2);
			SetAudioBitrate(64 * 1000);
			SetVideoBitrate(350 * 1000);
			SetVideoBitrateMin(0);
			SetVideoBitrateMax(750 * 1000);
			SetAudioSampleRate(32000);
			SetVideoVBRMode(BITRATEMODE_MVBR);
		}
		break;
	case SYSTEMSFORMAT_MPEG2:
	case SYSTEMSFORMAT_DVB:
		SetVideoFormat(VIDEOFORMAT_MPEG2);
		SetAudioFormat(AUDIOFORMAT_MP2);
		SetSystemsFormat(systemsFormat);
		SetVideoVBRMode(BITRATEMODE_MVBR);
		SetAspectRatio(ASPECTRATIO_4TO3);
		m_pMuxProfile->SetMultiplexFormat(systemsFormat);
		SetAudioBitrate(192 * 1000);
		SetFramerate(0);
		SetWidth(0);
		SetAudioChannels(2);
		SetHeight(0);
		SetVideoBitrate(6000 * 1000);
		SetVideoBitrateMin(0);
		SetVideoBitrateMax(9000 * 1000);
		SetProfileName(L"Standard MPEG-2");
		SetAudioSampleRate(32000);
		
		if (systemsFormat == SYSTEMSFORMAT_DVB)
			SetProfileName(L"MPEG-2 Transport Stream (DVB)");

		if (constraint == CONSTRAINT_HD)
		{
			SetConstraint(CONSTRAINT_HD);
			SetProfileName(L"Standard MPEG-2 HD");
			SetWidth(960);
			SetHeight(576);
			SetVideoBitrate(20000 * 1000);
			SetVideoBitrateMin(0);
			SetVideoBitrateMax(20000 * 1000);
			m_EncodeParameters.nProfile = 1;
			m_EncodeParameters.nLevel = 4;
		}

#if defined(SPECIAL_BUILD_SMARTCAST)
		SetProfileName(L"Standard MPEG-2 SmartCast");
		SetVideoVBRMode(BITRATEMODE_CBR);
		SetVideoBitrate(6000 * 1000);
		SetVideoBitrateMin(6000 * 1000);
		SetVideoBitrateMax(6000 * 1000);
		SetWidth(720);
		SetHeight(576);
		SetAudioFormat(AUDIOFORMAT_MP2);
		SetAudioSampleRate(48000);
		SetAudioBitrate(224 * 1000);
#endif


		break;
	case SYSTEMSFORMAT_SVCD_STILL:
		SetVideoFormat(VIDEOFORMAT_MPEG2);
		SetAudioFormat(AUDIOFORMAT_NONE);
		SetSystemsFormat(SYSTEMSFORMAT_SVCD_STILL);
		SetVideoVBRMode(BITRATEMODE_MVBR);
		SetAspectRatio(ASPECTRATIO_4TO3);
		m_pMuxProfile->SetMultiplexFormat(SYSTEMSFORMAT_SVCD_STILL);
		SetWidth(480);
		SetVideoBitrate(6200);
		SetVideoBitrateMin(6200);
		SetVideoBitrateMax(6200);

		switch (constraint)
		{
			case CONSTRAINT_PAL:
				SetHeight(576);
				SetFramerate(25);
				SetGOPSize(15);
				SetConstraint(CONSTRAINT_PAL);
				SetProfileName(L"SVCD Still (PAL)");
				break;
			case CONSTRAINT_NTSC:
				SetHeight(480);
				SetFramerate(29.97);
				SetGOPSize(18);
				SetConstraint(CONSTRAINT_NTSC);
				SetProfileName(L"SVCD Still (NTSC)");
				break;
		}
		break;
	case SYSTEMSFORMAT_SVCD:
		SetVideoFormat(VIDEOFORMAT_MPEG2);
		SetAudioFormat(AUDIOFORMAT_MP2);
		SetSystemsFormat(SYSTEMSFORMAT_SVCD);
		SetVideoVBRMode(BITRATEMODE_MVBR);
		SetAspectRatio(ASPECTRATIO_4TO3);
		m_pMuxProfile->SetMultiplexFormat(SYSTEMSFORMAT_SVCD);
		SetAudioBitrate(224 * 1000);
		SetWidth(480);
		SetVideoBitrate(2040000);
		SetVideoBitrateMin(0);
		SetVideoBitrateMax(2516000);
		SetAudioSampleRate(32000);
		SetAudioChannels(2);

		switch (constraint)
		{
			case CONSTRAINT_PAL:
				SetHeight(576);
				SetFramerate(25);
				SetGOPSize(15);
				SetConstraint(CONSTRAINT_PAL);
				SetProfileName(L"MPEG2 with SVCD Extensions (PAL)");
				break;
			case CONSTRAINT_NTSC:
				SetHeight(480);
				SetFramerate(29.97);
				SetGOPSize(18);
				SetConstraint(CONSTRAINT_NTSC);
				SetProfileName(L"MPEG2 with SVCD Extensions (NTSC)");
				break;
		}
		break;
	case SYSTEMSFORMAT_DVD:
		SetVideoFormat(VIDEOFORMAT_MPEG2);
		SetAudioFormat(AUDIOFORMAT_AC3);
		SetSystemsFormat(SYSTEMSFORMAT_DVD);
		SetVideoVBRMode(BITRATEMODE_MVBR);
		SetAspectRatio(ASPECTRATIO_4TO3);
		m_pMuxProfile->SetMultiplexFormat(SYSTEMSFORMAT_DVD);
		SetAudioBitrate(448 * 1000);
		SetWidth(720);
		SetVideoBitrate(6000000);
		SetVideoBitrateMin(0);
		SetAudioChannels(2);
		SetVideoBitrateMax(9000000);
		SetAudioSampleRate(48000);
		
		m_EncodeParameters.nProfile = 4; // 4 = main
		m_EncodeParameters.nLevel = 8; // 6 = High-1440, 8 = main

		switch (constraint)
		{
			case CONSTRAINT_PAL:
				SetHeight(576);
				SetFramerate(25);
				SetGOPSize(15);
				SetConstraint(CONSTRAINT_PAL);
				SetProfileName(L"MPEG2 with DVD Extensions (PAL)");
				break;
			case CONSTRAINT_NTSC:
				SetHeight(480);
				SetFramerate(29.97);
				SetGOPSize(18);
				SetConstraint(CONSTRAINT_NTSC);
				SetProfileName(L"MPEG2 with DVD Extensions (NTSC)");
				break;
		}
		break;
	};

	SetVideoQuality(50);

	return S_OK;
}

BOOL CMPEGProfile::IsFrameRateSupported(double dFPS)
{
	if (FLOAT_EQ(dFPS, 23.97) ||
		FLOAT_EQ(dFPS, 24) || FLOAT_EQ(dFPS, 25) || 
		FLOAT_EQ(dFPS, 30) || FLOAT_EQ(dFPS, 50) || 
		FLOAT_EQ(dFPS, 60) || FLOAT_EQ(dFPS, 23.976) ||
		FLOAT_EQ(dFPS, 29.97) || FLOAT_EQ(dFPS, 59.94))
	{
		return true;
	}

	return false;
}

void CMPEGProfile::SetFixed(BOOL bFixed)
{
	m_bFixed = bFixed;
}

STDMETHODIMP CMPEGProfile::SaveProfile(BSTR strKey)
{
	/*
	CRegKey regKey;
	regKey.Create(HKEY_CURRENT_USER, strKey);
	regKey.SetDWORDValue("Width", (DWORD)m_nOutputWidth);
	regKey.SetDWORDValue("Height", (DWORD)m_nOutputHeight);
//	regKey.SetDWORDValue("VBR", (DWORD)m_bVBR);
//	regKey.SetDWORDValue("IFrames", (DWORD)m_bEncodeOnlyIFrames);
	regKey.SetDWORDValue("AudioBitrate", (DWORD)m_nAudioBitrate);
	regKey.SetDWORDValue("Quality", (DWORD)m_nQuality);
	regKey.SetDWORDValue("VideoBitrate", (DWORD)m_nVideoBitrate);
	regKey.SetDWORDValue("AudioSampleRate", (DWORD)m_nAudioSampleRate);
	regKey.Close();
*/
	return S_OK;
}

STDMETHODIMP CMPEGProfile::LoadProfile(BSTR strKey)
{
	/*
	CRegKey regKey;
	regKey.Open(HKEY_CURRENT_USER, pstrKey);
	regKey.QueryDWORDValue("Width", (DWORD&)m_nOutputWidth);
	regKey.QueryDWORDValue("Height", (DWORD&)m_nOutputHeight);
	regKey.QueryDWORDValue("AudioBitrate", (DWORD&)m_nAudioBitrate);
	regKey.QueryDWORDValue("Quality", (DWORD&)m_nQuality);
	regKey.QueryDWORDValue("VideoBitrate", (DWORD&)m_nVideoBitrate);
	regKey.QueryDWORDValue("AudioSampleRate", (DWORD&)m_nAudioSampleRate);

	DWORD dwVal = FALSE;
//	if (regKey.QueryDWORDValue("VBR", dwVal) == ERROR_SUCCESS)
//		m_bVBR = dwVal == TRUE;

//	if (regKey.QueryDWORDValue("IFrames", dwVal) == ERROR_SUCCESS)
//		m_bEncodeOnlyIFrames = dwVal == TRUE;

	regKey.Close();
*/
	return S_OK;
}

STDMETHODIMP CMPEGProfile::SetProfileName(BSTR strName)
{
	m_strProfileName = strName;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::GetProfileName(BSTR* strName)
{
	m_strProfileName.CopyTo(strName);
	return S_OK;
}

STDMETHODIMP CMPEGProfile::GetHeight(long * pnHeight)
{	
	if (pnHeight)
		*pnHeight = m_EncodeParameters.nOutputY;

	return S_OK;
}

STDMETHODIMP CMPEGProfile::SetHeight(long nHeight)
{
	if (m_bFixed == false)
		m_EncodeParameters.nOutputY = nHeight;

	return S_OK;
}

STDMETHODIMP CMPEGProfile::SetFramerate(double fps)
{
	if (m_bFixed == false)
	{
		VideoOutputFormat vFormat;
		AudioOutputFormat aFormat;
		SystemsOutputFormat sFormat;
		
		GetVideoFormat(&vFormat);
		GetAudioFormat(&aFormat);
		GetSystemsFormat(&sFormat);

		if (vFormat == 	VIDEOFORMAT_MPEG4 ||
			vFormat == 	VIDEOFORMAT_H263 ||
			vFormat == VIDEOFORMAT_H264 ||
			aFormat == AUDIOFORMAT_AAC ||
			sFormat == SYSTEMSFORMAT_MP4 ||
			sFormat == SYSTEMSFORMAT_3GP ||
			sFormat == SYSTEMSFORMAT_MOV ||
			sFormat == SYSTEMSFORMAT_3G2 ||
			sFormat == SYSTEMSFORMAT_PSP ||
			sFormat == SYSTEMSFORMAT_AVI ||
			sFormat == SYSTEMSFORMAT_RM )
		{
			m_EncodeParameters.dOutputFPS = fps;
		}
		else
		{
			if (IsFrameRateSupported(fps) || fps == 0.0f)
				m_EncodeParameters.dOutputFPS = fps;
			else
				m_EncodeParameters.dOutputFPS = 25;
		}
	}
	return S_OK;
}

STDMETHODIMP CMPEGProfile::GetFramerate(double* fps)
{		
	if (fps)
		*fps = m_EncodeParameters.dOutputFPS;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::SetVideoBitrateMin(long nBitrate)
{
	m_EncodeParameters.nOutputVideoBitrateMin = nBitrate;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::GetVideoBitrateMin(long * nBitrate)
{
	*nBitrate = m_EncodeParameters.nOutputVideoBitrateMin;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::SetVideoBitrateMax(long nBitrate)
{
	m_EncodeParameters.nOutputVideoBitrateMax = nBitrate;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::GetVideoBitrateMax(long * nBitrate)
{
	*nBitrate = m_EncodeParameters.nOutputVideoBitrateMax;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::SetWidth(long nWidth)
{
	if (m_bFixed == false)
		m_EncodeParameters.nOutputX = nWidth;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::GetWidth(long* nWidth)
{
	if (nWidth)
		*nWidth = m_EncodeParameters.nOutputX;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::SetVideoBitrate(long nBitrate)
{
	m_EncodeParameters.nOutputVideoBitrate = nBitrate;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::GetVideoBitrate(long * nBitrate)
{
	if (nBitrate)
		*nBitrate = m_EncodeParameters.nOutputVideoBitrate;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::SetAudioBitrate(long nBitrate)
{
	m_EncodeParameters.nOutputAudioBitrate = nBitrate;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::GetAudioBitrate(long * nBitrate)
{
	if (nBitrate)
		*nBitrate = m_EncodeParameters.nOutputAudioBitrate;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::SetVideoQuality(long nQuality)
{
	m_EncodeParameters.nOutputVideoQuality = nQuality;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::GetVideoQuality(long * nQuality)
{
	if (nQuality)
		*nQuality = m_EncodeParameters.nOutputVideoQuality;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::SetVideoVBRMode(BitrateMode vbrMode)
{
	m_EncodeParameters.vbrVideo = vbrMode;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::GetVideoVBRMode(BitrateMode * pvbrMode)
{
	if (pvbrMode)
		*pvbrMode = m_EncodeParameters.vbrVideo;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::SetVideoVBVBufferSize(long vbvlen)
{
	m_EncodeParameters.nOutputVideoBufferSize = vbvlen;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::GetVideoVBVBufferSize(long * vbvlen)
{
	*vbvlen = m_EncodeParameters.nOutputVideoBufferSize;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::SetAudioVBRMode(BitrateMode vbrMode)
{
	m_EncodeParameters.vbrAudio = vbrMode;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::GetAudioVBRMode(BitrateMode * pvbrMode)
{
	if (pvbrMode)
		*pvbrMode = m_EncodeParameters.vbrAudio;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::SetAudioBitrateMin(long nBitrate)
{
	m_EncodeParameters.nOutputAudioBitrateMin = nBitrate;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::GetAudioBitrateMin(long * nBitrate)
{
	*nBitrate = m_EncodeParameters.nOutputAudioBitrateMin;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::SetAudioBitrateMax(long nBitrate)
{
	m_EncodeParameters.nOutputAudioBitrateMax = nBitrate;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::GetAudioBitrateMax(long * nBitrate)
{
	*nBitrate = m_EncodeParameters.nOutputAudioBitrateMax;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::SetGOPStructure(BSTR strStructure)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGProfile::GetGOPStructure(BSTR* pstrStructure)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGProfile::SetAudioSampleRate(long nSampleRate) // Valid values are 32000, 48000, btnOptions ONLY!
{
	m_EncodeParameters.nOutputAudioSampleRate = nSampleRate;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::GetAudioSampleRate(long * pnSampleRate)
{
	if (pnSampleRate)
		*pnSampleRate = m_EncodeParameters.nOutputAudioSampleRate;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::SetAudioChannels(long nChannelCount) // Valid values are 32000, 48000, btnOptions ONLY!
{
	m_EncodeParameters.nOutputAudioChannels = nChannelCount;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::GetAudioChannels(long * pnChannelCount)
{
	if (pnChannelCount)
	{
		*pnChannelCount = m_EncodeParameters.nOutputAudioChannels;
	}
	return S_OK;
}

STDMETHODIMP CMPEGProfile::SetAudioFlags(BOOL bErrorProtection, BOOL bOriginal, BOOL bCopyright, BOOL bPrivate)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGProfile::SetEncodeMode(EncodeMode nValue)
{
	HRESULT hr = E_NOTIMPL;
	if (nValue == ENCODEMODE_INTERLACE)
	{
		if (m_EncodeParameters.bForceInterlaceME == TRUE)
			SetInterlaceMode(FALSE, FALSE, TRUE);
		else
			SetInterlaceMode(FALSE, TRUE, FALSE);

		hr = S_OK;
	}
	else if (nValue == ENCODEMODE_INTERLACE)
	{
		SetInterlaceMode(m_EncodeParameters.bDeInterlace, FALSE, FALSE);
		hr = S_OK;
	}

	return hr;
}

STDMETHODIMP CMPEGProfile::GetEncodeMode(EncodeMode * pnValue)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGProfile::SetAudioFormat(AudioOutputFormat audioFormat)
{
	m_EncodeParameters.audioOutputFormat = audioFormat;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::GetAudioFormat(AudioOutputFormat * audioFormat)
{
	if (audioFormat)
	{
		*audioFormat = m_EncodeParameters.audioOutputFormat;
	}
	return S_OK;
}

STDMETHODIMP CMPEGProfile::SetVideoFormat(VideoOutputFormat videoFormat)
{
	m_EncodeParameters.videoOutputFormat = videoFormat;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::GetVideoFormat(VideoOutputFormat * videoFormat)
{
	if (videoFormat)
	{
		*videoFormat = m_EncodeParameters.videoOutputFormat;
	}
	return S_OK;
}

STDMETHODIMP CMPEGProfile::SetSystemsFormat(SystemsOutputFormat systemsFormat)
{
	m_EncodeParameters.systemsOutputFormat = systemsFormat;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::GetSystemsFormat(SystemsOutputFormat * systemsFormat)
{
	if (systemsFormat)
	{
		*systemsFormat = m_EncodeParameters.systemsOutputFormat;
	}
	return S_OK;
}

STDMETHODIMP CMPEGProfile::SetAspectRatio(AspectRatio mode)
{
	m_EncodeParameters.aspectRatio = mode;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::GetAspectRatio(AspectRatio * pmode)
{
	*pmode = m_EncodeParameters.aspectRatio;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::NonDelegatingQueryInterface(REFIID riid, void ** ppv)
{
    CheckPointer(ppv, E_POINTER);

	if (riid == IID_IStandardMpegMultiplexerProfile) {
		return GetInterface((IStandardMpegMultiplexerProfile*) m_pMuxProfile, ppv);
	}
	else if (riid == IID_IStandardMpegEncoderProfile) {
		return GetInterface((IStandardMpegEncoderProfile *) this, ppv);
	}

    return CUnknown::NonDelegatingQueryInterface(riid, ppv);

} // NonDelegatingQueryInterface

STDMETHODIMP CMPEGProfile::SetProfileAndLevel(BSTR strProfileAndLevel)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGProfile::GetProfileAndLevel(BSTR * pstrProfileAndLevel)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGProfile::SetMotionSearchPrecision(long nVal)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGProfile::GetMotionSearchPrecision(long * nVal)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGProfile::SetDetectSceneChange(BOOL bVal)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGProfile::SetAutoSelectDimensions(BOOL bVal)
{
	m_EncodeParameters.bAutoSelectDimensions = bVal == TRUE;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::GetAutoSelectDimensions(BOOL * pbVal)
{
	*pbVal = m_EncodeParameters.bAutoSelectDimensions;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::SetAutoSelectBitrate(BOOL bVal)
{
	m_EncodeParameters.bAutoSelectBitrate = bVal == TRUE;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::GetAutoSelectBitrate(BOOL * pbVal)
{
	*pbVal = m_EncodeParameters.bAutoSelectBitrate;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::GetDetectSceneChange(BOOL * nVal)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGProfile::SetSceneChangeThreshold(float f)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGProfile::SetClosedGOP(BOOL bVal)
{
	m_EncodeParameters.bClosedGOP = bVal == TRUE;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::GetClosedGOP(BOOL * pVal)
{
	*pVal = m_EncodeParameters.bClosedGOP;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::SetInterlaceMode(BOOL bPreProcessDeinterlace, BOOL bInterlacedOutputDCT, BOOL bInterlacedOutputME)
{
	m_EncodeParameters.bDeInterlace = bPreProcessDeinterlace == TRUE;
	m_EncodeParameters.bForceInterlaceDCT = bInterlacedOutputDCT == TRUE;
	m_EncodeParameters.bForceInterlaceME = bInterlacedOutputME == TRUE;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::GetInterlaceMode(BOOL * bPreProcessDeinterlace, BOOL * bInterlacedOutputDCT, BOOL * bInterlacedOutputME)
{
	* bPreProcessDeinterlace = m_EncodeParameters.bDeInterlace;
	* bInterlacedOutputDCT = m_EncodeParameters.bForceInterlaceDCT;
	* bInterlacedOutputME = m_EncodeParameters.bForceInterlaceME; 
	return S_OK;
}

STDMETHODIMP CMPEGProfile::SetOutputIntervalOfSequenceHeader(long nVal)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGProfile::GetOutputIntervalOfSequenceHeader(long * nVal)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGProfile::SetComments(BSTR strVal)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGProfile::SetInformation(BSTR strTitle, BSTR strAuthor, BSTR strCopyright)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGProfile::SetVideoQualityRange(long nMin, long nMax)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGProfile::SetQuantBias(long nIntra, long nInter)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGProfile::SetConstraint(Constraint systemsConstraint)
{
	m_EncodeParameters.systemsConstraint = systemsConstraint;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::GetConstraint(Constraint * systemsConstraint)
{
	*systemsConstraint = m_EncodeParameters.systemsConstraint;
	return S_OK;
}

STDMETHODIMP CMPEGProfile::SetIDCT(long n)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGProfile::SetStrictGOP(BOOL bVal)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGProfile::SetGOPSize(long nGOPSize)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGProfile::GetGOPSize(long * nGOPSize)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGProfile::Set2PassLogFile(BSTR Path)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGProfile::SetBWVideo(BOOL bVal)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGProfile::SetQuantFactor(float fQuantFactor)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGProfile::GetQuantFactor(float * pfQuantFactor)
{
	return E_NOTIMPL;
}

CMPEGMultiplexProfile::CMPEGMultiplexProfile() : CUnknown(NAME("CMPEGMultiplexProfile"), NULL)
{
}

CMPEGMultiplexProfile::~CMPEGMultiplexProfile()
{

}

STDMETHODIMP CMPEGMultiplexProfile::SetDeleteElementaryStreams(BOOL bDelete)
{
	m_pEncodeParameters->bDeleteTmpAfterMultiplex = bDelete == TRUE;
	return S_OK;
}

STDMETHODIMP CMPEGMultiplexProfile::GetDeleteElementaryStreams(BOOL * bDelete)
{
	if (bDelete)
		*bDelete = m_pEncodeParameters->bDeleteTmpAfterMultiplex;
	return S_OK;
}

STDMETHODIMP CMPEGMultiplexProfile::SetMultiplexRate(long nRate)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGMultiplexProfile::GetMultiplexRate(long * pnMux)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGMultiplexProfile::SetMultiplexPacketSize(long nSize)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGMultiplexProfile::GetMultiplexPacketSize(long * pnSize)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGMultiplexProfile::SetMultiplexPreload(float fPreload)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGMultiplexProfile::GetMultiplexPreload(float * pfPreload)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGMultiplexProfile::SetMultiplexMaxDelay(float fMaxDelay)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGMultiplexProfile::SetMultiplexStreams(BOOL bMux)
{
	m_pEncodeParameters->bMultiplex = bMux == TRUE;
	return S_OK;
}

STDMETHODIMP CMPEGMultiplexProfile::GetMultiplexStreams(BOOL * bMux)
{
	if (bMux)
		*bMux = m_pEncodeParameters->bMultiplex;
	return S_OK;
}

STDMETHODIMP CMPEGMultiplexProfile::SetMultiplexFormat(SystemsOutputFormat format)
{
	m_pEncodeParameters->multiplexFormat = format;
	return S_OK;
}

STDMETHODIMP CMPEGMultiplexProfile::GetMultiplexFormat(SystemsOutputFormat* format)
{
	*format = m_pEncodeParameters->multiplexFormat;
	return S_OK;
}

STDMETHODIMP CMPEGMultiplexProfile::AddMultiplexFile(BSTR strPath)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGMultiplexProfile::SetOnFlyMultiplex(BOOL bOnFlyMultiplex)
{
	m_pEncodeParameters->bDirectMultiplexing = bOnFlyMultiplex == TRUE;
	return S_OK;
}

STDMETHODIMP CMPEGMultiplexProfile::GetOnFlyMultiplex(BOOL * pbOnFlyMultiplex)
{
	*pbOnFlyMultiplex = m_pEncodeParameters->bDirectMultiplexing;
	return S_OK;
}

STDMETHODIMP CMPEGMultiplexProfile::SetMultiplexFrameBalance(BOOL bVal)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGMultiplexProfile::SetMultiplexOnStop(BOOL bVal)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGMultiplexProfile::GetMultiplexProgress(double* dProgress)
{
	return E_NOTIMPL;
}


